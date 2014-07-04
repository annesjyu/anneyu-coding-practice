/*
 *Let A and Q be arrays of strings, find a minimum subarray of A to cover Q. Suppose Q is small can be stored in RAM.
 * */
#include <algorithm>
#include <iostream>
#include <list>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

const int find_minimum_subarray(const vector<string>& A, const vector<string>& G) {
    if ( A.empty() || G.empty() || A.size() < G.size() ) {
        throw length_error("Input array size are too small.");
    }
    
    unordered_map<string, list<int> > hash_a; //list can easily push from back and pop from front, compared with vector, can be deleted and inserted O(1)
    unordered_map<string, int> hash_g;
    
    for ( int i = 0; i < G.size(); i ++ ) {
        string s = G[i];
        transform (s.begin(), s.end(), s.begin(), ::tolower); //use for_each c++11 syntax
        hash_g[s]++; //frequency of each word
    }

    //debug
    cout << "hash_g: " << endl;
    for ( auto &p : hash_g ) {
        cout << "key = " << p.first << ", value = " << p.second << endl;
    }

    bool matched = false;
    int min_len = A.size(), min_start = 0, min_end = A.size() - 1;
    for ( int i = 0 ; i < A.size(); i ++ ) {
        string s = A[i];
        transform(s.begin(), s.end(), s.begin(), ::tolower); //tolower is a global namespace not std
        if ( hash_g.find(s) != hash_g.end() ) {
            hash_a[s].emplace_back(i); //add a new position to the list
            if ( hash_a[s].size() > hash_g[s] ) {
                hash_a[s].pop_front(); //more than enough occurence found, discard the first matched position
            }
            if ( !matched ) {
                if ( hash_g.size() == hash_a.size() ) {
                    auto itg = hash_g.begin();
                    auto ita = hash_a.begin();
                    while ( itg != hash_g.end() && ita != hash_a.end() ) {
                        if ( itg->second != ita->second.size() ) {
                            break;
                        }
                        ita++; itg++;
                    }
                    matched = (itg == hash_g.end() && ita == hash_a.end());
                }
            }
            if ( matched ) { //found all strings in g
                //debug
                cout << "hash_a: ";
                for ( auto &p : hash_a ) {
                    cout << "k = " << p.first << ", v = ";
                    for ( auto &idx : p.second ) {
                       cout << idx << " | ";
                    }
                }
                cout << endl;
                //update min subarray size
                int start = A.size() - 1, end = i;
                auto it = hash_a.begin();
                while ( it != hash_a.end() ) {
                    if ( start > it->second.front() ) {
                        start = it->second.front();
                    } //find the start position of subarray, lest index
                    it++;
                }
                int len = end - start + 1;
                if ( min_len > len ) {
                    min_len = len;
                    min_start = start;
                    min_end = end;
                    //debug
                    cout << "found another match: start = " << start;
                    cout << ", end = " << end << " :";
                    for ( int j = start; j <= end; j ++ ) {
                        cout << "\"" << A[j] << "\", ";
                    }
                    cout << endl;
                }
            }
        }    
    }
    return min_len;
}

int main(int argc, char** argv) {
    string test = "My paramount object in this struggle is to save the Union, and is not either to save or to destroy slavery. If I could save the Union without freeing any slave I would do it, and if I could save it by freeing all the slaves I would do it; and if I could save it by freeing some and leaving others alone I would also do that.";
    istringstream iss(test);
    vector<string> A;
    string line;
    while ( getline(iss, line, ' ') ) {
        for ( int i = 0; i < line.size(); i ++ ) {
            char c = line[i];
            if ( c == ',' || isspace(c) || ispunct(c) ) {
                line.erase(i, 1);
            }
        }
        A.emplace_back(line);
    }
    vector<string> G = {"save", "save", "Union"};
    
    cout << "A = ";
    for ( auto &s : A ) {
        cout << s << " ";
    }
    cout << endl;
    cout << "G = ";
    for ( auto &s : G ) {
        cout << s << " ";
    }
    cout << endl;
    
    const int len = find_minimum_subarray(A, G);
    cout << "found min subarray length = " << len << endl;

    return 0;
}
