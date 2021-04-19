//[用两个栈实现队列](https://leetcode-cn.com/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof/)
#include<iostream>
#include<stack>
using namespace std;
class CQueue {
public:
    stack<int> stk1;
    stack<int> stk2;
    CQueue() {
    }
    void appendTail(int value) {
        stk1.push(value);
    }
    int deleteHead() {
        if (stk1.empty()) return -1;
        while (stk1.size() - 1)
        {
            stk2.push(stk1.top());
            stk1.pop();
        }
        int res = stk1.top();
        stk1.pop();
        while (stk2.size()) {
            stk1.push(stk2.top());
            stk2.pop();
        }
        return res;
    }
};

int main()
{
    CQueue* obj = new CQueue();
    obj->appendTail(5);
    obj->appendTail(2);
    cout<< obj->deleteHead() <<endl;
    cout<< obj->deleteHead() <<endl;
    cout << obj->deleteHead() << endl;
    delete obj;
    return 0;
}