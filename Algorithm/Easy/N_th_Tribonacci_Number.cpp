//
// Created by jungk on 26. 7. 13..
//

#include <iostream>

using namespace std;

class Solution {
public:
    // 트리보나치 수열 Tn을 반환한다.
    // T0 = 0, T1 = 1, T2 = 1, Tn+3 = Tn + Tn+1 + Tn+2 (n >= 0)
    int tribonacciPrev(int n) {
        if (n <= 0) return 0;
        if (n <= 2) return 1;

        return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n -  3);
    }

    int tribonacci(int n) {
        vector<int> vec(n + 1);
        vec.push_back(0);
        vec.push_back(1);
        vec.push_back(1);

        for (int i = 3; i <= n; ++i)
        {
            vec.push_back(vec[i - 1] + vec[i - 2] + vec[i - 3]);
        }

        return vec[n];
    }
};

int main()
{
    Solution s;

    // Example 1: n = 4 -> 4
    auto res = s.tribonacci(4);   // expected: 4

    // Example 2: n = 25 -> 1389537
    auto res2 = s.tribonacci(25); // expected: 1389537

    return 0;
}
