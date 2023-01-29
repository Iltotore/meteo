#include <stdio.h>
#include "model.h"
#include "avl.h"
#include "tree.h"
#include "doublelinkedlist.h"

#ifndef METEO_IO_H
#define METEO_IO_H

/**
 * Read a single CSV line.
 *
 * @param file the file to read.
 * @return a new WeatherRow instance built from the read data.
 */
typedef WeatherRow (*Reader)(FILE *file);

/**
 * Write a single CSV line.
 *
 * @param file the file to write into.
 * @return a new WeatherRow instance built from the read data.
 */
typedef void (*Writer)(FILE *file, WeatherRow row);

/**
 * Read all lines and add them to an AVL.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
AVL *readLinesAVL(FILE *file, Reader reader, Comparator comparator, Reducer reducer);

/**
 * Read all lines and add them to an BST.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
Tree *readLinesBST(FILE *file, Reader reader, Comparator comparator, Reducer reducer);

/**
 * Read all lines and add them to a DoubleLinkedList.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
DoubleLinkedList *readLinesList(FILE *file, Reader reader, Comparator comparator, Reducer reducer);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param avl the enties to write
 */
void writeLinesAVL(FILE *file, AVL *avl);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param bst the enties to write
 */
void writeLinesBST(FILE *file, Tree *tree);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param list the enties to write
 */
void writeLinesList(FILE *file, DoubleLinkedList *list);

WeatherRow readTemperature(FILE *file);

WeatherRow readPressure(FILE *file);

WeatherRow readWind(FILE *file);

WeatherRow readMoisture(FILE *file);

WeatherRow readHeight(FILE *file);

void writeTemperature1(FILE *file, WeatherRow row);

void writeTemperature2(FILE *file, WeatherRow row);

void writeTemperature3(FILE *file, int id, struct tm *date, int hours[24]);

void writePressure1(FILE *file, WeatherRow row);

void writePressure2(FILE *file, WeatherRow row);

void writePressure3(FILE *file, WeatherRow row);

void writeWind(FILE *file, WeatherRow row);

void writeMoisture(FILE *file, WeatherRow row);

void writeHeight(FILE *file, WeatherRow row);

#endif

