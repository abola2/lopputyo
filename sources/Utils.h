#ifndef LOPPUTYO_UTILS_H
#define LOPPUTYO_UTILS_H
#include <iostream>
#include <random>
#include <thread>

inline int numberBetween(const int min, const int max) {
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution dist(min, max);

    return dist(engine);
}

inline int numberBetween(const long seed, const int min, const int max) {
    std::mt19937 engine(seed);
    std::uniform_int_distribution dist(min, max);

    return dist(engine);
}

inline int createUniqueBookingNumber()
{
    const long seed = time(nullptr);
    //Spec requires that booking number is between above values
    return numberBetween(seed, 10000, 99999);
}

inline int GetUserNumberInput(const std::string& message) {
    int number = {};
    std::cout << message << std::endl;
    while (!(std::cin >> number)) {
        std::cout << message << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return number;
}

inline double GetRandomDiscount() {
    const double discounts[3]  = {0.0, 0.8, 0.9};
    const auto value = numberBetween(0, 2);

    return discounts[value];
}

inline int GetUserInputInRange(const int min, const int max, const std::string& message) {
    int number = {};
    while (number < min || number > max) {
        number = GetUserNumberInput(message);
    }
    return number;
}

inline int GenerateBookingNumber() {
    return numberBetween(10000, 99999);
}

#endif //LOPPUTYO_UTILS_H