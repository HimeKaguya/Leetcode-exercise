//[ÒÆ³ýÖØ¸´½Úµã](https://leetcode-cn.com/problems/remove-duplicate-node-lcci/)
#include<iostream>
using namespace std;
//Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    ListNode* removeDuplicateNodes(ListNode* head)
    {
        int nodes[20001] = { 0 };
        if (head == NULL) return head;
        ListNode* h = h->next, * pre = head;
        nodes[h->val] = 1;
        while (h)
        {
            if (nodes[h->val])
            {
                pre->next = h->next;
                ListNode* q = h;
                h = h->next;
                delete(q);
            }
            else
            {
                nodes[h->val] = 1;
                pre = h;
                h = h->next;
            }
        }
        return head;
    }
};
