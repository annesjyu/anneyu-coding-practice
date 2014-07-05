/*
 * Collatz Conjecture:
 * Take any natural number n. If n is even, divide it by 2 to get n / 2. If n is odd, multiply it by 3 and add 1 to obtain 3n + 1. Repeat the process (which has been called "Half Or Triple Plus One", or HOTPO[6]) indefinitely. The conjecture is that no matter what number you start with, you will always eventually reach 1. The property has also been called oneness.

 For instance, starting with n = 6, one gets the sequence 6, 3, 10, 5, 16, 8, 4, 2, 1.
 n = 11, for example, takes longer to reach 1: 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1.
 * */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

vector<int> test_collatz_conjecture(const int n) {
    if ( n <= 0 ) {
        throw invalid_argument("n should be a positive integer");
    }
    
    unordered_set<int> proved; //a memory cache to remember numbers have been proved before, simple dp
    vector<int> result;

    for ( int i = 1; i <= n; i ++ ) {
        int t = i;
        int iteration = 0;
        unordered_set<int> tempset;
        do {
            if ( i == n ) result.emplace_back(t);
            if ( proved.find(t) != proved.end() ) {
                cout << "found cached item " << t << endl;
                break;
            } 
            if ( (t & 1) == 1 ) {
                tempset.emplace(t);
                t = 3 * t + 1;
            } else {
                t = t / 2;
            }
            iteration ++;
        } while ( t != 1 && t < numeric_limits<int>::max() && iteration < numeric_limits<int>::max());
        if ( t >= numeric_limits<int>::max() || iteration >= numeric_limits<int>::max() ) {
            string msg = "when calculate " + to_string(i) + ", either " + to_string(t) + " or " + to_string(iteration) + " overflows";
            throw overflow_error(msg);
        }
        for_each(tempset.begin(), tempset.end(), [&](int v) { proved.emplace(v); });
    }

    //debug
    cout << "total " << result.size() << " steps : " << endl << "( ";
    for_each(result.begin(), result.end(), [](int i){cout << i << " ";});
    cout << " ) " << endl;
    cout << "proved cache size = " << proved.size() << endl;

    return result;
}

int main() {
    int test1 = 11;
    int test2 = 27;
    vector<int> r1 = test_collatz_conjecture(test1);
    vector<int> r2 = test_collatz_conjecture(test2);
    return 0;
}
