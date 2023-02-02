#include <stdio.h>
#include "model.h"

/**
 * Compares the station's ID of two WeatherRow
 */
Comparison compareStationID(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Greater;
    else return Less;
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
    if(a.date == b.date) return compareStationID(a, b);
    else if(a.date > b.date) return Greater;
    return Less;
}
/**
 * Compares the measure date of two WeatherRow 
 */
Comparison compareDate(WeatherRow a, WeatherRow b) {
    if(a.date == b.date) return Equal;
    else if(a.date > b.date) return Greater;
    return Less;
}
/**
 * Compares the station's pressure  of two WeatherRow and takes the maximum
 */
WeatherRow maxStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure > *b.stationPressure ? a : b ;
}
/**
 * Compares the station's pressure  of two WeatherRow and takes the minimum
 */
WeatherRow minStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure < *b.stationPressure ? a : b ;
}
/**
 * Sums two wind speed and direction
 */
WeatherRow sumWind(WeatherRow a, WeatherRow b){
    *a.windX += *b.windX;
    *a.windY += *b.windY;
    return a;
}
/**
 * Calculates the average of two wind speed and direction
 */
WeatherRow averageWind(int count, WeatherRow value){
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
 * Sums two temperatures
 */
WeatherRow sumTemperature(WeatherRow a, WeatherRow b) {
    *a.temperature += *b.temperature;
    return a;
}
/**
 *Calculates the average of two temperature
 */
WeatherRow averageTemperature(int count, WeatherRow value){
    *value.temperature /= count;
    return value;
}
/**
 * Returns min, max and sum (for average) of pressures
 */
WeatherRow reducePressure1(WeatherRow a, WeatherRow b) {
    *a.stationPressureMin = *a.stationPressureMin <= *b.stationPressureMin ? *a.stationPressureMin : *b.stationPressureMin;
    *a.stationPressureMax = *a.stationPressureMax >= *b.stationPressureMax ? *a.stationPressureMax : *b.stationPressureMax;
    *a.stationPressure += *b.stationPressure;
    return a;
}
/**
 * Sums two stationPressure
 */
WeatherRow sumStationPressure(WeatherRow a, WeatherRow b){
    *a.stationPressure += *b.stationPressure;
    return a;
}
/**
 *Calculates the average of two stationPressure
 */
WeatherRow averageStationPressure(int count, WeatherRow value){
    *value.stationPressure /= count;
    return value;
}
/**
 * Ignores the second row
*/
WeatherRow ignore(WeatherRow a, WeatherRow b){
    return a;
}
/**
*Creates an empty row
*/
WeatherRow emptyRow(){
    WeatherRow a;
    a.id=-1;
    a.date= NULL;
    a.seaPressure=NULL;
    a.windX=NULL;
    a.windY=NULL;
    a.moisture=NULL;
    a.stationPressure=NULL;
    a.stationPressureMin=NULL;
    a.stationPressureMax=NULL;
    a.pressureVariation=NULL;
    a.precipitation=NULL;
    a.coordX=NULL;
    a.coordY=NULL;
    a.temperature=NULL;
    a.temperatureMin=0;
    a.height=NULL;
    a.townCode=NULL;
    return a;

}
