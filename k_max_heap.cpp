/*
 * Give a max-heap on n elements, represented as an array A, design an algorithm that computes the k largest elements stored in A. You can not modify the heap.
 * Anne Yu
 * July 1, 2014
 * */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int, int> Item; //first = position, second = value

class lesscmp {
    public:
        bool operator() (const Item& a, const Item& b) {
            return ( a.second < b.second ) ; 
        }
};

void k_largest(const vector<int>& A, const int k) {
    if ( k > A.size() || A.empty() ) {
        throw length_error("Array is too small");
    }
    
    priority_queue<Item, vector<Item>, lesscmp> max_q;
    max_q.emplace(0, A[0]);
    int count = 0;

    while ( !max_q.empty() && count < k ) {
        Item i = max_q.top();
        cout << i.second << ", ";
        max_q.pop();
        int child = 2 * i.first + 1;
        if ( child < A.size() ) {
            max_q.emplace(child, A[child]);
        }
        if ( ++child < A.size() ) {
            max_q.emplace(child, A[child]);
        }
        count ++;     
    }
    cout << endl; 
}

int main() {
    vector<int> A = {74,64,50,38,20,40,29,17,10,11,18,30,20,14,28};
    for ( auto &i : A ) {
        cout << i << ", ";
    }
    cout << endl;
    k_largest(A, 6);
    return 0;
}

