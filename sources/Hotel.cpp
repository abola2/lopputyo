
#include "Hotel.h"
#include "Utils.h"


void Hotel::GenerateHotelRoom() {
    const int rooms = numberBetween(1,2);
    const int price = rooms == 1 ? 100 : 150;
    const auto room = HotelRoom(price, hotelIdCounter++,rooms);
    hotelRooms.insert_or_assign(room.roomId, room);
}

Hotel::Person Hotel::GeneratePerson(std::string name) {
    auto person = Person(name, personIdCounter++);
    persons.push_back({person});
    return person;
}

int Hotel::GetAvailableRoomsAmount() const {
    return hotelRooms.size() - assignedHotelRooms.size();
}

std::optional<std::pair<Hotel::HotelRoom, int>> Hotel::GetPersonRoom(const Person& p) {
    if (const auto result = assignedHotelRooms.find(p.id); result != assignedHotelRooms.end()) {
        return std::optional{result->second};
    }
    return std::nullopt;
}

std::vector<Hotel::Person> Hotel::GetPersons() {
    return persons;
}

bool Hotel::isRoomAvailable(const int roomId) const {
    if (!hotelRooms.contains(roomId)) {
        return false;
    }
    return !assignedHotelRooms.contains(roomId);
}

void Hotel::rentRoom(int roomId, int dayCount, int personId) {
    auto room = hotelRooms.at(roomId);
    std::pair rentedRoom = {room, dayCount};
    assignedHotelRooms.insert_or_assign(personId, rentedRoom);
}
