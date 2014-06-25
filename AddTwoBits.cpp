/*
 * Take two string s and t of bits encoding binary number Bs and Bt, and returns a new string of bits representing the number Bs + Bt
 * Anne Yu
 * June 26, 2014
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> AddTwoBits(const vector<int>& s, const vector<int>& t) {
    vector<int> r;
    int i = s.size() - 1, j = t.size() - 1;
    int carry = 0;

    while ( i >= 0 && j >= 0 ) {
        r.insert(r.begin(), (s[i] ^ t[j] ^ carry));
        carry = (s[i] & t[j]) | (s[i] & carry) | (t[j] & carry);        
        i --; j --;
    }

    while ( i >= 0 ) {
        r.insert(r.begin(), s[i] ^ carry);
        carry = s[i] & carry;
        i --;
    }

    while ( j >= 0 ) {
        r.insert(r.begin(), t[j] ^ carry);
        carry = t[j] & carry;
        j --;
    }

    if ( carry ) {
        r.insert(r.begin(), 1);
    }

    return r;
}

int main() {
    vector<int> s = {1,1,1,1,1};
    vector<int> t = {1,1};
    vector<int> r = AddTwoBits(s, t);
    cout << "s = ";
    for ( auto &i : s ) cout << i;
    cout << endl << "t = ";
    for ( auto &i : t ) cout << i;
    cout << endl << "result = ";
    for ( auto &i : r ) cout << i;
    cout << endl;
    return 0;
}
