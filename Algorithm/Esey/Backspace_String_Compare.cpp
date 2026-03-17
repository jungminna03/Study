//
// Created by jungk on 26. 3. 17..
//

#include <iostream>
#include <stack>

using namespace std;

class Solution
{
public:

    // 역시나 스택을 2개나 만들어서 그런지 메모리 사용률이 높음
    bool backspaceComparePrev(string s, string t) {

        stack <char> st1;
        for (int i = 0; i < s.length(); i++)
        {
            if (isalnum(s[i]))
                st1.push(s[i]);
            else if (s[i] == '#' && !st1.empty())
                st1.pop(); // pop을 할 때는 항상 비어있는지 확인
        }

        stack <char> st2;
        for (int i = 0; i < t.length(); i++)
        {
            if (isalnum(t[i]))
                st2.push(t[i]);
            else if (t[i] == '#' && !st2.empty())
                st2.pop();
        }

        while (!st1.empty() && !st2.empty())
        {
            if (st1.top() != st2.top())
                return false;

            st1.pop();
            st2.pop();
        }

        if (!st2.empty() || !st1.empty()) return false;

        return true;
    }

    // 뒤에서부터 읽는 기법을 적용해야 할 때
    // 1. 미래가 과거를 결정할 때
    // 2. 삭제를 할 때마다 앞당겨지는 컨테이너에서 순회하며 삭제를 할 때
    // 3. 두 배열을 정렬 시키며 합칠 때 (뒤에서부터 큰 순서대로 채워넣기)
    bool backspaceCompare(string s, string t)
    {
        int sI = s.length() - 1;
        int tI = t.length() - 1;
        int skipS = 0;
        int skipT = 0;

        while (sI >= 0 && tI >= 0)
        {
            while (sI >= 0)
            {
                if (s[sI] == '#') {++skipS; --sI;}
                else if (skipS > 0) {--skipS; --sI;}
                else break;
            }

            while (tI >= 0)
            {
                if (s[tI] == '#') {++skipT; --tI;}
                else if (skipT > 0) {--skipT; --tI;}
                else break;
            }

            if (sI >= 0 && tI >= 0 && s[sI] != t[tI]) return false;
            if ((sI >= 0) != (tI >= 0)) return false;

            --sI;
            --tI;
        }

        return true;
    }
};

int main()
{
    Solution s;

    string s1 = "bxj##tw";
    string t1 = "bxj###tw";

    string s2 = "ab##";
    string t2 = "c#d#";

    string s3 = "a#c";
    string t3 = "b";

    auto result1 = s.backspaceCompare(s1, t1);
    auto result2 = s.backspaceCompare(s2, t2);
    auto result3 = s.backspaceCompare(s3, t3);

    return 0;
}