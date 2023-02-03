#!/usr/bin/env bash
executed="$0"
run_cmd="./app.out"
compile_cmd=$(make)

filtered_file_for() {
  echo "filtered_$1_$input"
}

sorted_file_for() {
  echo "sorted_$1_$output"
}

plot_file_for() {
  echo "plot_$1_$output.png"
}

filter_columns() {
  cut -d ";" -f "$1"
}

filter_coords() {
  coord_filter='1'
  if [[ -v latitude ]]
  then
    coord_filter="$coord_filter && \$10 >= ${latitude[0]} && \$10 <= ${latitude[1]}"
  fi
  if [[ -v longitude ]]
  then
    coord_filter="$coord_filter && \$11 >= ${longitude[0]} && \$11 <= ${longitude[1]}"
  fi

  non_empty_filter=''

  for column in "$@"
  do
    non_empty_filter="$non_empty_filter && \$$column != \"\""
  done

  result=$(tail -n +2 "$input" | awk "$coord_filter$non_empty_filter" FS='[;,]' OFS=';')
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
    if [[ -v "$3" ]]
    then
      wrong_usage "$1 option should have $3 values passed"
    else
      wrong_usage "$1 option should not be empty"
    fi
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

set_sorting_mode() {

  if [[ -v sorting_mode ]]
  then
    wrong_usage "Only a single sorting mode should be specified"
  fi

  sorting_mode="$1"
}

sort_file() {
  echo "Sorting $1 with mode '$3'..."
  "$run_cmd" "$1" "$2" "$sorting_mode" "$3" "$reverse" "$(cat "$1" | wc -l)"
}

plot_file() {
  echo "Plotting $2..."
  gnuplot -c "$@"
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
  -o: The file path to write at.

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
  -a <min> <max>: Min and max longitudes.

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
      reverse="true"
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
      set_region '43.347901' '50.589122' '-1.846217' '3.913466'
      ;;

    -G)
      set_region '2.227946' '5.489382' '-54.509905' '-51.445417'
      ;;

    -S)
      set_region '46.733125' '47.125133' '-56.436296' '-56.128474'
      ;;

    -A)
      set_region '14.385966' '16.545873' '-61.829015' '-60.839586'
      ;;

    -O)
      set_region '-57.545313' '-1.812442' '45.737867' '97.803858'
      ;;

    -Q)
      set_region '-84.748452' '-66.394761' '-155.994220' '175.229298'
      ;;

    -g)
      not_empty "-g" "$2" '2'
      not_empty "-g" "$3" '2'
      set_longitude "$2" "$3"
      shift
      shift
      ;;

    -a)
      not_empty "-a" "$2"
      not_empty "-a" "$3"
      set_latitude "$2" "$3"
      shift
      shift
      ;;

    --avl)
      set_sorting_mode 'avl'
      ;;

    --abr)
      set_sorting_mode 'abr'
      ;;

    --tab)
      set_sorting_mode 'tab'
      ;;

    -*)
      wrong_usage "The option $1 does not exist"
      ;;

    *)
      wrong_usage "Value $1 is set without option"
      ;;
      
  esac
  shift
done

if [[ ! -v input ]]
then
  wrong_usage "Missing argument -f"
fi

if [ ! -f "$input" ]; then
    echo -e "\e[31m$input doesn't exist!\e[0m"
    exit 2
fi


if [[ ! -v output ]]
then
  wrong_usage "Missing argument -o"
fi

if [[ ! -v temperature && ! -v pressure && ! -v wind && ! -v height && ! -v moisture ]]
then
  wrong_usage "At least one field must be selected"
fi

if [[ ! -v sorting_mode ]]
then
  set_sorting_mode 'avl'
fi

if [[ ! -v reverse ]]
then
  reverse="false"
fi

compilation=$(make 2>&1)

res="$?"
if [[ "$res" -ne 0 ]]
then
  echo -e "\e[31mCannot compile C program ($res):\e[0m"
  echo -e "\e[31m${compilation}\e[0m"
  exit 4
fi

echo "Filtering..."

if [[ -v temperature ]]
then
  if [[ "$temperature" -eq 3 ]]
  then
    cols=("1" "2" "12")
    filtered_file="$(filtered_file_for "temperature_$temperature")"
    sorted_file="$(sorted_file_for "temperature_$temperature")"
    filter_coords "${cols[@]}" | filter_columns '1,2,11' > "$filtered_file"
    sort_file "$filtered_file" "$sorted_file" "t$temperature"
    plot_file "plot/mode_$temperature.gnu" "plot_$sorted_file" "$(plot_file_for "temperature_$temperature")" "Temperature"
  else
    cols=("1" "2" "12" "13" "14")
    filtered_file="$(filtered_file_for "temperature_$temperature")"
    sorted_file="$(sorted_file_for "temperature_$temperature")"
    filter_coords "${cols[@]}" | filter_columns '1,2,11,12,13' > "$filtered_file"
    sort_file "$filtered_file" "$sorted_file" "t$temperature"
    plot_file "plot/mode_$temperature.gnu" "$sorted_file" "$(plot_file_for "temperature_$temperature")" "Temperature"
  fi
fi

if [[ -v pressure ]]
then
  if [[ "$pressure" -eq 3 ]]
  then
    cols=("1" "2" "7")
    filtered_file="$(filtered_file_for "pressure_$pressure")"
    sorted_file="$(sorted_file_for "pressure_$pressure")"
    filter_coords "${cols[@]}" | filter_columns '1,2,7' > "$filtered_file"
    sort_file "$filtered_file" "$sorted_file" "p$pressure"
    plot_file "plot/mode_$pressure.gnu" "plot_$sorted_file" "$(plot_file_for "pressure_$pressure")" "Pressure"
  else
    cols=("1" "2" "3" "7")
    filtered_file="$(filtered_file_for "pressure_$pressure")"
    sorted_file="$(sorted_file_for "pressure_$pressure")"
    filter_coords "${cols[@]}" | filter_columns '1,2,3,7' > "$filtered_file"
    sort_file "$filtered_file" "$sorted_file" "p$pressure"
    plot_file "plot/mode_$pressure.gnu" "$sorted_file" "$(plot_file_for "pressure_$pressure")" "Pressure"
  fi
fi

if [[ -v wind ]]
then
  cols=("1" "2" "4" "5" "10")
  filtered_file="$(filtered_file_for 'wind')"
  sorted_file="$(sorted_file_for 'wind')"
  filter_coords "${cols[@]}" | filter_columns '1,2,4,5,10' > "$filtered_file"
  sort_file "$filtered_file" "$sorted_file" "w"
  plot_file "plot/wind.gnu" "$sorted_file" "$(plot_file_for 'wind')"
fi

if [[ -v moisture ]]
then
  cols=("1" "6" "10")
  filtered_file="$(filtered_file_for 'moisture')"
  sorted_file="$(sorted_file_for 'moisture')"
  filter_coords "${cols[@]}" | filter_columns '1,6,10' > "$filtered_file"
  sort_file "$filtered_file" "$sorted_file" "m"
  plot_file "plot/moisture.gnu" "$sorted_file" "$(plot_file_for 'moisture')"
fi

if [[ -v height ]]
then
  cols=("1" "15" "10")
  filtered_file="$(filtered_file_for 'height')"
  sorted_file="$(sorted_file_for 'height')"
  filter_coords "${cols[@]}" | filter_columns '1,14,10' > "$filtered_file"
  sort_file "$filtered_file" "$sorted_file" "h"
  plot_file "plot/height.gnu" "$sorted_file" "$(plot_file_for 'height')"
fi