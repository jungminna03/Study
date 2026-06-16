//
// Created by jungk on 26. 5. 31.
//

#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;

        for (int stone : stones)
        {
            pq.push(stone);
        }

        while (pq.size() > 1)
        {
            int a = pq.top(); pq.pop();
            int b = pq.top(); pq.pop();

            if (a != b)
            {
                pq.push(a - b);
            }

            if (pq.size() <= 0)
                return 0;
        }
        return pq.top();
    }
};

int main()
{
    Solution s;
    vector<int> stones = { 2,7,4,1,8,1 };
    vector<int> stones2 = { 2, 2 };

    auto res1 = s.lastStoneWeight(stones);
    auto res2 = s.lastStoneWeight(stones2);

    return 0;
}