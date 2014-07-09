/*
Element of Programming interview

Write a function to take an array of digits encoding a dicimal number D
and update array to represent the number D + 1. For example, if A = <1,
2, 3> then you should update A to <1, 2, 4>;

Anne Yu
June 26 Wed
*/
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

void AddOne_2(vector<int>& D) {
    if ( D.empty() ) {
        return;
    }
    int carry = 0;
    for (int i = D.size() - 1; i >= 0; i -- ) {
        D[i] += ( i == D.size() - 1 ) ? 1 : carry;
        carry = (D[i] == 10) ? 1 : 0;
        D[i] = D[i] % 10;
    }
    if ( carry ) {
        D.insert(D.begin(), carry);
    }
}

int main() {
    vector<vector<int>> tests = {{1,2,3}, {9,9}, {0}};
    cout << "version1-----------------" << endl;
    for ( auto v : tests ) {
        cout << "n = ";
        for_each(v.begin(), v.end(), [](int n){cout << n;});
        cout << ", + 1 = ";
        AddOne(v);
        for_each(v.begin(), v.end(), [](int n){cout << n;});
        cout << ", ";
        cout << endl;
    } 
        cout << endl;

    cout << "version2-----------------" << endl;
    for ( auto v : tests ) {
        cout << "n = ";
        for_each(v.begin(), v.end(), [](int n){cout << n;});
        cout << ", + 1 = ";
        AddOne_2(v);
        for_each(v.begin(), v.end(), [](int n){cout << n;});
        cout << ", ";
        cout << endl;
     }    
    cout << endl;
    return 0;
}
