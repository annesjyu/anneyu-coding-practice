/*
 * takes an array A of n numbers, and returns the number of inverted pairs of indices
 * Divide and conquer O(nlogn)
 * Brute Force O(n^2)
 * */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int count_inversions_helper(vector<int>& A, const int l, const int h) {
    if ( l == h ) {
        return 0;
    }
    int mid = l + ( h - l ) / 2;
    int left_larger_than_right = count_inversions_helper(A, l, mid);
    left_larger_than_right += count_inversions_helper(A, mid + 1, h);
    //merge and count inversions
    vector<int> sorted_A = A;
    int i = l, j = mid + 1, k = l;
    while ( i <= mid && j <= h ) {
        if ( A[i] < A[j] ) {
            sorted_A[k++] = A[i++];
        } else {
            for ( int m = i; m <= mid; m ++ ) {
                cout << "Found " << A[m] << " > " << A[j] << endl;
                left_larger_than_right += 1;
            }
            sorted_A[k++] = A[j++];
        }
    }
    while ( i <= mid ) {
        sorted_A[k++] = A[i++];
    }
    copy(sorted_A.begin(), sorted_A.end(), A.begin());
    //for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    //cout << endl;
    return left_larger_than_right;
}

const int count_inversions(vector<int>& A) {
    if ( A.empty() ) {
        return 0;
    }
    return count_inversions_helper(A, 0, A.size() - 1);    
}

const int naive_solution(const vector<int>& A) {
    int res = 0;
    for ( int i = 0; i < A.size() - 1; i ++ ) {
        for ( int j = i + 1; j < A.size(); j ++ ) {
            if ( A[i] > A[j] ) {
                res ++;
                cout << "Found " << A[i] << " > " << A[j] << endl;
            }
        }
    }
    return res;
}

int main() {
    vector<int> A = {5, 4, 1, 2, 0, 9, 10};
    cout << "A = ";
    for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    cout << endl;
    
    cout << "naive solution inversions:" << endl << naive_solution(A) << endl;
    cout << endl << "divide and conquer inversions = " << endl << count_inversions(A) << endl;
    return 0;
}

