#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

int main() {
    int n;
    cin >> n;
    
    vector<Point> points;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }
    
    // Sort points by x-coordinate
    sort(points.begin(), points.end());
    
    int count = 0;
    
    // For each point as a potential bottom-left corner
    for (int i = 0; i < n; i++) {
        // Set to store y-coordinates of points with x > points[i].x
        set<int> activeY;
        
        // Process points with larger x-coordinate
        for (int j = i + 1; j < n; j++) {
            // If this point has larger y-coordinate, it could be a top-right corner
            if (points[j].y > points[i].y) {
                // Check if there are any active points in the y-range (points[i].y, points[j].y)
                auto it = activeY.lower_bound(points[i].y + 1);
                if (it == activeY.end() || *it >= points[j].y) {
                    // No points in the open interval (points[i].y, points[j].y)
                    // This means the rectangle is empty
                    count++;
                }
            }
            
            // Add current point's y-coordinate to active set
            activeY.insert(points[j].y);
        }
    }
    
    cout << count << endl;
    
    return 0;
}