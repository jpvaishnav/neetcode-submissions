/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        /*
        Approach:
            create n copy node and maintain hash map of old and new node
            Then in second traversal, for each node,
                get its next and random mode
                get node's copy from hash-map m[curr]
                get next node's copy from hash-map m[curr->next]
                get random's copy from hash-map m[curr->random]
                and perform assignment
            O(n) time, O(n) aux space
            without destroying original LL

        Approach2: In places, in O(1) aux space
            - 1st traversal: create new node and insert between curr and curr next
            - 2nd traversal: assign random node for copy nodes
                -> curr->next->random = curr->random->next
                why not updating random as well in this iteration:
                    - because original next is still used in assigning random of future elements
                    - so updating next would create incorrect links for random assignments for further elements
            - 3rd traversal: assign next nodes for copy nodes
                - curr->next = curr->next->next
            maintain copyhead and return

        visual diagrams in notes
        */

        // base case: early exit
        if(head == NULL)
        {
            return NULL;
        }

        Node* curr = head;
        while(curr!=NULL)
        {
            Node* currNext = curr->next;
            Node* copyNode = new Node(curr->val);

            curr->next = copyNode;
            copyNode->next = currNext;
            curr = currNext;
        }

        curr = head;
        while(curr!=NULL)
        {
            // curr->random!=NULL also required as random can be NULL
            // in that case no need to re-assign as default random.next pointer is NULL
            if(curr->next && curr->random)
            {
                // these should be part of if condition instead of while, otherwise loop exists pre-mature, and provide incorrect output
                curr->next->random = curr->random->next;
            }
            curr = curr->next->next;
        }

        curr = head->next;
        // example: 1->1->2->2->3->3->.....
        // in this iteration, we start from copyHead instead of originalHead
        Node* copyHead = curr;
        while(curr != NULL && curr->next != NULL)
        {
            // curr->next != NULL is required for last node. otherwise it will hit
            // NULL->next throwing error
            curr->next = curr->next->next;
            curr=curr->next;
        }

        return copyHead;
    }
};
