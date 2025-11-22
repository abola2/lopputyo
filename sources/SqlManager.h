
#ifndef LOPPUTYO_SQLMANAGER_H
#define LOPPUTYO_SQLMANAGER_H
#include <string>
#include <sqlite3.h>
#include <optional>

struct QueryResult
{
    std::string name;
    int dayCount;
    int bedAmount;
};

class SqlManager
{

    sqlite3* db = nullptr;

public:

    SqlManager();
    void executeSql(const std::string& sql) const;
    int queryTotalHotelRooms() const;
    void generateHotel() const;
    std::optional<QueryResult> queryBooking(const std::string& sql, const int id) const;
    bool checkFreeRoomsByBedCount(const std::string& sql, const int& bedAmount) const;
    int saveUser(const std::string& sql, const std::string& name) const;
    void saveBooking(const std::string& sql, const int& dayCount, const int& bookingId, const int& customerId) const;
    void saveRoom(const std::string& sql, const int& bedCount, const int& id) const;
    void createDatabase() const;
    [[nodiscard]] sqlite3* database() const
    {
        return db;
    }


};


#endif //LOPPUTYO_SQLMANAGER_H