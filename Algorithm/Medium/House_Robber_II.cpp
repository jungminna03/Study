//
// Created by jungk on 26. 7. 15.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums)
    {
        int size = nums.size();

        if (size == 0) return 0;
        if (size == 1) return nums[0];
        if (size == 2) return max(nums[0], nums[1]);

        vector<int> withoutFirst(size - 1);
        vector<int> withoutLast(size - 1);
        copy(nums.begin() + 1, nums.end(), withoutFirst.begin());
        copy(nums.begin(), nums.end() - 1, withoutLast.begin());

        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (i == 0)
            {
                withoutFirst[0] = nums[1];
                withoutLast[0] = nums[0];
            }
            else if (i == 1)
            {
                withoutFirst[1] = nums[2];
                withoutLast[1] = nums[1];
            }
            else if (i == 2)
            {
                withoutFirst[2] = nums[3] + nums[1];
                withoutLast[2] = nums[2] + nums[0];
            }
            else
            {
                withoutFirst[i] = nums[i + 1] + max(withoutFirst[i - 2], withoutFirst[i - 3]);
                if (i != size) withoutLast[i] = nums[i] + max(withoutLast[i - 2], withoutLast[i - 3]);
            }
        }

        int withoutFirstMax = max(withoutFirst[size - 2], withoutFirst[size - 3]);
        int withoutLastMax = max(withoutLast[size - 2], withoutLast[size - 3]);

        return max(withoutFirstMax, withoutLastMax);
    }
};

int main()
{
    Solution s;
    vector<int> vec1 {1,2,1,1};
    vector<int> vec2 {200,3,140,20,10};
    vector<int> vec3 {1, 2, 3};

    auto res1 = s.rob(vec1); // 3
    auto res2 = s.rob(vec2); // 340
    auto res3 = s.rob(vec3); // 3

    return 0;
}