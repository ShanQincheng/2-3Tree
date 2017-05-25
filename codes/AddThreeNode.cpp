# include "headFile.h"

void AddThreeNode(TwoThreeNode *currentNode, ElementType toBeInsertedKey)
{
	// choose the middle key from the 3 key in current temporary 4-node, and then assigned to the variable toBeInsertedKey
	SortTwoThreeNode(currentNode, &toBeInsertedKey);
	// current node is root node
	if(currentNode->parentNode == NULL)
	{
		// create a new root node
		TwoThreeNode *newHead = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
		newHead->leftChildNode = currentNode; // the left child node of the new root node is current node
		newHead->isTwoNode = true;
		newHead->keySmall = toBeInsertedKey;
		// create a new right child node
		TwoThreeNode *newRightChild = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
		newHead->rightChildNode = newRightChild;
		newRightChild->isTwoNode = true;
		newRightChild->parentNode = newHead; // the parent node of the new right child node is the new root node
		newRightChild->keySmall = currentNode->keyBig; // the current node right key assigned to the key of the new right child node
		newRightChild->leftChildNode = currentNode->reserveNode; // the reserve child of the current node assigned to the left child of the new right child node 
		newRightChild->rightChildNode = currentNode->rightChildNode; // the right child of the current node assigned to the right child of the new right child node 
		
		/*
			 Always keep the poniter bidirectional
		*/
		if(currentNode->reserveNode != NULL){
			currentNode->reserveNode->parentNode = newRightChild;
			currentNode->rightChildNode->parentNode = newRightChild;
		}		
		
		currentNode->keyBig = {}; // the right key of current node has been assigned to the new right child node, so it set null.
		currentNode->isTwoNode = true; // current node changes from 3-node to 2-node
		currentNode->rightChildNode = currentNode->middleChildNode; // the middle child of current node assigned to the right child of current node
		
		currentNode->middleChildNode = NULL; // 2-node can't has middleChild, so it set null
		currentNode->reserveNode = NULL;  // 2-node can't has reserveChild, so it set null
		currentNode->parentNode = newHead;
		
		return;
		
	 // if the parent node of current 3-node is a 2-node
	}else if(currentNode->parentNode->isTwoNode == true){ 
		// create a new middle child node
		TwoThreeNode *newMiddleChild = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));	
		newMiddleChild->parentNode = currentNode->parentNode; // the parent node of current node assigned to the parent link of new middle child node 
		
		/*
			parent node 是 2 Node 其實有兩種情況，當前節點是左孩子，當前節點是右孩子，掛到父親中間孩子的 key 是不同的 	
			
		*/	
		// if current node is the left child of the parent node of current node
		if(currentNode == currentNode->parentNode->leftChildNode)
		{
			newMiddleChild->keySmall = currentNode->keyBig; // the right key of current node assigned to the new middle child node
			newMiddleChild->leftChildNode = currentNode->reserveNode; // the left link of new middle child node ponit to the reserve child of current node
			newMiddleChild->rightChildNode = currentNode->rightChildNode; // the right link of new middle child node ponit to the right child of current node
			/*
			 Always keep the poniter bidirectional
			*/
			if(currentNode->reserveNode != NULL)
			{
				currentNode->reserveNode->parentNode = newMiddleChild;
			}
			if(currentNode->rightChildNode != NULL)
			{
				currentNode->rightChildNode->parentNode = newMiddleChild;	
			}
			
			
			currentNode->rightChildNode = currentNode->middleChildNode; // the right link of current node point to the middle child node of current node
			currentNode->keyBig = {};	 // set the right key of  current node  NULL
			currentNode->middleChildNode = NULL; // set the middle link of  current node  NULL
			currentNode->reserveNode = NULL; // set the reserve link of  current node  NULL
			currentNode->isTwoNode = true; // change current node from 3-node to 2-node
			
		// if current node is the right child of the parent node of current node
		}else{
			newMiddleChild->keySmall = currentNode->keySmall; // the left key of current node assigned to the new middle child node
			
			newMiddleChild->leftChildNode = currentNode->leftChildNode; // the left link of new middle child node ponit to the left child of current node
			newMiddleChild->rightChildNode = currentNode->middleChildNode; // the right link of new middle child node ponit to the middle child of current node
			/*
			 Always keep the poniter bidirectional
			*/
			if(currentNode->leftChildNode != NULL)
			{
				currentNode->leftChildNode->parentNode = newMiddleChild;
			}
			if(currentNode->middleChildNode != NULL)
			{
				currentNode->middleChildNode->parentNode = newMiddleChild;
			}
						
	
			currentNode->leftChildNode = currentNode->reserveNode; // the left link of current node point to the reserve child node of current node
			currentNode->keySmall = currentNode->keyBig; // the right key of current node assigend to the left key of current node
			currentNode->keyBig = {};	 // set the right key of current node NULL
			currentNode->middleChildNode = NULL;  // set the middle link of  current node  NULL
			currentNode->reserveNode = NULL;  // set the reserve link of  current node  NULL
			currentNode->isTwoNode = true; // change current node from 3-node to 2-node
		}
		
		newMiddleChild->isTwoNode = true; 
		// Always keep the poniter bidirectional
		currentNode->parentNode->middleChildNode = newMiddleChild;
		// the parent node of current node is a 2-node, so just call the AddTwoNode() function, every thing will be done correctly
		AddTwoNode(currentNode->parentNode, toBeInsertedKey);	
		
		return;	
	// if the parent node of current node is a 3-node 
	}else{
		// create a new reserve node
		TwoThreeNode *newReserveNode = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
		// make the reserve link of the parent node of current node point to the new reserve node
		currentNode->parentNode->reserveNode = newReserveNode;
		// when current node is the left child or middle child of the parent node of current node
		if(currentNode == currentNode->parentNode->leftChildNode 
				|| currentNode == currentNode->parentNode->middleChildNode)
		{
			newReserveNode->parentNode = currentNode->parentNode; // make the parent link of new reserve node point to the parent node of current node
			newReserveNode->leftChildNode = currentNode->reserveNode;  // make the left link of new reserve node ponit to the reserve child of current node
			newReserveNode->rightChildNode = currentNode->rightChildNode; // make the right link of new reserve node ponit to the reserve child of current node
			/*
			 Always keep the poniter bidirectional
			*/
			if(currentNode->reserveNode != NULL)
			{
				currentNode->reserveNode->parentNode = newReserveNode;
			}
			if(currentNode->rightChildNode != NULL)
			{
				currentNode->rightChildNode->parentNode = newReserveNode;	
			}
			
			newReserveNode->keySmall = currentNode->keyBig;	
			
			currentNode->keyBig = {};
			currentNode->rightChildNode = currentNode->middleChildNode;
			currentNode->middleChildNode = NULL;
			currentNode->reserveNode = NULL;
			currentNode->isTwoNode = true;
		// when current node is the right child of the parent node of current node
		}else{
			newReserveNode->parentNode = currentNode->parentNode;		
			newReserveNode->leftChildNode = currentNode->leftChildNode;
			newReserveNode->rightChildNode = currentNode->middleChildNode;
			/*
			 Always keep the poniter bidirectional
			*/
			if(currentNode->leftChildNode != NULL)
			{
				currentNode->leftChildNode->parentNode = newReserveNode;
			}
			if(currentNode->middleChildNode != NULL)
			{
				currentNode->middleChildNode->parentNode = newReserveNode;	
			}
			
			newReserveNode->keySmall = currentNode->keySmall;	

			currentNode->leftChildNode = currentNode->reserveNode;
			currentNode->middleChildNode = NULL;	
			currentNode->reserveNode = NULL;			

			currentNode->keySmall = currentNode->keyBig;
			currentNode->keyBig = {};			
			currentNode->isTwoNode = true;
		}
		newReserveNode->parentNode = currentNode->parentNode;
		newReserveNode->isTwoNode = true;
		
		AddThreeNode(currentNode->parentNode, toBeInsertedKey);
		
		return;
	}
}
