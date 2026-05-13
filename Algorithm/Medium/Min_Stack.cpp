//
// Created by jungk on 26. 5. 11.
//

#include <set>
#include <stack>
using namespace std;

class MinStack {
    stack<int> stk;
    stack<int> minStk;

public:
    void push(int val) {
        stk.push(val);

        if (minStk.empty() || val < minStk.top())
            minStk.push(val);
    }

    void pop() {
        stk.pop();
        minStk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return minStk.top();
    }
};

int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    auto res1 = minStack.getMin(); // return -3
    minStack.pop();
    auto res2 = minStack.top();    // return 0
    auto res3 = minStack.getMin(); // return -2

    return 0;
}