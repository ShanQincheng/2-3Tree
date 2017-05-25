# include "headFile.h"

TwoThreeNode *GetHeadNode(TwoThreeNode *currentNode)
{
	TwoThreeNode *temp;
	temp = currentNode;
//	while(currentNode != NULL && currentNode->parentNode != NULL)
//		currentNode = currentNode->parentNode;

	while(temp != NULL && temp->parentNode != NULL)
		temp = temp->parentNode;
		
	//return currentNode;
	return temp;
}
