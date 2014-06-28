/*
 * A be an array of length n, and w the window size. Entry A[i] is a pair (ti, vi), where ti is the timestamp and vi the traffic volume at that time. Assume A is sorted by incrasing timestamp. Design an algorithm to compute vi = max{vj|(ti - tj) <= w, j <= i} for 0 <= i <= n - 1.
 * For example,
 * timewindow = 10
 * timestamp = 0, A[0] =70, q.front = 70,
 * time = 1, A[1] =0, q.front = 70, max  = 70, q.size = 2, max_q.size = 2
 * time = 2, A[2] =87, q.front = 70, max  = 87, q.size = 3, max_q.size = 1
 * time = 3, A[3] =87, q.front = 70, max  = 87, q.size = 4, max_q.size = 2
 * time = 4, A[4] =38, q.front = 70, max  = 87, q.size = 5, max_q.size = 3
 * time = 5, A[5] =50, q.front = 70, max  = 87, q.size = 6, max_q.size = 3
 * time = 6, A[6] =68, q.front = 70, max  = 87, q.size = 7, max_q.size = 3
 * time = 7, A[7] =18, q.front = 70, max  = 87, q.size = 8, max_q.size = 4
 * time = 8, A[8] =68, q.front = 70, max  = 87, q.size = 9, max_q.size = 4
 * time = 9, A[9] =40, q.front = 70, max  = 87, q.size = 10, max_q.size = 5
 * time = 10, A[10] =37, q.front = 0, max  = 87, q.size = 10, max_q.size = 6
 * time = 11, A[11] =69, q.front = 87, max  = 87, q.size = 10, max_q.size = 3
 * time = 12, A[12] =95, q.front = 87, max  = 95, q.size = 10, max_q.size = 1
 * time = 13, A[13] =88, q.front = 38, max  = 95, q.size = 10, max_q.size = 2
 * time = 14, A[14] =17, q.front = 50, max  = 95, q.size = 10, max_q.size = 3
 * time = 15, A[15] =10, q.front = 68, max  = 95, q.size = 10, max_q.size = 4
 * time = 16, A[16] =52, q.front = 18, max  = 95, q.size = 10, max_q.size = 3
 *
 * A deque is used for emplace on the back and pop from back.
 * */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct TrafficVolume {
    int timestamp;
    int volume;
};

void max_traffic_within_window(vector<TrafficVolume>& A, int time_window) {
    queue<TrafficVolume> q;
    deque<TrafficVolume> max_queue; 
    q.emplace(A[0]);
    max_queue.emplace_back(A[0]);
    
    cout << "timewindow = " << time_window << endl;
    cout << "timestamp = " << A[0].timestamp << ", ";
    cout << "A[0] =" << A[0].volume << ", ";
    cout << "q.front = " << q.front().volume << ", ";
    cout << endl;

    for ( int i = 1; i < A.size(); i ++ ) {
        q.emplace(A[i]);
        if ( q.back().timestamp >= time_window ) {
            if ( q.front().volume == max_queue.front().volume ) {
                max_queue.pop_front();
            }
            q.pop();     
        }

        while ( !max_queue.empty() && max_queue.back().volume < A[i].volume ) {
            max_queue.pop_back();                
        }
        max_queue.emplace_back(A[i]);

        cout << "time = " << A[i].timestamp << ", ";
        cout << "A[" << i << "] =" << A[i].volume << ", ";
        cout << "q.front = " << q.front().volume << ", ";
        cout << "max  = " << max_queue.front().volume << ", ";
        cout << "q.size = " << q.size() << ", ";
        cout << "max_q.size = " << max_queue.size() << endl;
    }    
}

int main() {
    srand(time(0));
    vector<TrafficVolume> test;
    for ( int i = 0; i < 100; i ++ ) {
        TrafficVolume t;
        t.timestamp = i;
        t.volume = rand() % 100; 
        test.emplace_back(t);
    }

    max_traffic_within_window(test, 10);
}


