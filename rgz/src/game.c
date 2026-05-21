#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

location_t* world_locations = NULL;
int total_locations = 0;
int curr_location_idx =0;

item_t* player_inventory = NULL;
int player_inventory_count = 0;

char buffer[2048];

char* copy_string(const char* str){
    if (!str) return NULL;
    char* new_str = (char*)malloc(strlen(str) + 1);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

int find_locashion_idx(int id){
    for (int i = 0; i < total_locations; i++){
        if (world_locations[i].id == id) return i;
    }
    return -1;
}

int game_save(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file for saving!!\n");
        return 0;
    }

    int curr_id = world_locations[curr_location_idx].id;
    fwrite(&curr_id, sizeof(int),1,file);

    fwrite(&player_inventory_count, sizeof(int), 1, file);
    for (int i = 0; i < player_inventory_count; i++) {
        int item_id = player_inventory[i].id;
        int len_name = (int)strlen(player_inventory[i].name);
        int len_inf = (int)strlen(player_inventory[i].inf);

        fwrite(&item_id, sizeof(int), 1, file);
        fwrite(&len_name, sizeof(int), 1, file);
        fwrite(player_inventory[i].name, sizeof(char), len_name, file);
        fwrite(&len_inf, sizeof(int), 1, file);
        fwrite(player_inventory[i].inf, sizeof(char), len_inf, file);
    }

    fclose(file);
    return 1;
}

int game_load(const char* filename){
    FILE* file = fopen(filename,"rb");
    if (file == NULL){
        printf("Error opening file!!\n");
        return 0;
    }

    int id_load = 0;
    if (fread(&id_load,sizeof(int),1,file) != 1) {fclose(file);return 0;}

    int tar_idx = find_locashion_idx(id_load);
    if (tar_idx == -1) {fclose(file);return 0;}

    
    game_free();
    if (!game_init("data/scenario.txt")) { 
        fclose(file);
        return 0;
    }

    // for (int i =0; i < player_inventory_count; i++) {
    //     free(player_inventory[i].name);
    //     free(player_inventory[i].inf);
    // }

    // free(player_inventory);
    // player_inventory = NULL;
    // player_inventory_count = 0;

    int inv_count = 0;
    fread(&inv_count,sizeof(int),1,file);

    if (inv_count > 0) {
        player_inventory = (item_t*)malloc(sizeof(item_t)*inv_count);
        player_inventory_count = inv_count;

        for (int i = 0; i<inv_count;i++){
            int item_id = 0, len_name = 0, len_inf = 0;
            
            fread(&item_id, sizeof(int), 1, file);
            player_inventory[i].id = item_id;

            fread(&len_name, sizeof(int), 1, file);
            player_inventory[i].name = (char*)malloc(len_name + 1);
            fread(player_inventory[i].name, sizeof(char), len_name, file);
            player_inventory[i].name[len_name] = '\0';

            fread(&len_inf, sizeof(int), 1, file);
            player_inventory[i].inf = (char*)malloc(len_inf + 1);
            fread(player_inventory[i].inf, sizeof(char), len_inf, file);
            player_inventory[i].inf[len_inf] = '\0';

            for (int loc = 0; loc < total_locations; loc++) {
                for (int it = 0; it < world_locations[loc].item_count; it++) {
                    if (world_locations[loc].items[it].id == item_id) {
                        // Чистим память удаляемого из комнаты предмета
                        free(world_locations[loc].items[it].name);
                        free(world_locations[loc].items[it].inf);
                        // Сдвигаем массив предметов в комнате
                        for (int k = it; k < world_locations[loc].item_count - 1; k++) {
                            world_locations[loc].items[k] = world_locations[loc].items[k + 1];
                        }
                        world_locations[loc].item_count--;
                        if (world_locations[loc].item_count == 0) {
                            free(world_locations[loc].items);
                            world_locations[loc].items = NULL;
                        } else {
                            world_locations[loc].items = (item_t*)realloc(world_locations[loc].items, sizeof(item_t) * world_locations[loc].item_count);
                        }
                        break;
                    }
                }
            }
        }
    }

    curr_location_idx = tar_idx;
    fclose(file);
    return 1;
}

