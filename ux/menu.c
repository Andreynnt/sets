#include <memory.h>
#include <assert.h>
#include "menu.h"
#include "stdio.h"

#define EXIT_CODE 5

//парсинг входных данных
int parse(char *s){
    if (!strcmp(s, "1")){
        return 1;
    }else if (!strcmp(s, "2")){
        return 2;
    }else if (!strcmp(s, "3")){
        return 3;
    }else if (!strcmp(s, "4")){
        return 4;
    }else if (!strcmp(s, "5")){
        return EXIT_CODE;
    }else{
        return 0;
    }
}

//Выбор программы
int setCommand(){
    printf("\nSelect command:\n");
    printf("1. Make new set:\n");
    printf("2. Add element to set:\n");
    printf("3. Delete element from set\n");
    printf("4. Show set\n");
    printf("5. Exit\n");
    printf("Command: ");
    char buff[64];
    scanf("%s", buff);
    switch (parse(buff)){
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            printf("\nGood bye!\n");
            return EXIT_CODE;
        default:
            printf("\nInvalid command! Please, try again\n");
            return 0;
    }
}

//Создание нового множества
Set* newSet(int i){
    printf("\nMaking set with id: %d\n", i);
    printf("To stop the process enter /stop\n");
    Set *set = initSet();
    set->id = i;
    char buffer[64];
    while (true) {
        scanf("%s", buffer);
        if (!strcmp(buffer, "/stop")) {
            showSet(set);
            return set;
        }
        insertInSet(set, buffer);
    }
}

//Парсинг и возвращение id
int setId(){
    char buffer[64];
    printf("\nEnter set id: ");
    scanf("%s", buffer);
    int id = parse(buffer);
    if (id == 1){
        return 1;
    }else if(id == 2){
        return 2;
    }else{
        return 0;
    }
}

//Выбор первого, либо втрого множества
Set* parseId(Set *firstSet, Set *secondSet){
    Set *set = NULL;
    if (!firstSet || !secondSet){
        printf("\nWe haven't any set\n");
        return NULL;
    }
    int id = setId();
    if (id == 1){
        set = firstSet;
    }else if(id == 2){
        set = secondSet;
    }else{
        printf("\nInvalid id!\n");
    }
    return set;
}

//Вставка элемента в множетсво
bool idInsertNode(Set *firstSet, Set *secondSet){
    Set *set = parseId(firstSet, secondSet);
    if (!set){
        return false;
    }
    char str[64];
    printf("\nEnter new element: ");
    scanf("%s", str);
    if (insertInSet(set, str)){
        printf("\nInserted!\n");
        return true;
    }else{
        printf("\nWe have this element!\n");
    }
    return false;
}

//Показать выбранное множество
bool idShowSet(Set *firstSet, Set *secondSet){
    printf("\n");
    Set *set = parseId(firstSet, secondSet);
    if (!set){
        return false;
    }
    showSet(set);
    return true;
};

//Удаление элемента множества
bool idDeleteNode(Set *firstSet, Set *secondSet){
    Set *set = parseId(firstSet, secondSet);
    if (!set){
        return false;
    }
    char buffer[64];
    printf("\nEnter element, which you want delete: ");
    scanf("%s", buffer);
    if (deleteNode(set, buffer)){
        printf("\n%s was deleted!\n", buffer);
        return true;
    }else{
        printf("\nSet doesn't contain this value!\n");
    }
    return false;
}

void showSet(Set *set){
    printf("Set: ");
    for (int i = 0; i < SET_MAX_SIZE; i++){
        Node *node = set->buffer[i];
        if (node){
            while (node->next){
                printf(" %s ", node->value);
                node = node->next;
            }
            printf(" %s ", node->value);
        }
    }
    printf("\n");
}

//Основное меню
int menu(){
    int command = 0, setsAmount = 0;
    Set *firstSet = NULL, *secondSet = NULL;
    while (command != EXIT_CODE){
        command = setCommand();
        assert(command >= 0 && command <= 5);
        switch (command){
            case 1:
                if (setsAmount >= 2){
                    printf("\nWe can make only two sets!\n");
                    break;
                }
                firstSet = newSet(1);
                setsAmount++;
                secondSet = newSet(2);
                setsAmount++;
                break;
            case 2:
                idInsertNode(firstSet, secondSet);
                break;
            case 3:
                idDeleteNode(firstSet, secondSet);
                break;
            case 4:
                idShowSet(firstSet, secondSet);
                break;
            case 5:
                if (firstSet)
                    deleteSet(firstSet);
                if (secondSet)
                    deleteSet(secondSet);
                command = EXIT_CODE;
            default:
                break;
        }
    }
    return 0;
}