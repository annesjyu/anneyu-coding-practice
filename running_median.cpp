/*
compute the running median of a sequence, the time complexity should be O(logn) per element read in, where n is the number of values read in up to that element.
*/
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void running_median() {
    int n;
    priority_queue<int, vector<int>, greater<int> > min_larger_heap;
    priority_queue<int, vector<int>, less<int> > max_smaller_heap;

    while ( cin >> n ) {
        if ( min_larger_heap.empty() || n > min_larger_heap.top() ) {
            min_larger_heap.push(n);
            if ( min_larger_heap.size() - max_smaller_heap.size() > 1 ) {
                max_smaller_heap.push(min_larger_heap.top());
                min_larger_heap.pop();
            }
        } else {
            max_smaller_heap.push(n);
            if ( max_smaller_heap.size() - min_larger_heap.size() > 1 ) {
                min_larger_heap.push(max_smaller_heap.top());
                max_smaller_heap.pop();
            }
        }
        
        cout << "n = " << n << ", median = ";

        if ( min_larger_heap.size() == max_smaller_heap.size() ) {
            cout << (min_larger_heap.top() + max_smaller_heap.top()) * 0.5 << endl;
        } else if (min_larger_heap.size() > max_smaller_heap.size() ) {
            cout << min_larger_heap.top() << endl;
        } else {
            cout << max_smaller_heap.top() << endl;
        }
    }
}

int main() {
    running_median();
    return 0;
}
