//
// Created by jungk on 26. 4. 24..
//

class Solution {
public:
    // DP 감이 안 잡히네,,, 더 풀어봐야겠다.
    int fib(int n) {
        if (n <= 1) return n;

        int prev1 = 0;
        int prev2 = 1;
        int current = 0;

        for (int i = 2; i <= n; i++)
        {
            current = prev1 + prev2;
            prev1 = prev2;
            prev2 = current;
        }

        return current;
    }
};

int main()
{
    Solution s;

    auto res = s.fib(2);
    auto res2 = s.fib(3);
    auto res3 = s.fib(4);

    return 0;
}