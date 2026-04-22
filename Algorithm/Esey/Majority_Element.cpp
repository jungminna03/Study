//
// Created by jungk on 26. 4. 22..
//

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElementPrev(vector<int>& nums) {
        unordered_map<int, int> map;
        int result = 0;
        int higest = 0;

        for (int num : nums)
            map[num] = map[num] + 1;

        for (auto pair : map)
            if (pair.second > higest)
            {
                result = pair.first;
                higest = pair.second;
            }

        return result;
    }

    // Boyer-Moore Voting
    // 과반수 원소가 있을때만 작동
    int majorityElement(vector<int>& nums)
    {
        int result = 0;
        int count = 0;

        for (int num : nums)
        {
            if (count == 0)
                result = num;

            count += (result == num) ? 1 : -1;
        }

        return result;
    }
};

int main()
{
    Solution s;

    vector<int> vec1 {3, 2, 3};
    vector<int> vec2 {2,2,1,1,1,2,2};

    auto result = s.majorityElement(vec1);
    auto result2 = s.majorityElement(vec2);

    return 0;
}