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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int total_nodes = 0;
        ListNode* curr = head;
        while(curr != NULL)
        {
            total_nodes++;
            curr = curr->next;
        }

        int traversals = total_nodes - n -1;
        // edge-case from examples
        if(traversals == -1)
        {
            return head->next;
        }

        curr = head;
        while(traversals!=0)
        {
            curr=curr->next;
            traversals--;
        }
        ListNode* temp = curr->next;
        curr->next = curr->next->next;
        // Delete temp;
        return head;

    }
};
