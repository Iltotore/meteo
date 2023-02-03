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

int main(int argc, char **argv) {

    if(argc < 7) error("Not enough arguments!", WRONG_ARGUMENTS);
    else if(argc > 7) error("Too much arguments!", WRONG_ARGUMENTS);

    int lines = atoi(argv[6]);

    bool reversed;

    if(strcmp(argv[5], "true") == 0)reversed = true;

    else if(strcmp(argv[5], "false") == 0)reversed = false;

    else error("Reverse must be either true or false !", WRONG_ARGUMENTS);

    char *nfile = argv[1];
    FILE *file = fopen(nfile, "r");

    if(file == NULL) {
        error("It's absolutely impossible to open the file !", INPUT_FILE_ERROR);
    }
    char *nout = argv[2];
    FILE *out = fopen(nout, "w");
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
                AVL *avl = readLinesAVL(file, readTemperature, compareStationID, reduceTemperature1, lines);
                mapCountInfixAVL(avl, averageTemperature);
                writeLinesAVL(out, avl, writeTemperature1, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readTemperature, compareStationID, reduceTemperature1, lines);
                mapCountInfix(bst, averageTemperature);
                writeLinesBST(out, bst, writeTemperature1, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readTemperature, compareStationID, reduceTemperature1, lines);
                mapCount(list, averageTemperature);
                writeLinesList(out, list, writeTemperature1, reversed);
            }
                break;

        }
    } else if(strcmp(argv[4], "t2") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readTemperature, compareDate, sumTemperature, lines);
                mapCountInfixAVL(avl, averageTemperature);
                writeLinesAVL(out, avl, writeTemperature2, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readTemperature, compareDate, sumTemperature, lines);
                mapCountInfix(bst, averageTemperature);
                writeLinesBST(out, bst, writeTemperature2, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readTemperature, compareDate, sumTemperature, lines);
                mapCount(list, averageTemperature);
                writeLinesList(out, list, writeTemperature2, reversed);
            }
                break;

        }

    } else if(strcmp(argv[4], "t3") == 0) {
        switch(mode) {
            case AVL_MODE: {
            AVL *avl = readLinesAVL(file, readTemperature3, compareDateThenStation, ignore, lines);
            writeLinesAVL(out, avl, writeTemperature3, reversed);
            }
                break;
            case BST_MODE: {
            Tree *bst = readLinesBST(file, readTemperature3, compareDateThenStation, ignore, lines);
            writeLinesBST(out, bst, writeTemperature3, reversed);
            }
                break;
            case LIST_MODE: {
            DoubleLinkedList *list = readLinesList(file, readTemperature3, compareDateThenStation, ignore, lines);
            writeLinesList(out, list, writeTemperature3, reversed);
            }
                break;

        }

    } else if(strcmp(argv[4], "p1") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readPressure, compareStationID, reducePressure1, lines);
                mapCountInfixAVL(avl, averageStationPressure);
                writeLinesAVL(out, avl, writePressure1, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readPressure, compareStationID, reducePressure1, lines);
                mapCountInfix(bst, averageStationPressure);
                writeLinesBST(out, bst, writePressure1, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readPressure, compareStationID, reducePressure1, lines);
                mapCount(list, averageStationPressure);
                writeLinesList(out, list, writePressure1, reversed);
            }
                break;
        }
    } else if(strcmp(argv[4], "p2") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readPressure, compareDate, sumStationPressure, lines);
                mapCountInfixAVL(avl, averageStationPressure);
                writeLinesAVL(out, avl, writePressure2, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readPressure, compareDate, sumStationPressure, lines);
                mapCountInfix(bst, averageStationPressure);
                writeLinesBST(out, bst, writePressure2, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readPressure, compareDate, sumStationPressure, lines);
                mapCount(list, averageStationPressure);
                writeLinesList(out, list, writePressure2, reversed);
            }
                break;
        }
    } else if(strcmp(argv[4], "p3") == 0) {
        switch(mode) {
            case AVL_MODE: {
            AVL *avl = readLinesAVL(file, readPressure3, compareDateThenStation, ignore, lines);
            writeLinesAVL(out, avl, writePressure3, reversed);
            }
                break;
            case BST_MODE: {
            Tree *bst = readLinesBST(file, readPressure3, compareDateThenStation, ignore, lines);
            writeLinesBST(out, bst, writePressure3, reversed);
            }
                break;
            case LIST_MODE: {
            DoubleLinkedList *list = readLinesList(file, readPressure3, compareDateThenStation, ignore, lines);
            writeLinesList(out, list, writePressure3, reversed);
            }
                break;
        }
    } else if(strcmp(argv[4], "w") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readWind, compareStationID, sumWind, lines);
                mapCountInfixAVL(avl, averageWind);
                writeLinesAVL(out, avl, writeWind, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readWind, compareStationID, sumWind, lines);
                mapCountInfix(bst, averageWind);
                writeLinesBST(out, bst, writeWind, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readWind, compareStationID, sumWind, lines);
                mapCount(list, averageWind);
                writeLinesList(out, list, writeWind, reversed);
            }
                break;
        }
    } else if(strcmp(argv[4], "h") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readHeight, compareHeight, ignore, lines);
                writeLinesAVL(out, avl, writeHeight, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readHeight, compareHeight, ignore, lines);
                writeLinesBST(out, bst, writeHeight, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readHeight, compareHeight, ignore, lines);
                writeLinesList(out, list, writeHeight, reversed);
            }
                break;
        }
    } else if(strcmp(argv[4], "m") == 0) {
        switch(mode) {
            case AVL_MODE: {
                AVL *avl = readLinesAVL(file, readMoisture, compareStationIDDesc, maxMoisture, lines);
                writeLinesAVL(out, avl, writeMoisture, reversed);
            }
                break;
            case BST_MODE: {
                Tree *bst = readLinesBST(file, readMoisture, compareStationIDDesc, maxMoisture, lines);
                writeLinesBST(out, bst, writeMoisture, reversed);
            }
                break;
            case LIST_MODE: {
                DoubleLinkedList *list = readLinesList(file, readMoisture, compareStationIDDesc, maxMoisture, lines);
                writeLinesList(out, list, writeMoisture, reversed);
            }
                break;
        }

    } else {
        printf("arg: %s\n", argv[4]);
        error("Invalid argument !", WRONG_ARGUMENTS);
    }


    return 0;
}
