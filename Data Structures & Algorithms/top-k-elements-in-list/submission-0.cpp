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
    }
};
