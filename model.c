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



