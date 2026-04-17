#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node{
    int num;
    struct node *up;
    struct node *next;
    struct node *down;
}node_t;

node_t* NewNode(int data){
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node ->num = data;
    new_node->next = NULL;
    new_node->down = NULL;
    new_node->up = NULL;

    return new_node;
}

node_t *AppendBack(node_t* head, int data){
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
node_t *AppendFront(node_t* head, int data){
    node_t* new_node = NewNode(data);

    if (head == NULL) {
        return new_node;
    }

    new_node->next = head;
    return new_node;
}

void FillList_Back(node_t *head, int end, int start){

    for (int i = 1; i < end; i++){  
        AppendBack(head,start + i);
    }
}
void FillList(node_t *head, int end){
    for (int i = 1; i < end; i++){  
        AppendBack(head, (1+i)*(-1));
    }
}

node_t* FillList_Front(node_t *head, int end,int start){

    for (int i = 1; i < end; i++){  
        head = AppendFront(head, start + i);
    }
     return head;
}

node_t *Create(node_t *head_K, node_t *head_N,node_t *head_S) {
    node_t* cur_K = head_K;
    node_t* cur_S = head_S;
    node_t* cur_N = head_N;

    while (1) {
        if (cur_N != NULL) {
            cur_S->down = cur_N;  // Привязка S к N
            cur_N = cur_N->next;  // Сдвиг N
        }else cur_S->down = NULL;
        if (cur_K != NULL) {
            cur_S->up = cur_K;  
            cur_K = cur_K->next; 
        }
        else cur_S->up = NULL;
        if (cur_S->next == NULL){ break;} // Останавливаемся на последнем узле
        cur_S = cur_S->next;
    }
    // if (cur_N != NULL && cur_K != NULL){
    //     last_K->down = cur_N;
    // }
    cur_S->next = head_S;
    
    return head_S;
}

void drawMap(node_t* curr, const char* msg) {
    printf("\n========================================\n");
    printf("Статус: %s\n\n", msg);
    printf("ТЕКУЩИЙ УЗЕЛ: [ %p ]\n", (node_t*)curr);
    printf("Номер комнаты: %d\n", curr->num);
    printf("----------------------------------------\n");
    printf("  UP:   %d (%p)\n", (curr->up ? curr->up->num : 0),(node_t*)curr->up);
    printf("  DOWN: %d (%p)\n", (curr->down ? curr->down->num : 0),(node_t*)curr->down);
    printf("  NEXT: %d (%p)\n", (curr->next ? curr->next->num : 0),(node_t*)curr->next);
    printf("----------------------------------------\n");
    printf(" Управление: [W]-вверх, [S]-вниз, [D]-вперед, [Q]-выход");
    printf("\n > ");
}

int main() {
    srand(time(NULL));
    int N, K;

    printf("Введите количество элементов N (нижний список) > ");
    if(scanf("%d", &N) != 1) return 1;
    printf("Введите количество элементов K (верхний список) > ");
    if(scanf("%d", &K) != 1) return 1;


    node_t *node_N = NewNode(1); 
    node_N= FillList_Front(node_N, N, 1);
    
    node_t *node_K = NewNode(N+1); 
    FillList_Back(node_K, K, N+1);
    
    node_t *node_S = NewNode(-1);   
    FillList(node_S, (N > K ? N : K));
    
    node_S = Create(node_K, node_N, node_S);


    node_t *head_S_fixed = node_S; // точка входа
    node_t *curr = node_S;         // Текущ позиция

    char cmd;
    const char* message = "Вы находитесь в начале пути S";

    while (1) {
        drawMap(curr, message);
        scanf(" %c", &cmd);

        if (cmd == 'r' || cmd == 'R') {
            curr = node_S;
            message = "Вы вернулись в начало пути (S)!";
        }

        if (cmd == 'q' || cmd == 'Q') break;
        message = "---";

        if ((cmd == 'd' || cmd == 'D') && curr->next) {
            curr = curr->next;
            message = "Переход по NEXT";
        } 
        else if ((cmd == 'w' || cmd == 'W') && curr->up) {
            curr = curr->up;
            message = "Переход по UP";
        } 
        else if ((cmd == 's' || cmd == 'S') && curr->down) {
            curr = curr->down;
            message = "Переход по DOWN";
        } 
        else {
            message = "Пути в этом направлении нет!";
        }
    }
}