
#include "HotelManager.h"
#include "Utils.h"
#include <algorithm>

#include "Sql.h"


void HotelManager::bookRoomsForCustomer(const int& customerId) const
{

    int requestRoomBedAmount, dayCount;


    requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko varata huoneen vai noutaa varaamasi huoneen (Paina 1 tai 2)");


    requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko yksi vai kaksi huonetta (Paina 1 tai 2)");
    const bool isAvailable =  sql_manager_.checkFreeRoomsByBedCount(QUERY_ROOM_AMOUNT, requestRoomBedAmount);
    if (!isAvailable)
    {
        std::printf("Huoneita ei ole vapaana!\n");
    }
    dayCount = GetUserNumberInput("Montako yötä yövyt?");
    //Clear cin buffer
    std::cin.clear();
    std::cin.ignore();

    const int bookingNumber = createUniqueBookingNumber();
    sql_manager_.saveBooking(SAVE_BOOKING, dayCount, bookingNumber, customerId);
    sql_manager_.saveRoom(SAVE_ROOM, requestRoomBedAmount, bookingNumber);
}

//Return customer id
int HotelManager::registerNewCustomer() const
{
    std::string name;
    std::cout << "Mikä on nimesi" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Tervetuloa " << name << std::endl;
    const int customerId = sql_manager_.saveUser(SAVE_USER, name);
    return customerId;
}


void HotelManager::tellCustomerResult(const int& bookingNumber)
{

    const double discount = GetRandomDiscount();
    const double readableDiscount = (1.0-discount) * 100;


    std::cout << "varasnumerosi on " << bookingNumber << std::endl;

}



HotelManager::HotelManager(const SqlManager& sql_manager)
{
    sql_manager_ = sql_manager;
}
