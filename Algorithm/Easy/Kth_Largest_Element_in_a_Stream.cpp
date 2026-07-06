//
// Created by admin on 26. 5. 28..
//

#include <queue>
#include <vector>
using namespace std;

class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> pq;
    int largest;
    int k = 0;

public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (auto i : nums)
        {
            add(i);
        }
    }

    int add(int val) {
        pq.push(val);

        if (static_cast<int>(pq.size()) > k)
        {
            pq.pop();
        }

        return pq.top();
    }
};

int main()
{
    auto nums = vector<int>{1,2,3,4,5};
    auto* kth = new KthLargest(3, nums);

    auto res1 = kth->add(3); // return 4
    auto res2 = kth->add(5); // return 5
    auto res3 = kth->add(10); // return 5
    auto res4 = kth->add(9); // return 8
    auto res5 = kth->add(4); // return 8

    delete kth;

    nums = vector<int>{7, 7, 7, 7, 8, 3};
    kth = new KthLargest(3, nums);

    res1 = kth->add(2); // return 7
    res2 = kth->add(10); // return 7
    res3 = kth->add(9); // return 7
    res4 = kth->add(9); // return 8

    delete kth;

    return 0;
}

