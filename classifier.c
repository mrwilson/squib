#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sqlite3.h>
#include "classifier.h"
#include "utils.h"

#define NUMBER_OF_PASSES 10

typedef struct Classifier {
  int count;
  int feature_count;
  double features[];
} Classifier;

Classifier *c;

int pass = 1;

double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}

double classify_instance(int count, sqlite3_value** features) {
  double logit = c->features[0],
         feature_value;

  for(int i = 0; i < count; i++) {
    feature_value = sqlite3_value_double(features[i]);
    logit += c->features[i+1] * feature_value;
  }

  return sigmoid(logit);
}

void trainClassifierStep(sqlite3_context* context, int argc, sqlite3_value** argv){
  UNUSED(context);

  long long label;
  double result, feature_value, alpha;

  alpha = 1/pass;

  argc--;

  if(c == NULL) {
    c = malloc(sizeof(struct Classifier) + ((unsigned long) argc)*sizeof(double));
    c->feature_count = argc;
  }

  c->count++;

  label  = sqlite3_value_int64(argv[argc]);
  result = classify_instance(argc, argv);

  c->features[0] = c->features[0] + alpha*(label - result); // Bias term

  for(int i = 0; i < argc; i++) {
    feature_value = sqlite3_value_double(argv[i]);
    c->features[i+1] = c->features[i+1] + (alpha * (label - result) * feature_value);
  }
}

void trainClassifierFinalise(sqlite3_context *context){
  sqlite3 *db = sqlite3_context_db_handle(context);
  sqlite3_stmt *stmt = sqlite3_next_stmt(db, NULL);

  if(pass < NUMBER_OF_PASSES) {
    printf("Pass %d complete\n",pass);
    pass++;
    sqlite3_reset(stmt);
    sqlite3_step(stmt);
  } else {
    printf("(Bias) %f\n", c->features[0]);
    for(int i = 0; i < c->feature_count; i++) {
      printf("(%d) %f\n", i+1, c->features[i+1]);
    }
  }
}

void classifyData(sqlite3_context* context, int argc, sqlite3_value** argv){
  sqlite3_result_double(context, classify_instance(argc, argv));
}
