#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//вывод комнат в консоле аски симв

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
}node_t;

node_t* NewNode(room_t data){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node ->data = data;
    new_node->next = NULL;

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
    printf("._____________________________________.\n");
    printf("|           ROOM INFORMATION         |\n");
    printf("|____________________________________|\n");
    printf("| Name       : %-21s |\n", cur->data.name);
    printf("| Level      : %-21d |\n", cur->data.level);
    printf("| Number     : %-21d |\n", cur->data.number);
    printf("| Resolution : %-21d |\n", cur->data.resolution);
    printf("|____________________________________|\n");
    cur = cur->next;
    printf("      |      \n");
    printf("      v      \n");
    }
    printf("     NULL\n");
}

void FillRandList(node_t *head, int N){
    room_t data;
    // node_t *head = (node_t *)malloc(sizeof(node_t));
    // head ->data = data;
    // head->next = NULL;
    for (int i = 1; i<N;i++){
        data.name = name_rooms[rand() % 20];
        data.level = rand() % 100;
        data.number = i + 1;
        data.resolution = rand() % 20 + 4;
        head = AppendBack(head, data);
    }
}

int main() {
    srand(time(NULL));
    int N;
    printf("Введите количество N элементов >\n");scanf("%d",&N);

    room_t data;
    data.name = name_rooms[rand() % 20];
    data.level = rand() % 100;
    data.number = 1;
    data.resolution = rand() % 20;

    node_t *node1 = NewNode(data);
    FillRandList(node1,N);
    printList(node1);

}