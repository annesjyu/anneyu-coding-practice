/*
 * chunk a string into a valid ip address. print all possibilities.
 * e.g. 19216811, 192.168.1.1, 19.216.8.11, 19.216.81.1
 * */

#include <exception>
#include <iostream>
#include <string>

using namespace std;

bool valid_ip(string& ip) {
    //0., 11.0. are valid
    if ( ip.empty() || ip.size() > 3 || (ip.front() == '0' && ip.size() > 1) ) {
        return false;
    }
    int n = 0;
    try {
        n = stoi(ip);
    } catch (exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    return 0 <= n && n <= 255;
}

void gen_valid_ip_address(string& numbers) {
    //iterative solution
    for ( int i = 0; i < 3 && i < numbers.size(); i ++ ) {
        string ip1 = numbers.substr(0, i+1);
        if ( !valid_ip(ip1) ) {
            continue;
        }
        for ( int j = i + 1; j < i + 4 && j < numbers.size(); j ++ ) {
            string ip2 = numbers.substr(i+1, j-i);
            if ( !valid_ip(ip2) ) {
                continue;
            }
            for ( int k = j + 1; k < j + 4 && k < numbers.size(); k ++ ) {
                string ip3 = numbers.substr(j+1, k-j);
                if ( k + 1 < numbers.size() ) {
                    string ip4 = numbers.substr(k+1, numbers.size()-1-k);
                    if ( valid_ip(ip3) && valid_ip(ip4) ) {
                        cout << ip1 << "." << ip2 << "." << ip3 << "." << ip4 << endl;
                    }
                }
            }
        }     
    }    
}

int main() {
    string test = "19216811";
    cout << "test string = " << test << endl;
    cout << "valid ip addresses:" << endl;
    gen_valid_ip_address(test);
    return 0;
}
