cmake_minimum_required(VERSION 3.10)

project(coffee_cmake)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src) 
# CMAKE_CURRENT_SOURCE_DIR в CMake — это встроенная переменная, указывающая полный путь к директории исходного кода, содержащей CMakeLists.txt

set(SOURCE_LIB ${SOURCE_DIR}/coffeehouse.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

option(TEST "это коммент" OFF) #если его никто не создавал то ,будет значение офф, можно менять с кансоли $cmake .. -DTEST=ON
# -DCMAKE_BULD_TYPE=Release - оптимизированный файл
# Debug - сгенерит маке файл

if (${TEST})
    add_library(COFFEE_LIB STATIC ${SOURCE_LIB})
else()
    add_library(COFFEE_LIB SHARED ${SOURCE_LIB})
endif()

add_executable(main ${SOURCE_DIR}/main.c) # Создает исполняемый файл с именем main

target_link_libraries(main COFFEE_LIB) # Линковка





# add_subdirectory(<путь>)


######
#add_library(COFFEE_LIB ${SOURCE_LIB})	# Создание библиотеки с именем SOURCE_LIB
# чтобы опция -D работала, команда add_library должна вызываться без указания типа (без STATIC или SHARED)
# $ cmake -DBUILD_SHARED_LIBS=ON .. (или OFF- стат., ON - дин.)
#####