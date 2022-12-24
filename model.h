#include <stdbool.h>
#include "time.h"

#ifndef METEO_MODEL_H
#define METEO_MODEL_H

/**
 * A row from weather dataset.
 *
 * @param id the station OMM ID.
 * @param date the date when this record was taken.
 * @param seaPressure the pressure at sea level.
 * @param windDirection the direction of the wind in degrees.
 * @param windSpeed the wind speed.
 * @param moisture the moisture, between 0 and 100.
 * @param stationPressure the pressure at the station.
 * @param pressureVariation the pressure variation since the last 24 hours (percentage).
 * @param precipitation the precipitation since the last 24 hours.
 * @param coordX the x coordinate where this measure was taken.
 * @param coordY the y coordinate where this measure was taken.
 * @param temperature the measured temperature in Celsius.
 * @param temperatureMin the lowest temperature since the last 24 hours.
 * @param temperatureMax the highest temperature since the last 24 hours.
 * @param height the station height in meters.
 * @param townCode the code of this station's commune.
 */
typedef struct {
    int id;
    time_t date;
    int *seaPressure; //Pointer represent optional values (aka can be NULL)
    int *windDirection;
    float *windSpeed;
    int *moisture;
    int *stationPressure;
    float *pressureVariation;
    int *precipitation;
    float coordX;
    float coordY;
    float *temperature;
    float *temperatureMin;
    float *temperatureMax;
    int *height;
    int townCode;
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

/**
 * Compares the station's ID of two WeatherRow
 */

Comparison compareStationID(WeatherRow a, WeatherRow b);

/**
 * Compares the height of two WeatherRow
 */

Comparison compareHeight(WeatherRow a, WeatherRow b);

/**
 * Compares the moisture of two WeatherRow
 */
Comparison compareMoisture(WeatherRow a, WeatherRow b);

/**
 * Compares the measure date of two WeatherRow
 */
Comparison compareTime3(WeatherRow a, WeatherRow b);

Comparison compareTime2(WeatherRow a, WeatherRow b);

typedef void (*Callback)(WeatherRow);

typedef WeatherRow (*Reducer)(WeatherRow, WeatherRow);

typedef WeatherRow (*Mapper)(int, WeatherRow);

#endif