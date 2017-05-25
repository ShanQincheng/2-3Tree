# include "headFile.h"
/**
	��ȡ����λ�� 
**/
TwoThreeNode* GetInsertPosition(TwoThreeNode *headNode, ElementType toBeInsertedKey)  // ������WУ��Ϣ�Y���w 
{
	TwoThreeNode *currentNode;  // ��ǰ�ߵ��Ĺ��cλ�� 
	currentNode = headNode;
	
	while(DetermineIsLeafNode(currentNode) == false)   // �����ǰ���c�����~�ӹ��c 
	{
		if(currentNode->isTwoNode == true)	// �����ǰ���c�� 2 ���c 
		{
			if(strcmp(toBeInsertedKey.schoolName, currentNode->keySmall.schoolName) < 0) // ���������Y���w�ЌWУ���QС춮�ǰ 2 ���c�� key 
			{
				currentNode = currentNode->leftChildNode;	// ��ǰ 2 ���c�����^�m���� 
			}else{
				currentNode = currentNode->rightChildNode;	// ��ǰ 2 ���c�Һ����^�m���� 
			}	
		}else{ // �����ǰ���c�� 3 ���c 
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



