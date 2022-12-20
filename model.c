#include "model.h"

Comparison compareStationID(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Greater;
    else return Less;
}

Comparison compareHeight(WeatherRow a, WeatherRow b){
    if(*a.height == *b.height) return Equal; 
    else if (*a.height > *b.height) return Less;
    return Greater;
 } 