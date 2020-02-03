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
  make all
fi

if [ -n "${RUN}" ]; then
  for f in prace-pi.e1*; do
    echo $f
    ./$f
  done
  for f in prace-pi.e[2\|3]*; do
    echo $f
    for i in $(seq 0 ${RUN}); do
      echo -n "$i "; ./$f
    done
  done
fi