const char* game_command(const char* input){
    char cmd_copy[256];
    strncpy(cmd_copy, input, sizeof(cmd_copy) - 1);
    cmd_copy[sizeof(cmd_copy) - 1] = '\0';

    char* action = strtok(cmd_copy, " \t\n");
    if (!action) {
        return "Вы ничего не ввели.";
    }

    location_t* room = &world_locations[curr_location_idx];


    if (strcmp(action,"осмотреться")==0){
        int len = snprintf(buffer,sizeof(buffer),"=== %s ===\n%s\n",room->name,room->inf);

        len += snprintf(buffer + len, sizeof(buffer) - len,"Выходы: ");
        if (room->exit_count == 0) {
            len += snprintf(buffer + len, sizeof(buffer) - len, "нет выходов.\n");
        } else {
            for (int i =0; i < room->exit_count; i++) 
            {
                len += snprintf(buffer + len, sizeof(buffer) - len, "[%s] ", room->exit_way[i]);
            }
            len += snprintf(buffer + len, sizeof(buffer) - len, "\n");
        }

        len += snprintf(buffer + len, sizeof(buffer) - len,"Предметы здесь: ");
        if (room->item_count == 0) {
            len += snprintf(buffer + len, sizeof(buffer) - len, "ничего интересного.\n");
        } else {
            for (int i =0; i < room->item_count; i++) 
            {
                len += snprintf(buffer + len, sizeof(buffer) - len, "[%s] ", room->items[i].name);
            }
            len += snprintf(buffer + len, sizeof(buffer) - len, "\n");
        }

        if (room->npc_count > 0) {
            len += snprintf(buffer + len, sizeof(buffer) - len, "Вы видите: ");
            for (int i = 0; i<room->npc_count;i++){
                len += snprintf(buffer + len, sizeof(buffer) - len, "[%s] ", room->npcs[i].name);
            }
            len += snprintf(buffer + len, sizeof(buffer) - len, "\n");
        }
        return buffer;        
    }

    if (strcmp(action,"инвентарь") == 0) {
        if (player_inventory_count == 0) return "Ваш инвентарь пуст.";

        int len = snprintf(buffer, sizeof(buffer),"Ваши вещи:\n");
        for (int i = 0; i < player_inventory_count; i++) {
            len += snprintf(buffer + len, sizeof(buffer) - len, "- %s (%s)\n",
                player_inventory[i].name,player_inventory[i].inf);
        }
        return buffer;
    }

    //второе слово
    char* target = strtok(NULL, "\n");
    // if (target) {
    //     while(*target == ' ' || *target == '\t') target++;
    // }
    if (!target) {
        snprintf(buffer, sizeof(buffer), "Что именно вы хотите сделать? (Например: <действие> <предмет>)");
        return buffer;
    }

    if (strcmp(action,"идти") == 0) {
        for (int i = 0; i < room->exit_count; i++) {
            if (strcmp(room->exit_way[i],target)==0){
                int next_idx = find_locashion_idx(room->exit_location_ids[i]);
                if (next_idx != -1) {
                    curr_location_idx = next_idx;
                    snprintf(buffer,sizeof(buffer), "Вы перешли в локацию: %s.", world_locations[curr_location_idx].name);
                    return buffer;
                }
            }
        }
        return "Вы не можете идти в этом направлении.";
    }

    if (strcmp(action,"говорить") == 0){
        for (int i = 0; i < room->npc_count; i++) {
            if (strcmp(room->npcs[i].name, target) == 0) {
                snprintf(buffer, sizeof(buffer), "%s говорит: \"%s\"", room->npcs[i].name, room->npcs[i].dialogue);
                return buffer;
            }
        }
        return "Этого персонажа здесь нет.";
    }

    if (strcmp(action,"взять") == 0){
        for (int i = 0; i < room->item_count; i++) {
            if (strcmp(room->items[i].name, target) == 0){
                //добавляем в инвентарь
                player_inventory_count++;
                player_inventory = (item_t*)realloc(player_inventory, sizeof(item_t) * player_inventory_count);
                player_inventory[player_inventory_count - 1].name = copy_string(room->items[i].name);
                player_inventory[player_inventory_count - 1].inf = copy_string(room->items[i].inf);
                player_inventory[player_inventory_count - 1].id = room->items[i].id;

                //удаляем из комнаты, сдвиг массива
                free(room->items[i].name);
                free(room->items[i].inf);
                for (int j = i; j < room->item_count - 1; j++) {
                    room->items[j] = room->items[j + 1];
                }
                room->item_count--;
                if (room->item_count == 0) {
                    free(room->items);
                    room->items = NULL;
                } else {
                    room->items = (item_t*)realloc(room->items, sizeof(item_t) * room->item_count);
                }

                snprintf(buffer, sizeof(buffer), "Вы подобрали: %s", target);
                return buffer;
            }

        }
        return "Такого предмета здесь нет.";
    }

    snprintf(buffer, sizeof(buffer), "Такой команды нет. Доступные действия: осмотреться, идти, взять, говорить, инвентарь.");
    return buffer;
}

