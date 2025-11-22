#ifndef LOPPUTYO_HOTEL_H
#define LOPPUTYO_HOTEL_H
#include <string>

#include "SqlManager.h"

enum class State
{
    VIEW = 1,
    USER = 2,
    CLOSE = 3
};

struct BookingResult {
    int bookingID;
    std::string name;
    int dayAmount;
    int bedAmount;
};

struct Customer
{
    std::string name;
    int id;
};

class HotelManager {

public:
    void checkUserBookings() const;
    State askWhatUserWantsToDo();
    BookingResult bookRoomsForCustomer(const Customer& customer) const;
    Customer registerNewCustomer() const;
    static void tellCustomerResult(const BookingResult& booking_result);
    explicit HotelManager(const SqlManager& sql_manager);

    [[nodiscard]] State getState() const
    {
        return state;
    }

    void setState(const State& newState)
    {
        this->state = newState;
    }

private:
    State state = State::USER;
    SqlManager sql_manager_ = {};
};

#endif //LOPPUTYO_HOTEL_H