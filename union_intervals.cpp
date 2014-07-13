/*
 * take an input of a set of intervals I, and output the union of the intervals.
 * */

#include <iostream>
#include <vector>

using namespace std;

struct Interval {
    int start;
    int end;
    bool operator < (const Interval& rInterval) const {
        return ( start != rInterval.start ? ( start < rInterval.start ) : (end < rInterval.end) );
    }
};

vector<Interval> union_intervals(vector<Interval>& I) {
    if ( I.empty() ) {
        return {};
    }
    sort(I.begin(), I.end());
    vector<Interval> res;
    Interval interval = I[0];
    for ( int i = 1; i < I.size(); i ++ ) {
        if ( interval.end < I[i].start ) {
            res.emplace_back(interval);
            interval = I[i];
        } else if ( I[i].start <= interval.end && interval.end <= I[i].end ) {
            interval.end = I[i].end;
        }
    }
    res.emplace_back(interval); 
    return res;
}

int main() {
    vector<Interval> I = {{1,1}, {0,3},{2,4},{3,4},{5,7},{7,8},{8,11},{9,11},{12,14},{12,15},{16,17},{13,13}};
    auto unions = union_intervals(I);
    cout << "Input intervals:" << endl;
    for_each(I.begin(), I.end(), [](Interval& i) {cout << "[" << i.start << ", " << i.end << "]" << endl;});
    cout << endl;    
    cout << "Union intervals:" << endl;
    for_each(unions.begin(), unions.end(), [](Interval& i) {cout << "[" << i.start << ", " << i.end << "]" << endl;});   
    cout << endl;
    return 0;
}
