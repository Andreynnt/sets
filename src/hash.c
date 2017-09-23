#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//Инициализия множества
Set* initSet(){
    Set *set = malloc(sizeof(Set));
    set->buffer = calloc(SET_MAX_SIZE, sizeof(Node*));
    set->id = 0;
    return set;
}

//Хэширующая функция
unsigned int hash(char *s) {
    unsigned int hashval = 0;
    while (*s != '\0'){
        hashval = *s + 31 * hashval;
        s++;
    }
    return hashval % SET_MAX_SIZE;
}

//Вставка элемента в множество
bool insertInSet(Set *set, char *s) {
    unsigned int hashValue = hash(s);
    Node *node = set->buffer[hashValue];
    size_t len = strlen(s) + 1;
    if (node){
        if (!strcmp(node->value, s)){
            return false;
        }
        while (node->next){
            if (!strcmp(node->value, s)){
                return false;
            }
            node = node->next;
        }
        node = malloc(sizeof(Node));
        node->value = malloc(len * sizeof(char));
        node->next = NULL;
        memcpy(node->value, s, strlen(s) + 1);
        set->buffer[hashValue]->next = node;
        return true;
    }else{
        node = malloc(sizeof(Node));
        node->value = malloc(len * sizeof(char));
        node->next = NULL;
        memcpy(node->value, s, strlen(s) + 1);
        set->buffer[hashValue] = node;
    }
    return true;
}

//Удаление элемента множества
bool deleteNode(Set *set, char *s){
    unsigned int hashValue = hash(s);
    Node *node = set->buffer[hashValue];
    if (node){
        Node *prev = NULL;
        while(node->next){
            if (!strcmp(node->value, s)){
                prev->next = node->next;
                freeNode(node);
                return true;
            }
            prev = node;
            node = node->next;
        }
        if (!strcmp(node->value, s)) {
            free(node->value); node->value = NULL;
            free(node); node = NULL;
            set->buffer[hashValue] = NULL;
            return true;
        }
    }
    return false;
}

//Освобождение памяти элемента
void freeNode(Node *node){
    free(node->value); node->value = NULL;
    free(node); node = NULL;
}

//Освобождение памяти множества
void deleteSet(Set *set){
    for (int i = 0; i < SET_MAX_SIZE; i++){
        Node *node = set->buffer[i];
        if (node){
            while (node->next){
                Node *tmp = node;
                node = node->next;
                freeNode(tmp);
            }
            freeNode(node);
        }
    }
    free(set->buffer); set->buffer = NULL;
    free(set); set = NULL;
}