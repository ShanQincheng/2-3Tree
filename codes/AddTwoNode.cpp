# include "headFile.h"

void AddTwoNode(TwoThreeNode *currentNode, ElementType toBeInsertedKey)
{
	/* 
	   compare the key to be inserted with the key in the current node
	   if toBeInsertedKey > node.key, do nonthing
	   		else swap(toBeInsertedKey, node.key)
	   so the variable toBeInsertedKey always is the big one
	*/
	SortTwoThreeNode(currentNode, &toBeInsertedKey);
	
	// 2-node after adding a new key to become a 3-node
	currentNode->isTwoNode = false;
	currentNode->keyBig = toBeInsertedKey;
}
