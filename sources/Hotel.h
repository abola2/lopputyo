#ifndef LOPPUTYO_HOTEL_H
#define LOPPUTYO_HOTEL_H
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>


constexpr int TOTAL_ROOM_AMOUNT = 400;

class Hotel {

    struct Person {
        std::string name;
        int id;
        int bookingNumber;
    };

    struct HotelRoom {
        int price;
        int roomId;
        int roomAmount;
    };

public:
    void GenerateHotelRoom();
    Person GeneratePerson(std::string name);
    int GetAvailableRoomsAmount() const;
    std::optional<std::pair<Hotel::HotelRoom, int>> GetPersonRoom(const Person& p);
    std::vector<Person> GetPersons();
    bool isRoomAvailable(int roomId) const;
    void rentRoom(int roomId, int dayCount, int personId);



private:
    int personIdCounter = 0;
    int hotelIdCounter = 0;
    std::unordered_map<int, HotelRoom> hotelRooms;
    std::unordered_map<int, std::pair<HotelRoom, int>> assignedHotelRooms; //User id, (room. rented days)
    std::vector<Person> persons;
};


#endif //LOPPUTYO_HOTEL_H