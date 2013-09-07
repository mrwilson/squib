void trainClassifierStep(sqlite3_context* context, int argc, sqlite3_value** argv);
void trainClassifierFinalise(sqlite3_context *context);
void classifyData(sqlite3_context* context, int argc, sqlite3_value** argv);
double sigmoid(double x);
double classify_instance(int count, sqlite3_value** features);
