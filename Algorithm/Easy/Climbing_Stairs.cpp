//
// Created by jungk on 26. 4. 29.
//

#include <vector>

class Solution {
public:
    // 재귀는 쓸것이 못됨
    int climbStairsPrev(int n) {
        if (n <= 1) return 1;

        return climbStairs(n - 1) + climbStairs(n - 2);
    }

    int climbStairstemp(int n)
    {
        if (n <= 1) return n;

        int prev1 = 1;
        int prev2 = 1;
        for (int i = 1; i < n; ++i)
        {
            int temp = prev1 + prev2;
            prev1 = prev2;
            prev2 = temp;
        }

        return prev2;
    }

    int climbStairs(int n)
    {
        if (n <= 2) return n;

        std::pmr::vector<int> dp(n + 1);
        dp[0] = 1;
        dp[1] = 2;

        for (int i = 2; i < n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[n - 1];
    }
};

int main()
{
    Solution s;

    auto res = s.climbStairs(2);
    auto res2= s.climbStairs(3);
    auto res3= s.climbStairs(4);

    return 0;
}