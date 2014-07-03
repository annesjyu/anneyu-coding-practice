/*
 *Given an array of n strings, compute the k strings that appear most frequently in A. Print them in a reverse order
 * */

#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class GreaterCmp {
    public:
    bool operator () ( pair<string, int>& a, pair<string, int>& b) {
        if ( a.second == b.second ) {
            return a.first < b.first;
        } else {
            return a.second > b.second;
        }
    }
};

void print_k_most_frequent(const vector<string>& v, const int k) {
    if ( v.empty() ) {
        return;
    }
    
    if ( k <= 0 ) {
        throw length_error("k <= 0");
    }
    
    unordered_map<string, int> counts;
    for ( auto &s : v ) {
        counts[s]++;
    }

    priority_queue<pair<string, int>, vector<pair<string, int> >, GreaterCmp> min_heap;
    for ( auto it = counts.begin(); it != counts.end(); it ++ ) {
        min_heap.emplace(it->first, it->second);
        if ( min_heap.size() > k ) {
            min_heap.pop();
        }
    }

    vector<pair<string, int> > res;
    while ( !min_heap.empty() ) {
        pair<string, int> p = min_heap.top();
        res.emplace_back(p.first, p.second);
        min_heap.pop();
    }

    for ( auto it = res.rbegin(); it != res.rend(); it ++ ) {
        cout << it->first << ", frequency = " << it->second << endl;
    }
    cout << endl;
}


int main () {
    vector<string> tests = {"one", "two", "two", "three", "three","three","four", "four", "four","four","five","five","five","five","five","six","six","six","six","six","six","six", "seven","seven","seven","seven","seven","seven","seven"};
    cout << "print out the 4 most frequent strings" << endl;
    print_k_most_frequent( tests, 4 );    
    return 0;
}
