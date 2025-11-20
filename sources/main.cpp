#include <iostream>
#include "Hotel.h"
#include "Utils.h"



void generateHotel(Hotel &hotel) {
    for (int i = 1; i <= TOTAL_ROOM_AMOUNT; i++) {
        hotel.GenerateHotelRoom();
    }
}



int main() {
    Hotel hotel = {};
    std::string name;
    int requestRoomNumber, requestRoomBedAmount, dayCount;
    generateHotel(hotel);
    while (true) {
        std::cout << "Tervetuloa hotelliin!" << std::endl;
        std::cout << "Mikä on nimesi" << std::endl;
        std::getline(std::cin, name);
        auto person = hotel.GeneratePerson(name);
        std::cout << "Tervetuloa " << person.name << std::endl;
        requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko varata huoneen vai noutaa varaamasi huoneen (Paina 1 tai 2)");



        requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko yksi vai kaksi huonetta (Paina 1 tai 2)");
        requestRoomNumber = GetFreeHotelRoom(1, 400, "Mihinkä huoneeseen haluat? (Paina 1 tai 400)", hotel);
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
    return 0;
}