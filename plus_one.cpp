/*
 * plus two A=<1,2,3>, A+2=<1,2,5>
 * 
 * */
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

void plus_two(int* A, int& sz) {
    if ( !A || !sz ) {
        throw invalid_argument("A is empty");
    } 
    int carry = 2;
    for( int i = sz - 1; i >= 0; i -- ) {
        A[i] += carry;
        if ( A[i] >= 10 ) {
            A[i] -= 10;
            carry = 1;
        } else {
            break;
        }
    }
    if ( carry ) {
        int* new_array = new int[++sz];
        for (int i = 1; i < sz; i ++ ) {
            new_array[i] = A[i - 1];
        }
        delete [] A;
        A = new_array;
    }
}

// assume A and B store positive numbers
vector<int> plus_vectors(vector<int>& A, vector<int>& B) {
    vector<int> res;
    int i = A.size() - 1, j = B.size() - 1, carry = 0;
    while ( i >= 0 || j >= 0 ) {
        if ( i >= 0 ) {
            carry += A[i--];
        }
        if ( j >= 0 ) {
            carry += B[j--];
        }
        res.emplace_back(carry % 10);
        carry = (carry >= 10 ? 1 : 0); 
    }
    if ( carry ) {
        res.emplace_back(carry);
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> minus_vectors(vector<int>& A, vector<int>& B) {
    //check sign
    const int n = A.size();
    const int m = B.size();
    bool positive = true ;
    if ( n < m ) {
        positive = false;
    } else if ( n == m ) {
        for ( int i = 0; i < n; i ++ ) {
            if ( A[i] < B[i] ) {
                positive = false;
                break;
            }
        }
    }
    auto l_it = A.begin(); auto l_end = A.end();
    auto s_it = B.begin(); auto s_end = B.end();
    if ( !positive ) {
        l_it = B.begin(); l_end = B.end();
        s_it = A.begin(); s_end = A.end();
    }
    //minus
    vector<int> res;
    int borrow = 0;
    while ( l_it != l_end ) {
        int m = (*l_it++) - borrow; 
        borrow = 0;
        if ( s_it != s_end ) {
            m -= (*s_it++);
        }
        if ( m < 0 ) {
            m += 10;
            borrow = 1;        
        }
        res.emplace_back(m);
    }
    assert(borrow==0);
    //rememer to remove 0 in the front
    while ( res.back() == 0 ) {
        res.pop_back();
    }
    //reverse result
    reverse(res.begin(), res.end());
    //insert sign
    if ( !positive ) {
        res.insert(res.begin(), -1);
    }
    return res;
}

int main() {
    /*
    vector<int> A = {2, 3, 9, 9};
    vector<int> B = {1, 4, 2, 9, 9, 0};
    vector<int> res = plus_vectors(A, B);
    cout << "A = ";
    for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    cout << endl;
    cout << "B = ";
    for_each(B.begin(), B.end(), [](int i){cout << i << " ";});
    cout << endl;
    cout << "res = ";
    for_each(res.begin(), res.end(), [](int i){cout << i << " ";});
    cout << endl;
    */
    
    cout << "test minus:" << endl;
    vector<int> A = {1,0,1};
    vector<int> B = {9,9, 9};
    vector<int> res = minus_vectors(A, B);
    cout << "A = ";
    for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    cout << endl;
    cout << "B = ";
    for_each(B.begin(), B.end(), [](int i){cout << i << " ";});
    cout << endl;
    cout << "res = ";
    for_each(res.begin(), res.end(), [](int i){
            if ( i == -1 ) {
                cout << "- ";
            } else {
            cout << i << " ";}
    });
    cout << endl;
    return 0;
}   

