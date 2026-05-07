//
// Created by jungk on 26. 5. 7.
//

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1; // static_cast<int>(numbers.size()) - 1;

        while (left <= right) // left < right
        {
            if (numbers[left] + numbers[right] == target) // 미리 계산해서 재사용
                return {left + 1, right  + 1};
            else if (numbers[left] + numbers[right] > target)
                right -= 1; // --right;
            else
                left += 1; // ++right;
        }

        // return {};
    }
};

int main()
{
    Solution s;

    vector<int> nums = {2,7,11,15};
    vector<int> nums2 = {2, 3, 4};
    vector<int> nums3 = {-1, 0};

    auto res = s.twoSum(nums, 9);
    auto res2 = s.twoSum(nums2, 6);
    auto res3 = s.twoSum(nums3, -1);

    return 0;
}