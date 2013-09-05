#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void trainClassifierStep(sqlite3_context* context, int argc, sqlite3_value** argv);
void trainClassifierFinalise(sqlite3_context *context);
void classifyData(sqlite3_context* context, int argc, sqlite3_value** argv);
