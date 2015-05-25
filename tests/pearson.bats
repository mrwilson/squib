#!/usr/bin/env bats

load utils

@test "Pearson :: should return 1.0 on perfect positive correlation" {
  run_sql "create table input (x integer, y integer);"

  for val in 1 2; do
    run_sql "insert into input values(${val}, ${val});"
  done;

  run_sql "select pearson(x,y) from input;"

  [ "${output}" == "1.0" ]
}

@test "Pearson :: should return -1.0 on perfect negative correlation" {
  run_sql "create table input (x integer, y integer);"

  for val in 1 2; do
    run_sql "insert into input values(${val}, -${val});"
  done;

  run_sql "select pearson(x,y) from input;"

  [ "${output}" == "-1.0" ]
}
