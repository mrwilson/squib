#!/bin/bash

TESTS=./tests

SQLITE=$(which sqlite3)
TESTDB=temp.db

for T in $(find $TESTS -type f -printf "%f\n"); do
  echo -n Running $T...

  rm -f $TESTDB

  $SQLITE $TESTDB < $TESTS/$T

  if [[ $? -eq 0 ]]; then
    echo passed.
  else
    echo failed.
    exit 1;
  fi

done
