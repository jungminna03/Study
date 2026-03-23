//
// Created by jungk on 26. 3. 23..
//

#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroesPrev(vector<int>& nums) {

        if (nums.size() <= 1) return;

        int n = 0;

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[n] == 0)
            {
                nums.erase(nums.begin() + n);
                nums.push_back(0);
            }
            else
                ++n;
        }
    }

    // 배열을 다룰 때 가장 먼저 떠올리는 생각 = 원본을 파괴(Erase)하지 말고, 새로운 결과물을 덮어쓰자(Overwrite)
    // 포인터 개념을 활용해라
    void moveZeroes(vector<int>& nums) {
        int n = 0;

        for (int i = 0; i < nums.size(); i++)
            if (nums[i] != 0)
                nums[n++] = nums[i];

        while (n < nums.size()) {
            nums[n++] = 0;
        }
    }
};

int main()
{
    Solution s;

    auto nums = vector<int> {0,1,0,3,12};
    auto nums2 = vector<int> {0};

    s.moveZeroes(nums);
    s.moveZeroes(nums2);
}