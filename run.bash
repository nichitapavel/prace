#!/bin/bash
#set -ex

VERSION="v0.1"

usage="${0} -c -r [NUMBER_OF_RUNS]
Compile and/or run pi program.

Options:
-c                  - compile pi program
-r [NUMBER_OF_RUNS] - run pi program"


while [ "$1" != "" ]
do
case $1 in
  -c)
    COMPILE="1"
    shift 1
  ;;
  -r)
    RUN="$2"
    shift 2
  ;;
  -h|--help)
    echo "$usage" || exit 2
    exit
  ;;
  -v|--version)
    echo "$0 ${VERSION}" || exit 2
    exit
  ;;
  *)
    echo -e "ERROR: unknown argument, read help for more info.\n"
    echo "$usage" || exit 2
    exit
  ;;
esac
done


if [ -n "${COMPILE}" ]; then
  gcc -g -fopenmp pi.c -o prace-pi -lm
  gcc -fopenmp pi.c -o prace-pi-ndb -lm
  gcc -g pi.c -o prace-pi-nomp -lm
  gcc pi.c -o prace-pi-ndb-nomp -lm
fi

if [ -n "${RUN}" ]; then
  for f in prace-pi prace-pi-ndb prace-pi-nomp prace-pi-ndb-nomp; do
    echo $f
      for i in $(seq 0 ${RUN}); do
      echo -n "$i "; ./$f
    done
  done
fi
