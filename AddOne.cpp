#include <iostream>
#include <vector>

using namespace std;

void AddOne(vector<int>& n) {
    int t = n.back() + 1;
    n.back() = t % 10;
    int carry = t >= 10 ? 1 : 0;
    for ( int i = n.size() - 2; i >= 0 && carry; i -- ) {
        t = n[i] + carry;
        if ( t == 10 ) {
            carry = 1;
            n[i] = 0;
        }
    }
    if ( carry ) {
        n.insert(n.begin(), carry);
    }
}

int main() {
    vector<vector<int>> tests = {{1,2,3}, {9,9}, {0}};
    for ( auto &v : tests ) {
        AddOne(v);
        for ( auto &i : v ) {
            cout << i;
        }
        cout << endl;
    }
    return 0;
}
