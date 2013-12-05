// cci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chapter.1.h"
#include "chapter.2.h"
#include "chapter.3.h"
#include "chapter.4.h"
#include "chapter.9.h"
#include "chapter.10.h"
#include "chapter.11.h"
#include "chapter.13.h"
#include "chapter.17.h"

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
    Node* ll = MakeList(data, AS(data));
    
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
    Node* ll26 = MakeList(data26, AS(data26));
    PrintList(ll26);
    MakeCycleAt(ll26, 2);
    Node* start = FindCycleStart(ll26);
#endif

#if 0
    //
    // 2.7 - the O(2n) non-runner method must just be more straightforward
    //
    int data27[] = {0,1};
    Node* ll27 = MakeList(data27, AS(data27));
    PrintList(ll27);
    IsPalindrome(ll27);
#endif

#if 0
    int data44[] = {1,2,3,4,5,6};
    TreeNode* tree = MakeOptimalBST(data44, AS(data44));
    vector<LinkedListNode*> result;
    GetLevelsLinkedLists(tree, result);
    for (int i = 0; i < result.size(); ++i){
        PrintList(result[i]);
    }
#endif 
#if 0
    int data45[] = {1,2,4,5,6,7};
    TreeNode* tree = MakeOptimalBST(data45, AS(data45));
    vector<LinkedListNode*> result;
    GetLevelsLinkedLists(tree, result);
    for (int i = 0; i < result.size(); ++i){
        PrintList(result[i]);
    }
    printf("IsBST=%d\n", IsBST(tree)); 
#endif 
#if 0
    //
    // 9.1
    //
    for (int i = 4; i >=0; --i) {
        printf("WAYS(%d)=%d\n",i, ways(i));
    }
#endif
#if 0
    //
    // 9.2
    //
    int width = 3;
    int height = 3;
    printf("compute_paths(width=%d, height=%d) is %d", width, height, compute_paths(width, height)); 
    printf("\n FindPathTo=%d\n", FindPathTo(width, height));

#endif
#if 0
    //
    // 9.4
    //
    int items93[] = {1,2,3,4,5,6,7,8,9,10};
    // Subsets(items93, AS(items93));
    // SubsetsIterative(items93, AS(items93));
    SubsetsBinary(items93, AS(items93));
#endif 
#if 0
    //
    // 9.5
    //
    string s("abcdefgh");
    GetPermutations(s);
    GetPermutationsIter(s);
#endif
#if 0
    //
    // 9.6
    //
    PrintParens(4);
#endif
#if 0
    //
    // 9.7
    //
    // First, attempting to calculate the same way as the "ways to climb stairs" problem
    // causes us to run into problems because it double counts combinations that are the
    // same when dealing with coins (e.g [1c,5c] is the same as [5c,1c] whereas if this
    // was ways of stepping instead of coins, they would indeed be two different ways
    int amount = 1 * 6;
    //printf("Ways to change make for [%d cents] is %d \n", amount, CountWaysToMakeChangeBroken(amount));
    CountWaysToMakeChangeRecursive(50, 25);
#endif
#if 0
    //
    // 10.3
    //
    FindNumber();
#endif
#if 0
    //
    // 10.4
    //
    CheckDuplicates(_getArray());
#endif
#if 0
    //
    // 11.1
    //
    int a111[] = {0,5,7,9,89,0,0};
    int b111[] = {1,4};
    MergeSorted(a111, AS(a111)-AS(b111), b111, AS(b111));
#endif
#if 0
    int qs[] = {5,6,7,90,23,1,4,5};
    _quicksort(qs, 0, AS(qs)-1);
    _P(qs, AS(qs));

    int ms[] = {5,6,7,90,23,1,4,5};
    _mergesort(ms, 0, AS(ms)-1);
    _P(ms, AS(ms));

#endif
#if 0
    //
    // 11.2
    //
    const char* a112[] = {"cat", "acre", "act", "race", "care", "tac"};
    vector<string> v;
    for(int i=0; i < AS(a112); ++i) {
        v.push_back(string(a112[i]));
    }
    GroupAnagrams(v);
    PrintVector(v, "anagrams");
#endif
#if 0
    //
    // 11.3
    //
    int a113[] = {0,1,2,3,4,5,6,7,8,12,16};
    rotate(a113, AS(a113), 0);
    int l = 12;
    printf("found %d at index = %d\n", l, search(a113, l, 0, AS(a113)-1));
#endif
#if 0
    //
    // 11.5
    //
    char* target = "ball";
    char* a115[] = {"at","","","","ball","","","car","","","dad","",""}; 
    printf("found '%s' at index = %d\n", target, FindString(a115, AS(a115), target));
#endif
#if 0
    //
    // 11.6
    //
    Location l = {-1,-1};
    int a116[4][5] = 
    { {1, 22, 23, 24, 25},
      {12,33, 34, 35, 36},
      {13,44, 45, 46, 46},
      {14,55, 56, 57, 58}}; 
    int find = 35;
    bool found = SearchMatrix(a116,find,5,4,&l);
    printf("Found=%d for elem=%d at location (row=%d, col=%d)", found, find, l.row, l.col);  
#endif
#if 0
    //
    // 11.7
    //
    htwt a117[] = {{65,100},{70,150},{56,90},{75,190},{60,95},{68,110}};
    int len = AS(a117);
    vector<htwt> v117(a117, a117+len);
    BuildCircusTower(v117);
  
#endif
#if 0
    //
    // 11.8
    //
    Rank r;
    r.Track(6);
    r.Track(9);
    r.Track(12);
    r.Track(57);
    r.Track(0);
    r.Track(5);
    r.Track(112);
    r.Track(1);
    int locate=57;
    printf("GetRank(%d)=%d", locate, r.GetRank(locate));

#endif 
#if 0
    //
    // 13.09
    //
    void* mem = aligned_malloc(10, 16);
    aligned_free(mem);
#endif
#if 0
    //
    // 17.2
    //
#define BS 4
    Type _b[BS][BS] = 
    {
        { X,     X,     X,     O },
        { Empty, X,     O,     Empty },
        { Empty, O,     Empty, Empty },
        { O,     Empty, Empty, Empty }
    };
    vector<vector<Type>> b(BS, vector<Type>(BS));
    for (size_t row = 0; row < BS; ++row) {
        for (size_t col = 0; col < BS; ++col) {
            b[row][col] = _b[row][col];
        }
    }
    Move m = {0, 3, O};
    cout << m.value << " has made a winning move?=" << IsWinningMove(m, b); 
#endif
#if 0
    //
    // 17.3
    //
    cout << "countZerosGood(20)=" << CountZerosGood(20) << endl;
    cout << "countZerosBest(20)=" << CountZerosBest(20) << endl;
    cout << "countZerosGood(25)=" << CountZerosGood(25) << endl;
    cout << "countZerosBest(25)=" << CountZerosBest(25) << endl;
#endif
#if 0
    //
    // 17.4
    //
    cout << "max of 0, 1 = " << safe_max_opt(0,1) << endl;
    cout << "max of 1, 1 = " << safe_max_opt(1,1) << endl;
    cout << "max of -1, -2 = " << safe_max_opt(-1, -2) << endl;
#endif
#if 1
    //
    // 17.6
    //
    int a176[] = {1,2,4,7,10,11,7,12,6,7,16,18,19};
    vector<int> v(a176, a176+AS(a176));
    GetSortRange(v);
#endif 
    cin.get(); // pause console before exit
    return 0;
}

