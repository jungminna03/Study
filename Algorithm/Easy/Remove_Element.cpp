//
// Created by admin on 26. 6. 23..
//

#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        erase(nums, val);
        return nums.size();
    }

    int removeElementPrev(vector<int>& nums, int val)
    {
        int res = 0;
        int cur = 0;

        for (auto num : nums)
        {
            if (num != val)
            {
                ++res;
                nums[cur++] = num;
            }
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> v1{3, 2, 2, 3};
    vector<int> v2{0,1,2,2,3,0,4,2};

    auto res1 = s.removeElement(v1, 3);
    auto res = s.removeElement(v2, 2);

    return 0;
}
