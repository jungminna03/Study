//
// Created by jungk on 26. 4. 19..
//

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums)
    {
        int count = 0;

        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i] != nums[count])
            {
                nums[++count] = nums[i];
            }
        }

        return count + 1;
    }
};

int main()
{
    Solution s;

    vector<int> intput1 {1, 1, 2};
    vector<int> intput2 {0, 0, 1, 1, 1, 2, 2, 3, 3 ,4};

    auto res = s.removeDuplicates(intput1);
    auto res2 = s.removeDuplicates(intput2);

    return 0;
}