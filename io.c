#define _GNU_SOURCE 1
#include <stdio.h>
#include <time.h>
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
 * Read all lines and execute the given callback for each.
 *
 * @param callback the callback to consume for each WeatherRow.
 */
void readLines(FILE *file, Callback callback, Reader reader) {
    while(!feof(file)) {
        callback(readLine(file));
    }
}

struct tm *parseTime(char* c){
    struct tm *date = safeMalloc(sizeof(struct tm));
    strptime(c, "%FT%T%z", date);
    return date;
}

WeatherRow readTemperature(FILE *file){
    WeatherRow a=emptyRow();
    char date[26];
    fscanf(file, "%d;%25c;%f;%f;%f\n",&a.id,date,a.temperature,a.temperatureMax,a.temperatureMin);
    a.date= parseTime(date);
    return a;
}

WeatherRow readPressure(FILE *file){
   WeatherRow a=emptyRow();
   char date[26];
   fscanf(file, "%d;%25c;%d;%d\n",&a.id,date,a.seaPressure,a.stationPressure);
   a.date= parseTime(date);
   return a;
}

WeatherRow readWind(FILE *file){
   WeatherRow a=emptyRow();
   char date[26];
   fscanf(file, "%d;%25c;%d;%f\n",&a.id,date,a.windDirection,a.windSpeed);
   a.date= parseTime(date);
   return a;
}

WeatherRow readMoisture(FILE *file){
   WeatherRow a=emptyRow();
   char date[26];
   fscanf(file, "%d;%25c;%d\n",&a.id,date,a.moisture);
   a.date= parseTime(date);
   return a;
}

WeatherRow readHeight(FILE *file){
    WeatherRow a=emptyRow();
   char date[26];
   fscanf(file, "%d;%25c;%d\n",&a.id,date,a.height);
   a.date= parseTime(date);
   return a;
}
