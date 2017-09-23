#include <stdbool.h>

#ifndef LOGICTASK1_HASH_H
#define LOGICTASK1_HASH_H

#define SET_MAX_SIZE 32

struct Node{
    char *value;
    struct Node *next;
}typedef Node;

struct Set{
    Node **buffer;
    int id;
}typedef Set;

bool insertInSet(Set *set, char *s);
bool  deleteNode(Set *set, char *s);

Set* initSet();
void freeNode(Node *node);
void deleteSet(Set *set);
unsigned int hash(char *s);

#endif //LOGICTASK1_HASH_H
