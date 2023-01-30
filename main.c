#include <stdbool.h>
#include "stdio.h"
#include <string.h>
#include "doublelinkedlist.h"
#include "tree.h"
#include "avl.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"
#include "util.h"
#include "io.h"

Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

WeatherRow maxMoisture(WeatherRow a, WeatherRow b) {
    return *a.moisture >= *b.moisture ? a : b;
}


int main(int argc, char **argv) {
//    bool reverse;
//
//    if(strcmp(argv[5], "true") == 0)reverse = true;
//
//    else if(strcmp(argv[5], "false") == 0)reverse = false;
//
//    else error("Reverse must be either true or false !", WRONG_ARGUMENTS);
    char *nfile = argv[1];
    FILE *file = fopen(nfile, "r");

    if(file == NULL) {
        error("It's absolutely impossible to open the file !", INPUT_FILE_ERROR);
    }
    char *nout = argv[2];
    FILE *out = fopen(nout, "r");
    if(out == NULL) {
        error("It's absolutely impossible to open the file !", OUTPUT_FILE_ERROR);
    }

    SortMode mode;

    if(strcmp(argv[3], "avl") == 0)mode = AVL_MODE;
    else if(strcmp(argv[3], "abr") == 0)mode = BST_MODE;
    else if(strcmp(argv[3], "array") == 0)mode = LIST_MODE;
    else error("Invalid sorting mode", WRONG_ARGUMENTS);

    if(strcmp(argv[4], "t1") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readTemperature, compareStationID, minTemperatureMin);
                writeLinesAVL(file, avl, writeTemperature1);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readTemperature, compareStationID, minTemperatureMin);
                writeLinesBST(file, bst, writeTemperature1);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readTemperature, compareStationID, minTemperatureMin);
                writeLinesList(file, list, writeTemperature1);
            }
                break;

        }
    } else if(strcmp(argv[4], "t2") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readTemperature, compareDate, minTemperatureMin);
                writeLinesAVL(file, avl, writeTemperature2);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readTemperature, compareDate, minTemperatureMin);
                writeLinesBST(file, bst, writeTemperature2);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readTemperature, compareDate, minTemperatureMin);
                writeLinesList(file, list, writeTemperature2);
            }
                break;

        }

    } else if(strcmp(argv[4], "t3") == 0) {
        switch(mode) {
            case AVL_MODE: {
//            AVL *avl = readLinesAVL(file, readTemperature, compareDateThenStation, minTemperatureMin);
//            writeLinesAVL(file, avl, writeTemperature3);
            }
                break;
            case BST_MODE: {
//            Tree *bst = readLinesBST(file, readTemperature, compareDateThenStation, minTemperatureMin);
//            writeLinesBST(file, bst, writeTemperature3);
            }
                break;
            case LIST_MODE: {
//            DoubleLinkedList *list = readLinesList(file, readTemperature, compareDateThenStation, minTemperatureMin);
//            writeLinesList(file, list, writeTemperature3);
            }
                break;

        }

    } else if(strcmp(argv[4], "p1") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readPressure, compareStationID, minStationPressure);
                writeLinesAVL(file, avl, writePressure1);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readPressure, compareStationID, minStationPressure);
                writeLinesBST(file, bst, writePressure1);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readPressure, compareStationID, minStationPressure);
                writeLinesList(file, list, writePressure1);
            }
                break;
        }
    } else if(strcmp(argv[4], "p2") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readPressure, compareDate, minStationPressure);
                writeLinesAVL(file, avl, writePressure2);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readPressure, compareDate, minStationPressure);
                writeLinesBST(file, bst, writePressure2);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readPressure, compareDate, minStationPressure);
                writeLinesList(file, list, writePressure2);
            }
                break;
        }
    } else if(strcmp(argv[4], "p3") == 0) {
        switch(mode) {
            case AVL_MODE: {
//            AVL *avl = readLinesAVL(file, readPressure, compareDateThenStation, minStationPressure);
//            writeLinesAVL(file, avl, writePressure3);
            }
                break;
            case BST_MODE: {
//            Tree *bst = readLinesBST(file, readPressure, compareDateThenStation, minStationPressure);
//            writeLinesBST(file, bst, writePressure3);
            }
                break;
            case LIST_MODE: {
//            DoubleLinkedList *list = readLinesList(file, readPressure, compareDateThenStation, minStationPressure);
//            writeLinesList(file, list, writePressure3);
            }
                break;
        }
    } else if(strcmp(argv[4], "w") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readWind, compareStationID, sumWind);
                mapCountInfixAVL(avl, averageWind);
                writeLinesAVL(file, avl, writeWind);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readWind, compareStationID, sumWind);
                mapCountInfix(bst, averageWind);
                writeLinesBST(file, bst, writeWind);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readWind, compareStationID, sumWind);
                mapCount(list, averageWind);
                writeLinesList(file, list, writeWind);
            }
                break;
        }
    } else if(strcmp(argv[4], "h") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readHeight, compareHeight, ignore);
                writeLinesAVL(file, avl, writeHeight);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readHeight, compareHeight, ignore);
                writeLinesBST(file, bst, writeHeight);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readHeight, compareHeight, ignore);
                writeLinesList(file, list, writeHeight);
            }
                break;
        }
    } else if(strcmp(argv[4], "m") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readMoisture, compareStationIDDesc, maxMoisture);
                writeLinesAVL(file, avl, writeMoisture);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readMoisture, compareStationIDDesc, maxMoisture);
                writeLinesBST(file, bst, writeMoisture);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readMoisture, compareStationIDDesc, maxMoisture);
                writeLinesList(file, list, writeMoisture);
            }
                break;
        }

    } else error("Invalid argument !", WRONG_ARGUMENTS);


    return 0;
}
