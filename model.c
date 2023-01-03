#include <stdio.h>
#include "model.h"


Comparison compareStationID(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Greater;
    else return Less;
}

Comparison compareHeight(WeatherRow a, WeatherRow b) {
    if(*a.height == *b.height) return Equal;
    else if(*a.height > *b.height) return Less;
    return Greater;
}

Comparison compareMoisture(WeatherRow a, WeatherRow b) {
    if(*a.height == *b.height) return Equal;
    else if(*a.height > *b.height) return Less;
    return Greater;
}

Comparison compareTime3(WeatherRow a, WeatherRow b) {
    if(a.date == b.date) return compareStationID(a, b);
    else if(a.date > b.date) return Greater;
    return Less;
}

Comparison compareTime2(WeatherRow a, WeatherRow b) {
    if(a.date == b.date) return Equal;
    else if(a.date > b.date) return Greater;
    return Less;
}

WeatherRow maxTemperature(WeatherRow a, WeatherRow b){
    return *a.temperature > *a.temperature ? a : b ;
}

WeatherRow minTemperature(WeatherRow a, WeatherRow b){
    return *a.temperature < *a.temperature ? a : b ;
}

WeatherRow maxTemperaturemax(WeatherRow a, WeatherRow b){
    return *a.temperatureMax > *b.temperatureMax ? a : b ;
}

WeatherRow minTemperatureMax(WeatherRow a, WeatherRow b){
    return *a.temperatureMax < *b.temperatureMax ? a : b ;
}
WeatherRow maxTemperatureMin(WeatherRow a, WeatherRow b){
    return *a.temperatureMin > *b.temperatureMin ? a : b ;
}

WeatherRow minTemperatureMin(WeatherRow a, WeatherRow b){
     return a.temperatureMin < b.temperatureMin ? a : b;
}

WeatherRow maxStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure > *b.stationPressure ? a : b ;
}

WeatherRow minStationPressure(WeatherRow a, WeatherRow b){
    return *a.stationPressure < *b.stationPressure ? a : b ;
}


WeatherRow sumWindSpeed(WeatherRow a, WeatherRow b){
      WeatherRow result = a;
    *a.windSpeed += *b.windSpeed;
    return result;
}

WeatherRow averageWindSpeed(int count, WeatherRow value){
      WeatherRow result = value;
    *result.windSpeed /= count;
    return result;
}

WeatherRow sumWindDirection(WeatherRow a, WeatherRow b){
     WeatherRow result = a;
    *a.windDirection += *b.windDirection;
    return result;
}

WeatherRow averageWindDirection(int count, WeatherRow value){
    WeatherRow result = value;
    *result.windDirection /= count;
    return result;
    
}

WeatherRow sumTemperature(WeatherRow a, WeatherRow b){
    WeatherRow result = a;
    *a.temperature += *b.temperature;
    return result;
}

WeatherRow averageTemperature(int count, WeatherRow value){
    WeatherRow result = value;
    *result.temperature /= count;
    return result;
}

WeatherRow sumTemparatureMax(WeatherRow a, WeatherRow b){
    WeatherRow result = a;
    *a.temperatureMax += *b.temperatureMax;
    return result;
}

WeatherRow averageTemperatureMax(int count, WeatherRow value){
    WeatherRow result = value;
    *result.temperatureMax /= count;
    return result;
}

WeatherRow sumTemparatureMin(WeatherRow a, WeatherRow b){
    WeatherRow result = a;
    *a.temperatureMin += *b.temperatureMin;
    return result;

}

WeatherRow averageTemperatureMin(int count, WeatherRow value){
     WeatherRow result = value;
    *result.temperatureMin /= count;
    return result;
}

WeatherRow sumStationPressure(WeatherRow a, WeatherRow b){
    WeatherRow result = a;
    *a.stationPressure += *b.stationPressure;
    return result;
}

WeatherRow averageStationPressure(int count, WeatherRow value){
    WeatherRow result = value;
    *result.stationPressure /= count;
    return result;    
}

WeatherRow emptyRow(){
    WeatherRow a;
    a.id=-1;
    a.date= NULL;
    a.seaPressure=NULL;
    a.windDirection=NULL;
    a.windSpeed=NULL;
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
