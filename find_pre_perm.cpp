/*
 * given a permutation, representing by an array A of integers, find the previous and next permutations.
 * */

#include <iostream>
#include <vector>

using namespace std;

vector<int> find_pre_perm(vector<int>& perm) {
    //from left, find the first integer which is larger than its following integer
    int i = perm.size() - 1;
    while ( i >= 1 && perm[i] > perm[i-1]) {    
        i--;
    }
    
    if ( i == 0 ) {
        return {}; //the smallest perm, no permutation is before it
    }
    
    int replace = i - 1;
    int prev = perm.size() - 1;

    //find the smallest integer which is larger than the to-be-replaced integer
    while ( prev >= i && perm[prev] > perm[replace] ) {    
        prev--;
    }
    
    vector<int> prev_perm = perm;
    swap(prev_perm[replace], prev_perm[prev]); // swap the to-be-replaced integer with the smallest integer which is larger than it

    reverse(prev_perm.begin() + i, prev_perm.end());
    return prev_perm;
}

void test(vector<int>& test) {
    vector<int> res = test;
    while ( !res.empty() ) {
        res = find_pre_perm(res);
        for_each(res.begin(), res.end(), [](int i) {cout << i << " ";});
        cout << endl;
    }
}

int main() {
    vector<int> test1 = {4, 3, 2, 1};
    cout << "test = ";
    for_each(test1.begin(), test1.end(), [](int i) {cout << i << " ";});
    cout << endl;
    test(test1);
    return 0;
}
