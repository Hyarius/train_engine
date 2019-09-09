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

int printOglError(const char *file, int line)
{
	vector<string>tab = strsplit(file, "\\");
	if (tab.size() == 1)
		vector<string>tab = strsplit(file, "/");
	string file_name = tab[tab.size() - 1];
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	string text = "";

	if (glErr == GL_NO_ERROR)
		text = "";
	else if (glErr == GL_INVALID_VALUE)
		text = "Invalid value";
	else if (glErr == GL_INVALID_OPERATION)
		text = "Invalid operation";
	else if (glErr == GL_INVALID_ENUM)
		text = "Invalid enum";
	else
		text = "Other error";

	if (text != "")
	{
		string error = "opengl state in file " + file_name + ":line[" + to_string(line) + "] : " + text.c_str();
		error_exit(1, error);
	}
	retCode = 1;
	return retCode;
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
		string error = "SDL2 state in file " + file_name + ":line[" + to_string(line) + "] : " + SDL_GetError();
		error_exit(1, error);
	}
}
