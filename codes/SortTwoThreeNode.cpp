# include "headFile.h"

void SortTwoThreeNode(TwoThreeNode *sortNode, ElementType *toBeInsertedKey)
{
	ElementType tempElement;
	TwoThreeNode *tempNodePointer;
	
	if(sortNode->isTwoNode == true)
	{
		if(strcmp(sortNode->keySmall.schoolName, toBeInsertedKey->schoolName) > 0) // 如果當前節點中的 key 大於待插入的 key 
		{
			tempElement = *toBeInsertedKey;			// 交換當前節點 key 與待插入的key 
			*toBeInsertedKey = sortNode->keySmall;
			sortNode->keySmall = tempElement;
		}
	}else{
		if(strcmp(sortNode->keySmall.schoolName, toBeInsertedKey->schoolName) > 0) // 如果待插入的 key 比當前節點的 small key 要小，則 small key 提升 
		{
			tempElement = *toBeInsertedKey;			// 交換當前節點 small key 與待插入的key 
			*toBeInsertedKey = sortNode->keySmall;
			sortNode->keySmall = tempElement;	
		
		//debug here
		}else if(strcmp(sortNode->keyBig.schoolName, toBeInsertedKey->schoolName) < 0){
		//}else if(strcmp(sortNode->keyBig.schoolName, toBeInsertedKey->schoolName) <= 0){
			tempElement = *toBeInsertedKey;			// 交換當前節點 big key 與待插入的key 
			*toBeInsertedKey = sortNode->keyBig;
			sortNode->keyBig = tempElement;	
		} 
	}
	
	/*
		如果當前節點有四個孩子，則需要對四個孩子做排序
		因為呼叫 AddThreeNode() 函數之後， 會將 parent node 的 reserve child 賦值
		而賦值之後是沒有對其進行排序的，為了保持 left middle reserve right 的升序排列
		需要對當前節點的四個孩子進行排序 
	
	*/
	if(sortNode->reserveNode != NULL)
	{	
		/* right child 有兩種情況，當其為 2 node 或 3 node時，
			分別需要比較其 key small 和 key big 
		*/ 
		if(sortNode->rightChildNode->isTwoNode == true)
		{
			/*
				debug here for a long time;   邏輯出了問題，小問題，但是很噁心 
			*/
			if(strcmp(sortNode->reserveNode->keySmall.schoolName, sortNode->rightChildNode->keySmall.schoolName) > 0)
			{
				tempNodePointer = sortNode->reserveNode;
				sortNode->reserveNode = sortNode->rightChildNode;
				sortNode->rightChildNode = tempNodePointer;
				
				return;
			}
		}else{
			// debug here
			if(strcmp(sortNode->reserveNode->keySmall.schoolName, sortNode->rightChildNode->keyBig.schoolName) > 0)
			{
				tempNodePointer = sortNode->reserveNode;
				sortNode->reserveNode = sortNode->rightChildNode;
				sortNode->rightChildNode = tempNodePointer;
				
				return;
			}
		}
		
		/*
			將 reserve child 與 left child 做比較 
		*/ 
		if(strcmp(sortNode->reserveNode->keySmall.schoolName, sortNode->leftChildNode->keySmall.schoolName) < 0)
		{
			/*
				Reserve child 需要和 Left child 交換
				而四個孩子的排序是 left middle reserve right
				所以 reserver child 和 left child 交換之後
				此時的 reserver child 還要和 middle child 作交換
				才能保持四個孩子升序排列 
			*/
			tempNodePointer = sortNode->reserveNode;
			sortNode->reserveNode = sortNode->leftChildNode;
			sortNode->leftChildNode = tempNodePointer;
			
			tempNodePointer = sortNode->reserveNode;
			sortNode->reserveNode = sortNode->middleChildNode;
			sortNode->middleChildNode = tempNodePointer;
			
			return;
		}
		
		/*
			將 reserve child 與 middle child 做比較 
		*/
		if(strcmp(sortNode->reserveNode->keySmall.schoolName, sortNode->middleChildNode->keySmall.schoolName) < 0)
		{
			tempNodePointer = sortNode->reserveNode;
			sortNode->reserveNode = sortNode->middleChildNode;
			sortNode->middleChildNode = tempNodePointer;
			
			return;
		}
	}else{
		return;
	}
}
