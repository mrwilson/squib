#include <sqlite3ext.h>

SQLITE_EXTENSION_INIT1

#include "./functions/pearson.h"
#include "./functions/classifier.h"

void setup_functions(sqlite3 *db) {
  // pearson
  sqlite3_create_function(db, "pearson",   2, SQLITE_UTF8, NULL, NULL, &pearsonStep, &pearsonFinalize);

  // classifier
  sqlite3_create_function(db, "train",    -1, SQLITE_UTF8, NULL, NULL, &trainClassifierStep, &trainClassifierFinalise);
  sqlite3_create_function(db, "classify", -1, SQLITE_UTF8, NULL, &classifyData, NULL, NULL);
}

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg, const sqlite3_api_routines *pApi){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  setup_functions(db);
  return rc;
}
