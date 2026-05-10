//
// Created by jungk on 26. 5. 10.
//
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> set;
        int left = 0;
        int maxLen = 0;

        for (int right = 0; right < s.length(); right++)
        {
            while (set.count(s[right]))
            {
                set.erase(s[left]);
                left++;
            }

            set.insert(s[right]);
            maxLen = max(maxLen, right - left + 1);
        }

        return maxLen;
    }
};

int main()
{
    Solution s;

    auto res1 = s.lengthOfLongestSubstring("aabaab!bb");
    auto res2 = s.lengthOfLongestSubstring("abcabcbb");
    auto res3 = s.lengthOfLongestSubstring("bbbbb");

    return 0;
}
