#include "stdio.h"
#include "tree.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

void printRow(WeatherRow row) {
    printf("%d ", row.id);
}

int main() {

    srand(time(NULL));

    Node* node = NULL;
    for(int i = 0; i < 10; i++) {
        WeatherRow row;
        row.id = rand()%100;
        node = insertABR(node, row, compareStationID);
    }

    printInfix(node);
    forEachInfix(node, printRow, false);
    printf("\n");
    forEachInfix(node, printRow, true);
    printf("\n");

    return 0;
}