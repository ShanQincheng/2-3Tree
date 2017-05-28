# 2-3 Tree



# 前言
這是“資料結構與演算法”課程的第 3 次上機練習作業，實現 2-3 樹資料結構。這是我寫過的最麻煩的一次 C 語言程式。  
寫完之後問了做 ACM 的同學有沒有快速方便的方法實現 2-3 樹，同學回覆說他從來不會用指針寫樹，而是用鄰接表。簡單講如下圖。沒有做過算法競賽對我學習資料結構這門課來說挺吃虧的。截圖僅以為記。
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170322141925.png)

***

**扯了這麼多，現在上本次上機練習題目**
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170322143647.png)
本篇文章主要介紹 2-3 樹，純 C 語言，指針實現的方法。

***
# 環境
    OS        Windows10
    IDE       DEV C++
    language  C

***

# 開始
* 1、簡介 2-3 樹
 * 2-3 樹的定義 
 * 2-3 樹的查找效率 
 * 我的 2-3 樹程式頭文件解讀
* 2、2-3 樹的算法
 * 2-3 樹的查找算法
 * 2-3 樹的插入算法
     * 總的插入算法
     * 將 key 插入 2-node
     * 將 key 插入 3-node 的根節點
     * 將 key 插入 3-node 節點（ 當前 3-node 節點的父節點是 2-node ）
     * 將 key 插入 3-node 節點（ 當前 3-node 節點的父節點是 3-node ）
 * 2-3 樹獲取插入位置算法
 * 2-3 樹對節點中 key 進行排序的算法
 * 2-3 樹確定當前節點是否為葉子節點算法
 * 2-3 樹獲取根節點的算法


***
### 1、簡介 2-3 樹
> 為了使 2-3 樹獲取靈活性，首要步驟就是允許每一個節點存放一個或者兩個 Key 來保證 2-3 樹的平衡。

#### 2-3 樹的定義
一棵 2-3 樹要麼是空的，要麼就由 2-node 或 3-node 組成。   

* 2-node：2-node 存有一個 key 和指向兩個孩子的鏈接（ *left link and right link* ）。左孩子是一棵 2-3 樹，樹中存放的 key 均要小於當前 2-node 中的 key。右孩子也是一棵 2-3 樹，樹中存放的 key 均要大於當前 2-node 中的 key。   

* 3-node：3-node 存有兩個 key 和指向三個孩子的鏈接（ *left link, middle link and right link* ），left key < right key。左孩子是一棵 2-3 樹，樹中存放的 key 均要小於當前 3-node 中的 left key。中間孩子是一棵 2-3 樹，樹中存放的 key 均要在當前 3-node 中的 left key 和 right key 之間。右孩子是一棵 2-3 樹，樹中存放的 key 均要大於當前 3-node 中的 right key。
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323193254.png)
> 圖片來自 http://blog.jobbole.com/79307/

一個完全平衡的 2-3 樹表示當前樹中所有由 node 指向 null 的鏈接，到根節點的距離都是相同的。


#### 2-3 樹的查找效率
**討論算法的效率用的最廣泛的方法是討論該算法在最壞情況下的效率。**  
二元搜寻树最壞情況是一棵歪斜樹(Skewed Binary Tree)，此時的查找效率从 O（log n）跌落到了 O（n）。
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323113631.png)
> 圖片來自 http://emn178.pixnet.net/blog/post/94164966-%E8%B3%87%E6%96%99%E7%B5%90%E6%A7%8B---%E4%BA%8C%E5%85%83%E6%A8%B9(binary-tree)

而 2-3 樹是二元搜尋樹的進化版,它是一棵幾乎完美的平衡樹，==樹高最多是 logN==， 所以 2-3 樹最壞的查找效率也是 logN。  
==Log << Polynomial(Linear)  ==  
 ==O（log n） 與 O（n）差很多,所以 2-3 樹的效率是很好的  ==

==**但是，2-3 樹每個節點不一定會存滿，最壞的情況下退化為二元搜尋樹，所以 2-3 樹在空間利用率上比二元搜尋樹差得多**==
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323113822.png)
> 圖片來自  
https://www.google.com.tw/search?q=Example+of+2-3+tree&tbm=isch&tbo=u&source=univ&sa=X&ved=0ahUKEwjl_eKowuzSAhUlDZoKHQYDCqsQsAQIMw&biw=1919&bih=986#imgrc=K7_Ffh3p-dQL_M:

