/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Robert Miller
 * Date        : 9/23/2021
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    for(int i = 0; i < (int)s.length(); i++){
        if(!(islower(s[i]))){
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    unsigned int vector = 0;
    unsigned int setter;
    int count = 0;
    while(count < 27 && count < (int)s.length()){
        setter = 1 << (s[count] - 'a');
    if((setter & vector) != 0){
        return false;
    }
    vector = vector | setter;
    count++;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    string str;
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }
    if(!(is_all_lowercase(argv[1]))){
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    if(all_unique_letters(argv[1])){
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    return 0;
    }
