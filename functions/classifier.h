#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef SQLITE_EXTENSION_INIT1
  #include <sqlite3ext.h>
  SQLITE_EXTENSION_INIT1
#endif

typedef struct Classifier {
  int count;
  int feature_count;
  double features[];
} Classifier;

Classifier *c;

double sigmoid(double x) {
  return 1.0 / (1.0 + exp(-x));
}

double classify_instance(int count, sqlite3_value** features) {
  double logit = 0.0,
         feature_value;

  for(int i = 0; i < count; i++) {
    feature_value = sqlite3_value_double(features[i]);
    logit += c->features[i] * feature_value;
  }

  return sigmoid(logit);
}

void trainClassifierStep(sqlite3_context* context, int argc, sqlite3_value** argv){
  int label;
  double result, feature_value;

  argc--;

  if(c == NULL) {
    c = malloc(sizeof(struct Classifier) + argc*sizeof(double));
    c->feature_count = argc;
  }

  c->count++;

  label  = sqlite3_value_int64(argv[argc]);
  result = classify_instance(argc, argv);

  for(int i = 0; i < argc; i++) {
    feature_value = sqlite3_value_double(argv[i]);
    c->features[i] = c->features[i] + (0.01 * (label - result) * feature_value);
  }
}

void trainClassifierFinalise(sqlite3_context *context){
  for(int i = 0; i < c->feature_count; i++) {
    printf("(%d) %f\n",i,c->features[i]);
  }
}

void classifyData(sqlite3_context* context, int argc, sqlite3_value** argv){
  sqlite3_result_double(context, classify_instance(argc, argv));
}
