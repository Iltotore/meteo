#!/usr/bin/env bash
run_cmd=./app.out
compile_cmd=make

filter_columns() {
  file="$1"
  columns="$2"

  cut "$file" -d ";" -f "$columns"
}

show_help() {
  echo "$help_msg"
  exit $1
}

wrong_usage() {
  echo "Wrong usage: $1"
  echo ""
  show_help 1
}

set_latitude() {

  if [[ -v longitude ]]
  then
    wrong_usage "Latitude cannot be set multiple times"
  fi

  latitude=["$1" "$2"]
}

set_longitude() {

  if [[ -v longitude ]]
  then
    wrong_usage "Longitude cannot be set multiple times"
  fi

  longitude=["$1" "$2"]
}

set_region() {

  if [[ -v region ]]
  then
    wrong_usage "Only a single region should be specified"
  fi

  if [[ -v latitude || -v longitude ]]
  then
    wrong_usage "Cannot use region and -g/-a together"
  fi

  set_latitude "$1" "$2"
  set_longitude "$3" "$4"
}

read -r -d '' help_msg << EOM
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

if [ $# -eq 0 ]
then
  show_help 1
fi

while [[ $# -gt 0 ]]
do
  case "$1" in
    # Help
    --help)
      show_help 0
      ;;

    # Mandatory
    -f|--input)
      input="$2"
      shift
      ;;

    -o|--output)
      output="$2"
      shift
      ;;

    # Misc optional
    -r)
      reverse=""
      ;;

    # Columns
    -t)
      temperature="$2"
      shift
      ;;

    -p)
      pressure="$2"
      shift
      ;;

    -w)
      wind=""
      ;;

    -m)
      moisture=""
      ;;

    -h)
      height=""
      ;;

    # Regions
    # TODO coords
    -F)
      set_region 0 0 0 0
      ;;

    -G)
      set_region 0 0 0 0
      ;;

    -S)
      set_region 0 0 0 0
      ;;

    -A)
      set_region 0 0 0 0
      ;;

    -O)
      set_region 0 0 0 0
      ;;

    -Q)
      set_region 0 0 0 0
      ;;

    -g)
      set_longitude "$2" "$3"
      shift
      shift
      ;;

    -a)
      set_latitude "$2" "$3"
      shift
      shift
      ;;

  esac
  shift
done

if [[ ! -v input ]]
then
  wrong_usage "Missing argument -f"
fi

if [[ ! -v output ]]
then
  wrong_usage "Missing argument -o"
fi
