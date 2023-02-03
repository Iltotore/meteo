# Météo

This is the Pre ING 2 computer science project of semester 1 at CYTech, done by Raphaël FROMENTIN and Rachel EMESSIENE.

## Lancement

The main.sh program works as follows:

```
Usage: ./main.sh <arguments>

Mandatory arguments:
  -f: The file path to read.

  Sorting:
    --avl: Using AVL
    --abr: Using BST
    --tab: Using a double linked list.

Columns (at least one must be passed):
  -t <mode>: Temperature. See below.
  -p <mode>: Pressure. See below.
  -w: Average wind speed and direction by station number in ascending order.
  -m: Max moisture by station in descending order.
  -h: Height in descending order.

  Modes:
    1: Output min, max and average by station sorted by station number in ascending order.
    2: Output average by date/hour in chronological order.
    3: Order by time then by station number in ascending order.

Regions (optional, up to one):
  -F: France
  -G: French Guiana
  -S: Saint-Pierre and Miquelon
  -A: Antilles
  -O: Indian Ocean
  -Q: Antarctica

  -g <min> <max>: Min and max longitudes.
  -d <min> <max>: Min and max longitudes.

Date and time:
  -d <min> <max>: Min and max dates using the format `YYYY-MM-DD`.

Miscellaneous:
  --help: Show this message.
```

Example:
```sh
./main.sh -f météo.csv --avl -h -r -o wind.csv
./main.sh -f météo.csv --avl -t 1 -w -o wandt.csv
```
**⚠️ The Makefile only works under Linux**


**⚠️ Requiers `Make` et `GCC`**
