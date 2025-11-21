#ifndef LOPPUTYO_SQL_H
#define LOPPUTYO_SQL_H
#include <string>


const std::string CREATE_BOOKINGS = R"(
        CREATE TABLE IF NOT EXISTS Bookings (
            ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            NUMBER INTEGER NOT NULL
        );
        CREATE INDEX IF NOT EXISTS Bookings_ID_IDX ON Bookings(ID);
    )";

const std::string CREATE_ROOMS = R"(
        CREATE TABLE IF NOT EXISTS Rooms (
            ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            BED_AMOUNT INTEGER NOT NULL,
            BookingID INTEGER,
            FOREIGN KEY (BookingID) REFERENCES Bookings(ID)
        );
    )";

const std::string CREATE_CUSTOMER = R"(
        CREATE TABLE IF NOT EXISTS Customer (
            ID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
            NAME TEXT NOT NULL,
            BookingID INTEGER,
            FOREIGN KEY (BookingID) REFERENCES Bookings(ID)
        );
        CREATE UNIQUE INDEX IF NOT EXISTS Customer_ID_IDX ON Customer(ID);
    )";

const std::string CREATE_SETTINGS = R"(
        create table IF NOT EXISTS Settings
(
    ROOM_AMOUNT integer not null
);
    )";



#endif //LOPPUTYO_SQL_H
