#include <stdio.h>
#include "model.h"

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
 * Read all lines and execute the given callback for each.
 *
 * @param callback the callback to consume for each WeatherRow.
 */
void readLines(FILE *file, Callback callback, Reader reader);

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

