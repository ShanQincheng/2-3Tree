# include "headFile.h"

void SearchKey(TwoThreeNode *currentNode, char *schoolName)
{
	/* 
		p.s. DetermineIsLeafNode() is a function which be used to judge whether current node is a leaf node
		if current node is a leaf node 
	*/
	if(DetermineIsLeafNode(currentNode) == true)
	{
		// if current node is a 2-node 
		if(currentNode->isTwoNode == true)
		{
			// if the key to be found is equals to the key in current node 
			if((strcmp(currentNode->keySmall.schoolName, schoolName)) == 0)
			{
				// debug
				printf("%d  %s\n", currentNode->keySmall.serialNumber, currentNode->keySmall.schoolName);
			}
			
			return;
		// if current node is a 3-node 
		}else{
			// if the key to be found is equals to the left key in current node 
			if((strcmp(currentNode->keySmall.schoolName, schoolName)) == 0)
			{
				// debug
				printf("%d  %s\n", currentNode->keySmall.serialNumber, currentNode->keySmall.schoolName);
			}
			// if the key to be found is equals to the right key in current node 
			if((strcmp(currentNode->keyBig.schoolName, schoolName)) == 0)
			{
				// debug
				printf("%d  %s\n", currentNode->keyBig.serialNumber, currentNode->keyBig.schoolName);
			}
			
			return;
		}
		
	}else{
		// if current node is a 2 node
		if(currentNode->isTwoNode == true)
		{
			if(strcmp(currentNode->keySmall.schoolName, schoolName) > 0) // if the key to be found less than the key
			{	
			//	currentNode = currentNode->leftChildNode;
				SearchKey(currentNode->leftChildNode, schoolName);
			}else if(strcmp(currentNode->keySmall.schoolName, schoolName) < 0){ // if the key to be found greater than the key
			//	currentNode = currentNode->rightChildNode;
				SearchKey(currentNode->rightChildNode, schoolName);
			}else if(strcmp(currentNode->keySmall.schoolName, schoolName) == 0){ // if the key to be found equal the key
				// debug
				printf("%d  %s\n", currentNode->keySmall.serialNumber, currentNode->keySmall.schoolName);
			
				/*
					 if current node's left child's small key is equal to the the key to be found,
						recursive call SearchKey
				*/
				SearchKey(currentNode->leftChildNode, schoolName);
				SearchKey(currentNode->rightChildNode, schoolName);
			}	
		// if current node is a 3 node	
		}else{
			if(strcmp(currentNode->keySmall.schoolName, schoolName) > 0) // if the key to be found less than the left key
			{
			//	currentNode = currentNode->leftChildNode;
				SearchKey(currentNode->leftChildNode, schoolName);
			}else if(strcmp(currentNode->keyBig.schoolName, schoolName) < 0){ // if the key to be found greater than the right key
			//	currentNode = currentNode->rightChildNode;
				SearchKey(currentNode->rightChildNode, schoolName);
				
			// if the key to be found between the left key and the right key
			}else if((strcmp(currentNode->keySmall.schoolName, schoolName) < 0) && (strcmp(currentNode->keyBig.schoolName, schoolName) > 0)){
				/*
					debug here for a long time
				*/
				SearchKey(currentNode->middleChildNode, schoolName);
				
			// if the key to be found equal the left key
			}else if(strcmp(currentNode->keySmall.schoolName, schoolName) == 0){
					// debug
					printf("%d  %s\n", currentNode->keySmall.serialNumber, currentNode->keySmall.schoolName);
					
					SearchKey(currentNode->leftChildNode, schoolName);
					SearchKey(currentNode->middleChildNode, schoolName);
					SearchKey(currentNode->rightChildNode, schoolName);
			
			// if the key to be found equal the right key	
			}else if(strcmp(currentNode->keyBig.schoolName, schoolName) == 0)
			{
				// debug
				printf("%d  %s\n", currentNode->keyBig.serialNumber, currentNode->keyBig.schoolName);
				
				SearchKey(currentNode->leftChildNode, schoolName);
				SearchKey(currentNode->middleChildNode, schoolName);
				SearchKey(currentNode->rightChildNode, schoolName);
			}else{
				return ;
			}
		}
	}
}

