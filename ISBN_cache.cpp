/*
 * Implement a cache for looking up prices of books identified by their ISBN. Use the Lease Recent Used strategy for cache eviction policy.
 *
 * LRU - least recently used oldest item
 * */

#include <iostream>
#include <unordered_map>

using namespace std;

class ISBNCache {
    private:
        struct isbn_item {
            float price;
            list<string>::iterator it;
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
                isbn_price[isbn] = isbn_item(isbn, policy.begin());
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
            isbn_price[isbn] = isbn_item(isbn, policy.begin());            
            cache_capacity ++;
        }
};
