# include <stdio.h>
# include <malloc.h> 
# include <string.h>

typedef struct key 
{
	int serialNumber; // serial number
	int position; 
	char schoolName[25];
}SchoolNameKey;

typedef SchoolNameKey ElementType;
typedef struct TwoThreeTreeNode{
	ElementType keySmall; // key's value is small
	ElementType keyBig; // key's value is big(optional)
	
//	bool (*isLeafNode)(struct TwoThreeTreeNode *);
	bool isTwoNode = true;	 // To determine whether it is 2 node, default true
	struct TwoThreeTreeNode *parentNode = NULL; // father node pointer
	struct TwoThreeTreeNode *leftChildNode = NULL; // left child node pointer
	struct TwoThreeTreeNode *middleChildNode = NULL; // middle child node pointer
	struct TwoThreeTreeNode *reserveNode = NULL; // 作為備份，第四個子孩子
	struct TwoThreeTreeNode *rightChildNode = NULL; // right child node pointer	
		
}TwoThreeNode;


bool DetermineIsLeafNode(TwoThreeNode *);
TwoThreeNode* GetInsertPosition(TwoThreeNode *, ElementType);
void SortTwoThreeNode(TwoThreeNode *, ElementType *);
void AddTwoNode(TwoThreeNode *, ElementType);
void AddThreeNode(TwoThreeNode *, ElementType);
TwoThreeNode* AddElement(TwoThreeNode *, ElementType);
void display(TwoThreeNode *);
TwoThreeNode *GetHeadNode(TwoThreeNode *);
void SearchKey(TwoThreeNode *, char *);

