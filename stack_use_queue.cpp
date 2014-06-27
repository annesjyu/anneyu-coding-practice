/*
 * Implement a stsack using two queues
 * For example,
 * Push = 1, 2, 3, 4, 5,
 * Top = 5
 * After pop, Top = 4
 * Push 7, Top = 7
 */

#include <iostream>
#include <queue>

using namespace std;

class StackUseQueue {
    private:
        queue<int> qa;
        queue<int> qb;

    public:
        void push(const int v) {
            if ( !qa.empty() ) {
                qa.push(v);
            } else if ( !qb.empty() ) {
                qb.push(v);
            } else {
                qa.push(v);
            }
        }

        void pop() {
            if ( !qa.empty() ) {
                _dump_data(qa, qb);
                qa.pop();
            } else if ( !qb.empty() ) {
                _dump_data(qb, qa);
                qb.pop();
            } else {
                throw length_error("Empty stack");
            }
        }

        const int top() {
            queue<int> *ptr_full, *ptr_empty;
            if ( !qa.empty() ) {
                ptr_full = &qa;
                ptr_empty = &qb;
            } else if ( !qb.empty() ) {
                ptr_full = &qb;
                ptr_empty = &qa;
            } else {
                throw length_error("Empty stack");
            }
            
            _dump_data(*ptr_full, *ptr_empty);
            
            int v = ptr_full->front();
            ptr_full->pop();
            ptr_empty->push(v);
            return v;
        }

        void _dump_data(queue<int>& a, queue<int>& b) {
            while ( a.size() > 1 ) {
                b.push(a.front());
                a.pop();
            }
        }
};

int main() {
    StackUseQueue s;
    cout << "Push = ";
    for ( int i = 1; i <= 5; i ++ ) {
        s.push(i);
        cout << i << ", ";
    }
    cout << endl << "Top = " << s.top() << endl;
    s.pop();

    cout << "After pop, Top = " << s.top() << endl;
    
    s.push(7);
    cout << "Push 7, Top = " << s.top() << endl;

    return 0;
}
