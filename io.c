#define _GNU_SOURCE 1
#include <stdio.h>
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
    int windDir;
    float windSpeed;
    float pi = acosf(-1);

    fscanf(file, "%d;%25c;%d;%f\n",&a.id,date,&windDir,&windSpeed);
    a.date = parseTime(date);
    *a.windX = cosf(windDir*pi/180)*windSpeed;
    *a.windY = sinf(windDir*pi/180)*windSpeed;

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

void writeTemperature1(FILE *file, WeatherRow row) { //TODO Order ?
    fprintf(file, "%d;%f;%f;%f\n", row.id, *row.temperature, *row.temperatureMin, *row.temperatureMax);
}

void writeTemperature2(FILE *file, WeatherRow row) {
    fprintf(file, "%d;%ld;%f\n", row.id, mktime(row.date), *row.temperature);
}

void writeTemperature3(FILE *file, int id, struct tm *date, int hours[24]) {
    fprintf(file, "%d;%ld", id, mktime(date));

    //TODO hours
    for(int h = 0; h < 23; h++) fprintf(file, ";%d", hours[h]);
}

void writePressure1(FILE *file, WeatherRow row);

void writePressure2(FILE *file, WeatherRow row);

void writePressure3(FILE *file, WeatherRow row);

void writeWind(FILE *file, WeatherRow row) {
    printf("%d;%f;%f;%f;%f\n", row.id, *row.coordX, *row.coordY, *row.windX, *row.windY);
}

void writeMoisture(FILE *file, WeatherRow row) {
    fprintf(file, "%f;%f;%d\n", *row.coordX, *row.coordY, *row.moisture);
}

void writeHeight(FILE *file, WeatherRow row) {
    fprintf(file, "%f;%f;%d\n", *row.coordX, *row.coordY, *row.height);
}