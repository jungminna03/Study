//
// Created by jungk on 26. 4. 16..
//

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> countBitsPrev(int n) {
        vector<int> res;
        res.push_back(0);

        for (int i = 1; i <= n; ++i)
        {
            int temp1 = 0;
            int temp2 = i;

            for (int j = 1; j <= 32; ++j)
            {
                if (temp2 & 1)
                    ++temp1;

                temp2 >>= 1;
            }

            res.push_back(temp1);
        }

        return res;
    }

    vector<int> countBits(int n)
    {
        vector<int> res(n + 1);
        res[0] = 0; // 크기가 정해져 있다면 push_back는 절대 금지

        for (int i = 1; i <= n; ++i)
        {
            res[i] = res[i >> 1] + (i & 1);
        }

        return res;
    }
};

int main()
{
    Solution s;

    auto res = s.countBits(2);
    auto res2 = s.countBits(5);

    return 0;
}