
#include "HotelManager.h"
#include "Utils.h"

#include "Sql.h"


void HotelManager::checkUserBookings() const
{
    const int bookingNumber = GetUserNumberInput("Mikä on varausnumerosi?");
    std::optional<QueryResult> result = sql_manager_.queryBooking(QUERY_BOOKING, bookingNumber);
    if (result.has_value())
    {
        printf("Nimesi on %s, olet varannut huoneen %i sängyllä %i päiväksi. \n", result.value().name.c_str(), result.value().dayCount, result.value().bedAmount);
    } else
    {
        printf("Antamillasi tiedoilla ei löytynyt huonetta. \n\n\n");

    }
}

State HotelManager::askWhatUserWantsToDo()
{
    const int result = GetUserInputInRange(1, 3, "Haluatko katsoa varauksiasi [1], tehdä uusia varauksia [2], sulje ohjelma [3]");
    if (result == 1)
    {
        state = State::VIEW;
    } else if (result == 2)
    {
        state = State::USER;
    } else
    {
        state = State::CLOSE;
    }
    return state;
}

BookingResult HotelManager::bookRoomsForCustomer(const Customer& customer) const
{

    int requestRoomBedAmount, dayCount;

    requestRoomBedAmount = GetUserInputInRange(1, 2, "Haluatko yksi vai kaksi huonetta (Paina 1 tai 2)");
    const bool isAvailable =  sql_manager_.checkFreeRoomsByBedCount(QUERY_ROOM_AMOUNT, requestRoomBedAmount);
    if (!isAvailable)
    {
        std::printf("Huoneita ei ole vapaana!\n");
    }
    dayCount = GetUserInputInRange(1, INT_MAX, "Montako yötä yövyt?");
    const int bookingNumber = createUniqueBookingNumber();
    sql_manager_.saveBooking(SAVE_BOOKING, dayCount, bookingNumber, customer.id);
    sql_manager_.saveRoom(SAVE_ROOM, requestRoomBedAmount, bookingNumber);
    BookingResult result = { bookingNumber, customer.name, dayCount, requestRoomBedAmount};
    return result;
}

//Return customer id
Customer HotelManager::registerNewCustomer() const
{
    std::string name;
    std::cout << "Mikä on nimesi" << std::endl;
    std::getline(std::cin, name);
    std::cout << "Tervetuloa " << name << std::endl;
    const int customerId = sql_manager_.saveUser(SAVE_USER, name);
    return {name, customerId};
}


void HotelManager::tellCustomerResult(const BookingResult& booking_result)
{

    const double discount = GetRandomDiscount();
    const double readableDiscount = (1.0-discount) * 100;

    printf("Varasit huoneen %i sängyllä %i päiväksi.\n", booking_result.bedAmount, booking_result.dayAmount);
    if (discount < 1.0)
    {
        printf("Onnittelut sait %2.f%% alennusta!\n", readableDiscount);
    }
    int price = booking_result.bedAmount == 1 ? 100 : 150;
    printf("Varaus maksaa yhteensä %2.f\n", (price * booking_result.dayAmount) * discount);
    std::cout << "varasnumerosi on " << booking_result.bookingID << std::endl;

}

HotelManager::HotelManager(const SqlManager& sql_manager)
{
    sql_manager_ = sql_manager;
}
