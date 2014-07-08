/*
 * an array A of distinct integers and prints all permutations of A. No permutation appear more than once. The permutation should appear in lexicographic order. Your function should use O(n) space.
 * Space complexity is the maximum depth of recursion calls.
 * */
//#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print_perm_helper(vector<int>& A, const int idx, int& total) {
    for ( int i = (idx == 0 ? 0 : idx + 1); i < A.size(); i ++ ) {
        if ( i == 0  || A[i] != A[idx] ) {
            swap(A[idx], A[i]);
            for_each(A.begin(), A.end(), [](int i) { cout << i; });
            cout << endl;
            total ++;
            print_perm_helper(A, idx + 1, total);
            swap(A[idx], A[i]);
        }
    }
}

void print_perm(vector<int>& A) {
    if ( A.empty() ) {
        return;
    }
    int total = 0;
    sort(A.begin(), A.end());
    print_perm_helper(A, 0, total);
    cout << "Total = " << total << endl;
}

void print_perm_book(vector<int>& A) {
    int count = 0;
    sort(A.begin(), A.end());
    do {
        for_each(A.begin(), A.end(), [](int i) { cout << i; });
        cout << endl;
        count ++;
    } while (next_permutation(A.begin(), A.end()));
    cout << "Total = " << count << endl;
}

void print_my_next_permutation(vector<int>& A) {
    if ( A.empty() ) {
        return;
    }
    sort(A.begin(), A.end());
    int count = 1;
    do {
        for_each(A.begin(), A.end(), [](int i) { cout << i; });
        cout << endl;
        int i = A.size() - 2;
        while ( i >= 0 && A[i] >= A[i+1] ) {
            i --;
        }
        if ( i == -1 ) {
            break;
        }
        int l = i;
        for ( int j = i + 1; j < A.size(); j ++ ) {
            if ( A[j] > A[i] ) {
                l = j;
            }
        }
        swap(A[i], A[l]);
        reverse(A.begin() + i + 1, A.end());
        count ++;
    } while ( true );
    cout << "Total = " << count << endl;
}

int main() {
    vector<int> A = {2,2,0,3};
    
    cout << "[Debug] A = ";
    for_each(A.begin(), A.end(), [](int i) { cout << i; });
    cout << endl;
   
    cout  << "---------------------my implementation, rotation of integers----------" << endl; 
    vector<int> test1 = A;
    print_perm(test1);

    cout << "---------------------use next_permutation libary call----------" << endl;
    vector<int> test2 = A;
    print_perm_book(test2);

    //cout  << "---------------------my implementation, my next permutation----------" << endl;
    //vector<int> test3 = A;
    //print_my_next_permutation(test3);
    return 0;
}


