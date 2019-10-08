#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

using namespace std;

bool string_is_numeric(string text);
vector<string> strsplit(string input, string c);
void error_exit(int num, string error);
string ftoa(float i);
bool is_middle(float a, float b, float c);

#endif
