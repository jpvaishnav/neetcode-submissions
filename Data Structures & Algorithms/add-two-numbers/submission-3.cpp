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
    ListNode* reverse(ListNode* l)
    {
        ListNode* curr = l;
        ListNode* prev = NULL;
        while(curr!=NULL)
        {
            ListNode* currNext = curr->next;
            curr->next = prev;
            prev = curr;
            curr = currNext;
        }
        return prev;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        /*
        Approach:
            - Since numbers are given in forward traversing format,
            but for addition, we need backward traversing.
                - maintain previous pointer(doubly linked list)
                - or reverse linked list
            - reverse both linked list
            - now traverse both from head pointer
                1 <- 2 <- 3
                4 <- 5 <- 6
                pointer is at 3 and 6 and traversing towards front now
            - maintain a reminder 0 which can be 1 if sum of 2 digits > 10
            - sum = l1->val + l2->val + reminder
            - l3-> val = sum%10
            - reminder = sum/10

            problem: question understanding/reading was incorrect,
                which was corrected by AI, and writing one example

                The FixThe standard LeetCode problem "Add Two Numbers" (LeetCode 2) provides the digits already in reverse order.

                visual diagram: https://github.com/jpvaishnav/Profile/blob/main/images/linkedlist_addsum.jpg
        */

        // ListNode* rev_l1 = reverse(l1);
        // ListNode* rev_l2 = reverse(l2);

        ListNode* rev_l1 = l1;
        ListNode* rev_l2 = l2;

        ListNode* sumListNode = NULL;
        ListNode* sumHead = NULL;
        int reminder = 0;
        while(rev_l1!= NULL || rev_l2!=NULL)
        {
            /*
            Why || or condition, not && condition
                - because numbers like 1234, 12
                    - && condition will terminate after 2 pointers
                        as second list is of size 2
                - and same applies for 23, 1234
                    where 1st one would terminate
                - hence considering default 0 and gating sum behind NULL condition
                - why maintaining reminder
                    - for case like: 999, 9
                        - hence 1 will be propagated to end
                    - and if reminder is non-zero in then end, then need to add reminder as new node in linked list
            */
            int sum = reminder;
            if(rev_l1!=NULL)
            {
                sum = sum + rev_l1->val;
                rev_l1 = rev_l1->next;
            }
            if(rev_l2!=NULL)
            {
                sum = sum + rev_l2->val;
                rev_l2 = rev_l2->next;
            }

            reminder = sum /10;
            int sum_val = sum%10;

            ListNode* newNode = new ListNode(sum_val);
            if(sumHead == NULL)
            {
                sumHead = newNode;
            }
            if(sumListNode!=NULL)
            {
                sumListNode->next = newNode;
            }
            sumListNode = newNode;
        }

        if(reminder > 0)
        {
            ListNode* newNode = new ListNode(reminder);
            sumListNode->next = newNode;
        }

        //ListNode* reversed_sum = reverse(sumHead);

        return sumHead;
        //return reversed_sum;
    }
};
