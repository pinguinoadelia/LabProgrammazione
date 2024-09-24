cmake_minimum_required(VERSION 3.28)
project(LabProgrammazione)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Test)

set(SOURCE_FILES main.cpp
        Item.h
        Observer.h
        Subject.h
        ShoppingList.h
        ShoppingList.cpp
        User.h
        User.cpp
        Item.cpp
)
add_executable(LabProgrammazione main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(LabProgrammazione core)