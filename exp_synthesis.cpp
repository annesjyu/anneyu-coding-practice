/*
 * Given an array of digits A and a nonnegtive integer k, intersperse multiplies and adds with the digits such at th the resulting arithmetical expression evaluates to k.
 * July 14, 2014
 * */

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

const int string_to_num(const string& s, int& i) {
    int n = 0;
    while ( i < s.size() && isdigit(s[i]) ) {
        n = n * 10 + s[i++] - '0';
    }
    i--;
    cout << "string_to_num " << n << endl;
    return n;
}

void evaluate_mult(stack<int>& numbers, stack<char>& operators) {
    if ( operators.top() != '*' ) {
        return;
    }
    operators.pop();
    int a = numbers.top(); numbers.pop();
    int b = numbers.top(); numbers.pop();        
    numbers.push(a*b);
}

const int evaluate_sol(const string& cur_sol) {
    cout << "[Debug] cur_sol = " << cur_sol << endl;
    stack<int> numbers;
    stack<char> operators;
    int i = 0;
    while ( i < cur_sol.size() ) {
        if ( isdigit(cur_sol[i]) ) {
            const int n = string_to_num(cur_sol, i);
            numbers.push(n);
            if ( numbers.size() >= 2 && ( !operators.empty() && operators.top() == '*') ) {
                try {
                    evaluate_mult(numbers, operators);
                } catch ( const exception& e ) {
                    cout << e.what() << endl;
                    return 0;
                }
            }
        } else if ( cur_sol[i] == '+' ) {
            if ( operators.empty() || operators.top() != '*' ) {
                operators.push('+');
            } else {
                try {
                    evaluate_mult(numbers, operators);
                } catch (const exception& e) {
                    cout << e.what() << endl;
                    return 0;
                }
            }
        }
        else {
            operators.push(cur_sol[i]);
        }
        i++;
    }
    cout << "[Debug] numbers = ";
    int res = 0;
    while ( !numbers.empty() ) {
        cout << numbers.top() << ", ";
        res += numbers.top();
        numbers.pop();
    }
    cout << endl;
    cout << "[Debug] operators = ";
    while ( !operators.empty() ) {
        cout << operators.top() << ", ";
        operators.pop();
    }
    cout << endl;
    cout << "[Debug]res = " << res << endl;
    return res;
}

string exp_synthesis_helper(const vector<int>& A, const int k, int id, string& cur_sol) {
    cur_sol += to_string(A[id]);
    if ( id == A.size() - 1 ) {
        if ( evaluate_sol(cur_sol) == k ) 
            return cur_sol;
        return {};
    }
    string ops = "+*";
    for ( int i = 0; i < ops.size(); i ++ ) {
        string new_sol = cur_sol + ops[i];
        string res = exp_synthesis_helper(A, k, id + 1, new_sol);
        if ( !res.empty() ) {
            return res;
        }
    }
    return exp_synthesis_helper(A, k, id + 1, cur_sol);
}

bool exp_synthesis(const vector<int>& A, const int k) {
    //only x and + used, including no operator, there are three cases: 
    //no operator, concatenate two integers to another integer; 
    //+ 
    //*
    string cur_sol;
    string res = exp_synthesis_helper(A, k, 0, cur_sol);
    cout << "[Debug] res solution = " << res << endl;
    return ( res.empty() ? false:true );
}

int main() {
    const int k = 995;
    vector<int> A = {1,2,3,2,5,3,7,8,5,9};
    //const int k = 9;
    //vector<int> A = {1,2,3};
    cout << "A = " << endl;
    for_each(A.begin(), A.end(), [](int i) { cout << i << ", ";});
    cout << endl;
    if ( exp_synthesis(A, k) ) {
        cout << "A can be evaluated to " << k << endl;
    } else {
        cout << "A can not be evaluated to " << k << endl;
    }
    return 0;
}
