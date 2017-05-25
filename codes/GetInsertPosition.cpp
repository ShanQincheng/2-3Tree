# include "headFile.h"
/**
	获取插入位置 
**/
TwoThreeNode* GetInsertPosition(TwoThreeNode *headNode, ElementType toBeInsertedKey)  // 待插入學校信息結構體 
{
	TwoThreeNode *currentNode;  // 當前走到的節點位置 
	currentNode = headNode;
	
	while(DetermineIsLeafNode(currentNode) == false)   // 如果當前節點不是葉子節點 
	{
		if(currentNode->isTwoNode == true)	// 如果當前節點是 2 節點 
		{
			if(strcmp(toBeInsertedKey.schoolName, currentNode->keySmall.schoolName) < 0) // 如果待插入結構體中學校名稱小於當前 2 節點的 key 
			{
				currentNode = currentNode->leftChildNode;	// 向當前 2 節點左孩子繼續查找 
			}else{
				currentNode = currentNode->rightChildNode;	// 向當前 2 節點右孩子繼續查找 
			}	
		}else{ // 如果當前節點是 3 節點 
			if(strcmp(toBeInsertedKey.schoolName, currentNode->keySmall.schoolName) < 0)
			{
				currentNode = currentNode->leftChildNode;
			}else if(strcmp(toBeInsertedKey.schoolName, currentNode->keyBig.schoolName) >= 0){
				currentNode = currentNode->rightChildNode;
			}else{
				currentNode = currentNode->middleChildNode;
			}
		}	
		
	}
	
	return currentNode;		 
}



