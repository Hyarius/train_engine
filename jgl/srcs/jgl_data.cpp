#include "jgl.h"

Data::Data(void *p_data)
{
	content.clear();
	content.push_back(p_data);
}

Data::Data(int nb_param, ...)
{
	va_list list_param;
    va_start(list_param, nb_param);

	content.clear();
	for (int i = 0; i < nb_param; i++)
		content.push_back(va_arg(list_param, void *));

	va_end(list_param);
}

void		Data::operator = (void *p_data)
{
	content.clear();
	content.push_back(p_data);
}

void		Data::operator + (void *p_ptr)
{
	content.push_back(p_ptr);
}
