/*
 * take as input a phone number, specified as a string of digits, return all possible character sequences that correspond to the phone number.
 * */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void phone_mnemonic_recursion_helper(string& s, string* mapping, int idx, string& cur_mapping) {
    if ( idx == s.size() ) {
        cout << cur_mapping << " ";
        return;
    }
    for ( auto c : mapping[s[idx] - '0'] ) {
        cur_mapping.push_back(c);
        phone_mnemonic_recursion_helper(s, mapping, idx+1, cur_mapping);
        cur_mapping.pop_back();
    }
}

void phone_mnemonic_recursion(string& s) {
    string cur_mapping;
    string mapping[10] = { "0", "1", "ABC", "DEF", "GHI", "JKL",
                                   "MNO", "PQRS", "TUV", "WXYZ" };
    phone_mnemonic_recursion_helper(s, mapping, 0, cur_mapping);
}

void phone_mnemonic(string& s) {
    vector<string> res;
    res.emplace_back("");
    string mapping[10] = { "0", "1", "ABC", "DEF", "GHI", "JKL", 
                           "MNO", "PQRS", "TUV", "WXYZ" };
    for ( const char c : s ) {
        string mp = mapping[c-'0'];
        vector<string> new_res;
        for ( auto m : mp ) {
            for ( auto r : res ) {
                string new_s = r + m;
                new_res.emplace_back(new_s);
            }
        }
        res = new_res;
    }
    cout << "total " << res.size() << " mappings = ";
    for_each(res.begin(), res.end(), [](string& s) {cout << s << " ";});
    cout << endl;
}

int main() {
    string test = "289";
    cout << "phone number = " << test << endl;
    phone_mnemonic(test);
    cout << "phone number (recursion) = " << test << endl;
    phone_mnemonic_recursion(test);
    return 0;
}
