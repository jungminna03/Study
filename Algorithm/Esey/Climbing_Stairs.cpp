//
// Created by jungk on 26. 4. 29.
//

class Solution {
public:
    // 재귀는 쓸것이 못됨
    int climbStairsPrev(int n) {
        if (n <= 1) return 1;

        return climbStairs(n - 1) + climbStairs(n - 2);
    }

    int climbStairs(int n)
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
};

int main()
{
    Solution s;

    auto res = s.climbStairs(2);
    auto res2= s.climbStairs(3);
    auto res3= s.climbStairs(4);

    return 0;
}