/*
 * take a postive number and return pascal triangles up to n levels.
 * In mathematics, Pascal's triangle is a triangular array of the binomial coefficients. 
 * */

#include <iostream>
#include <vector>

using namespace std;

void gen_pascal_triangle(const int n) {
    vector<int> pascal(n, 0);
    pascal[0] = 1;
    cout << pascal[0] << endl;
    for ( int i = 1; i < n; i ++ ) {
        vector<int> old_pascal = pascal;
        for ( int j = 0; j <= i; j ++ ) {
            if ( j - 1 >= 0 ) {
                pascal[j] += old_pascal[j-1];        
            }
            cout << pascal[j] << " ";
        }
        cout << endl;
    }
}

int main() {
    gen_pascal_triangle(16);
    return 0;
}
