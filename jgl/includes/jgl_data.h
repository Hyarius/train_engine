#ifndef JGL_DATA_H
#define JGL_DATA_H

#include "jgl_includes.h"

using namespace std;

typedef struct Data
{
	vector<void *> content;

	Data(void *p_data = NULL);
	Data(int nb_param, ...);

	void operator = (void *p_data);
	void operator + (void *p_ptr);
}					t_data;

#endif
