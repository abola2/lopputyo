#ifndef LOPPUTYO_HOTEL_H
#define LOPPUTYO_HOTEL_H
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "SqlManager.h"


constexpr int TOTAL_ROOM_AMOUNT = 400;

class HotelManager {

    struct Person {
        std::string name;
        int id;
    };

    struct HotelRoom {
        int price;
        int roomId;
        int roomAmount;
    };

public:
    void bookRoomsForCustomer(const int& customerId) const;
    int registerNewCustomer() const;
    static void tellCustomerResult(const int& bookingNumber);
    explicit HotelManager(const SqlManager& sql_manager);

private:
    SqlManager sql_manager_ = {};
    int personIdCounter = 0;
    int hotelIdCounter = 0;
    std::unordered_map<int, HotelRoom> hotelRooms;
    std::unordered_map<int, std::pair<HotelRoom, int>> assignedHotelRooms; //User id, (room. rented days)
    std::vector<Person> persons;
};


#endif //LOPPUTYO_HOTEL_H