/*
 *A is a sorted array, the length of A is not known in advance, accessing A[i] for i beyond the end of array throws an exception, design an algorithm that takes A and a key k and returns an index i such that A[i] = k; return -1 if k does not appear in A.
 * July 13, 2014
 * */
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

const int binary_search_unknown_length(const vector<int>& A, const int k) {
    int steps = 1, l = 0, h = 0;
    while (true) {
        try {
            cout << "Debug: steps = " << steps << ", l = " << l << ", h = " << h << endl; 
            h = l + steps;
            int v = A.at(h);// use at(), so throw exceptions if go out of the boundary, do NOT use A[m]
            if ( v < k ) {
                steps <<= 1; //use << to increase steps
                l = h + 1;
            } else if ( v == k ) {
                return h;
            } else {
                break;
            }
        } catch (const exception& e) {
            cout << "go out of the boundary: l = " << l << ", h = " << h << endl;
            break;
        }    
    }
    int m = 0;
    while ( l <= h ) {
        try {
            m = l + ( h - l ) / 2;
            int v = A.at(m);
            if ( v < k ) {
                l = m + 1;
            } else if ( v == k ) {
                return m;
            } else {
                h = m - 1;
            }
        } catch ( const exception& e ) {
            cout << "go out of the boundary: l = " << l << ", h = " << h << endl;
            h = m - 1;
        }
    }
    return -1;
}

int main() {
    default_random_engine gen((random_device())());
    uniform_int_distribution<int> n_dis(11, 200);
    vector<int> A;
    const int range = 20;
    for ( int i = 0; i < range; i ++ ) {
        A.emplace_back(n_dis(gen));
    }
    sort(A.begin(), A.end());
    cout << "A ( size = " << range << " ) = ";
    for_each(A.begin(), A.end(), [](int i) {cout << i << " ";});
    cout << endl;
    const int k1 = n_dis(gen);
    const int k2 = A[range/2];
    cout << "found " << k1 << " at " << binary_search_unknown_length(A, k1) << endl;
    cout << "found " << k2 << " at " << binary_search_unknown_length(A, k2) << endl;
    return 0;
}
