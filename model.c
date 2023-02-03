#include <stdio.h>
#include "model.h"
#include "util.h"

/**
 * Compares the station's ID of two WeatherRow
 */
Comparison compareStationID(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Greater;
    else return Less;
}

/**
 * Compares the station's ID of two WeatherRow in descending order
 */
Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

/**
 * Compares the height of two WeatherRow
 */
Comparison compareHeight(WeatherRow a, WeatherRow b) {
    if(*a.height == *b.height) return compareStationID(a, b);
    else if(*a.height > *b.height) return Less;
    return Greater;
}

/**
 * Compares the moisture of two WeatherRow
 */
Comparison compareMoisture(WeatherRow a, WeatherRow b) {
    if(*a.moisture == *b.moisture) return Equal;
    else if(*a.moisture > *b.moisture) return Less;
    return Greater;
}

/**
 * Compares the measure date and station ID of two WeatherRow
 */
Comparison compareDateThenStation(WeatherRow a, WeatherRow b) {
    Comparison compDate = compareDate(a, b);
    return compDate == Equal ? compareStationID(a, b) : compDate;
}

int compareInts(int a, int b) {
    if(a == b) return Equal;
    else if(a > b) return Greater;
    else return Less;
}

Comparison compareTm(struct tm *a, struct tm *b) {
    Comparison compYear = compareInts(a->tm_year, b->tm_year);
    if(compYear == Equal) {
        Comparison compDay = compareInts(a->tm_yday, b->tm_yday);
        if(compDay == Equal) {
            Comparison compHour = compareInts(a->tm_hour, b->tm_hour);
            if(compHour == Equal) {
                Comparison compMin = compareInts(a->tm_min, b->tm_min);
                if(compMin == Equal) return compareInts(a->tm_sec, b->tm_sec);
                else return compMin;
            } else return compHour;
        } else return compDay;
    } else return compYear;
}

/**
 * Compares the measure date of two WeatherRow 
 */
Comparison compareDate(WeatherRow a, WeatherRow b) {
    return compareTm(a.date, b.date);
}

/**
 * Compares the measure day of two WeatherRow
*/
Comparison compareDayThenID(WeatherRow a, WeatherRow b) {
    if(a.date->tm_year == b.date->tm_year) {
        if(a.date->tm_yday == b.date->tm_yday) return compareStationID(a, b);
        else if(a.date->tm_yday > b.date->tm_yday) return Greater;
        else return Less;
    } else if(a.date->tm_year > b.date->tm_year) return Greater;
    return Less;
}

/**
 * Compares the station's pressure  of two WeatherRow and takes the maximum
 */
WeatherRow maxStationPressure(WeatherRow a, WeatherRow b) {
    return *a.stationPressure > *b.stationPressure ? a : b;
}

/**
 * Compares the station's pressure  of two WeatherRow and takes the minimum
 */
WeatherRow minStationPressure(WeatherRow a, WeatherRow b) {
    return *a.stationPressure < *b.stationPressure ? a : b;
}

/**
 * Compares two moistures and returns the greater
 */
WeatherRow maxMoisture(WeatherRow a, WeatherRow b) {
    return *a.moisture >= *b.moisture ? a : b;
}

/**
 * Sums two wind speed and direction
 */
WeatherRow sumWind(WeatherRow a, WeatherRow b) {
    *a.windX += *b.windX;
    *a.windY += *b.windY;
    return a;
}

/**
 * Calculates the average of two wind speed and direction
 */
WeatherRow averageWind(int count, WeatherRow value) {
    *value.windX /= count;
    *value.windY /= count;
    return value;
}

/**
 * Returns min, max and sum (for average) of temperatures
 */
WeatherRow reduceTemperature1(WeatherRow a, WeatherRow b) {
    *a.temperatureMin = *a.temperatureMin <= *b.temperatureMin ? *a.temperatureMin : *b.temperatureMin;
    *a.temperatureMax = *a.temperatureMax >= *b.temperatureMax ? *a.temperatureMax : *b.temperatureMax;
    *a.temperature += *b.temperature;
    return a;
}

/**
 * Concatenantes hours of two temperature of the same date
*/
WeatherRow reduceTemperature3(WeatherRow a, WeatherRow b) {
    int aHour = a.date->tm_hour;
    int lastHour = b.date->tm_hour;

    for(int i = aHour + 1; i <= lastHour; i++) {
        a.hours[i] = *a.temperature;
    }

    a.hours[lastHour] = *b.temperature;

    return a;
}

/**
 * Concatenantes hours of two pressures of the same date
*/
WeatherRow reducePressure3(WeatherRow a, WeatherRow b) {
    int aHour = a.date->tm_hour;
    int lastHour = b.date->tm_hour;

    for(int i = aHour + 1; i <= lastHour; i++) {
        a.hours[i] = *a.stationPressure;
    }

    a.hours[lastHour] = *b.stationPressure;

    return a;
}

/**
 * Sums two temperatures
 */
WeatherRow sumTemperature(WeatherRow a, WeatherRow b) {
    *a.temperature += *b.temperature;
    return a;
}

/**
 *Calculates the average of two temperature
 */
WeatherRow averageTemperature(int count, WeatherRow value) {
    *value.temperature /= count;
    return value;
}

/**
 * Returns min, max and sum (for average) of pressures
 */
WeatherRow reducePressure1(WeatherRow a, WeatherRow b) {
    *a.stationPressureMin =
            *a.stationPressureMin <= *b.stationPressureMin ? *a.stationPressureMin : *b.stationPressureMin;
    *a.stationPressureMax =
            *a.stationPressureMax >= *b.stationPressureMax ? *a.stationPressureMax : *b.stationPressureMax;
    *a.stationPressure += *b.stationPressure;
    return a;
}

/**
 * Sums two stationPressure
 */
WeatherRow sumStationPressure(WeatherRow a, WeatherRow b) {
    *a.stationPressure += *b.stationPressure;
    return a;
}

/**
 *Calculates the average of two stationPressure
 */
WeatherRow averageStationPressure(int count, WeatherRow value) {
    *value.stationPressure /= count;
    return value;
}

/**
 * Ignores the second row
*/
WeatherRow ignore(WeatherRow a, WeatherRow b) {
    return a;
}

/**
*Creates an empty row
*/
WeatherRow emptyRow() {
    WeatherRow a;
    a.id = -1;
    a.date = NULL;
    a.seaPressure = NULL;
    a.seaPressureMin = NULL;
    a.seaPressureMax = NULL;
    a.windX = NULL;
    a.windY = NULL;
    a.moisture = NULL;
    a.stationPressure = NULL;
    a.stationPressureMin = NULL;
    a.stationPressureMax = NULL;
    a.pressureVariation = NULL;
    a.precipitation = NULL;
    a.coordX = NULL;
    a.coordY = NULL;
    a.temperature = NULL;
    a.temperatureMin = NULL;
    a.height = NULL;
    a.townCode = NULL;
    a.hours = safeMalloc(sizeof(float) * 24);
    for(int i = 0; i < 24; i++) a.hours[i] = 0;
    return a;
}