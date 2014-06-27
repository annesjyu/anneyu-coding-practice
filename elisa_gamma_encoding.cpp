/*
 * Elias gamma code, 
 * - write n in bnary to form string b
 * - subtract 1 from the number of bits written in the first step, and add that many zeros to the beginning of string b
 * For example,
 * number = 13,
 * encoded = (4bits - 1) 0s + (1101)_2 = 0001101
 * decoded = 13
 * */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

string EliasGammaEncoding(const int n);

string ElisaGammaEncodingHelper(const vector<int>& A) {
    string S;
    for ( int i = 0; i < A.size(); i ++ ) {
        S.append(EliasGammaEncoding(A[i]));
    }
    return S;
}

string EliasGammaEncoding(const int n) {
    string encoded;
    int t = n;
    while ( t ) {
        encoded.insert(0, 1, ((t & 1) + '0'));
        t >>= 1;
    }
    encoded.insert(0, encoded.size() - 1, '0');
    return encoded;
}

vector<int> EliasGammaDecode(const string& s) {
    vector<int> res;
    int i = 0;
    while ( i < s.size() ) {    
        int count = 0;
        while ( i < s.size() && s[i] == '0' ) {
            count ++; i ++;
        }
        count += 1;
        int number = 0;
        for ( int k = i; k < i+count; k ++ ) {
            number = (number << 1) | ( s[k] - '0' );        
        }
        res.emplace_back(number);
        i += count;
    }
    return res;
}

int main() {
    vector<int> n = {13, 14, 45, 678};
    for ( auto &i : n ) {
        cout << i << ", ";
    }
    string s = ElisaGammaEncodingHelper(n);
    cout << endl << "Encoded = " << s << endl;
    cout << "Decoded = ";
    vector<int> decoded = EliasGammaDecode(s);
    for ( auto &i : decoded ) {
        cout << i << ", ";
    }  
    cout << endl;  
    return 0;
}
