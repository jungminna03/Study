//
// Created by jungk on 26. 4. 30.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // 각 집의 금액 nums가 주어질 때, 인접한 두 집을 연속으로 털지 않으면서
    // 훔칠 수 있는 최대 금액을 반환한다.
    int robPrev(vector<int>& nums) {
        int size = nums.size();
        if (size <= 1) return nums[0];
        if (size == 2) return max(nums[0], nums[1]);
        if (size == 3) return max(nums[1], nums[0] + nums[2]);

        vector<int> dp(size);
        dp[0] = nums[0];
        dp[1] = nums[1];
        dp[2] = nums[2] + nums[0];

        for (int i = 3; i < size; i++) {
            dp[i] = nums[i] + max(dp[i - 2], dp[i - 3]);
        }

        return max(dp[size - 1], dp[size - 2]);
    }

    int rob(vector<int>& nums) { // 벡터를 안 쓸 수 있음.
        int size = nums.size();
        if (size <= 1) return nums[0];
        if (size == 2) return max(nums[0], nums[1]);
        if (size == 3) return max(nums[1], nums[0] + nums[2]);

        nums[2] = nums[2] + nums[0];

        for (int i = 3; i < size; i++)
            nums[i] += max(nums[i - 2], nums[i - 3]);

        return max(nums[size - 1], nums[size - 2]);
    }
};

int main()
{
    Solution s;

    // Example 1: nums = [1,2,3,1] -> 4
    vector<int> nums1 {1, 2, 3, 1};

    // Example 2: nums = [2,7,9,3,1] -> 12
    vector<int> nums2 {2, 7, 9, 3, 1};

    auto res = s.rob(nums1);  // expected: 4
    auto res2 = s.rob(nums2); // expected: 12

    return 0;
}
