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

 Comparison compareMoisture(WeatherRow a, WeatherRow b){
    if(*a.height == *b.height) return Equal; 
    else if (*a.height > *b.height) return Less;
    return Greater;
 } 

 Comparison compareTime3(WeatherRow a, WeatherRow b){
    if(a.date == b.date) return compareStationID(a,b) ;
    else if (a.date > b.date) return Greater;
    return Less;
 }

  Comparison compareTime2(WeatherRow a, WeatherRow b){
    if(a.date == b.date) return Equal;
    else if (a.date > b.date) return Greater;
    return Less;
 }