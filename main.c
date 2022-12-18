#include "stdio.h"
#include "doublelinkedlist.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

void printRow(WeatherRow row) {
    printf("%d ", row.id);
}

int main() {

    srand(time(NULL));

    DoubleLinkedList* list = emptyList();
    for(int i = 0; i < 10; i++) {
        WeatherRow row;
        row.id = rand()%100;
        list = insertOrd(list, row, compareStationID);
    }

    printList(list);
    forEach(list, printRow, false);
    printf("\n");
    forEach(list, printRow, true);
    printf("\n");

    return 0;
}