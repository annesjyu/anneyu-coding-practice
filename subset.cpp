/*
 * a set s of n distinct elements, print the power set of S, Print the subsetsone per line, with elements seperated by comma
 * */

#include <iostream>
#include <vector>

using namespace std;


void print_power_set(vector<int>& S, const size_t i, vector<int>& cur_set) {
    for ( int l = i; l < S.size(); l ++ ) {
        if ( l > i && S[l] == S[l-1] ) {
            continue;
        }
        cur_set.emplace_back(S[l]);
        //for_each(cur_set.begin(), cur_set.end() - 1, [](int n) { cout << n << ", "; });
        copy(cur_set.begin(), cur_set.end() - 1, ostream_iterator<int>(cout, ","));
        cout << cur_set.back() << endl;
        print_power_set(S, l + 1, cur_set);
        cur_set.pop_back();
    }
}

void print_power_set(vector<int>& S) {
    if ( S.empty() ) {
        return;
    }
    sort(S.begin(), S.end());
    vector<int> cur_set;
    print_power_set(S, 0, cur_set);
}


void print_power_set_size_k_helper(vector<int>& S, const size_t i, vector<int>& cur_set, const int k) {
    if ( cur_set.size() == k ) {
        for_each(cur_set.begin(), cur_set.end() - 1, [](int n) { cout << n << ", "; });
        cout << cur_set.back() << endl;
        return;
    }
    for ( int l = i; l < S.size(); l ++ ) {
        if ( l > i && S[l] == S[l-1] ) {
            continue;
        }
        cur_set.emplace_back(S[l]);
        print_power_set_size_k_helper(S, l + 1, cur_set, k);
        cur_set.pop_back();
    }
}

void print_power_set_size_k(vector<int>& S, const int k) {
    if ( S.empty() ) {
        return;
    }
    if ( k > S.size() ) {
        throw invalid_argument("k should be less than the size of S");
    }
    vector<int> cur_set;
    print_power_set_size_k_helper(S, 0, cur_set, k);
}

int main() {
    vector<int> S = {1, 2, 3, 2};
    print_power_set(S);
    //print_power_set_size_k(S, 3);
}
