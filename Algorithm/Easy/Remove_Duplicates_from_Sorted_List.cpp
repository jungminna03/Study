//
// Created by jungk on 26. 3. 18..
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
    // 포인터에서 초회 nullptr체크는 필수
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;

        auto h = head;

        while (h->next != nullptr)
        {
            if (h->val == h->next->val)
            {
                auto temp = h->next;
                h->next = h->next->next;
                delete temp;
            }
            else
                h = h->next;
        }

        return head;
    }
};

int main()
{
    Solution s;

    ListNode* l = new ListNode(1);
    ListNode* l2 = new ListNode(1);
    ListNode* l3 = new ListNode(2);
    l->next = l2;
    l2->next = l3;

    auto r = s.deleteDuplicates(l);

    return 0;
}