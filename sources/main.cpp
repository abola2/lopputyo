#include <format>
#include <iostream>
#include "HotelManager.h"
#include "Utils.h"
#include <sqlite3.h>
#include "imgui.h"
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
                Customer customer = hotel.registerNewCustomer();
                BookingResult booking_result = hotel.bookRoomsForCustomer(customer);
                hotel.tellCustomerResult(booking_result);
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



