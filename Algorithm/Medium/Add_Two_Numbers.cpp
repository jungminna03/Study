//
// Created by nyxrux62 on 26. 6. 29..
//

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode head(0);
        ListNode* cur = head.next;

        int temp = 0;
        while (l1 || l2) {
            int vel = 0;
            if (temp > 0) vel += temp--;
            vel += l1 ? l1->val : 0;
            vel += l2 ? l2->val : 0;

            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;

            if (vel >= 10) {
                vel -= 10;
                ++temp;
            }
            cur = new ListNode(vel);
            cur = cur->next;
        }

        return head.next;
    }
};


int main() {
    Solution s;

    ListNode *l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode *l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);

    auto res1 = s.addTwoNumbers(l1, l2); // [7,0,8]

    ListNode *l3 = new ListNode(0);
    ListNode *l4 = new ListNode(0);

    auto res2 = s.addTwoNumbers(l3, l4); // [0]

    return 0;
}