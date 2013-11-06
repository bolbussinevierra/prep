// cci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chapter.1.h"
#include "chapter.2.h"

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

    //2.1
    int data[] = {13,6,5,4,1,0,3,3,2,1};
    Node* ll = MakeList(data, ARRAY_SIZE(data));
#if 0
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

    // 2.4
    PrintList(ll);
    PrintList(PartitionList(ll, 4));

    return 0;
}

