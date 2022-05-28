using namespace std;
/*Basic c library*/
#include <iostream>
#include <vector>

// convert string to integer
int Str_To_Int(string s, bool *valid){
    *valid = true;
    int result = 0;
    int len = s.length();
    int i = 0;
    int coeff = 1;
    int temp = 0;
    if ((int)s[0] == 45){
        i = 1;
        coeff = -1;
    }
    for (; i < len; i++){
        temp = ((int)s[i] - 48);
        if ((temp >= 0) && (temp <= 9)){
            for (int j = 1; j < (len - i); j++){
                temp = temp * 10;
            }
        }
        else{
            *valid = false;
        }
        result += temp;
    }
    if (len == 0){
        *valid = false;
    }

    return (result * coeff);
}

// convert string to integer
int Str_To_Int(string s){
    int result = 0;
    int len = s.length();
    int i = 0;
    int coeff = 1;
    int temp = 0;
    if ((int)s[0] == 45){
        i = 1;
        coeff = -1;
    }
    for (; i < len; i++){
        temp = ((int)s[i] - 48);
        if ((temp >= 0) && (temp <= 9)){
            for (int j = 1; j < (len - i); j++){
                temp = temp * 10;
            }
        }
        result += temp;
    }

    return (result * coeff);
}

// convert integer to string
string Int_To_Str(int val){
    string tmp = "";
    string coeff = "";
    if (val < 0){
        val *= -1;
        coeff = "-";
    }
    string result = coeff;
    if (val == 0){result = "0";}

    while(val > 0){
        tmp += (char)((val % 10) + 48);
        val /= 10;
    }
    for(int i = tmp.length(); i >= 0;i--){
        result += tmp[i];
    }

    return result;
}

// string >> char_codes >> string
string Str_To_Char_Codes(string str){
    string str_out;
    for (unsigned short int i = 0; i < str.length(); i++){
        str_out += Int_To_Str((int)str[i]);
    }

    return str_out;
}

// split string by array of strings
size_t Split_Str(const string &input_str, vector<string> &splitted_strings, char delimiter){
    size_t pos = input_str.find( delimiter );
    size_t initialPos = 0;
    splitted_strings.clear();

    // Decompose statement
    while( pos != string::npos ) {
        splitted_strings.push_back( input_str.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = input_str.find( delimiter, initialPos );
    }

    // Add the last one
    splitted_strings.push_back( input_str.substr( initialPos, min( pos, input_str.size() ) - initialPos + 1 ) );

    return splitted_strings.size();
}
