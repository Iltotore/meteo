#define _GNU_SOURCE 1

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "io.h"
#include "model.h"
#include "util.h"

/**
 * Read a single CSV line.
 *
 * @param file the file to read.
 * @return a new WeatherRow instance built from the read data.
 */
WeatherRow readLine(FILE *file) {
    WeatherRow row; //TODO readLine
    row.id = 5;
    return row;
}

/**
 * Read all lines and add them to an AVL.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
AVL *readLinesAVL(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines) {
    AVL *avl = NULL;

    for(int i = 0; i < lines; i++) avl = insertAVL(avl, reader(file), comparator, reducer);

    return avl;
}

/**
 * Read all lines and add them to a BST.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
Tree *readLinesBST(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines) {
    Tree *tree = NULL;

    for(int i = 0; i < lines; i++) tree = insertBST(tree, reader(file), comparator, reducer);

    return tree;
}

/**
 * Read all lines and add them to a DoubleLinkedList.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
DoubleLinkedList *readLinesList(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines) {
    DoubleLinkedList *list = emptyList();

    for(int i = 0; i < lines; i++) list = insertOrd(list, reader(file), comparator, reducer);

    return list;
}

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param avl the entries to write
 * @param writer the writing logic
 */
void writeLinesAVL(FILE *file, AVL *avl, Writer writer, bool reversed) {
    if(avl != NULL) {
        writeLinesAVL(file, reversed ? avl->right : avl->left, writer, reversed);
        writer(file, avl->value);
        writeLinesAVL(file, reversed ? avl->left : avl->right, writer, reversed);
    }
}

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param tree the entries to write
 * @param writer the writing logic
 */
void writeLinesBST(FILE *file, Tree *tree, Writer writer, bool reversed) {
    if(tree != NULL) {
        writeLinesBST(file, reversed ? tree->right : tree->left, writer, reversed);
        writer(file, tree->value);
        writeLinesBST(file, reversed ? tree->left : tree->right, writer, reversed);
    }
}

void writeLinesCell(FILE *file, Cell *cell, Writer writer, bool reversed) {
    if(cell != NULL) {
        writer(file, cell->value);
        writeLinesCell(file, reversed ? cell->parent : cell->tail, writer, reversed);
    }
}

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param list the entries to write
 * @param writer the writing logic
 */
void writeLinesList(FILE *file, DoubleLinkedList *list, Writer writer, bool reversed) {
    writeLinesCell(file, reversed ? list->last : list->head, writer, reversed);
}

struct tm *parseTime(char *c) {
    struct tm *date = safeMalloc(sizeof(struct tm));
    strptime(c, "%FT%T%z", date);
    return date;
}

WeatherRow readTemperature(FILE *file) {
    printf("Reading temperature %d\n", feof(file));
    WeatherRow a = emptyRow();
    char date[26];
    a.temperatureMax = safeMalloc(sizeof(float));
    a.temperatureMin = safeMalloc(sizeof(float));
    a.temperature = safeMalloc(sizeof(float));
    fscanf(file, "%d;%25c;%f;%f;%f\n", &a.id, date, a.temperature, a.temperatureMax, a.temperatureMin);
    a.date = parseTime(date);
    return a;
}

WeatherRow readPressure(FILE *file) {
    WeatherRow a = emptyRow();
    char date[26];
    a.seaPressure = safeMalloc(sizeof(int));
    a.seaPressureMax = safeMalloc(sizeof(int));
    a.seaPressureMin = safeMalloc(sizeof(int));
    a.stationPressure = safeMalloc(sizeof(int));
    fscanf(file, "%d;%25c;%d;%d\n", &a.id, date, a.seaPressure, a.stationPressure);
    *a.seaPressureMin = *a.seaPressure;
    *a.seaPressureMax = *a.seaPressure;
    *a.stationPressureMin = *a.stationPressure;
    *a.stationPressureMax = *a.stationPressure;
    a.date = parseTime(date);
    return a;
}

WeatherRow readWind(FILE *file) {
    WeatherRow a = emptyRow();
    char date[26];
    int windDir;
    float windSpeed;
    float pi = acosf(-1);

    a.windX = safeMalloc(sizeof(float));
    a.windY = safeMalloc(sizeof(float));
    a.coordX = safeMalloc(sizeof(float));
    a.coordY = safeMalloc(sizeof(float));

    fscanf(file, "%d;%25c;%d;%f;%f,%f\n", &a.id, date, &windDir, &windSpeed, a.coordX, a.coordY);
    a.date = parseTime(date);
    *a.windX = cosf(windDir * pi / 180) * windSpeed;
    *a.windY = sinf(windDir * pi / 180) * windSpeed;

    return a;
}

WeatherRow readMoisture(FILE *file) {
    WeatherRow a = emptyRow();
    a.moisture = safeMalloc(sizeof(int));
    a.coordX = safeMalloc(sizeof(float));
    a.coordY = safeMalloc(sizeof(float));
    fscanf(file, "%d;%d;%f,%f\n", &a.id, a.moisture, a.coordX, a.coordY);
    return a;
}

WeatherRow readHeight(FILE *file) {
    WeatherRow a = emptyRow();
    a.height = safeMalloc(sizeof(int));
    a.coordX = safeMalloc(sizeof(float));
    a.coordY = safeMalloc(sizeof(float));
    fscanf(file, "%d;%f,%f;%d\n", &a.id, a.coordX, a.coordY, a.height);
    return a;
}

void writeTemperature1(FILE *file, WeatherRow row) { //TODO Order ?
    fprintf(file, "%d;%f;%f;%f\n", row.id, *row.temperature, *row.temperatureMin, *row.temperatureMax);
}

void writeTemperature2(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%ld;%f\n", row.id, mktime(row.date), *row.temperature);
}

void writeTemperature3AVL(FILE *file, AVL *avl) {
//
//
//    fprintf(file, "%d;%ld", id, mktime(date));
//
//    //TODO hours
//    for(int h = 0; h < 23; h++) fprintf(file, ";%d", hours[h]);
}

void writePressure1(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%d;%d;%d\n", row.id, *row.stationPressure, *row.stationPressureMin, *row.stationPressureMax);
}

void writePressure2(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%ld;%d\n", row.id, mktime(row.date), *row.stationPressure);
}

void writePressure3(FILE *file, WeatherRow row) {}

void writeWind(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%f;%f;%f;%f\n", row.id, *row.coordX, *row.coordY, *row.windX, *row.windY);
}

void writeMoisture(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%f;%f;%d\n", row.id, *row.coordX, *row.coordY, *row.moisture);
}

void writeHeight(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%f;%f;%d\n", row.id, *row.coordX, *row.coordY, *row.height);
}