#!/bin/bash

setup () {
  rm -f input.sql temp.db
}

run_sql () {
  echo ".load ./squib" > input.sql
  echo "$1" >> input.sql
  run sqlite3 temp.db < input.sql
}
