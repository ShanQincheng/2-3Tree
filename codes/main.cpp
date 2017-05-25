# include "headFile.h"

int main(int argc, char** argv) 
{
	TwoThreeNode *ttNode = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
	TwoThreeNode *ttNode2 = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
	SchoolNameKey temp;
	TwoThreeNode *head, *current;
	char inputChar[25];
	char outchar[25] = "exit";
	int i = 1;
	head = NULL;
	char searchKey[25] = "\0";
	
	
	printf("請一個一個輸入待排序的字符串，回車輸入，length < 24, 輸入 exit 退出並排序\n");	
	
	scanf("%s", inputChar);
	while(strcmp(inputChar, outchar) != 0)
	{	
		strcpy(temp.schoolName, inputChar);
		temp.serialNumber = i++;
		head = AddElement(head, temp);	
		head = GetHeadNode(head);
		scanf("%s", inputChar);
	}
	
	head = GetHeadNode(head);
	
	char inputChar2[25]; 
	
	scanf("%s", inputChar2);
	while(strcmp(inputChar2, outchar) != 0)
	{	
		strcpy(temp.schoolName, inputChar2);
		temp.serialNumber = i++;
		head = AddElement(head, temp);	
		head = GetHeadNode(head);
		scanf("%s", inputChar2);
	}
	
	head = GetHeadNode(head);
	
	if(head->isTwoNode == true)
	{
		printf("%d %s\n", head->keySmall.serialNumber, head->keySmall.schoolName); 	
	}else{
		printf("%d %s   %d  %s\n", head->keySmall.serialNumber, head->keySmall.schoolName, head->keyBig.serialNumber, head->keyBig.schoolName); 	
	}
	
	
	printf("2-3樹構建完成，請輸入需要查找的字符串:  "); 
	scanf("%s", searchKey);
	
	SearchKey(head, searchKey);
	
	//printf("%d\n", strcmp("3","2"));
	//printf("%s %s\n", current->keySmall.schoolName, current->keyBig.schoolName);
//	head = ttNode;
//	strcpy(ttNode->keySmall.schoolName, "b");
//	ttNode->keySmall.serialNumber = 100; 
//	//ttNode->isTwoNode = true; 
//
//	ttNode->rightChildNode = ttNode2;
//	
//
//	temp.serialNumber = 102;
//	strcpy(temp.schoolName, "a");
//	ttNode->keyBig.serialNumber = 101;
//	strcpy(ttNode->keyBig.schoolName, "c");
//	ttNode->isTwoNode = false;
//
//	//SortTwoThreeNode(ttNode, &temp) ;
//	AddThreeNode(ttNode, temp);

	free(ttNode);
	free(ttNode2);
	free(head);
	head = NULL;
	ttNode = NULL;
	ttNode2 = NULL;
	
	return 0;
}
