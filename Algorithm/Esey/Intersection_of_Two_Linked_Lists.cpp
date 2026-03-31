//
// Created by jungk on 26. 3. 31..
//

#include <cstddef>
#include <unordered_map>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* a = headA;
        ListNode* b = headB;

        while (headA != headB)
        {
            a = (a == nullptr) ? headB : a->next;
            b = (b == nullptr) ? headA : b->next;
        }

        return a;
    }
};

int main()
{
    ListNode *common = new ListNode(8);
    common->next = new ListNode(4);
    common->next->next = new ListNode(5);

    ListNode *headA = new ListNode(4);
    headA->next = new ListNode(1);
    headA->next->next = common;

    ListNode *headB = new ListNode(5);
    headB->next = new ListNode(6);
    headB->next->next = new ListNode(1);
    headB->next->next->next = common;

    Solution sol;
    ListNode *result = sol.getIntersectionNode(headA, headB);

    return 0;
}