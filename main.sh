#!/usr/bin/env bash
executed="$0"
run_cmd=./app.out
compile_cmd=make

filter_columns() {
  file="$1"
  columns="$2"

  cut "$file" -d ";" -f "$columns"
}

filter_coords() {
  filter='1'
  if [[ -v latitude ]]
  then
    filter="$filter && \$10 >= ${latitude[0]} && \$10 <= ${longitude[1]}"
  fi
  if [[ -v longitude ]]
  then
    filter="$filter && \$11 >= ${latitude[0]} && \$11 <= ${latitude[1]}"
  fi

  result=$(head "$input" | awk "$filter" FS='[;,]')
  echo "$result"
}

show_help() {
  echo "$help_msg"
  exit "$1"
}

wrong_usage() {
  echo -e "\e[31mWrong usage: $1\e[0m"
  echo "Use $executed --help for further information"
  exit 1
}

not_empty() {
  if [[ -z "$2" ]]
  then
    wrong_usage "$1 option should not be empty"
  fi
}

valid_mode() {
  not_empty "$1" "$2"

  if [[ "$2" -ne 1 && "$2" -ne 2 && "$2" -ne 3 ]]
  then
    wrong_usage "Invalid mode '$2' for option $1. Should be 1, 2 or 3"
  fi
}

set_latitude() {

  if [[ -v region ]]
  then
    wrong_usage "Cannot use region and -g/-a together"
  fi

  if [[ -v longitude ]]
  then
    wrong_usage "Latitude cannot be set multiple times"
  fi

  latitude=("$1" "$2")
}

set_longitude() {

  if [[ -v region ]]
  then
    wrong_usage "Cannot use region and -g/-a together"
  fi

  if [[ -v longitude ]]
  then
    wrong_usage "Longitude cannot be set multiple times"
  fi


  longitude=("$1" "$2")
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

  region=""
}

check_var() {

  if [[ -v "$2" ]]
  then
    wrong_usage "Argument $1 cannot be set multiple times"
  fi

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
      check_var "-f/--input" "input"
      not_empty "-f" "$2"
      input="$2"
      shift
      ;;

    -o|--output)
      check_var "-o/--output" "output"
      not_empty "-o" "$2"
      output="$2"
      shift
      ;;

    # Misc optional
    -r|--reverse)
      check_var "-r/--reverse" "reverse"
      reverse=""
      ;;

    # Columns
    -t)
      check_var "-t" "temperature"
      valid_mode "-t" "$2"
      temperature="$2"
      shift
      ;;

    -p)
      check_var "-p" "pressure"
      valid_mode "-p" "$2"
      pressure="$2"
      shift
      ;;

    -w)
      check_var "-w" "wind"
      wind=""
      ;;

    -m)
      check_var "-m" "moisture"
      moisture=""
      ;;

    -h)
      check_var "-h" "height"
      height=""
      ;;

    # Regions
    -F)
      set_region '-1.846217' '43.347901' '3.913466' '50.589122'
      ;;

    -G)
      set_region '-54.509905' '2.227946' '-51.445417' '5.489382'
      ;;

    -S)
      set_region '-56.436296' '46.733125' '-56.128474' '47.125133'
      ;;

    -A)
      set_region '-61.829015' '14.385966' '-60.839586' '16.545873'
      ;;

    -O)
      set_region '45.737867' '-57.545313' '97.803858' '-1.812442'
      ;;

    -Q)
      set_region '-155.994220' '-84.748452' '175.229298' '-66.394761'
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

filter_coords > test.csv