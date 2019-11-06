#ifndef JGL_BASICS_FUNCTIONS_H
#define JGL_BASICS_FUNCTIONS_H

#include "jgl_includes.h"

using namespace std;

void check_sdl_error(const char *file, int line);
bool string_is_numeric(string text);
vector<string> strsplit(string input, string c);
void error_exit(int num, string error);
string ftoa(float n, int afterpoint);
bool is_middle(float a, float b, float c);
string convert_hour_to_string(int hour, int minute);
string convert_hour_to_string(int minute);
string convert_hour_to_string(float time);

int convert_string_to_hour(string text);
int convert_int_to_hour(int hour, int minute);
void remove_char(string &src, string to_remove);
template<typename K, typename V>
K find_key(map<K, V> &src_map, V &value)
{
	auto it = src_map.begin();

	while (it != src_map.end())
	{
		if(it->second == value)
		{
			break;
		}
		it++;
	}
	return (it->first);
}

#endif
