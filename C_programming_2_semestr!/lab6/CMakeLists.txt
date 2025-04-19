cmake_minimum_required(VERSION 3.10)
project(MyProject C)


set(LIB_TYPE "SHARED" CACHE STRING "Тип библиотеки: SHARED или STATIC")
set_property(CACHE LIB_TYPE PROPERTY STRINGS SHARED STATIC)



add_library(MyLib ${LIB_Type} student_search.c student_utils.c)

# target_include_directories(MyLib PUBLIC include)

# Сборка исполняемого файла из C-исходника
add_executable(myapp main.c)

target_link_libraries(myapp MyLib)