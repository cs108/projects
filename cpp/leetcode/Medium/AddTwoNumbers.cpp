/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;
		ListNode *head1;
		head1 = l1;
		//l1=l1+l2
		do
		{
			l1->val = l1->val + l2->val;
			if(l1->next==nullptr)
			{
				if (l2->next!=nullptr)
				{
					l1->next = new ListNode(0);
				}
			}
			l1 = l1->next;
		} while ((l2=l2->next)!=nullptr);
        
        //correct l1
		l1 = head1;
		while (l1!=nullptr)
		{
			if (l1->val / 10)
			{
				if (l1->next == nullptr)
				{
					l1->next = new ListNode(0);
				}
				l1->next->val += l1->val / 10;
				l1->val %= 10;
			}
			l1 = l1->next;
		}
        
		return head1;
	}
};
