#include "stdio.h"
#include "doublelinkedlist.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

void printRow(WeatherRow row) {
    printf("%d ", row.id);
}

Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

int main() {

    srand(time(NULL));

    DoubleLinkedList *list = emptyList();
    for(int i = 0; i < 10; i++) {
        WeatherRow row;
        row.id = rand() % 100;
        list = insertOrd(list, row, compareStationIDDesc);
    }

    printList(list);

    return 0;
}