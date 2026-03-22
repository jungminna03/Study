//
// Created by jungk on 26. 3. 22..
//

#include <vector>

using namespace std;

class Solution
{
    public:
    int maxProfit(vector<int>& prices) {
        int min = prices[0];
        int result = 0;

        for (int i = 0; i < prices.size(); ++i)
        {
            if (prices[i] < min)
            {
                min = prices[i];
                continue;
            }

            int temp = prices[i] - min; // 이렇게 2번 이상 쓰는거는 변수로 저장하는게 속도가 빠름
            if (temp > result)
            {
                result = temp;
            }
        }

        return result < 0 ? 0 : result;
    }
};

int main()
{
    Solution s;
    auto prices = vector<int> {7, 1, 5, 3, 6, 4};
    auto prices2 = vector<int> {7, 6, 4, 3, 1};

    auto result = s.maxProfit(prices);
    auto result2 = s.maxProfit(prices2);

    return 0;
}