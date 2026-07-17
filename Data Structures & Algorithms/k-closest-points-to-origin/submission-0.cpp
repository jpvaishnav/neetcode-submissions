class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        /*
        Approach: Traditional priority queue approach
        question requires k closest -> points with list distance
            -> Create heap of reverse type.
            -> max heap
        insert k elements with their distance
        iterate remaining elements.
        if distance of new element is greater than current heap top, then ignore
        otherwise pop heap, and insert this new element
        distance to be calculated by euclidean formula
            x^2 + y^2 of (x,y) from (0,0)
        in the end, put all remaining heap elements in vector<vector<vector<int>> and return

        Asking agent to write code for above
        */

        // Pair structure: {squared_distance, index_in_points_vector}
        // Max-heap prioritizes the largest distance at the top
        priority_queue<pair<int, int>> maxHeap;
        
        for (int i = 0; i < points.size(); ++i) {
            // Calculate squared Euclidean distance: x^2 + y^2
            int x = points[i][0];
            int y = points[i][1];
            int dist = x * x + y * y;
            
            if (maxHeap.size() < k) {
                // Insert the first k elements directly
                maxHeap.push({dist, i});
            } else if (dist < maxHeap.top().first) {
                // If current distance is smaller than the largest in our heap,
                // remove the largest and insert the current closer point
                maxHeap.pop();
                maxHeap.push({dist, i});
            }
        }
        
        // Extract all remaining elements from the heap into the result vector
        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            int index = maxHeap.top().second;
            result.push_back(points[index]);
            maxHeap.pop();
        }
        
        return result;
    }
};
