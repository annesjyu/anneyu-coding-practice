/*
org = 2e3c11d0b
decoded = eecccddddddddddd

Notes:
1. use isalpha, isdigit, isalnum, ispunct these functions
2. if a number, consider it might have multiple digits
*/

#include <iostream>
#include <string>

using namespace std;

string Decode(const string& s) {
    string decoded;
    if ( s.empty() ) {
        return decoded;
    }
    
    for ( int i = 0, n = 0; i < s.size(); i ++ ) {
        if ( isalpha(s[i]) ) {
            decoded.append(n, s[i]);
            n = 0;    
        } else if ( isdigit(s[i]) ) {
            n = n * 10 + s[i] - '0';
        }
    }
    return decoded;
}

int main() {
    string org("2e3c11d0b");
    cout << "org = " << org << endl;
    cout << "decoded = " << Decode("2e3c11d0b") << endl;
    return 0;
}
