//
// Created by jungk on 26. 4. 2..
//

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isAnagramPrev(string s, string t)
    {
        unordered_map<char, int> mp1;
        unordered_map<char, int> mp2;

        for (int i = 0; i < s.size(); ++i)
            mp1[s[i]]++;
        for (int i = 0; i < t.size(); ++i)
            mp2[t[i]]++;

        for (int i = 0; i < s.size(); ++i) // 둘이 같은 값인지 카운트 할거면 통합해서 ++, --로 조절시키고 0인지 확인
            if (mp1[s[i]] != mp2[s[i]])
                return false;

        for (int i = 0; i < t.size(); ++i)
            if (mp1[t[i]] != mp2[t[i]])
                return false;

        return true;
    }

    bool isAnagram(string s, string t)
    {
        if (s.size() != t.size()) // 미리 돌려보내기
            return false;

        int count[26] = {0}; // Hash 대신 배열 쓰기

        for (int i = 0; i < s.size(); ++i) // 하나로 합치기
        {
            count[s[i] - 'a']++;
            count[t[i] - 'a']--;
        }

        for (int i = 0; i < 26; ++i)
            if (count[i] != 0)
                return false;

        return true;
    }
};

int main()
{
    Solution s;

    auto s1 = "anagram";
    auto t1 = "nagaram";
    auto s2 = "rat";
    auto t2 = "cat";

    auto res1 = s.isAnagram(s1, t1);
    auto res2 = s.isAnagram(s2, t2);

    return 0;
}

