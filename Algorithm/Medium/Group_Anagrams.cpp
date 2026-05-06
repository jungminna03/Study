//
// Created by jungk on 26. 5. 6.
//

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;

        unordered_map<string, vector<string>> mp;
        for (auto str : strs) // const auto& str로 하면 복사하는거 막음
        {
            string s = str;
            sort(s.begin(), s.end());

            mp[s].push_back(str);
        }

        for (auto it = mp.begin(); it != mp.end(); ++it) // auto [_, value] : mp <- 구조적 바인딩
        {
            result.push_back(it->second);
        }

        return result;
    }
};

int main()
{
    Solution s;
    vector<string> strs1 = {"eat","tea","tan","ate","nat","bat"};
    vector<string> strs2 = {""};
    vector<string> strs3 = {"a"};

    auto res1 = s.groupAnagrams(strs1);
    auto res2 = s.groupAnagrams(strs2);
    auto res3 = s.groupAnagrams(strs3);


    return 0;
}