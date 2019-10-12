#ifndef JGL_FILE_HANDLER_H
#define JGL_FILE_HANDLER_H

ifstream open_file(string path);
string get_str(ifstream &myfile);
vector<string> get_strsplit(ifstream &myfile, const string c, int size);
vector<string> list_files(string path, string extension);
bool check_file_exist(string path);
bool copy_file(string src, string dest);
void write_on_file(string path, string text);
void rewrite_on_file(string path, string text);

#endif
