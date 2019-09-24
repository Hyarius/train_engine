#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

using namespace std;

vector<string> strsplit(string input, string c);
void error_exit(int num, string error);
int printOglError(const char *file, int line);
void check_sdl_error(const char *file, int line);
string ftoa(float i);

#endif
