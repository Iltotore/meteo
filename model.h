#ifndef METEO_MODEL_H
#define METEO_MODEL_H

typedef struct {
    int id;
} WeatherRow;

/**
 * The result of a comparison between two values
 */
typedef enum {
    Greater = 1, //a > b
    Equal = 0, //a == b
    Less = -1 //a < b
} Comparison;

typedef Comparison (*Comparator)(WeatherRow, WeatherRow);

#endif
