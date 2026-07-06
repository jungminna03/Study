//
// Created by jungk on 26. 6. 29.
//
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    int numOfStrings(vector<string>& patterns, string word) {
        int res = 0;

        for (const auto& pattern : patterns)
        {
            if (word.find(pattern) != string::npos)
                ++res;
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<string> input1 = {"a","b","c"};
    vector<string> input2 = {"a","abc","bc","d"};
    vector<string> input3 = {"a","a","a"};

    auto res1 = s.numOfStrings(input1, "abc");
    auto res2 = s.numOfStrings(input2, "aaaaabbbbb");
    auto res3 = s.numOfStrings(input3, "ab");

    return 0;
}