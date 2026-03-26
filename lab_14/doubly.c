#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char* name_rooms[]={"Echo of Bones", "Forgotten Gallery", "Hall of Whispers", "Damp Dead-end", "Vultures' Refectory", "Foul Nest", "Trial Arena", "Torture Chamber", "Pit of Penance", "Guard Post", "Smuggler’s Stash", "Silence Oasis", "Abandoned Forge", "Alchemical Lab", "Library of Truth", "Shrine of the Fallen", "Sleeper’s Abode", "Throne Hall of Dust", "Ritual Circle", "Mirror Bound"
};

typedef struct{
    const char* name;
    int level;
    int number;
    int resolution;
}room_t;

typedef struct node{
    room_t data;
    struct node *next;
    struct node *down;
}node_t;

node_t* NewNode(room_t data){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node ->data = data;
    new_node->next = NULL;
    new_node->down = NULL;

    return new_node;
}

node_t *AppendBack(node_t* head, room_t data){
    node_t* new_node = NewNode(data);

    if (head == NULL) {
        return new_node;
    }

    struct node* cur = head; //cur - текущий узел

    while (cur->next != NULL) { //перебирает пока не найдет последний
        cur = cur->next; // перебрасываем cur на следующий 
    }

    cur->next = new_node;

    return head;
}

void printList(node_t *head){
    node_t* cur = head;
    while (cur) {
        printf("._____________________________________.     ._____________________________________.\n");
        if (cur->down != NULL) {
            printf("|             ROOM  %-5d            |      |             ROOM  %-4d             |\n", cur->data.number, cur->down->data.number);
            printf("|____________________________________| ---> |____________________________________|\n");
            printf("| Name       : %-21s |      | Name       : %-21s |\n", cur->data.name, cur->down->data.name);
            printf("| Level      : %-21d |      | Level      : %-21d |\n", cur->data.level, cur->down->data.level);
        } else {
            printf("|             ROOM  %-5d            |      |             NULL                   |\n", cur->data.number);
            printf("|____________________________________| ---> |____________________________________|\n");
            printf("| Name       : %-21s |      | Name       : %-21s |\n", cur->data.name, "-");
            printf("| Level      : %-21d |      | Level      : %-21d |\n", cur->data.level, 0);
        }        
        printf("|____________________________________|      |____________________________________|\n");
        cur = cur->next;
        if (cur) printf("      |                                        |\n      v                                        v \n");
    }
    printf("     NULL\n");
}

void FillRandList(node_t *head, int nach, int start){
    room_t data;
    for (int i = 1; i < nach; i++){  data.name = name_rooms[rand() % 20];
        data.level = rand() % 100;
        data.number = start + i + 1;
        data.resolution = rand() % 20 + 4;
        AppendBack(head, data);
    }
}

node_t *Create_double(node_t *head_K, node_t *head_N) {
    node_t* cur_K = head_K;
    node_t* cur_N = head_N;
    node_t* last_K = NULL;

    while (cur_K != NULL) {
        if (cur_N != NULL) {
            cur_K->down = cur_N;  // Привязка N к K
            cur_N = cur_N->next;  // Сдвиг N
            last_K = cur_K;
        } else {
            cur_K->down = NULL;
        }
        cur_K = cur_K->next;
    }

    if (cur_N != NULL && cur_K != NULL){
        last_K->down = cur_N;
    }
    
    return head_K;
}

void drawMap(node_t *curr, char* msg) {

    node_t *R = curr->next;
    node_t *D = curr->down;
    node_t *RD = (R) ? R->down : NULL;

    printf("=== КАРТА КОМНАТ ===\n");
    printf("Статус: %s\n\n", msg);

    printf(".____________________.      .____________________.\n");
    printf("|  %-18s  |      |  %-18s    |\n", (curr ? "[*] ВЫ ЗДЕСЬ [*]" : ""), (R ? "КОМНАТА СПРАВА" : "     ПУСТО"));
    printf("| Room %-14d|  --> | Room %-14d|\n", curr->data.number, (R ? R->data.number : 0));
    printf("| Lvl:%-15d|      | Lvl:%-15d|\n", curr->data.level, (R ? R->data.level : 0));
    printf("|____________________|      |____________________|\n");

    printf("         |                           |            \n");
    printf("         v                           v            \n");

    printf(".____________________.      .____________________.\n");
    printf("|  %-18s     |      |%-13s|\n", (D ? "КОМНАТА СНИЗУ" : "     ПУСТО"), (RD ? "КОМНАТА СНИЗУ СПРАВА" : "     ПУСТО"));
    printf("| Room %-14d|  --> | Room %-14d|\n", (D ? D->data.number : 0), (RD ? RD->data.number : 0));
    printf("| Lvl:%-15d|      | Lvl:%-15d|\n", (D ? D->data.level : 0), (RD ? RD->data.level : 0));
    printf("|____________________|      |____________________|\n");

    printf("\nУправление: S-Вниз, D-Вправо, Q-Выход\n");
    printf("(W/A недоступны !! )\n");
}

int main() {
    srand(time(NULL));
    int N;
    printf("Введите количество N элементов >\n");scanf("%d",&N);

    int K;
    printf("Введите количество K элементов >\n");scanf("%d",&K);

    room_t data1;
    data1.name = name_rooms[rand() % 20];
    data1.level = rand() % 100;
    data1.number = 1 ;
    data1.resolution = rand() % 20;

    node_t *node_N = NewNode(data1);
    FillRandList(node_N,N,0);

    data1.name = name_rooms[rand() % 20];
    data1.level = rand() % 100;
    data1.number = N  + 1 ;
    data1.resolution = rand() % 20;

    node_t *node_K = NewNode(data1);
    FillRandList(node_K,K,N);
    node_K = Create_double(node_K,node_N);
    // printList(node_K);
    
    node_t *curr = node_K;
    char с;
    char *message = "Исследуйте подземелье!";

    while (1) {
        drawMap(curr, message);
        message = "---";

        printf("Команда > ");
        scanf(" %c", &с);

        if (с == 'q' || с == 'Q') break;

        if (с == 'd' || с == 'D') {
            if (curr->next) curr = curr->next;
            else message = "Справа стена!";
        } 
        else if (с == 's' || с == 'S') {
            if (curr->down) curr = curr->down;
            else message = "Внизу пропасть!";
        } 
        else if (с == 'w' || с == 'W' || с == 'a' || с == 'A') {
            message = "НЕТ ПУТИ (но возможно можно спуститься или проити дальше (назад/вверх))";
        }
    }
    return 0;
}