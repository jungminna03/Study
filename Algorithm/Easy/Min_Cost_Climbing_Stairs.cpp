//
// Created by jungk on 26. 7. 10..
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 계단의 각 칸 비용 cost가 주어질 때, 꼭대기(마지막 칸 다음)까지 도달하는
    // 최소 비용을 반환한다. 인덱스 0 또는 1에서 시작할 수 있고,
    // 비용을 지불하면 한 칸 또는 두 칸 오를 수 있다.
    int minCostClimbingStairs(vector<int>& cost) {
        int size = cost.size();
        vector<int> dp;
        dp.reserve(size);

        dp[0] = cost[0];
        dp[1] = cost[1];

        for (int i = 2; i < size; i++) {
            dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
        }

        return min(dp[size - 1], dp[size - 2]);
    }
};

int main()
{
    Solution s;

    // Example 1: cost = [10,15,20] -> 15
    vector<int> cost1 = {10, 15, 20};

    // Example 2: cost = [1,100,1,1,1,100,1,1,100,1] -> 6
    vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    auto res = s.minCostClimbingStairs(cost1);  // expected: 15
    auto res2 = s.minCostClimbingStairs(cost2); // expected: 6

    return 0;
}
