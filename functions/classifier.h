#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#ifndef SQLITE_EXTENSION_INIT1
  #include <sqlite3ext.h>
  SQLITE_EXTENSION_INIT1
#endif


void trainClassifierStep(sqlite3_context* context, int val, sqlite3_value** values){

}

void trainClassifierFinalise(sqlite3_context *context){

}

void classifyData(sqlite3_context* context, int val, sqlite3_value** values){

}
