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
    void reorderList(ListNode* head) {
        /*
        Pattern of re-ordering is picking ith node from start and jth node from end
        connect them, and increment pointers both side.
        If it was array or doubly linked list, then it would have been possible to traverse
        in both directions.
        And value modification is not allowed.
        So, to introduce array index accessing feature in linked list, we use HashMap here
        Unorder_Map<int index, ListNode> // hashTable
        we fill from i = 0 to i = n-1
        Then initialize i = 0, j = n-1
        Pick these indexed nodes from linked list. connect them, maintain tail
        i++, j--
        Time: O(N)
        Aux Space: O(N)
        */

        unordered_map<int, ListNode*> indexNodeMap;
        ListNode* curr = head;
        int index = 0;
        while(curr != NULL)
        {
            indexNodeMap[index] = curr;
            index++;
            curr = curr->next;
        }

        // for 0 length, 1 length, 2 length nodes, return
        if(index<=2)
        {
            return;
        }

        int i = 0;
        int j = index-1;
        ListNode* tail = NULL;
        while(i<j)
        {
            ListNode* firstPointerNode = indexNodeMap[i];
            ListNode* secondPointerNode = indexNodeMap[j];
            if(tail!=NULL)
            {
                // this wont be applied for first head node.
                // other than that, it will be applied for every node
                tail->next = firstPointerNode;
            }
            firstPointerNode->next = secondPointerNode;
            tail = secondPointerNode;
            i++;
            j--;
        }
        if(i == j) // if n is odd
        {
            ListNode* midPointerNode = indexNodeMap[i];
            tail->next = midPointerNode;
            tail = midPointerNode;
        }
        tail->next = NULL; // to cut tail from its next node;

        // Head is same, pointers are updated
    }
};
