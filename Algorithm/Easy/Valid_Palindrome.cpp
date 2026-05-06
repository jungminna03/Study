//
// Created by jungk on 26. 3. 17..
//

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution
{
    public:

    bool isPalindromePrev(string s)
    {
        vector<char> newString; // 메모리 할당을 하게됨.

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] >= 97 && s[i] <= 122)
                newString.emplace_back(s[i]);
            if (s[i] >= 65 && s[i] <= 90)
                newString.emplace_back(s[i] + 32);
            if (s[i] >= 48 && s[i] <= 57)
                newString.emplace_back(s[i]);
        }

        if (newString.empty()) return true;

        int j = newString.size() - 1;

        for (int i = 0; i < newString.size() / 2; i++)
        {
            if (newString[i] != newString[j])
                return false;

            --j;
        }

        return true;
    }

    // 이터레이터처럼 작동 시켜서 메모리 할당을 피함 (0.6 ~ 0.4 mb 절약)
        // SIGILL은 반환값이 없을때 뜨는 에러
    bool isPalindrome(string s)
    {
        int left = 0;
        int right = s.length() - 1;

        while (left <= right)
        {
            if (!isalnum(s[left]))
            {
                ++left;
                continue;
            }

            if (!isalnum(s[right]))
            {
                --right;
                continue;
            }

            if (tolower(s[left]) != tolower(s[right]))
                return false;

            ++left;
            --right;
        }

        return true;
    }
};

int main()
{
    Solution s;
    string s1 = "A man, a plan, a canal: Panama";
    string s2 = "race a car";
    string s3 = "......a.....";

    auto result1 = s.isPalindrome(s1);
    auto result2 = s.isPalindrome(s2);
    auto result3 = s.isPalindrome(s3);

    return 0;
}