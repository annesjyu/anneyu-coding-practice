/*
 * sort lines of a text file, that has one million lines such that the average length of a line is 100 characters, but the longest lne is one million characters long.
 */
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void indirect_sort(const string& fname) {
    ifstream ifs(fname.c_str());
    vector<string> lines;
    vector<const string*> ref;
    string orgline, line;
    while ( !ifs.eof() ) {
        getline(ifs, orgline);
        line = orgline;
        remove_if(orgline.begin(), orgline.end(), ::isspace); //remove white spaces
        if ( orgline.empty() ) { //remove blank line
            continue;
        }
        lines.emplace_back(line);
        //cout << "[Debug Input] " << line << endl;
        //cout << "[Debug Input Address] " << &(lines.back()) << endl;
    }
    // after populate the lines array, start to put line's address into ref array, the lines array is a dynamically changed one
    for ( auto &l : lines ) {
        ref.emplace_back( &l );
        //cout << "[Debug Output Address] " << ref.back() << endl;
    }
    sort(ref.begin(), ref.end(), [](const string *rptr, const string *lptr)->bool { // return bool;
            return *rptr < *lptr;
    });
    ofstream ofs("test_indirect_sort_output.txt");
    for ( const string* ptr : ref ) {
        cout << "[Debug Output] " << *ptr << endl;
        ofs << *ptr << endl;
    }
}

int main() {
    string file_name("test_indirect_sort.txt");
    indirect_sort(file_name);
    cout << "Wrote to test_indirect_sort_output.txt" << endl;
    return 0;
}
