//
// Created by jungk on 26. 5. 12.
//

#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1; // int mid = left + (right - left) / 2; 오버플로우 방지

        while (left <= right)
        {
            int mid = (left + right) / 2;

            if (nums[mid] == target)
                return mid;

            if (nums[mid] < target) // return이 포함된 if 뒤에는 else if를 안 붙임
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }
};

int main()
{
    Solution s;

    vector<int> nums = {-1, 0, 3, 5, 9, 12};

    auto res1 = s.search(nums, 9);
    auto res2 = s.search(nums, 2);

    return 0;
}