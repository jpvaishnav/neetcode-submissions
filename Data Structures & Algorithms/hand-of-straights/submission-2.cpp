class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        /*
        Approach:
        similar to longest consecutive subsequence in an array:
            HashMap was used.
        - put all elements in HashTable of <element, frequency>
        In each iteration,
            pick min from elements which have frequency > 0
            check if currMin+1, currMin+2, currMin+n exists
                - if any of them does not exist, return false
                because need to re-arrange all cards
                - and with currMin, this is not possible
        Time comlexity: O(N square)

        What is greedy here?
        The greedy aspect of this solution is the decision to always pick the smallest available card (min_card) to start the next consecutive group.

        How to optimize?
            get_min part can be optimized
            use ordered hash table, which uses red black tree internally
            keep min element on top
            and remove element from map, when frequency drops to 0
            O(NlogN)
            each operation on red black tree takes O(logN)

        */

        // unordered_map<int, int> freqMap;
        // for(auto card: hand)
        // {
        //     freqMap[card]++;
        // }

        // while(true)
        // {
        //     // get min value with >0 frequency
        //     int min_card = INT_MAX;
        //     for(auto p: freqMap)
        //     {
        //         if(p.second > 0)
        //         {
        //             min_card = min(min_card,p.first);
        //         }
        //     }
        //     if(min_card == INT_MAX)
        //     {
        //         // all elements are covered
        //         return true;
        //     }
        //     freqMap[min_card]--;
        //     for(int i=1; i<groupSize; i++)
        //     {
        //         int next_card = min_card+i;
        //         if(freqMap.find(next_card) == freqMap.end()
        //             || freqMap[next_card] == 0)
        //         {
        //             // next_card does not exist or used in other group
        //             return false;
        //         }
        //         freqMap[next_card]--;
        //     }
        // }

        // syntax of ordered_map
        // std::map<int, int>
        // search - find
        // insert - []++ access operator
        // delete - .erase
        // size - empty()
        // first element through iterator: .begin()->first, .begin()->second

        map<int, int> oMap;

        for(auto card: hand)
        {
            oMap[card]++;
        }

        while(true)
        {
            if(oMap.empty())
            {
                // all elements are picked
                return true;
            }
            // pick first element, which is min, and on top of red black tree
            int curr_min = oMap.begin()->first;
            // 
            for(int i=0; i<groupSize; i++)
            {
                int next_card = curr_min + i;
                if(oMap.find(next_card) == oMap.end())
                {
                    return false;
                    // next_card not present
                }
                oMap[next_card]--;
                if(oMap[next_card] == 0)
                {
                    oMap.erase(next_card);
                }
            }
        }
    }
};
