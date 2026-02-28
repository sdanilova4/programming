cmake_minimum_required(VERSION 3.10)

project(project)

include_directories(background pipes src) #говорит компилятору, где искать заголовочные файлы

add_subdirectory(pipes) #добавление подпроекта
add_subdirectory(background)

add_executable(main src/main.c) # Создает исполняемый файл с именем main

target_link_libraries(main BACKGROUND)