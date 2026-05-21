#ifndef GAME_H
#define GAME_H


typedef struct {
    int id;
    char* name;
    char* inf;
} item_t; //предмет

typedef struct {
    char* name;
    char* dialogue;
} npc_t;

typedef struct {
    int id;
    char* name;
    char* inf;

    int exit_count;
    char** exit_way;
    int* exit_location_ids;

    int item_count;
    item_t* items;
    
    int npc_count;
    npc_t* npcs;
} location_t;

int  game_init(const char* scenario_filename);
const char* game_command(const char* input);
void game_free(void);

int  game_save(const char* filename);
int  game_load(const char* filename);

#endif