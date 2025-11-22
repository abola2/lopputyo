#include "SqlManager.h"

#include <format>
#include <iostream>
#include <sqlite3.h>
#include <string>

#include "Sql.h"
#include "Utils.h"


SqlManager::SqlManager()
{
    sqlite3_open("hotel.db", &db);
}

void SqlManager::executeSql(const std::string& sql) const
{
    char* messaggeError = nullptr;

    int exit = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    }
}

int SqlManager::queryTotalHotelRooms() const
{
    const auto sql = "select ROOM_AMOUNT from Settings;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return {};

    int roomCount = 0;
    int rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        return  sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return roomCount;
}

void SqlManager::generateHotel() const
{
    int rooms = queryTotalHotelRooms();
    if (rooms != 0)
    {
        return;
    }
    rooms = numberBetween(20,150);
    const std::string sql2 = std::format("insert into Settings (ROOM_AMOUNT) values ({});", rooms * 2);
    executeSql(sql2);
}

std::optional<QueryResult> SqlManager::queryBookingById(const std::string& sql, const int id) const
{
    sqlite3_stmt* stmt = nullptr;
    auto queryResult = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (queryResult != SQLITE_OK)
        return std::nullopt;

    sqlite3_bind_int(stmt, 1, id);
    std::string name;
    int dayCount = -1;
    int bedAmount = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        dayCount  = sqlite3_column_int(stmt, 1);
        bedAmount  = sqlite3_column_int(stmt, 2);
    } else
    {
        return std::nullopt;
    }
    sqlite3_finalize(stmt);
    return QueryResult(name, dayCount, bedAmount);
}

std::optional<QueryResult> SqlManager::queryBookingByName(const std::string& sql, const std::string& customerName) const
{
    sqlite3_stmt* stmt = nullptr;
    auto queryResult = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (queryResult != SQLITE_OK)
        return std::nullopt;

    sqlite3_bind_text(stmt, 1, customerName.c_str(), -1, SQLITE_STATIC);
    std::string name;
    int dayCount = -1;
    int bedAmount = -1;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        dayCount  = sqlite3_column_int(stmt, 1);
        bedAmount  = sqlite3_column_int(stmt, 2);
    } else
    {
        return std::nullopt;
    }
    sqlite3_finalize(stmt);
    return QueryResult(name, dayCount, bedAmount);
}

bool SqlManager::checkFreeRoomsByBedCount(const std::string& sql, const int& bedAmount) const
{
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, bedAmount);
    int totalRooms = 0, usedRoomsCount = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        usedRoomsCount  = sqlite3_column_int(stmt, 0);
        totalRooms  = sqlite3_column_int(stmt, 1);
    }
    sqlite3_finalize(stmt);
    return (totalRooms / 2) - usedRoomsCount >= 0;
}

int SqlManager::saveUser(const std::string& sql, const std::string& name) const
{
    int id = -1;
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return -1;

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        id = sqlite3_column_int(stmt, 0); //Customer id
    }
    sqlite3_finalize(stmt);
    return id;
}

void SqlManager::saveBooking(const std::string& sql, const int& dayCount, const int& bookingId, const int& customerId) const
{
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return;

    sqlite3_bind_int(stmt, 1, bookingId);
    sqlite3_bind_int(stmt, 2, dayCount);
    sqlite3_bind_int(stmt, 3, customerId);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SqlManager::saveRoom(const std::string& sql, const int& bedCount, const int& id) const
{
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return;

    sqlite3_bind_int(stmt, 1, bedCount);
    sqlite3_bind_int(stmt, 2, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SqlManager::createDatabase() const
{
    executeSql(CREATE_BOOKINGS);
    executeSql(CREATE_CUSTOMER);
    executeSql(CREATE_ROOMS);
    executeSql(CREATE_SETTINGS);
    //There is only one connection so its recommend keep the connection open while the program is running

}