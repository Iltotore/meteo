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
AVL *readLinesAVL(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines);

/**
 * Read all lines and add them to an BST.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
Tree *readLinesBST(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines);

/**
 * Read all lines and add them to a DoubleLinkedList.
 *
 * @param reader the line reading logic.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 */
DoubleLinkedList *readLinesList(FILE *file, Reader reader, Comparator comparator, Reducer reducer, int lines);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param avl the entries to write
 * @param writer the writing logic
 */
void writeLinesAVL(FILE *file, AVL *avl, Writer writer, bool reversed);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param bst the enties to write
 * @param writer the writing logic
 */
void writeLinesBST(FILE *file, Tree *tree, Writer writer, bool reversed);

/**
 * Write all entries to a file.
 *
 * @param file the file to write into.
 * @param list the entries to write
 * @param writer the writing logic
 */
void writeLinesList(FILE *file, DoubleLinkedList *list, Writer writer, bool reversed);

/**
*Reads temperature min/max/current column 
*/
WeatherRow readTemperature(FILE *file);

/**
 * Reads temperature column
*/
WeatherRow readTemperature3(FILE *file);

/**
*Reads pressure min/max/current columns 
*/
WeatherRow readPressure(FILE *file);

/**
*Reads pressure column 
*/
WeatherRow readPressure3(FILE *file);

/**
*Reads wind's column 
*/
WeatherRow readWind(FILE *file);

/**
*Reads moisture's column 
*/
WeatherRow readMoisture(FILE *file);

/**
*Reads height's column 
*/
WeatherRow readHeight(FILE *file);

/**
*Writes temperature's column in the file according to mode 1
*/
void writeTemperature1(FILE *file, WeatherRow row);

/**
*Writes temperature's column in the file according to mode 2
*/
void writeTemperature2(FILE *file, WeatherRow row);

/**
 * Writes temperature's column in the file according to mode 3
*/
void writeTemperature3(FILE *file, WeatherRow row);

/**
*Writes pressure's column in the file according to mode 1
*/
void writePressure1(FILE *file, WeatherRow row);

/**
*Writes pressure's column in the file according to mode 2
*/
void writePressure2(FILE *file, WeatherRow row);

/**
*Writes pressure's column in the file according to mode 3
*/
void writePressure3(FILE *file, WeatherRow row);

/**
*Writes pressure's column in the file in a gnuplot-friendly format
*/
void writeMode3Plot(FILE *file, WeatherRow row);


/**
*Writes wind's column in the file
*/
void writeWind(FILE *file, WeatherRow row);

/**
*Writes moisture's column in the file 
*/
void writeMoisture(FILE *file, WeatherRow row);

/**
*Writes height's column in the file
*/
void writeHeight(FILE *file, WeatherRow row);

#endif

