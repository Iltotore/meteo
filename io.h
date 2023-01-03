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


#endif

