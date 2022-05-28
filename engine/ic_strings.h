using namespace std;
#ifndef STRINGS_H_INCLUDED
#define STRINGS_H_INCLUDED

// convert string to integer
int Str_To_Int(string s, bool *valid);
int Str_To_Int(string s);
// convert integer to string
string Int_To_Str(int val);
// string >> char_codes >> string
string Str_To_Char_Codes(string str);
// split string by array of strings
size_t Split_Str(const string &input_str, vector<string> &splitted_strings, char delimiter);

#endif

