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
    int a;
    srand(time(NULL));
    
    a=strcmp(argv[1],"avl");
    if(a==0) printf("Je vais faire l'affichage d'avl\n");
    else if (strcmp(argv[1], "tree")==0){
        printf("Je vais faire l'affichage d'un abr\n");
    }
    else if(strcmp(argv[1], "array")==0){
            printf("Je vais faire l'affichage d'un tableau\n");
    }
    else{
        printf("L'argument n'est pas valide !");
    }
    

    if(strcmp(argv[2],"t")==0)printf("Je vais faire l'affichage selon la temperature");
    else if(strcmp(argv[2],"p")==0)printf("Je vais faire l'affichage selon la pression");
    else if(strcmp(argv[2],"w")==0)printf("Je vais faire l'affichage selon le vent");
    else if (strcmp(argv[2],"h")==0) printf("Je vais faire l'affichage selon la wind");
    else if (strcmp(argv[2],"m")==0) printf("Je vais faire l'affichage selon l'humidité");
    
    else printf("L'argument n'est pas valide !");

    if (strcmp(argv[3],"1")==0)printf("Je vais faire l'affichage à l'envers");
    else if(strcmp(argv[3],"2")==0) printf("Je vais faire l'affichage à l'endroit");
    else printf("L'argument n'est pas valide !"); 


    return 0;
}
