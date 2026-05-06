//
// Created by jungk on 26. 3. 17..
//

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
    public:
        vector<int> twoSumPrev(vector<int> &nums, int target)
        {
            for (int i = 0; i < nums.size(); i++)
            {
                for (int j = i + 1; j < nums.size(); j++)
                {
                    if (nums[i] + nums[j] == target)
                        return {i, j};
                }
            }

            return vector<int>();
        }

        vector<int> twoSum(vector<int> &nums, int target)
        {
            unordered_map<int, int> map;

            for (int i = 0; i < nums.size(); i++)
            {
                auto targetNum = target - nums[i];

                if (map.find(targetNum) != map.end())
                    return vector<int>{map[targetNum], i};

                map[nums[i]] = i;
            }

            return vector<int>();
        }
};

int main()
{
    Solution s;
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> nums3 = {3, 3};
    int target3 = 6;

    auto result1 = s.twoSum(nums1, target1);
    auto result2 = s.twoSum(nums2, target2);
    auto result3 = s.twoSum(nums3, target3);

    for (int i = 0; i < result1.size(); i++)
        cout << result1[i] << " ";
    for (int i = 0; i < result2.size(); i++)
        cout << result2[i] << " ";
    for (int i = 0; i < result3.size(); i++)
        cout << result3[i] << " ";

    return 0;
}