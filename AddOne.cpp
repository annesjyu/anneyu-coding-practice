#include <iostream>
#include <vector>

using namespace std;

vector<int> AddOne(const vector<int>& n) {
    vector<int> res;
    int t = n.back() + 1;
    res.emplace_back(t % 10);
    int carry = t >= 10 ? 1 : 0;
    for ( int i = n.size() - 2; i >= 0; i -- ) {
        t = n[i] + carry;
        res.insert(res.begin(), t % 10);
        carry = t >= 10 ? 1 : 0;
    }
    if ( carry ) {
        res.insert(res.begin(), carry);
    }
    return res;
}

int main() {
    vector<vector<int>> tests = {{1,2,3}, {9,9}, {0}};
    for ( auto &v : tests ) {
        vector<int> res = AddOne(v);
        for ( auto &i : res ) {
            cout << i;
        }
        cout << endl;
    }
    return 0;
}
