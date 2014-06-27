/*
 * Implement a queue using stacks.
 * Notes:
 *  if queue is empty, throw appropriate exception
 *  only if queue is empty, dump data, otherwise dont
 *  std::stack won't throw exception when the stack is empty, segmentation fault will be thrown
 *  For example,
 *  Push = 1, 2, 3, 4, 5,
 *  Top = 1
 *  After one pop, Top = 2
 * */

#include <iostream>
#include <stack>

using namespace std;

class QueueUseStack {
    private:
        stack<int> in_stack;
        stack<int> out_stack;

    public:
        void push (const int v) {
            in_stack.push(v);
        }

        void pop() {
            if ( out_stack.empty() ) {
                _dump_data();
            }
            if ( !out_stack.empty() ) {
                out_stack.pop();
            } else {
                throw length_error("Empty queue");
            }
        }

        const int top() {
            if ( out_stack.empty() ) {
                _dump_data();
            }
            if ( !out_stack.empty() ) {
                return out_stack.top();
            } 
            throw length_error("Empty queue");
        }

        void _dump_data() {
            while ( !in_stack.empty() ) {
                int v = in_stack.top();
                out_stack.push(v);
                in_stack.pop();
            }
        }
};

int main() {
/*
    stack<int> s;
    s.push(1);
    cout << s.top() << endl;
    s.pop();
    //std::stack if stack is empty, top() and pop() threw segmentation fault 
*/
    QueueUseStack q;
    cout << "Push = ";
    for (int i = 1; i <= 5; i ++ ) {
        cout << i << ", ";
        q.push(i);
    }
    cout << endl;
    cout << "Top = " << q.top() << endl;
    q.pop();
    cout << "After one pop, Top = " << q.top() << endl;
    return 0;
}
