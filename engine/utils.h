using namespace std;
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// convert string to integer
int Str_To_Int(string s, bool *valid);
int Str_To_Int(string s);
// convert integer to string
string Int_To_Str(int val);
// string >> char_codes >> string
string Str_To_Char_Codes(string str);
// split string by array of strings
size_t Split_Str(const string &input_str, vector<string> &splitted_strings, char delimiter);

// draw string
void DrawStaticString(float x, float y, float z, void *font, string input);

#endif // UTILS_H_INCLUDED
