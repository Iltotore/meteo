#include <stdbool.h>
#include <time.h>

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
    struct tm *date;
    float *seaPressure; //Pointer represent optional values (aka can be NULL)
    float *seaPressureMin;
    float *seaPressureMax;
    float *windX;
    float *windY;
    int *moisture;
    float *stationPressure;
    float *stationPressureMin;
    float *stationPressureMax;
    float *pressureVariation;
    int *precipitation;
    float *coordX;
    float *coordY;
    float *temperature;
    float *temperatureMin;
    float *temperatureMax;
    int *height;
    int *townCode;
} WeatherRow;

/**
 * The type of sorting chosen
 */
typedef enum {
    LIST_MODE, BST_MODE, AVL_MODE
} SortMode;

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
Comparison compareDate(WeatherRow a, WeatherRow b);

/**
 * Compares the measure date and station ID of two WeatherRow
 */
Comparison compareDateThenStation(WeatherRow a, WeatherRow b);


typedef void (*Callback)(WeatherRow);

typedef WeatherRow (*Reducer)(WeatherRow, WeatherRow);

/**
 * Compares two moistures and returns the greater
 */
WeatherRow maxMoisture(WeatherRow a, WeatherRow b);

typedef WeatherRow (*Mapper)(int, WeatherRow);

/**
 * Sums two wind speed and direction
 */
WeatherRow sumWind(WeatherRow a, WeatherRow b);

/**
 * Calculates the average of two wind speed and direction
 */
WeatherRow averageWind(int count, WeatherRow value);

/**
 * Returns min, max and sum (for average) of temperatures
 */
WeatherRow reduceTemperature1(WeatherRow a, WeatherRow b);

/**
 * Sums two temperatures
 */
WeatherRow sumTemperature(WeatherRow a, WeatherRow b);

/**
 *Calculates the average of two temperature
 */
WeatherRow averageTemperature(int count, WeatherRow value);

/**
 * Returns min, max and sum (for average) of pressures
 */
WeatherRow reducePressure1(WeatherRow a, WeatherRow b);

/**
 * Sums two stationPressure
 */
WeatherRow sumStationPressure(WeatherRow a, WeatherRow b);

/**
 *Calculates the average of two stationPressure
 */
WeatherRow averageStationPressure(int count, WeatherRow value);

/**
 * Ignores the second row
*/
WeatherRow ignore(WeatherRow a, WeatherRow b);
/**
*Creates an empty row
*/
WeatherRow emptyRow();



#endif