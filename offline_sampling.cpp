/*
 * A be an array of n distict elements. return a subset of k elements of A. all subsets should be equally likely, use the random number generator as few as possible, use O(1) additional storage. You can return the result in the same array as input.
 * */
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void offline_sample_k(vector<int>& A, const int k) {
    default_random_engine gen((random_device())());
    for ( int i = 0; i < k; i ++ ) {
        uniform_int_distribution<int> n_dis(i, A.size() - 1);
        int l = n_dis(gen);
        swap(A[i], A[l]);
    }
    A.resize(k);
}

int main() {
    vector<int> A;
    for (int i = 0; i < 100; i ++ ) {
        A.emplace_back(i);
    }
    offline_sample_k(A, 20);
    cout << "after shuffle = ";
    for_each(A.begin(), A.end(), [](int i){cout << i << " ";});
    cout << endl;
    return 0;
}
