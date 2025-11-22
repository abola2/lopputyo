#include <format>
#include <iostream>
#include "HotelManager.h"
#include "Utils.h"
#include <sqlite3.h>
#include "Sql.h"
#include "imgui.h"
#include "SqlManager.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>






int main() {


    //Open connection to db
    auto sql_manager = SqlManager();
    const auto hotel = HotelManager(sql_manager);


    sql_manager.createDatabase();
    sql_manager.generateHotel();
    while (true) {
        int id = hotel.registerNewCustomer();
        std::cout << "Tervetuloa hotelliin!" << std::endl;
         hotel.bookRoomsForCustomer(id);
         hotel.tellCustomerResult(id);

    }
    sqlite3_close(sql_manager.database());
    return 0;
}



