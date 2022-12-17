#include "tree.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

int main() {

    srand(time(NULL));

    Node* node = NULL;
    for(int i = 0; i < 10; i++) {
        WeatherRow row;
        row.id = rand()%100;
        node = insertABR(node, row, reverseOrder(compareStationID));
    }

    printInfix(node);

    return 0;
}