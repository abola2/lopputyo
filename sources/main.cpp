#include <format>
#include <iostream>
#include "HotelManager.h"
#include "Utils.h"
#include <sqlite3.h>
#include "SqlManager.h"


int main() {

    //Open connection to db
    const auto sql_manager = SqlManager();
    auto hotel = HotelManager(sql_manager);

    sql_manager.createDatabase();
    sql_manager.generateHotel();
    while (true) {

        const State state = hotel.askWhatUserWantsToDo();
        std::cin.clear();
        std::cin.ignore();
        switch (state)
        {
        case State::USER:
            {
                bool reverseMore = false;
                Customer customer = hotel.registerNewCustomer();
                do
                {
                    std::optional<BookingResult> booking_result = hotel.bookRoomsForCustomer(customer);
                    if (!booking_result.has_value())
                    {
                        continue;
                    }
                    HotelManager::tellCustomerResult(booking_result.value());
                    reverseMore = hotel.continueOrBack();
                }
                while (reverseMore);

                break;
            }
        case State::VIEW:
            {
                hotel.checkUserBookings();
                break;
            }
        case State::CLOSE:
            {
                printf("Ohjelma suljetaan...\n");
                sqlite3_close(sql_manager.database());
                return 0;
                break;
            }
        default:
            {
                sqlite3_close(sql_manager.database());
                return 0;
            }
        }

    }
}



