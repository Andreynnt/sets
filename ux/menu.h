#ifndef LOGICTASK1_MENU_H
#define LOGICTASK1_MENU_H

#include "../src/hash.h"

int parse(char *s);
Set* parseId(Set *firstSet, Set *secondSet);

int setId();
int setCommand();
int menu();

Set* newSet(int i);
bool idInsertNode(Set *firstSet, Set *secondSet);
bool idDeleteNode(Set *firstSet, Set *secondSet);
void showSet(Set *set);




#endif //LOGICTASK1_MENU_H
