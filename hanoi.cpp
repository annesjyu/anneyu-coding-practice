/*
 * The Tower of Hanoi (also called the Tower of Brahma or Lucas' Tower and sometimes pluralized) is a mathematical game or puzzle.
 * Only one disk can be moved at a time.
 * Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack i.e. a disk can only be moved if it is the uppermost disk on a stack.
 * No disk may be placed on top of a smaller disk.
 *
 * */
#include <iostream>
#include <vector>

using namespace std;

void hanoi_move(const int from, const int steps, const int to, const int intermediate) {
    //cout << "[Debug] : " << "hanoi_move(" << from << ", " << steps << ", " << to << ", " << intermediate << ")" << endl;
    if ( steps == 1 ) {
        cout << "move " << steps << " from " << from << " -> " << to << endl;
        return; 
    }
    hanoi_move(from, steps - 1, intermediate, to);
    hanoi_move(from, 1, to, intermediate);
    hanoi_move(intermediate, steps - 1, to, from);
}

void hanoi(const int n) {
    if ( n <= 0 ) {
        throw invalid_argument("n should be a positive number, >= 1");
    }
    hanoi_move(1,n-1,3,2);
    hanoi_move(1,1,2,3);
    hanoi_move(3,n-1,2,1);
}

int main() {
    vector<int> n = {2, 3, 10};
    for ( int i = 0; i < n.size(); i ++ ) {
        cout << endl;
        hanoi(n[i]);
        cout << endl;
    }
    return 0;
}
