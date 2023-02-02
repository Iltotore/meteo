#include <stdio.h>
#include "model.h"


Comparison compareStationID(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Greater;
    else return Less;
}

Comparison compareHeight(WeatherRow a, WeatherRow b) {
    if(*a.height == *b.height) return compareStationID(a, b);
    else if(*a.height > *b.height) return Less;
    return Greater;
}

Comparison compareMoisture(WeatherRow a, WeatherRow b) {
    if(*a.moisture == *b.moisture) return Equal;
    else if(*a.moisture > *b.moisture) return Less;
    return Greater;
}

Comparison compareDateThenStation(WeatherRow a, WeatherRow b) {
    if(a.date == b.date) return compareStationID(a, b);
    else if(a.date > b.date) return Greater;
    return Less;
}

Comparison compareDate(WeatherRow a, WeatherRow b) {
    if(a.date == b.date) return Equal;
    else if(a.date > b.date) return Greater;
    return Less;
}

WeatherRow maxStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure > *b.stationPressure ? a : b ;
}

WeatherRow minStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure < *b.stationPressure ? a : b ;
}

WeatherRow sumWind(WeatherRow a, WeatherRow b){
    *a.windX += *b.windX;
    *a.windY += *b.windY;
    return a;
}

WeatherRow averageWind(int count, WeatherRow value){
    *value.windX /= count;
    *value.windY /= count;
    return value;
}

WeatherRow reduceTemperature1(WeatherRow a, WeatherRow b) {
    *a.temperatureMin = *a.temperatureMin <= *b.temperatureMin ? *a.temperatureMin : *b.temperatureMin;
    *a.temperatureMax = *a.temperatureMax >= *b.temperatureMax ? *a.temperatureMax : *b.temperatureMax;
    *a.temperature += *b.temperature;
    return a;
}

WeatherRow sumTemperature(WeatherRow a, WeatherRow b) {
    *a.temperature += *b.temperature;
    return a;
}

WeatherRow averageTemperature(int count, WeatherRow value){
    *value.temperature /= count;
    return value;
}

WeatherRow reducePressure1(WeatherRow a, WeatherRow b) {
    *a.stationPressureMin = *a.stationPressureMin <= *b.stationPressureMin ? *a.stationPressureMin : *b.stationPressureMin;
    *a.stationPressureMax = *a.stationPressureMax >= *b.stationPressureMax ? *a.stationPressureMax : *b.stationPressureMax;
    *a.stationPressure += *b.stationPressure;
    return a;
}

WeatherRow sumStationPressure(WeatherRow a, WeatherRow b){
    *a.stationPressure += *b.stationPressure;
    return a;
}

WeatherRow averageStationPressure(int count, WeatherRow value){
    *value.stationPressure /= count;
    return value;
}

WeatherRow ignore(WeatherRow a, WeatherRow b){
    return a;
}

WeatherRow emptyRow(){
    WeatherRow a;
    a.id=-1;
    a.date= NULL;
    a.seaPressure=NULL;
    a.windX=NULL;
    a.windY=NULL;
    a.moisture=NULL;
    a.stationPressure=NULL;
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