#### 我的 2-3 樹程式頭文件解讀
headFile.h 如下
```
# include <stdio.h>
# include <malloc.h> 
# include <string.h>

typedef struct key // actually the key in every node is a struct
{
	int serialNumber; // serial number
	int position; 
	char schoolName[25];
}SchoolNameKey;

typedef SchoolNameNode ElementType;
typedef struct TwoThreeTreeNode{ // node struct
	ElementType keySmall; // key's value is small, i.e. left key
	ElementType keyBig; // key's value is big(optional), i.e. right key
	bool isTwoNode = true;	 // To determine whether it is 2-node, default true
	struct TwoThreeTreeNode *parentNode = NULL; // father node pointer( parent link )
	struct TwoThreeTreeNode *leftChildNode = NULL; // left child node pointer( left link )
	struct TwoThreeTreeNode *middleChildNode = NULL; // middle child node pointer( middle link )
	struct TwoThreeTreeNode *reserveNode = NULL; // 作為備份，第四個子孩子指針 ( right link )
	struct TwoThreeTreeNode *rightChildNode = NULL; // right child node pointer ( reserve link )	
		
}TwoThreeNode;


bool DetermineIsLeafNode(TwoThreeNode *); // determine whether current node is a leaf node
TwoThreeNode* GetInsertPosition(TwoThreeNode *, ElementType);// get the leaf node to be inserted
void SortTwoThreeNode(TwoThreeNode *, ElementType *); // sort the key value in node
void AddTwoNode(TwoThreeNode *, ElementType);  // insert key into a 2-node
void AddThreeNode(TwoThreeNode *, ElementType); // insert key into a 3-node
TwoThreeNode* AddElement(TwoThreeNode *, ElementType); // inset key into node
TwoThreeNode *GetHeadNode(TwoThreeNode *); // get the root node of the tree
void SearchKey(TwoThreeNode *, char *); // search the specified key in the whole tree

```

***

### 2、2-3 樹的算法
#### 2-3 樹的查找算法( void SearchKey(TwoThreeNode *, char *) )
為了確定待查找的 key 是否存在於一個 2-3 樹中，我們首先拿這個 key 與 2-3 樹的樹根進行比較（ *注意每次需要比較的 node 都有兩種情況: 2-node 與 3-node* ）。   
如果命中，則記錄下當前 leaf node 中的信息，並繼續向當前節點的孩子節點遞迴查找。   
如果未命中，則繼續按照 key 的大小邏輯向左子樹、右子樹、中子樹（ *optional*）遞迴查找。   
該算法直到葉子節點結束遞迴（ return ）。

* 若是 leaf-node（ *2-node or 3-node* ）：   
     * 比較待查找 key 與當前 leaf-node 中 key 的關係。若相等則命中，並 return，若不等直接 return。      
* 若是 2-node：   
     * 待查找 key 比當前 2-node key 小的話，遞迴搜尋當前 node 的左子樹。   
     * 待查找 key 比當前 2-node key 大的話，遞迴搜尋當前 node 的右子樹。   
     * 若剛好命中，記錄下當前 key 的信息，然後遞迴搜尋當前 2-node 的左子樹，和右子樹。    
     * 若既不大也不小還不等於，直接 return 結束遞迴。   
* 若是 3-node：
     * 待查找 key 比當前 3-node left key 小的話，遞迴搜尋當前 3-node 的左孩子子樹。
     * 待查找 key 在當前 3-node left key 與 right key 之間的話，遞迴搜寻當前 3-node 的中间孩子子樹。
     * 待查找 key 大於當前 3-node的 right key 的話，遞迴搜尋當前 3-node 的右孩子子樹。
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323200159.png)
> 圖片來自  http://algs4.cs.princeton.edu/33balanced/

程式如下
```
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
```

***

#### 2-3 樹的插入算法
> 2-3 樹的插入永遠都從葉子節點插入，不會是從中間某個節點插入
##### 總的插入算法
傳入樹根的 pointer, 和待插入的 key。

* 1、若 pointer 為 NULL，說明當前是一棵空樹。生成根節點。
* 2、若 pointer 不為空，獲得插入位置，即自頂向下不斷比較各個節點中的 key ，直到找到葉子節點。
* 3、判斷當前插入位置，即當前葉子節點為 2-node 或者是 3-node，執行 AddTwoNode()函數 或者執行 AddThreeNode()函數。

先上獲取插入位置的算法，邏輯簡單，看程式就能看懂
```
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
```