void game_free(void) {
    for (int i = 0; i < total_locations; i++) {
        free(world_locations[i].name);
        free(world_locations[i].inf);
        
        for (int j = 0; j < world_locations[i].item_count; j++) {
            free(world_locations[i].items[j].name);
            free(world_locations[i].items[j].inf);
        }
        free(world_locations[i].items);
        
        for (int j = 0; j < world_locations[i].npc_count; j++) {
            free(world_locations[i].npcs[j].name);
            free(world_locations[i].npcs[j].dialogue);
        }
        free(world_locations[i].npcs);
        
        for (int j = 0; j < world_locations[i].exit_count; j++) {
            free(world_locations[i].exit_way[j]);
        }
        free(world_locations[i].exit_way);
        free(world_locations[i].exit_location_ids);
    }
    free(world_locations);
    world_locations = NULL;
    total_locations = 0;

    for (int i = 0; i < player_inventory_count; i++) {
        free(player_inventory[i].name);
        free(player_inventory[i].inf);
    }
    free(player_inventory);
    player_inventory = NULL;
    player_inventory_count = 0;
}

int game_init(const char* scenario_filename) {
    FILE* f = fopen(scenario_filename, "r");
    if (!f) {
        printf("Ошибка: не удалось открыть файл сценария %s\n", scenario_filename);
        return 0;
    }

    char line[512];
    
    // Читаем общее количество локаций
    if (!fgets(line, sizeof(line), f)) { fclose(f); return 0; }
    sscanf(line, "%d", &total_locations);

    world_locations = (location_t*)malloc(sizeof(location_t) * total_locations);

    for (int i = 0; i < total_locations; i++) {
        location_t* r = &world_locations[i];

        // 1. Читаем ID
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &r->id);

        // 2. Читаем Название
        fgets(line, sizeof(line), f);
        line[strcspn(line, "\r\n")] = '\0'; // Удаляем перенос строки
        r->name = copy_string(line);

        // 3. Читаем Описание
        fgets(line, sizeof(line), f);
        line[strcspn(line, "\r\n")] = '\0';
        r->inf = copy_string(line);

        // 4. Читаем Выходы
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &r->exit_count);
        if (r->exit_count > 0) {
            r->exit_way = (char**)malloc(sizeof(char*) * r->exit_count);
            r->exit_location_ids = (int*)malloc(sizeof(int) * r->exit_count);
            for (int j = 0; j < r->exit_count; j++) {
                char direction[64];
                int target_id;
                fgets(line, sizeof(line), f);
                sscanf(line, "%s %d", direction, &target_id);
                r->exit_way[j] = copy_string(direction);
                r->exit_location_ids[j] = target_id;
            }
        } else {
            r->exit_way = NULL;
            r->exit_location_ids = NULL;
        }

        // 5. Читаем Предметы
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &r->item_count);
        if (r->item_count > 0) {
            r->items = (item_t*)malloc(sizeof(item_t) * r->item_count);
            for (int j = 0; j < r->item_count; j++) {
                int item_id;
                char item_name[64];
                char item_desc[256];
                fgets(line, sizeof(line), f);
                // Читаем первое слово как имя, остальное как описание
                sscanf(line, "%d %s %[^\r\n]", &item_id, item_name, item_desc);
                r->items[j].id = item_id; // <- Записываем ID
                r->items[j].name = copy_string(item_name);
                r->items[j].inf = copy_string(item_desc);
            }
        } else {
            r->items = NULL;
        }

        // 6. Читаем NPC
        fgets(line, sizeof(line), f);
        sscanf(line, "%d", &r->npc_count);
        if (r->npc_count > 0) {
            r->npcs = (npc_t*)malloc(sizeof(npc_t) * r->npc_count);
            for (int j = 0; j < r->npc_count; j++) {
                char npc_name[64];
                char npc_dialogue[256];
                fgets(line, sizeof(line), f);
                sscanf(line, "%s %[^\r\n]", npc_name, npc_dialogue);
                r->npcs[j].name = copy_string(npc_name);
                r->npcs[j].dialogue = copy_string(npc_dialogue);
            }
        } else {
            r->npcs = NULL;
        }
    }

    fclose(f);
    curr_location_idx = 0;
    player_inventory_count = 0;
    player_inventory = NULL;
    return 1;
}