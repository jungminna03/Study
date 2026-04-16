//
// Created by jungk on 26. 4. 15..
//

#include <cstddef>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // 토끼와 거북이
    bool hasCycle(ListNode *head) {
        if (head == NULL || head->next == NULL)
            return false;

        ListNode* fastP = head->next->next;
        ListNode* slowP = head->next;

        while(fastP != NULL && fastP->next != NULL)
        {
            if (fastP == slowP) return true;

            fastP = fastP->next->next;
            slowP = slowP->next;
        }

        return false;
    }
};

int main()
{
    Solution s;

    {
        ListNode *head1 = new ListNode(3);
        ListNode *leaf1 = new ListNode(2);
        ListNode *leaf2 = new ListNode(0);
        ListNode *leaf3 = new ListNode(-4);

        head1->next = leaf1;
        leaf1->next = leaf2;
        leaf2->next = leaf3;
        leaf3->next = leaf1;

        auto res = s.hasCycle(head1);
    }

    {
        ListNode *head1 = new ListNode(1);
        ListNode *leaf1 = new ListNode(2);

        head1->next = leaf1;
        leaf1->next = head1;

        auto res = s.hasCycle(head1);
    }

    {
        ListNode *head = new ListNode(1);

        auto res = s.hasCycle(head);
    }

    return 0;
}