總的插入算法如下
```
TwoThreeNode* AddElement(TwoThreeNode *head, ElementType element)
{
	if(head == NULL)
	{
		TwoThreeNode *newHead = (TwoThreeNode *)calloc(1, sizeof(TwoThreeNode));
		newHead->isTwoNode = true;
		newHead->keySmall = element;
		head = newHead;
			
		return head;
	}
	// top-down looking for the leaf node 
	TwoThreeNode *currentNode = GetInsertPosition(head, element);
	if(currentNode->isTwoNode == true)
	{
		AddTwoNode(currentNode, element);
		
		return head;
	}else{
		AddThreeNode(currentNode, element);
		
		return head;
	}
}
```

##### 將 key 插入 2-node 的節點( *void AddTwoNode(TwoThreeNode *, ElementType);* )
這種是最簡單的情況，只需要比較待插入 key 與當前 2-node 節點中 key 的大小，如果待插入 key 大於當前 2-node 節點中的 key，那麼直接將待插入的 key 存放到當前 2-node 節點的 right key 中。如果待插入的 key 小於當前 2-node 節點中的 key，那麼將待插入的 key 與當前 2-node 節點中的 key 交換後，再將交換後的待插入 key 插入到當前 2-node 節點中的 right key 。最後，插入完成後，將當前 2-node 節點標記為 3-node 節點。（ *我的算法保持 toBeInsertedKey 為大的那一個，所以比較完之後，直接存到 right key 中* ）
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323212656.png)
> 圖片來自  http://algs4.cs.princeton.edu/33balanced/

程式如下    

```
void AddTwoNode(TwoThreeNode *currentNode, ElementType toBeInsertedKey)
{
	/* 
	   compare the key to be inserted with the key in the current node
	   if toBeInsertedKey > node.key, do nonthing
	   		else swap(toBeInsertedKey, node.key)
	   so the variable toBeInsertedKey always is the big one
	*/
	SortTwoThreeNode(currentNode, &toBeInsertedKey);
	
	// 2-node after adding a new key to become a 3-node
	currentNode->isTwoNode = false;
	currentNode->keyBig = toBeInsertedKey;
}
```
#### 將 key 插入 3-node 節點( *void AddThreeNode(TwoThreeNode *, ElementType);* )
##### 將 key 插入 3-node 的根節點
假設當前節點能夠容納 3 個 key，於是此時就會有 4 個鏈接，多出了一個指向 reserve 子樹的鏈接（ reserve link ）。   
新生成一個根節點，將 3 個 key 中的 middle key 存放到新根節點中。   
新生成一個右孩子節點，將 3 個 key 中的 max key 存放到右孩子節點中。  
**然後是關鍵的部分**  

* 1、新生成的根節點的 left link，指向舊的根節點。
* 2、新生成的根節點的 right link，指向新生成的右孩子節點。
* 3、舊的根節點的 parent link，指向新生成的根節點。
* 4、新生成的右孩子節點的 parent link，指向新生成的根節點
* 5、新生成右孩子節點的 left link，指向舊的根節點的 reserve 孩子節點，新生成右孩子節點的 right link，指向舊的根節點的右孩子節點。
* 5、舊的根節點的 right link，指向自己的 middle 孩子節點。
* 6、舊的根節點的 middle link, reserve link 置 NULL。  
** 只有做完以上 6 個步驟，才能實現 3-node 舊根節點的 split。原來舊的根節點下方掛著的 4 個孩子子樹，被左右拉開。left child 和 middle child 合併成左子樹，左子樹根節點是舊根節點。reserve child 和 right child 合併成右子樹，右子樹根節點是新生成的右孩子節點。最後，舊的根節點與新生成的右孩子節點，再合併成一棵樹，此時的根節點是新生成的根節點。==用指針操作各個節點之間的關係時，一定要記住，關係是雙向的。比如 parentNode -> leftchildNode,馬上要寫 leftchildNode -> parentNode。寫程式請時刻保持警惕，node 中的指針需要兩兩互相對應！！！==**
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170323223216.png)
程式如下
```
void AddThreeNode(TwoThreeNode *currentNode, ElementType toBeInsertedKey)
{
/* 
choose the middle key from the 3 key in current temporary 4-node, and then assigned to the variable toBeInsertedKey
*/
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
	}
```

