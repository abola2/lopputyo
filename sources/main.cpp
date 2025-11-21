#include <format>
#include <iostream>
#include "Hotel.h"
#include "Utils.h"
#include <sqlite3.h>
#include "Sql.h"


void executeSql(sqlite3* DB, const std::string& sql)
{
    char* messaggeError = nullptr;

    int exit = sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &messaggeError);

    if (exit != SQLITE_OK) {
        std::cerr << "SQL error: " << messaggeError << std::endl;
        sqlite3_free(messaggeError);
    }
}

int queryTotalHotelRooms(sqlite3* db)
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

void generateHotel(Hotel &hotel, sqlite3* db) {
    int rooms = queryTotalHotelRooms(db);
    if (rooms == 0)
    {
        rooms = numberBetween(20,150);
        const std::string sql2 = std::format("insert into Settings (ROOM_AMOUNT) values ({});", rooms * 2);
        executeSql(db, sql2);
    }

    const std::string sql1 = std::format("select ROOM_AMOUNT from Settings;");
        executeSql(db, sql1);


    for (int i = 1; i <= rooms; i++) {
        hotel.GenerateHotelRoom(1);

        hotel.GenerateHotelRoom(2);
    }
}


void createDatabase(sqlite3* db) {
    executeSql(db, CREATE_BOOKINGS);
    executeSql(db, CREATE_CUSTOMER);
    executeSql(db, CREATE_ROOMS);
    executeSql(db, CREATE_SETTINGS);
    //There is only one connection so its recommend keep the connection open while the program runs

}



int main() {
    Hotel hotel = {};

    sqlite3* DB;

    int exit = 0;
    exit = sqlite3_open("hotel.db", &DB);

    createDatabase(DB);
    std::string name;
    int requestRoomNumber, requestRoomBedAmount, dayCount;
    generateHotel(hotel, DB);
    while (true) {
        std::cout << "Tervetuloa hotelliin!" << std::endl;
        std::cout << "Mikä on nimesi" << std::endl;
        std::getline(std::cin, name);
        auto person = hotel.GeneratePerson(name);
        std::cout << "Tervetuloa " << person.name << std::endl;
        requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko varata huoneen vai noutaa varaamasi huoneen (Paina 1 tai 2)");



        requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko yksi vai kaksi huonetta (Paina 1 tai 2)");
        dayCount = GetUserNumberInput("Montako yötä yövyt?");
        hotel.rentRoom(requestRoomNumber, dayCount, person.id);
        auto room = hotel.GetPersonRoom(person);
        //Clear cin buffer
        std::cin.clear();
        std::cin.ignore();
        if (!room) {
            std::cout << "Jokin meni pieleen!"  << std::endl;
            continue;
        }
        const double discount = GetRandomDiscount();
        const double readableDiscount = (1.0-discount) * 100;
        std::printf("Sait %.0f alennusta \n", readableDiscount);
        std::printf("%i yötä %i euron huoneessa maksaa yhteensä %.2f\n", room->second, room->first.price, (room->second * room->first.price) * discount);
        std::cout << "Huoneesi " << room.value().first.roomId << " sänkyjä " << room.value().first.roomAmount << std::endl;
    }
    sqlite3_close(DB);
    return 0;
}
