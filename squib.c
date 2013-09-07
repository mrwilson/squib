#include <sqlite3ext.h>

SQLITE_EXTENSION_INIT1

#include "classifier.h"
#include "pearson.h"
#include "utils.h"

void setup_functions(sqlite3 *db);
int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi);

void setup_functions(sqlite3 *db) {
  // pearson
  sqlite3_create_function(db, "pearson",   2, SQLITE_UTF8, NULL, NULL, &pearsonStep, &pearsonFinalize);

  // classifier
  sqlite3_create_function(db, "train",    -1, SQLITE_UTF8, NULL, NULL, &trainClassifierStep, &trainClassifierFinalise);
  sqlite3_create_function(db, "classify", -1, SQLITE_UTF8, NULL, &classifyData, NULL, NULL);
}

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
  UNUSED(pzErrMsg);
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  setup_functions(db);
  return rc;
}
