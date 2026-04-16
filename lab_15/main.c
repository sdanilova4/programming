#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // sleep

#define N 100

typedef struct data
{
    char name[50];
    int num;
    char lvl[20];
}data_t;

int print_table_plus(FILE *file, data_t *list){
    char buffer[256];
    int line_count = 0;
    printf("--------------------------------------------\n");
    printf("%-23s | %-10s | %-10s\n", "имя", "ID", "уровень");
    printf("--------------------------------------------\n");
    while (fgets(buffer,sizeof(buffer),file) && line_count < 10)
    {
        buffer[strcspn(buffer, "\n")] = 0;
        char *name = strtok(buffer, ";");
        char *num = strtok(NULL, ";");
        char *level = strtok(NULL, ";");

        if (name && num && level) 
        {
            strcpy(list[line_count].name, name); // перенос из буфф в массив
            list[line_count].num = atoi(num);
            strcpy(list[line_count].lvl, level);
            printf("%-20s | %-10d | %-10s\n", list[line_count].name, list[line_count].num, list[line_count].lvl);
            line_count++;
        }
    }
    printf("------------------------------------------------------------\n");
    printf("всего сотрудников: %d\n", line_count);
    return line_count;
}

void save_bin_file(data_t *list, int list_count){
    FILE *bin_file = fopen("database.dat", "wb");
    if (bin_file == NULL) {
        printf("Error opening file!!\n");
        return;
    }
    if (bin_file) 
    {
        fwrite(list, sizeof(data_t), list_count, bin_file);
        fclose(bin_file);
        printf("\nмассив сохранен в database.dat\n");
    } else printf("ошибка сохранения в database.dat");
}

void find_id(){
    int id;
    printf("\nвведите ID для поиска > ");
    scanf("%d", &id);
    FILE *file = fopen("database.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!!\n");
        return;
    }

    data_t temp;
    int found = 0;
    while (fread(&temp, sizeof(data_t), 1, file)) 
    {
        if (temp.num == id) 
        {
            printf("\nНайдено 🎉!!\nИмя: %s, ID: %d, Уровень: %s\n", temp.name, temp.num, temp.lvl);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nОшибка 🙊 !! Сотрудник с ID %d не найден.\n", id);
    }

    fclose(file);
}

void compress(){
    FILE *file_in = fopen("database.dat", "rb");
    if (file_in == NULL) {
        printf("Error opening file!!\n");
        return;
    }
    FILE *file_out = fopen("database.rle", "wb");
    if (file_out == NULL) {
        printf("Error opening file!!\n");
        return;
    }

    unsigned char curr, next;
    int count = 1;

    if (fread(&curr, 1, 1, file_in) == 1) {
        while (fread(&next,1,1, file_in) == 1){ //пока считывается байтик
            if (next == curr && count < 255){
                count++;
            }
            else {
                fputc(count, file_out);
                fputc(curr,file_out);
                count = 1; curr = next;
            }
        }
        fputc(count, file_out);
        fputc(curr,file_out);

        fclose(file_in);fclose(file_out);   
    }
}

void decompress(){
    FILE *file_in = fopen("database.rle", "rb");
    if (file_in == NULL) {
        printf("Error opening file!!\n");
        return;
    }
    FILE *file_out = fopen("restored.dat", "wb");
    if (file_out == NULL) {
        printf("Error opening file!!\n");
        return;
    }

    unsigned char count, value;
    while (fread(&count, 1, 1, file_in) == 1 && fread(&value, 1, 1, file_in) == 1) {
        for (int i = 0; i < count; i++) {
            fputc(value, file_out);
        }
    }
    fclose(file_in); fclose(file_out);sleep(1);
    printf("Файл восстановлен в restored.dat\n");
}

long size_file(const char *filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file!!\n");
        return 0;
    }

    fseek(file,0,SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size;
}

int main(int argc, char *argv[]){
    if (argc <2){
        printf("Usage: %s staff.csv !!\n",argv[0]);
        exit(1);
    }

    FILE *file = fopen(argv[1],"r");
    if (file == NULL){
         printf("In %s:%d Error opening file\n", __FILE__, __LINE__);
        exit(1);
    }
    printf("Reading from file..\n");

    sleep(1);
    
    data_t list[N];
    int list_count = print_table_plus(file,list);

    sleep(1);

    save_bin_file(list, list_count);

    sleep(1);

    // int search_id;
    // printf("\nвведите ID для поиска > ");
    // scanf("%d", &search_id);
    find_id();
    // size_t elements_r = fread(arr,sizeof(data_t),N,file);
    // printf("Read > %zu elements\n",elements_r);
    fclose(file);

    sleep(1);
    
    printf("\nСжатие данных...\n");
    sleep(1);
    compress();

    long size_before = size_file("database.dat");
    long size_after = size_file("database.rle");
    float compression_file = (1.0 - (float)size_after / size_before) * 100.0;
    printf("Размер до: %ld байт, Размер после: %ld байт.\n", size_before, size_after);

    sleep(1);

    printf("Сжатие: %.2f%%\n", compression_file);
    
    decompress();
}