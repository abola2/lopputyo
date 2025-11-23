
#include "HotelManager.h"
#include <string>
#include <format>
#include <iostream>
#include "QuestionHelper.h"
#include "Utils.h"

void HotelManager::checkUserBookings() const
{
    std::vector<QueryResult> result;

    const int searchOption = GetUserInputInRange(1, 2, Questions::SEARCH_TYPE_PROMPT);
    if (searchOption == 1)
    {
        const int bookingNumber = GetUserNumberInput(Questions::BOOKING_NUMBER_PROMPT);
        result = sql_manager_.queryBookingById(bookingNumber);
    } else
    {
        std::cin.clear();
        std::cin.ignore();

        std::string namePrompt = std::format(
        "{}{}{}{}\n{}> {}",
        Color::Cyan, "Mikä on nimesi?", Color::Reset, "",
        Color::Yellow, Color::Reset
        );

        std::cout << namePrompt << std::endl;
        std::string name;
        std::getline(std::cin, name);
        result = sql_manager_.queryBookingByName(name);
    }

    if (!result.empty())
    {
        int bookingCounter = 0;
        auto customerName = result.at(0).name;
        std::cout << "Hei " << Color::Green << customerName << Color::Reset <<":" << std::endl;
        for (const auto& [name, dayCount, bedAmount] : result)
        {
            const std::string bookingResult = std::format("{}{}.{} Huone {}{}{} sängyllä {}{}{} päiväksi.", Color::Green, bookingCounter++, Color::Reset, Color::Green, bedAmount, Color::Reset, Color::Green, dayCount, Color::Reset);
            std::cout << bookingResult << std::endl;
        }
    } else
    {
        std::cout << Color::BrightRed << "Antamillasi tiedoilla ei löytynyt huonetta. \n" << Color::Reset << std::endl;
    }
}

State HotelManager::askWhatUserWantsToDo()
{
    const int result = GetUserInputInRange(1, 3, Questions::START_PROMPT);
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

std::optional<BookingResult> HotelManager::bookRoomsForCustomer(const Customer& customer) const
{
    const int requestRoomBedAmount = GetUserInputInRange(1, 2, Questions::BED_AMOUNT_PROMPT);
    const bool isAvailable =  sql_manager_.checkFreeRoomsByBedCount(requestRoomBedAmount);
    if (!isAvailable)
    {
        std::cout << Color::BrightRed << "Huoneita ei ole valitettavasti vapaana!" << Color::Reset << std::endl;
        return std::nullopt;
    }
    const int dayCount = GetUserInputInRange(1, INT_MAX, Questions::DAY_AMOUNT_PROMPT);
    const int bookingNumber = createUniqueBookingNumber();
    sql_manager_.saveBooking(dayCount, bookingNumber, customer.id);
    sql_manager_.saveRoom(requestRoomBedAmount, bookingNumber);
    BookingResult result = { bookingNumber, customer.name, dayCount, requestRoomBedAmount};
    return result;
}

Customer HotelManager::registerNewCustomer() const
{
    std::string name;

    std::cout << Questions::NAME_PROMPT << std::endl;
    std::getline(std::cin, name);
    std::cout << "Tervetuloa " << Color::Green << name << Color::Reset << std::endl;
    const int customerId = sql_manager_.saveUser(name);
    return {name, customerId};
}

void HotelManager::tellCustomerResult(const BookingResult& booking_result)
{
    const double discount = GetRandomDiscount();
    const double readableDiscount = (1.0-discount) * 100;

    const std::string discountMessage = std::format("Varasit huoneen {}{}{} sängyllä {}{}{} päiväksi.", Color::Green,booking_result.bedAmount, Color::Reset, Color::Green,booking_result.dayAmount, Color::Reset);
    std::cout << discountMessage << std::endl;

    if (discount < 1.0)
    {
        const std::string discountMessage = std::format("Onnittelut sait {}{:.0f}{}% alennusta!", Color::Green, readableDiscount, Color::Reset);
        std::cout << discountMessage << std::endl;
    }
    int price = booking_result.bedAmount == 1 ? 100 : 150;
    const std::string totalPriceMessage = std::format("Varaus maksaa yhteensä {}{}{}€", Color::Green, (price * booking_result.dayAmount) * discount, Color::Reset);
    std::cout << totalPriceMessage << std::endl;

    std::cout << "varausnumerosi on " << Color::Underline << Color::Green << booking_result.bookingID << Color::Reset << std::endl;
}

bool HotelManager::continueOrBack() const
{
    const int result = GetUserInputInRange(1, 2, Questions::CONTINUE_OR_RETURN_PROMPT);
    return result == 1;
}

HotelManager::HotelManager(const SqlManager& sql_manager)
{
    sql_manager_ = sql_manager;
}