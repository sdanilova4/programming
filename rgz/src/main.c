#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void read_input(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

int main() {
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    // ИСПРАВЛЕНО: убрали "data/", теперь ищет scenario.txt в папке запуска
    if (!game_init("scenario.txt")) {
        printf("ошибка: не удалось инициализировать мир игры!\n");
        return 1;
    }

    printf("==================================================\n");
    printf("                   ТЕКСТОВЫЙ КВЕСТ                \n");
    printf("==================================================\n");
    printf("Доступные команды:\n");
    printf("  сохранить  - сохранить текущий прогресс\n");
    printf("  загрузить  - загрузить последнее сохранение\n");
    printf("  выход      - выйти из игры\n\n");
    printf("Игровые команды:\n осмотреться\n идти [направление]\n взять [предмет]\n говорить [npc]\n инвентарь\n");
    printf("==================================================\n\n");

    printf("%s\n", game_command("осмотреться"));

    char input_buffer[256];

    while (1) {
        printf("\n> ");
        read_input(input_buffer, sizeof(input_buffer));

        if (strcmp(input_buffer, "выход") == 0) {
            printf("Спасибо за игру! До свидания.\n");
            break;
        }
        
        if (strcmp(input_buffer, "сохранить") == 0) {
            // ИСПРАВЛЕНО: привели путь к "save.dat" для синхронизации с game_load
            if (game_save("save.dat")) {
                printf("[Система]: Игра успешно сохранена.\n");
            } else {
                printf("[Система]: Ошибка при сохранении игры!\n");
            }
            continue;
        }

        if (strcmp(input_buffer, "загрузить") == 0) {
            if (game_load("save.dat")) {
                printf("[Система]: Игра успешно загружена!\n\n");
                printf("%s\n", game_command("осмотреться"));
            } else {
                printf("[Система]: Не удалось загрузить сохранение (возможно, файла нет).\n");
            }
            continue;
        }

        const char* response = game_command(input_buffer);
        printf("%s\n", response);
    }

    game_free();
    return 0;
}
