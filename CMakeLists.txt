cmake_minimum_required(VERSION 4.0)   # Минимальная версия CMake, которая нужна для сборки
project(lab2_2 C)                     # Имя проекта и выбранный языки программирования)

set(CMAKE_C_STANDARD 17)              # Установить стандарт C

add_executable(lab2_2 main.c)         # Создать исполняемый файл lab2_2 из файла main.c

target_link_libraries(lab2_2 m)       # Линковка с математической библиотекой libm