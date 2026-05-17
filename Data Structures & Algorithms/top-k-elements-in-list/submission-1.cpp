class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> elementFrequencyMap;

        // O(N) time, O(N) aux spcae
        for(auto ele: nums)
        {
            elementFrequencyMap[ele]++;
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > min_heap;

       // O(N*logK)

        for(auto p: elementFrequencyMap)
        {
            // cout << "[DEBUG] "<< p.first << " " << p.second;
            if(min_heap.size() < k)
            {
                min_heap.push({p.second, p.first});
            }
            else
            {
                int currentTopFrequency = min_heap.top().first;
                if (p.second > currentTopFrequency)
                {
                    min_heap.pop();
                    min_heap.push({p.second, p.first});
                }
            }
        }

        //remaining elements in heap are top K
        vector<int> ans;
        while(!min_heap.empty())
        {
            ans.push_back(min_heap.top().second);
            min_heap.pop();
        }

        return ans;

        // Another solution can be create a HashMap of <Number, Frequency>
        // Then create a new array of pair of <Number, Frequency>
        // then sort this array with custom sort algo where we put compare() function condition
        // (p1, p2) : p1.second > p2.second
        // Larger elements appear first
        // Now get first K element in this sorted array
        // Problem: Worst case time complexity is O(N* logN)
    }
};
