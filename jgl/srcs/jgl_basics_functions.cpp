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

void check_sdl_error(const char *file, int line)
{
	vector<string>tab = strsplit(file, "\\");
	if (tab.size() == 1)
		vector<string>tab = strsplit(file, "/");
	string file_name = tab[tab.size() - 1];
	string text = SDL_GetError();
	if (text.size() != 0)
	{
		string error = file_name + " - line [" + to_string(line) + "] : " + text;
		error_exit(1, error);
	}
}

void				error_exit(int num, string error)
{
	cout << error << endl;
	exit(num);
}

void reverse(string &base)
{
    int i = 0, j = base.length() - 1, temp;
    while (i<j)
    {
        temp = base[i];
        base[i] = base[j];
        base[j] = temp;
        i++; j--;
    }
}

string intToStr(int x, int d)
{
	char c;
	string result;

    int i = 0;
    while (x)
    {
		c = (x % 10) + '0';
        result.push_back(c);
        x = x/10;
		i++;
    }

    while (i < d)
	{
		result.append("0");
		i++;
	}

    reverse(result);

    return (result);
}

// Converts a floating point number to string.
string ftoa(float n, int afterpoint)
{
	string result;

	if (n == 0)
		return ("0");

	if (n < 0)
	{
		result.append("-");
		n = -n;
	}

    int ipart = (int)n;

    float fpart = n - (float)ipart;

    // convert integer part to string
    result.append(intToStr(ipart, 0));

    // check for display option after point
    if (afterpoint != 0 && fpart != 0.0f)
    {
        result.append(".");  // add dot

        fpart = fpart * pow(10, afterpoint);

        string tmp = intToStr((int)fpart, afterpoint);

		result.append(tmp);
    }

	return (result);
}

bool string_is_numeric(string text)
{
	return (text.find_first_not_of( "0123456789." ) == string::npos);
}

bool is_middle(float a, float b, float c)
{
	if (a > b)
		return (false);
	if (b > c)
		return (false);
	return (true);
}

string convert_hour_to_string(int hour, int minute)
{
	string hour_text = to_string(hour);
	string minute_text = to_string(minute);

	if (hour_text.length() == 1)
		hour_text.insert(0, "0");

	if (minute_text.length() == 1)
		minute_text.insert(0, "0");

	return (hour_text + "h" + minute_text);
}

string convert_hour_to_string(int minute)
{
	string hour_text = to_string(minute / 60);
	string minute_text = to_string(minute % 60);

	if (hour_text.length() == 1)
		hour_text.insert(0, "0");

	if (minute_text.length() == 1)
		minute_text.insert(0, "0");

	return (hour_text + "h" + minute_text);
}

int convert_string_to_hour(string text)
{
	vector<string> tab = strsplit(text, "h");

	if (tab.size() != 2)
		return (-1);

	return (atoi(tab[0].c_str()) * 60 + atoi(tab[1].c_str()));
}

int convert_int_to_hour(int hour, int minute)
{
	return (hour * 60 + minute);
}

void remove_char(string &src, string to_remove)
{
	string result;
	for (size_t i = 0; i < src.size(); i++)
	{
		char target = '\0';
		for (size_t j = 0; j < to_remove.size(); j++)
			if (to_remove[j] == src[i])
				target = to_remove[j];

		if (target == '\0')
			result.push_back(src[i]);
	}
	src = result;
}
