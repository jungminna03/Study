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
        vector<int> twoSum(vector<int> &nums, int target)
        {
            

            return vector<int>();
        }
};

int main()
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    auto result = s.twoSum(nums, target);

    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";

    return 0;
}