#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

void pearsonStep(sqlite3_context *context, int argc, sqlite3_value **argv);

void pearsonFinalize(sqlite3_context *context);
