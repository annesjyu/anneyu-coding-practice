/*
 * given a list of list, compute their average, for example,
 * [
 * ["abc", "cde", 2.34],
 * ["abc", "cde", 3.42],
 * ["12","213a", 3.45],
 * ["a", "bccde", 4.56],
 * ["a", "bccde", 33.0]
 * ]
 *
 * solution one : using sort
 * solution two: using hash
 * */

#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Item {
    string f1;
    string f2;
    float value;
    Item(const string& _f1, const string& _f2, float _value) : f1(_f1), f2(_f2), value(_value) {} 
    bool operator < (const Item& a) const {
        return (f1 != a.f1) ? (f1 < a.f1) : (f2 < a.f2); 
    }
    bool operator == (const Item& a) const {
        return ( f1 == a.f1 && f2 == a.f2 );
    }
};

/*bool ItemLess (Item& i1, Item& i2) {
    return (i1.f1 != i2.f1 ? i1.f1 < i2.f1 : i1.f2 < i2.f2) ;
}*/

vector<Item> compute_average(vector<Item>& array) {
    if ( array.empty() ) {
        return {};
    }
    
    sort(array.begin(), array.end());

    Item prev = array[0];
    float sum = prev.value;
    int count = 1;
    vector<Item> res;

    for ( int i = 1; i < array.size(); i ++ ) {
        if ( array[i] == prev ) {
            sum += array[i].value;
            count += 1;
        } else {
            res.emplace_back(prev.f1, prev.f2, sum/count);        
            sum = array[i].value;
            count = 1;
        }
        prev = array[i];
    }

    res.emplace_back(prev.f1, prev.f2, sum/count);

    return res;
}

struct ItemHash {
    size_t operator()(const pair<string, string>& key) const {
        return (hash<string>()(key.first) ^ (hash<string>()(key.second) << 1));
    }
};

vector<Item> compute_average_hash(const vector<Item>& array) {
    unordered_map<pair<string, string>, pair<float, int>, ItemHash> table;
    for ( auto &item : array ) {
        //size_t key = hash<string>()(item.f1) ^ (hash<string>()(item.f2) << 2);
        pair<string, string> key = {item.f1, item.f2};
        table[key].first += item.value;
        table[key].second += 1;
    }
    
    vector<Item> res;
    for (auto it = table.begin(); it != table.end(); it ++ ) {
        res.emplace_back(it->first.first, it->first.second, it->second.first/it->second.second);    
    }

    return res;
}

int main() {
    vector<Item> array;
    array.emplace_back(string("abc"), string("cde"), float(1.0));
    array.emplace_back(string("abc"), string("cde"), float(2.0));
    array.emplace_back(string("a"), string("xyz"), float(3.0));
    array.emplace_back(string("a"), string("xyz"), float(4.0));
    array.emplace_back(string("ax"), string("yz"), float(5.0));
    array.emplace_back(string("123"), string("yz"), float(10.0));
    cout << "array = " << endl;
    for_each(array.begin(), array.end(), [](Item &item) {
            cout << item.f1 << " " << item.f2 << " " << item.value << endl;});
    cout << endl;

    vector<Item> avgs = compute_average(array);
    cout << "avgs = " << endl;
    for_each(avgs.begin(), avgs.end(), [](Item& item) {
            cout << item.f1 << " " << item.f2 << " " << std::hex << item.value << endl;});
    cout << endl;

    avgs = compute_average_hash(array);
    cout << "avgs = " << endl;
    for_each(avgs.begin(), avgs.end(), [](Item& item) {
            cout << item.f1 << " " << item.f2 << " " << std::hex << item.value << endl;});
    cout << endl;
    return 0;
}

