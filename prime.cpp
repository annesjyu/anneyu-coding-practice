/*
 * generate primes from 1 to n
 * */
#include <iostream>
#include <vector>

using namespace std;

vector<int> generate_prime_1_to_n(const int n) {
    vector<int> res;
    res.emplace_back(2);
    for ( int i = 3; i <= n; i ++ ) {
        bool is_prime = true;
        for ( int j = 0; j < res.size() && res[j] <= (i >> 1); j ++ ) {    
            if ( i % res[j] == 0 ) {
                is_prime = false;
                break;
            }
        }
        if ( is_prime ) {
            res.emplace_back(i);
        }
    }
    res.insert(res.begin(),1);
    return res;
}

int main() {
    vector<int> primes = generate_prime_1_to_n(100);
    cout << "primes <= " << 100 << " :" << endl;
    for_each(primes.begin(), primes.end(), [](int i){ cout << i << " "; });
    cout << endl;
}
