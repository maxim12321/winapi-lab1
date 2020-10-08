cmake_minimum_required(VERSION 3.14)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(
        lab1

        main.cpp
        Controller/controller.cpp
        Controller/people_manager.cpp
        Model/lecturer.cpp
        Model/person.cpp
        Model/student.cpp
        Model/student_move_data.cpp
        Model/Containers/lecturer_container.cpp
        Model/Containers/person_container.cpp
        Model/Containers/student_container.cpp
        Model/Visitors/cashier.cpp
        Model/Utils/point.cpp
        View/person_drawer.cpp
        View/view.cpp
)

target_link_libraries(lab1 "Comctl32.lib")
