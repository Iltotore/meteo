#include "stdio.h"
#include <string.h>
#include "doublelinkedlist.h"
#include "tree.h"
#include "avl.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

void printRow(WeatherRow row) {
    printf("id: %d, wind: %f\n", row.id, *row.windSpeed);
}

Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

WeatherRow maxMoisture(WeatherRow a, WeatherRow b) {
    return *a.moisture >= *b.moisture ? a : b;
}


int main(int argc, char **argv) {
  //int a;
    srand(time(NULL));
    /*
    a=strmp(argv[1],"avl");
    if(a==0) range avl
    else{
        a=strmp(argv[1],"tree");
        if(a==0) range bst (abr)
    }
    else{ 
        a=strmp(argv[1],"array");
        if(a==0) range array(tableau)
    }
    */



    return 0;
}