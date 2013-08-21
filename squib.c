#include <sqlite3ext.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

SQLITE_EXTENSION_INIT1

typedef struct {
  double x_sum;
  double y_sum;
  double x_sqr;
  double y_sqr;
  double prod;
  int count;
} PrsCtx;

static void pearsonStep(sqlite3_context *context, int argc, sqlite3_value **argv){
  PrsCtx *p;
  int xType, yType;

  assert(argc == 2);

  p = sqlite3_aggregate_context(context, sizeof(*p));
  xType = sqlite3_value_numeric_type(argv[0]);
  yType = sqlite3_value_numeric_type(argv[1]);

  if (xType == SQLITE_NULL || yType == SQLITE_NULL || xType != yType) {
    sqlite3_result_error(context, "Null or incompatible types.", -1);
  }

  if(p){
    p->count++;
    double x, y;

    if(xType == SQLITE_INTEGER ){
      x = (double) sqlite3_value_int64(argv[0]);
      y = (double) sqlite3_value_int64(argv[1]);
    } else {
      x = sqlite3_value_double(argv[0]);
      y = sqlite3_value_double(argv[1]);
    }

    p->x_sum += x;
    p->y_sum += y;
    p->prod  += x * y;
    p->x_sqr += x * x;
    p->y_sqr += y * y;

  }
}

static double pearson(PrsCtx *p) {
  int n = p->count;

  double top = p->prod - (p->x_sum*p->y_sum / n),
         x_b = p->x_sqr - (p->x_sum*p->x_sum / n),
         y_b = p->y_sqr - (p->y_sum*p->y_sum / n);

  return top/sqrt(x_b * y_b);
}

static void pearsonFinalize(sqlite3_context *context){
  PrsCtx *p;
  p = sqlite3_aggregate_context(context, 0);

  if(!p || p->count <= 0) {
    sqlite3_result_error(context, "Error calculating value.", -1);
  }

  sqlite3_result_double(context, pearson(p));
}

void setup_functions(sqlite3 *db) {
  sqlite3_create_function(db, "pearson", 2, SQLITE_UTF8, NULL, NULL, &pearsonStep, &pearsonFinalize);
}

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  setup_functions(db);
  return rc;
}
