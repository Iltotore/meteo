#include <stdio.h>
#include "io.h"
#include "model.h"

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
 * Read all lines and execute the given callback for each.
 *
 * @param callback the callback to consume for each WeatherRow.
 */
void readLines(FILE *file, Callback callback, Reader reader) {
    while(!feof(file)) {
        callback(readLine(file));
    }
}

WeatherRow readTemperature(FILE *file){
    WeatherRow a=emptyRow();
    char date[26];
    fscanf(file, "%d;%25c;%f;%f;%f\n",&a.id,date,a.temperature,a.temperatureMax,a.temperatureMin);
   // *a.date=;
   return a;
}

WeatherRow readPressure(FILE *file){
    return emptyRow();
}

WeatherRow readWind(FILE *file){
    return emptyRow();
}

WeatherRow readMoisture(FILE *file){
    return emptyRow();
}

WeatherRow readHeight(FILE *file){
    return emptyRow();
}