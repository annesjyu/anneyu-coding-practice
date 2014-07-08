/*
 * The reflected binary code, also known as Gray code after Frank Gray, is a binary numeral system where two successive values differ in only one bit (binary digit). 
 * write a function which takes as input a single positive integer n and returns an n-bit gray code.
 * for example:
 * [my solution] n = 3 : 0, 1, 3, 2, 6, 7, 5, 4
 * [book solution] n = 3 : 0, 1, 3, 2, 6, 7, 5, 4
 * */

#include <algorithm>
//#include <bitset>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

string gray_code_helper(const int n, int cur_n, unordered_set<int>& selected, string gray_code) {
    if ( selected.size() == ( 1 << n ) ) {
        return gray_code;
    }
    for ( int i = 0; i < n; i ++ ) {
        //reverse ith bit of cur_n to get next_n
        int next_n = (cur_n & ( 1<<i )) ? ( cur_n & ~(1<<i) ) : ( cur_n | (1<<i)); 
        if ( selected.find(next_n) != selected.end() ) {
            continue;
        }
        selected.emplace(next_n);
        //bitset<3> next_n_bit(next_n);
        //string next_n_str = next_n_bit.to_string<char,std::string::traits_type,std::string::allocator_type>();
        string next_n_str = to_string(next_n);
        string res = gray_code_helper(n, next_n, selected, (gray_code+", "+next_n_str));
        if ( !res.empty() ) {
            return res;
        }
        selected.erase(next_n);
    }
    return {};
} 

string gray_code(const int n) {
    unordered_set<int> selected;
    selected.emplace(0);
    string gray_code("0");
    string res = gray_code_helper(n, 0, selected, gray_code);
    return res; 
}

vector<int> gray_code_book_helper(const int n) {
    if ( n == 1 ) {
        return {0, 1};
    }
    vector<int> res = gray_code_book_helper(n - 1);
    vector<int> next_res = res;
    //next_res, each res number prepend "0" in the front;
    //in the reverse order each res number prepend "1" in the front;
    for_each(res.rbegin(), res.rend(), [&](int i) {
        next_res.emplace_back( (1 << (n-1)) + i ); });
    return next_res;
}

string gray_code_book(const int n) {
    //add 0 in the front of prev_res, then add 1 in the front of prev_res in a reverse order
    vector<int> res = gray_code_book_helper(n);
    string res_s;
    for_each(res.begin(), prev(res.end(), 1), [&](int i) {
            res_s += to_string(i) + ", "; });
    res_s += to_string(res.back());
    return res_s;
}

int main() {
    string test3 = gray_code(3);
    cout << "[my solution] n = 3 : " << test3 << endl;
    string test3_book = gray_code_book(3);
    cout << "[book solution] n = 3 : " << test3_book << endl;
    return 0;
}
