# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes

add_library(BACKGROUND STATIC background.c)
target_link_libraries(BACKGROUND PUBLIC PIPES)