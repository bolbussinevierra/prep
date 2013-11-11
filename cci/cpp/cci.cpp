// cci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chapter.1.h"
#include "chapter.2.h"
#include "chapter.3.h"
#include "chapter.4.h"

int _tmain(int argc, _TCHAR* argv[])
{
#if 0
    //1.1
	bool result = is_unique_chars(""); 

    // 1.6
    int** someArray = new int*[5];
    fill_matrix(someArray, 5);
    rotate_matrix_90(someArray, 5);
#endif

#if 0
    //2.1
    int data[] = {13,6,5,4,1,0,3,3,2,1};
    Node* ll = MakeList(data, ARRAY_SIZE(data));
    
    PrintList(ll);
    RemoveDuplicates(ll);
    // RemoveDuplicatesNoBuffer(ll);
    PrintList(ll);
#endif

#if 0
    // 2.2
    int k = 1;
    Node * kNode = GetKthToLast(ll,k); 
    if (kNode){
        printf("%d-th element is %d", k, kNode->data); 
    }
#endif

#if 0
    // 2.4
    PrintList(ll);
    PrintList(PartitionList(ll, 4));
#endif

#if 0
    //
    // 2.6
    //
    int data26[] = {0,1,12,3,4,5,6,7,8,9};
    Node* ll26 = MakeList(data26, ARRAY_SIZE(data26));
    PrintList(ll26);
    MakeCycleAt(ll26, 2);
    Node* start = FindCycleStart(ll26);
#endif

#if 0
    //
    // 2.7 - the O(2n) non-runner method must just be more straightforward
    //
    int data27[] = {0,1};
    Node* ll27 = MakeList(data27, ARRAY_SIZE(data27));
    PrintList(ll27);
    IsPalindrome(ll27);
#endif

#if 1
    int data44[] = {1,2,3,4,5,6};
    TreeNode* tree = MakeOptimalBST(data44, ARRAY_SIZE(data44));
    vector<LinkedListNode*> result;
    GetLevelsLinkedLists(tree, result);
    for (int i = 0; i < result.size(); ++i){
        PrintList(result[i]);
    }
#endif 
    cin.get(); // pause console before exit
    return 0;
}

