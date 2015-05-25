#!/usr/bin/env bats

load utils

@test "Library loads without errors" {
  run_sql ".load ./squib"
}
