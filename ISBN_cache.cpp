/*
 * Implement a cache for looking up prices of books identified by their ISBN. Use the Lease Recent Used strategy for cache eviction policy.
 *
 * LRU - least recently used oldest item
 * */

#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class ISBNCache {
    private:
        class isbn_item {
            public:
            float price;
            list<string>::iterator it;
            isbn_item(float p, list<string>::iterator i) : price(p), it(i) {}
        };
        unordered_map<string, isbn_item> isbn_price;
        list<string> policy;
        size_t cache_capacity;

    public:
        ISBNCache(const size_t capacity) {
            cache_capacity = capacity; 
        }

        bool look_up(string& isbn, float& price) {
            auto s = isbn_price.find(isbn);
            if ( s != isbn_price.end() ) {
                price = s->second.price;
                policy.erase(s->second.it);
                policy.insert(policy.begin(), isbn);
                isbn_item item(price, policy.begin());
                isbn_price[isbn] = item;
                return true;
            } else {
                cout << "Couldn't find price" << endl;
                return false;
            }
        }

        void insert(string& isbn, float price) {
            if ( isbn_price.size() == cache_capacity ) {
                string isbn = policy.back();
                auto it = isbn_price.find(isbn);
                isbn_price.erase(it);        
            }
            policy.emplace_front(isbn);
            isbn_item item(price, policy.begin());
            isbn_price[isbn] = item;            
            cache_capacity ++;
        }
};

int main() {
    ISBNCache cache(5);
    for ( int i = 1; i <= 5; i ++ ) {
        float price = float(i)*11.0;
        cout << "insert isbn = " << i << ", price = " << price << endl;
        string isbn = to_string(i);
        cache.insert(isbn, price);
    }
    cout << endl;

    float price = 0;
    string isbn = "2";
    if ( cache.look_up(isbn, price) ) {
        cout << "isbn = " << isbn << ", price = " << price << endl;
    }

    return 0;
}
