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
    // 차이를 지우는 방법 찾기
    // 두 대상을 섞어서 차이를 상쇄시키는 작전

    // 실제 사용 예
    // 네트워크 동기화: 클라이언트 시간과 서버 시간을 이렇게 오프셋 계산을 통해 보정시킴
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