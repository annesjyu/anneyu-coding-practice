/*
 * the input is the name of a log file, and returns a pair of pages which have the highest affinity.

For example:

webset users :
yoku : tata2
yelp : gege3
tweeter : freakout5 gege3 tata2
yahoo : freakout5 gege3 sortof4 tata2 user1
youku : user1
google : gege3 tata2 user1
max affinity pairs :
freakout5 gege3 tata2
freakout5 gege3 sortof4 tata2 user1
page tweeter, and yahoo have the highest affinity.
 * */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

pair<string, string> highest_affinity_pair(ifstream& ifs) {
    string site, user;
    unordered_map<string, set<string> > hash; //set has order over items. actually items are sorted. set implemented in RB tree. unordered_set is a real hash
    
    while ( ifs >> site >> user ) {
        remove_if(site.begin(), site.end(), ::isspace);
        remove_if(user.begin(), user.end(), ::isspace);
        hash[site].emplace(user);
    }

    //debug
    cout << "webset users :" << endl;
    for ( auto it = hash.begin(); it != hash.end(); it++ ) {
        cout << it->first << " : ";
        for ( auto itset = it->second.begin(); itset != it->second.end(); itset ++ ) {
            cout << *itset << " ";
        }
        cout << endl;
    }

    int max_affinity = 0;
    pair<string, string> max_pair;

    for ( auto it = hash.begin(); it != hash.end(); it ++ ) {
        auto another_it = it;
        for ( advance(another_it, 1); another_it != hash.end(); another_it ++ ) { //O(views^2)
            vector<string> common_users; //advance, next, prev are iterator algorithms
            set_intersection(it->second.begin(), it->second.end(), // use set_intersection algorithm
                             another_it->second.begin(), another_it->second.end(),
                             back_inserter(common_users)); //back_inserter, front_inserter
            if ( common_users.size() > max_affinity ) {
                max_affinity = common_users.size();
                max_pair.first = it->first;
                max_pair.second = another_it->first;
            }
        } 
    }
    
    //debug
    cout << "max affinity pairs :" << endl;
    for_each (hash[max_pair.first].begin(), hash[max_pair.first].end(), 
                [](const string& v) { cout << v << " "; });
    cout << endl;
    for_each (hash[max_pair.second].begin(), hash[max_pair.second].end(),
                            [](const string& v) { cout << v << " "; });
    cout << endl;

    return max_pair;
}

int main() {
    string filename = "log.txt";
    ifstream ifs(filename, ifstream::in);
    pair<string, string> affinity = highest_affinity_pair(ifs);
    cout << "page " << affinity.first << ", and " << affinity.second << " have the highest affinity." << endl;
    return 0;
}

