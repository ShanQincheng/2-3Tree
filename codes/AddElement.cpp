# include "headFile.h"

TwoThreeNode* AddElement(TwoThreeNode *head, ElementType element)
{
	if(head == NULL)
	{
		TwoThreeNode *newHead = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
		newHead->isTwoNode = true;
		newHead->keySmall = element;
		head = newHead;
			
		return head;
	}
	// top-down looking for the leaf node 
	TwoThreeNode *currentNode = GetInsertPosition(head, element);
	if(currentNode->isTwoNode == true)
	{
		AddTwoNode(currentNode, element);
		
		return head;
	}else{
		AddThreeNode(currentNode, element);
		
		return head;
	}
}
