/*
 * Let D be a set of strings. write a function that takes as input a string s and returns the shortest prefix of s which is not a prefix of any string in D. the set D does not change. the function is called many times with different inputs.
 July 5, 2014
 * For example:
    test1 = dog be cut , s = cat, shortest prefix not in set = ca
    test2 = dog be cut car , s = cat, shortest prefix not in set = cat
    test3 = dog be cut car cat , s = cat, shortest prefix not in set =
 * */

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Trie {
    struct TrieNode {
        unordered_map<char, unique_ptr<TrieNode> > children; //use a hash to store children nodes
    };
    
    unique_ptr<TrieNode> root;

    public:
        Trie () {
            root = unique_ptr<TrieNode>(new TrieNode);
        }
    
        void insert(const string& s) {
            auto *node = root.get();
            for ( const char& c : s ) {
                if ( node->children.find(c) == node->children.cend() ) {
                    node->children[c] = unique_ptr<TrieNode>(new TrieNode);
                }
                node = node->children[c].get();
            }
        }

        string find_shortest_prefix(const string& s) {
            string prefix;
            auto *node = root.get();
            for ( const char& c : s ) {
                if ( node->children.find(c) == node->children.cend() ) {
                    break;
                } else {
                    prefix += c;
                    node = node->children[c].get();
                }
            }
            return prefix; 
        }
       
         
        void print_all_words_helper (unique_ptr<TrieNode>& root) { 
            // depth first to traverse the tree, preorder, recursion
            TrieNode *p = root.get();
            if ( p->children.empty() ) {
                cout << " ";
                return;
            }
            for ( auto &kv : p->children ) {
                cout << kv.first;
                print_all_words_helper(kv.second);
            }
        }

        void print_all_words() {
            print_all_words_helper(root);
        }
};

string shortest_prefix_not_covered(const vector<string>& D, const string& s) {
    Trie trie;
    for ( auto &d : D ) {
        trie.insert(d);
    }

    cout << "Debug: ";
    trie.print_all_words();
    cout << endl;

    string prefix = trie.find_shortest_prefix(s);
    
    if ( prefix.size() < s.size() ) {
        return prefix += s[prefix.size()];
    }

    return {};
}

int main() {
    vector<string> test1 = {"dog","be","cut"};
    vector<string> test2 = {"dog", "be", "cut", "car"};
    vector<string> test3 = {"dog", "be", "cut", "car", "cat"};
    
    const string s = "cat";

    string r1 = shortest_prefix_not_covered(test1, s);
    //string r2 = shortest_prefix_not_covered(test2, s);
    //string r3 = shortest_prefix_not_covered(test3, s);

    cout << "test1 = ";
    for_each(test1.begin(), test1.end(), [](const string& input){ cout << input << " "; } );
    cout << ", s = " << s << ", shortest prefix not in set = " << r1 << endl;
    //cout << "test2 = ";
    //for_each(test2.begin(), test2.end(), [](const string& input){ cout << input << " "; } );
    //cout << ", s = " << s << ", shortest prefix not in set = " << r2 << endl;
    //cout << "test3 = ";
    //for_each(test3.begin(), test3.end(), [](const string& input){ cout << input << " "; } );
    //cout << ", s = " << s << ", shortest prefix not in set = " << r3 << endl;
   
    return 0;    
}


