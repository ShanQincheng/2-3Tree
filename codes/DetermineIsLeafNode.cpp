# include "headFile.h"


bool DetermineIsLeafNode(TwoThreeNode *twoThreeNode)
{
	if(twoThreeNode->leftChildNode != NULL)
		return false;
	else if(twoThreeNode->middleChildNode != NULL)
		return false;
	else if(twoThreeNode->rightChildNode != NULL)
		return false;
	else
		return true;	
}
