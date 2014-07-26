/*
 * Multiple of two big intergers stored in vector
 * */
#include <iostream>
#include <string>

using namespace std;

string multiple_big_numbers(string& A, string& B) {
    string n1 = (A.front() == '-' ? A.substr(1, A.size() - 1) : A);
    string n2 = (B.front() == '-' ? B.substr(1, B.size() - 1) : B);
    
    bool negative = ( (A.front() == '-' && B.front() != '-') ||
                    (B.front() == '-' && A.front() != '-') );
    
    string res(n1.size() + n2.size(), '0'); 
    for ( int i = n1.size() - 1; i >= 0; i -- ) {
        int carry = 0;
        for ( int j = n2.size() - 1; j >= 0; j -- ) {
            int m = (n1[i] - '0') * (n2[j] - '0') + carry + (res[i+j+1] - '0');
            res[i+j+1] = m % 10 + '0';
            carry = m / 10;
        }
        if ( carry ) {
            res[i] += carry;
        }
    }
    while ( res.front() == '0' ) {
        res.erase(0,1);
    }
    if ( negative ) {
        res.insert(0, 1, '-');
    }
    return res;
}

int main() {
    string test1 = "-1100";
    string test2 = "11";
    cout << test1 << " * " << test2 << " = " << multiple_big_numbers(test1, test2) << endl;
    return 0;
}
