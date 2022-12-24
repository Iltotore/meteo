#include "stdio.h"
#include "doublelinkedlist.h"
#include "tree.h"
#include "avl.h"
#include "stdlib.h"
#include "time.h"
#include "model.h"

void printRow(WeatherRow row) {
    printf("id: %d, wind: %f\n", row.id, *row.windSpeed);
}

Comparison compareStationIDDesc(WeatherRow a, WeatherRow b) {
    if(a.id == b.id) return Equal;
    else if(a.id > b.id) return Less;
    else return Greater;
}

WeatherRow maxMoisture(WeatherRow a, WeatherRow b) {
    return *a.moisture >= *b.moisture ? a : b;
}

WeatherRow sumWindSpeed(WeatherRow a, WeatherRow b) {
    WeatherRow result = a;
    *a.windSpeed += *b.windSpeed;
    return result;
}

WeatherRow averageWindSpeed(int count, WeatherRow value) {
    WeatherRow result = value;
    *result.windSpeed /= count;
    return result;
}

int main() {

    srand(time(NULL));



    return 0;
}