//
// Created by jungk on 26. 3. 18..
//

#include <vector>

using namespace std;

class Solution
{
public:
    int searchInsert(std::vector<int>& nums, int target) {
        
    }
};

int main()
{
    Solution s;

    vector<int> v = {1, 3, 5, 6};

    auto r = s.searchInsert(v, 5);
    auto r2 = s.searchInsert(v, 2);
    auto r3 = s.searchInsert(v, 7);

    return 0;
}