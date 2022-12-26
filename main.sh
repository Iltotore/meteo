#!/usr/bin/env bash
RUN_CMD=./app.out
COMPILE_CMD=make

read -r -d '' HELP_MSG << EOM
Usage: $0 <arguments>

Mandatory arguments:
  -f: The file path to read.

  Sorting:
    --avl: Using AVL
    --abr: Using BST
    --tab: Using a double linked list.

Columns (at least one must be passed):
  -t<mode>: Temperature. See below.
  -p<mode>: Pressure. See below.
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
  -d <min> <max>: Min and max dates using the format \`YYYY-MM-DD\`.

Miscellaneous:
  --help: Show this message.

EOM

if [ $# -eq 0 ] || [ "$1" == "--help" ]
then
  echo "$HELP_MSG"
fi