#include "stdio.h"
#include <string.h>
#include "doublelinkedlist.h"
#include "tree.h"
#include "avl.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

WeatherRow maxMoisture(WeatherRow a, WeatherRow b) {
    return *a.moisture >= *b.moisture ? a : b;
}


int main(int argc, char **argv) {
    srand(time(NULL));

    /*char* nfile=argv[1];
    FILE* file= fopen(nfile, "r");

    if(nfile == NULL) {
        printf("It's absolutely impossible to open the file !\n");
        return 2;
    }
   

    SortMode sortMode=argv[2];
    
    switch(argv[2]) {
        case List :
           
           break ;
    }*/

    if(strcmp(argv[3],"t")==0)printf("Je vais faire l'affichage selon la temperature");

    else if(strcmp(argv[3],"p")==0)printf("Je vais faire l'affichage selon la pression");

    else if(strcmp(argv[3],"w")==0)printf("Je vais faire l'affichage selon le vent");

    else if (strcmp(argv[3],"h")==0) printf("Je vais faire l'affichage selon l'altitude");

    else if (strcmp(argv[3],"m")==0) {

    }
    
    else printf("L'argument n'est pas valide !");

    if (strcmp(argv[3],"1")==0)printf("Je vais faire l'affichage à l'envers");

    else if(strcmp(argv[3],"2")==0) printf("Je vais faire l'affichage à l'endroit");

    else printf("L'argument n'est pas valide !"); 


    return 0;
}
