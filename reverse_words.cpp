/*
 * reverse words in a sentence
 */
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

void ReverseString(string &s) {
    if ( s.size() <= 1 ) {
        return;
    }
    
    reverse(s.begin(), s.end());
    
    int start = 0, end = 0;
    
    while ( (end = s.find(" ", start)) != string::npos ) {
        reverse(s.begin() + start, s.begin() + end);
        start = end + 1;
    }
    reverse(s.begin() + start, s.end());
}

int main() {
    string s = "this is a test";
    cout << "org = \"" << s << "\"" << endl;
    ReverseString(s);
    cout << "reversed = \"" << s << "\"" << endl;

    return 0;
}