##### 將 key 插入 3-node( 當前 3-node 的父節點是 2-node)
將當前 3-node 中的 2 個 key 與待插入 key 按照由小到大順序排列，將 middle key 與待插入的 key 進行替換（*如果 middle key 剛好是待插入的 key，則什麼也不用做*）。接著生成一個新的 middle node 節點,將新的 middle node 節點的父節點置為當前 3-node 節點的父節點，說白了就是把 middle node 掛到当前 3-node 節點的父節點上去。 
**然後是關鍵的部分**  

* 1、如果當前 3-node 是父節點的左孩子。
     * 將當前 3-node 的 right key 存放到新的 middle node 節點中。
     * 新的 middle node 節點的 left child 指向當前 3-node 節點的 reserve child。
     * 新的 middle node 節點的 right child 指向當前 3-node 節點的 right child。
     * 當前 3-node 節點的 reserve child 的 parent link 指向新的 middle node 節點。
     * 當前 3-node 節點的 right child 的 parent link 指向新的 middle node 節點。
     * 將當前 3-node 節點的 right link 指向當前節點的 middle child。
     * 將當前 3-node 節點的 middle link，reserve link 置 NULL。
     * 將當前 3-node 節點恢復為 2-node 狀態。

* 2、如果當前 3-node 是父節點的右孩子。
     * 將當前 3-node 的 left key 存放到新的 middle node 節點中。
     * 新的 middle node 節點的 left child 指向當前 3-node 節點的 left child。
     * 新的 middle node 節點的 right child 指向當前 3-node 節點的 middle child。
     * 當前 3-node 節點的 left child 的 parent link 指向新的 middle node 節點。
     * 當前 3-node 節點的 middle child 的 parent link 指向新的 middle node 節點。
     * 將當前 3-node 節點的 left link 指向當前節點的 reserve child。
     * 將當前 3-node 節點的 middle link，reserve link 置 NULL。
     * 將當前 3-node 節點恢復為 2-node 狀態。  

==最後呼叫插入 2-node 節點函數， 將待插入 key（*與 3-node 中兩個 key 比較後的那個 middle key*）插入當前 3-node 節點的父節點中==
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170324154015.png)

程式如下
```
// if the parent node of current 3-node is a 2-node
	else if(currentNode->parentNode->isTwoNode == true){ 
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
	}
```

##### 將 key 插入 3-node( 當前 3-node 的父節點是 3-node )
與父節點是 2-node 不同的是，此時要新增的是 reserve node，並在最後遞迴呼叫當前 AddThreeNode() 函數（*因為父節點也是 3-node*）。別的都與前一個算法大同小異。
![](http://codingstory.com.cn/content/images/2017/03/QQ--20170324213115.png)
程式如下
```
// if the parent node of current node is a 3-node 
	else{
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
```

***

#### 2-3 樹獲取插入位置算法
這個很簡單，看程式注釋就能看懂  
程式如下
```
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

```

***

#### 2-3 樹對節點中 key 進行排序的算法
一共有三種情況需要排序  

* 1、插入 2-node 節點時，比較 2-node 節點中已存在的 key 和待插入的 key 的大小。如果 2-node 中的 key 小，則不進行操作。若 2-node 中的 key 大，則交換。保持待插入的 key 為大的那個，因為之後進行的將新 key 作為 2-node 節點中的 right key插入到 2-node 節點中。
* 2、插入 3-node 節點時，比較 3-node 節點中已存在的 left key， right key 和待插入的 key 的大小。選出中間的 key，與待插入的 key交換（*如果待插入的 key 剛好是 middle key，則不進行操作*）。因為之後是將 middle key 提升，呼叫插入函數，重新進行排序、插入操作（*此時傳入的待插入 key 就是 middle key*）。
* 3、若當前節點有 reserve child，說明當前節點是 3-node 節點，而且當前 3-node 節點的某個 3-node 子節點，剛剛分裂過，生成了新的 reserve node 掛在了當前節點上。因為我的分裂算法，並不能保證存在 reserve node 中的 key 剛好是在 middle node key 與 right node key 之間（ *要保證孩子節點中的 key 按照順序排列 left key < middle key < reserve key < right key* ）。所以此時還需要將四個孩子排序，調整好四個孩子的順序。   

程式如下
```
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
```

***

#### 2-3 樹確定當前節點是否為葉子節點算法
簡單，直接看程式  
程式如下
```

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
```

***

#### 2-3 樹獲取根節點的算法
簡單，直接看程式  
程式如下
```
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
```

***
#以上
2017 年 3 月 24 日
