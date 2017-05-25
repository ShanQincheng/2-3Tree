# include "headFile.h"

void SortTwoThreeNode(TwoThreeNode *sortNode, ElementType *toBeInsertedKey)
{
	ElementType tempElement;
	TwoThreeNode *tempNodePointer;
	
	if(sortNode->isTwoNode == true)
	{
		if(strcmp(sortNode->keySmall.schoolName, toBeInsertedKey->schoolName) > 0) // �����ǰ���c�е� key ��춴������ key 
		{
			tempElement = *toBeInsertedKey;			// ���Q��ǰ���c key �c�������key 
			*toBeInsertedKey = sortNode->keySmall;
			sortNode->keySmall = tempElement;
		}
	}else{
		if(strcmp(sortNode->keySmall.schoolName, toBeInsertedKey->schoolName) > 0) // ���������� key �Ȯ�ǰ���c�� small key ҪС���t small key ���� 
		{
			tempElement = *toBeInsertedKey;			// ���Q��ǰ���c small key �c�������key 
			*toBeInsertedKey = sortNode->keySmall;
			sortNode->keySmall = tempElement;	
		
		//debug here
		}else if(strcmp(sortNode->keyBig.schoolName, toBeInsertedKey->schoolName) < 0){
		//}else if(strcmp(sortNode->keyBig.schoolName, toBeInsertedKey->schoolName) <= 0){
			tempElement = *toBeInsertedKey;			// ���Q��ǰ���c big key �c�������key 
			*toBeInsertedKey = sortNode->keyBig;
			sortNode->keyBig = tempElement;	
		} 
	}
	
	/*
		�����ǰ���c���Ă����ӣ��t��Ҫ���Ă�����������
		������ AddThreeNode() ����֮�ᣬ ���� parent node �� reserve child �xֵ
		���xֵ֮���Ǜ]�Ќ����M������ģ����˱��� left middle reserve right ����������
		��Ҫ����ǰ���c���Ă������M������ 
	
	*/
	if(sortNode->reserveNode != NULL)
	{	
		/* right child �ЃɷN��r������� 2 node �� 3 node�r��
			�քe��Ҫ���^�� key small �� key big 
		*/ 
		if(sortNode->rightChildNode->isTwoNode == true)
		{
			/*
				debug here for a long time;   ߉݋���ˆ��}��С���}�����Ǻ܇f�� 
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
			�� reserve child �c left child �����^ 
		*/ 
		if(strcmp(sortNode->reserveNode->keySmall.schoolName, sortNode->leftChildNode->keySmall.schoolName) < 0)
		{
			/*
				Reserve child ��Ҫ�� Left child ���Q
				���Ă����ӵ������� left middle reserve right
				���� reserver child �� left child ���Q֮��
				�˕r�� reserver child ߀Ҫ�� middle child �����Q
				���ܱ����Ă������������� 
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
			�� reserve child �c middle child �����^ 
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
