//
// Created by jungk on 26. 3. 25..
//

#include <string>

using namespace std;

class Solution {
public:
    string removeDuplicates(string s) {
        for (int i = 0; i < s.length(); i++)
        {
            for (int j = 0; j < s.length(); j++)
            {
                if (s[i] == s[j])
                {
                    s.erase(s.begin() + i);
                    s.erase(s.begin() + j);
                }
            }
        }
    }
};

int main()
{
    Solution s;

    string s1 = "abbaca";
    string s2 = "azxxzy";

    auto res1 = s.removeDuplicates(s1);
    auto res2 = s.removeDuplicates(s2);

    return 0;
}