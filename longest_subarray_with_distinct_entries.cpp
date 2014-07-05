/*
 *Given an array A of integers, return the length of a longest subarray of A with the constraint taht all its elements are distinct.
 for example:
A = 5 7 5 11 13 2 11 19 2 11
longest subarray = 7 5 11 13 2
 * */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> longest_subarray_with_distinct_elements(const vector<int>& A) {
    unordered_map<int, size_t> hash_a;
    int lstart = 0, lend = 0, maxl = 0;
    for ( int i = 0, start = 0; i < A.size(); i ++ ) {
        if ( hash_a.find(A[i]) != hash_a.end() ) {
            int end = i - 1;
            int len = end - start + 1;
            if ( maxl < len ) {
                maxl = len;
                lstart = start;
                lend = end;
            }
            start = hash_a[A[i]] + 1;
        }
        hash_a[A[i]] = i;
    }
    vector<int> res(A.begin() + lstart, A.begin() + lend + 1);
    return res;
}

int main() {
    vector<int> A = {5, 7, 5, 11, 13, 2, 11, 19, 2, 11};
    cout << "A = ";
    for_each(A.begin(), A.end(), [](int v){cout << v << " ";});
    cout << endl;
    cout << "longest subarray = ";
    vector<int> subarray = longest_subarray_with_distinct_elements(A);
    for_each(subarray.begin(), subarray.end(), [](int v) {cout << v << " ";});
    cout << endl;
    return 0;
}
