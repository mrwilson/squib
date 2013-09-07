#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

typedef struct {
  float x_sum;
  float y_sum;
  float x_sqr;
  float y_sqr;
  float prod;
  int count;
} PrsCtx;

double pearson(PrsCtx *p);
void pearsonStep(sqlite3_context *context, int argc, sqlite3_value **argv);
void pearsonFinalize(sqlite3_context *context);
