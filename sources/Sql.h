#ifndef LOPPUTYO_SQL_H
#define LOPPUTYO_SQL_H
#include <string>

const std::string SAVE_ROOM = "insert into Rooms (BED_AMOUNT, BookingID) VALUES (?, ?);";
const std::string SAVE_USER = "insert into Customer (NAME) values (?) RETURNING ID;";
const std::string SAVE_BOOKING = "insert into Bookings (BOOKING_ID, DAY_COUNT, CUSTOMER_ID) values (?, ?, ?);";
const std::string QUERY_BOOKING = "SELECT Customer.NAME, Bookings.DAY_COUNT, Rooms.BED_AMOUNT from Bookings LEFT JOIN Customer ON Customer.ID=Bookings.CUSTOMER_ID LEFT JOIN Rooms ON Rooms.BookingID=Bookings.BOOKING_ID WHERE Bookings.BOOKING_ID=?";
const std::string QUERY_ROOM_AMOUNT = "SELECT COUNT(), Settings.ROOM_AMOUNT from Rooms INNER JOIN Settings where BED_AMOUNT=?;";


const std::string CREATE_BOOKINGS = R"(
        create table IF NOT EXISTS Bookings
(
    ID          INTEGER not null
        primary key autoincrement
        constraint Bookings_Customer__fk
            references Customer (""),
    BOOKING_ID  INTEGER not null,
    DAY_COUNT   integer,
    CUSTOMER_ID integer
);

create index IF NOT EXISTS Bookings_ID_IDX
    on Bookings (ID);
    )";

const std::string CREATE_ROOMS = R"(
        create table IF NOT EXISTS Rooms
(
    ID         INTEGER not null
        primary key autoincrement,
    BED_AMOUNT INTEGER not null,
    BookingID  INTEGER
        references Bookings
);
    )";

const std::string CREATE_CUSTOMER = R"(
        create table IF NOT EXISTS Customer
(
    ID   INTEGER not null
        primary key autoincrement,
    NAME TEXT    not null
);

create unique index IF NOT EXISTS Customer_ID_IDX
    on Customer (ID);
    )";

const std::string CREATE_SETTINGS = R"(
        create table IF NOT EXISTS Settings
(
    ROOM_AMOUNT integer not null
);
    )";

#endif //LOPPUTYO_SQL_H
