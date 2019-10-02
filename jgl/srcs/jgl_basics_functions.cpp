#include "jgl.h"

using namespace std;

vector<string>		strsplit(string input, string c)
{
	vector<string>	tab;
	string			val;
	int 			start = 0;
	int 			end = 0;

	while (end != -1)
	{
		end = input.find(c, start);
		val = input.substr(start, end - start);
		if (val.size() != 0)
			tab.push_back(val);
		start = end + c.size();
	}
	return (tab);
}

void				error_exit(int num, string error)
{
	cout << error << endl;
	exit(num);
}

string				ftoa(float i)
{
	return (to_string(i));
}

bool string_is_numeric(string text)
{
	return (text.find_first_not_of( "0123456789." ) == string::npos);
}
