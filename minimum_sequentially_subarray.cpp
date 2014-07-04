/*
 *Give two integer-valued array A and Q, and cmputes a minimum length subarray of A such that sequentially covers Q. Assume all elements in Q are distinct.
 July 4, 2014 !

for example,
Q = 3 4 5
A = 1 2 3 4 10 43 23 54 5 3 45 90 4 100 5
hash_a:
5 at positions: 8 | 14 |
4 at positions: 3 | 12 |
3 at positions: 2 | 9 |

Found one solution: A[2] = 3, A[8] = 5
Found one solution: A[9] = 3, A[14] = 5
Final answer:
3 45 90 4 100 5
 * */

#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> minimum_sequentially_covered_array(vector<int>& A, vector<int>& Q) {
    unordered_set<int> hash_q(Q.cbegin(), Q.cend());
    unordered_map<int, list<size_t> > hash_a; //key is the integer, value is the position
    //debug
    cout << "Q = ";
    for_each( Q.begin(), Q.end(), [](int v) { cout << v << " "; } );
    cout << endl;
    
    cout << "A = ";
    for_each( A.begin(), A.end(), [](int v) { cout << v << " "; } );
    cout << endl;

    for ( int i = 0; i < A.size(); i ++ ) {
        if ( hash_q.find(A[i]) != hash_q.end() ) {
            hash_a[A[i]].emplace_back(i);
        }
    }
    
    //debug
    cout << "hash_a:" << endl;
    for ( auto &p : hash_a ) {
        cout << p.first << " at positions: ";
        for ( auto i : p.second ) {
            cout << i << " | ";
        }
        cout << endl;
    }
    cout << endl;

    int min_start = 0, min_end = A.size() - 1, min_len = A.size();
    while ( !hash_a[Q[0]].empty() ) {
        int start = hash_a[Q[0]].front();
        hash_a[Q[0]].pop_front();
        int end = start, i = 1;
        for ( ; i < Q.size(); i ++ ) {
            list<size_t> pos = hash_a[Q[i]];
            auto it = pos.begin();
            for ( ; it != pos.end(); it ++ ) {
                if ( (*it) > end ) {
                    end = (*it);
                    break;
                } 
            }
            if ( it == pos.end() ) {
                break; //can not find a position > start
            }
        }
        if ( i == Q.size() ) {
            //debug
            cout << "Found one solution: ";
            cout << "A[" << start << "] = " << A[start] << ", ";
            cout << "A[" << end << "] = " << A[end] << endl;  
            int len = end - start + 1;
            if ( len < min_len ) {
                min_start = start;
                min_end = end;
                min_len = len;
            }
        }
    }

    vector<int> res(A.begin() + min_start, A.begin() + min_end + 1);
    return res;
}

int main() {
    vector<int> A = {1, 2, 3, 4, 10, 43, 23, 54, 5, 3, 45, 90, 4, 100, 5};
    vector<int> Q = {3, 4, 5};
    vector<int> v = minimum_sequentially_covered_array(A, Q);
    cout << "Final answer: " << endl;
    for_each(v.begin(), v.end(), [](int v) {cout << v << " ";});
    cout << endl;
    return 0;
}
