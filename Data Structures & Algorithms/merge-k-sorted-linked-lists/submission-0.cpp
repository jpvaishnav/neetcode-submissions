/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        /* k pointer problem
        put k pointer - one at each linked list
        find pointer with min value, put this value in final chain, and move further that pointer.
        keep on doing this, till we reach end of list for all k pointers
        // How do we know which one is min among k pointers - should we do O(k) traversal each time
        // that would be O(k*N) time. k = number of linked lists. N = size of final linked list
        // Finding Min of K elements -> Use MinHeap
        Perform top, pop, push operations in O(K) time
        // time complexity would be reduced to O(N*logK)
        Aux Space complexity: O(K), for min heap of K size
        */

        if(lists.size() == 0)
        {
            return NULL;
        }

        ListNode* ans = NULL;
        ListNode* ansHead = NULL;

        priority_queue<pair<int, ListNode*>, 
                        vector<pair<int,ListNode*>>, 
                        greater<pair<int, ListNode*>> > minHeap; // do we need initialization in c++?
        
        for(auto list: lists)
        {
            if(list!=NULL)
            {
                minHeap.push(make_pair(list->val, list));
            }
        }
        // all lists are covered so far

        while(minHeap.empty() == false)
        {
            pair<int, ListNode*> top = minHeap.top();
            minHeap.pop();
            ListNode* topNode = new ListNode(top.first);
            if(ans == NULL)
            {
                ans = topNode;
                ansHead = ans;
            }
            else
            {
                ans->next=topNode;
                ans = topNode;
            }

            // top node list should add its next value in heap
            ListNode* topPtr = top.second;
            if(topPtr->next !=NULL)
            {
                minHeap.push(make_pair(topPtr->next->val, topPtr->next));
            }
        }

        return ansHead;
    }
};
