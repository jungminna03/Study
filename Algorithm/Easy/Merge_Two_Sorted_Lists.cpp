//
// Created by admin on 26. 6. 16..
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;

            }

            tail = tail->next;
        }

        if (list1 != nullptr) tail->next = list1;
        if (list2 != nullptr) tail->next = list2;

        return dummy.next;
    }
};

int main()
{
    Solution s;

    // Example 1: list1 = [1,2,4], list2 = [1,3,4] -> [1,1,2,3,4,4]
    ListNode *list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);

    ListNode *list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);

    auto res1 = s.mergeTwoLists(list1, list2);

    // Example 2: list1 = [], list2 = [] -> []
    auto res2 = s.mergeTwoLists(nullptr, nullptr);

    // Example 3: list1 = [], list2 = [0] -> [0]
    ListNode *list3 = new ListNode(0);
    auto res3 = s.mergeTwoLists(nullptr, list3);

    return 0;
}