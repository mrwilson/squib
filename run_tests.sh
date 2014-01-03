#!/bin/bash

TESTS=./tests

SQLITE=$(which sqlite3)
TESTDB=temp.db

function cleanup {
  rm -f $TESTDB
}

function run_test {
  echo -n Running $1 ...

  OUT=$($SQLITE $TESTDB < $1)

  if [[ $? -ne 0 ]]; then
    echo error!
    echo $OUT
    exit 1
  fi

  if [ "$OUT" == "SUCCESS" ]; then
    echo passed.
  else
    echo failed!
  fi
  
  cleanup

}

trap cleanup EXIT

for T in $(find $TESTS -type f); do

  run_test $T

done
