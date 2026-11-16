//
// Created by admin on 26. 11. 16..
//

#include <string>
using namespace std;

class Solution {
public:
    string digitSum(string s, int k)
    {
        return 0;
    }

    string digitSumPrev(string s, int k) {
        int idx1 = 0;
        int idx2 = 0;
        int roundCount = s.size();
        int temp = 0;
        while (roundCount > k)
        {
            temp = 0;

            for (int i = idx1; i < k + idx1 && i < s.size(); ++i)
            {
                temp += s[i] - 48;
                ++idx2;
            }

            s.erase(idx1, k);
            s.insert(idx1, std::to_string(temp));

            if (idx2 < roundCount)
            {
                idx1 += to_string(temp).size();
            }
            else
            {
                idx1 = 0;
                idx2 = 0;
                roundCount = s.size();
            }

        }

        return s;
    }
};

int main()
{
    Solution s;

    auto res1 = s.digitSum("01234567890", 2);
    auto res2 = s.digitSum("248689", 4);

    return 0;
}