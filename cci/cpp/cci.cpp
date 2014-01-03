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
#include "chapter.18.h"
#include "dp.h"
#include "hm.h"

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
#if 0
    //
    // 17.6
    //
    int a176[] = {1,2,4,7,10,11,7,12,6,7,16,18,19};
    vector<int> v(a176, a176+AS(a176));
    GetSortRange(v);
#endif 
#if 0
    //
    // 17.8
    //
    int a178[] = {2, -8, 3, -2, 4, -10};
    int a178b[] = {-2, -8, -3, -2, -4, -10};
    vector<int> v(a178, a178+AS(a178));
    PrintMaxSumNaive(v);
    PrintMaxSumBest(v);
#endif
#if 0
    //
    // 17.9
    //
    char* a179[] = {"FOO", "bar", "CALYpso", "Calypso", "Bar"};
    vector<string> v(a179, a179+AS(a179));
    SetupFrequencyTable(v);
    string lookup("Calypso");
    cout << "Frequency of " << lookup << " is=" << LookupWord(lookup) << endl;
#endif 
#if 0
    //
    // 17.12
    //
    int a1712[] = {1,2,1,2,1,2,2};
    vector<int> v(a1712, a1712+AS(a1712));
    cout << "O(N) with Hash: ArraySize=" << AS(a1712) << endl;
    CorrectWithoutDuplicateLogic_PrintPairSum_O_N_withHash(v, 3);
    cout << "O(NLogN, NoDupeHandled) ArraySize=" << AS(a1712) << endl;
    Correct_PrintPairSum_O_NLogN_InPlace_NoDuplicates(a1712, AS(a1712), 3);
    cout << "O(NLogN  DupesHandled) ArraySize=" << AS(a1712) << endl;
    WorksButNah_PrintPairSum_O_NLogN_InPlace_HandlesDuplicates(a1712, AS(a1712), 3);
#endif
#if 0
    //
    // 17.13
    //
    int a1713[] = {1,2,3,4,5};
    BiNode* root = BiNode::MakeFromSortedArray(a1713, 0, AS(a1713)-1);
    cout << "Made a tree with the following inOrderT" << endl;
    root->Print();
    BiNode* head = nullptr, *tail = nullptr;
    BST2DLL(root, head, tail);
    _PrintAsList(head, tail);
    cout << "now turning list back to BST" << endl;
    BiNode* headAgain = DLL2BST(head, 0, AS(a1713)-1);
    headAgain->Print();
#endif 
#if 0
    string w("ycatxdog");
    ParseResult result = ParseWords(w);
    cout << "inv:" << result.invalid << " parsed:" <<  result.parsed << endl;
#endif 

#if 0
    //
    // 18.1
    //
    badd(5,-4);
#endif 
#if 0
    //
    //
    // 18.2
    //
    //
    Card cards[] = {{0,1}, {0,2}, {0, 3}, {0,4}, {0,5}}; 
    vector<Card> v(cards, cards+AS(cards));
    ShuffleDeck_Mine(v);
#endif
#if 0
    //
    // 18.3
    //
    int a183[] = {1,2,3,4,5};
    PickM_MineBetter(vector<int>(a183, a183+AS(a183)), 3);
#endif
#if 0
    //
    // 18.4
    // 
    int n = 22;
    cout << "Twos between 0 and " << n << "=" << CountTwosBruteForce(n) << endl;
#endif
#if 0
    //
    // 18.5
    //
    char* s185[] = {"foo", "cow", "boy", "bar", "cow", "foo" };
    cout << "MinDist=" << MinDist("foo", "bar", vector<string>(s185, s185+AS(s185)));
#endif
#if 0
    //
    // 18.6
    //
    int a186[] = {5,4,3,1,1,2,9,8,7,7,6,10};
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 1);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 2);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 3);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 4);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 5);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 6);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 7);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 8);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 9);
    print_n_smallest(vector<int>(a186, a186+AS(a186)), 10);
#endif
#if 0
    //
    // 18.7
    //
    char* a187[] = { "cat", "cats", "catsdogcats", "catxdogcatsrat", "dog", "dogcatsdog",
        "hippopotamuses", "rat", "ratcatdogcat" };
    LongestCompoundWord_DP(vector<string>(a187, a187+AS(a187)));
    LongestCompoundWord_Trie(vector<string>(a187, a187+AS(a187)));
    LongestCompoundWord_Memo(vector<string>(a187, a187+AS(a187)));
#endif 
#if 0
    //
    // 18.8
    // 
    char* a188[] = { "cat", "dog", "ass", "assk" };
    SearchStringIn("catfragdogasbass", vector<string>(a188, a188+AS(a188)));
#endif
#if 0
    //
    // 18.9
    //
    OnlineMedianAlgorithm();
#endif
#if 0
    //
    // 18.10
    //
    list<string> path;
    HRESULT hr = CalculateTransform("Damp", "Like", path);
    if (SUCCEEDED(hr)) {
        cout << "CalculateTransform Succeeded!" << endl;
    } else {
        cout << "CalculateTransform Failed!" << endl;
    }
    cout << "Transform:";
    for (string const& s : path) {
        cout << s << " ";
    }
    cout << endl;
#endif 
#if 0
    //
    // 18.11
    //
#define DIM 3
    int s1811[DIM][DIM] = 
    { 
        {1,0,1},
        {0,0,1},
        {0,0,1}
    };
    vector<vector<int>> v(DIM, vector<int>(DIM));
    for (int i = 0; i < DIM; ++i) {
        v[i].assign(s1811[i], s1811[i] + DIM);
    }
    result res;
    if (GetSquare(v, res)) {
        cout << "Found Square! \n" ;
        cout << " TL=" << res.tlr << "," << res.tlc << endl;
        cout << " size=" << res.size << endl;
    }
#endif 
#if 0
    //
    // 18.12
    //
#define DIM_ROW 4
#define DIM_COL 5
    int s1812[DIM_ROW][DIM_COL] = 
    { 
        {1,  2, -1,-4, -20},
        {-8,-3,  4, 2, 1},
        { 3, 8, 10, 1, 3},
        {-4,-1, 1, 7, -6}
    };
    vector<vector<int>> v(DIM_ROW, vector<int>(DIM_COL));
    for (int i = 0; i < DIM_ROW; ++i) {
        v[i].assign(s1812[i], s1812[i] + DIM_COL);
    }
    Rect res;
    int max_sum = Kadane2D(v, res);
    cout << "Maximum_Sum=" << max_sum << endl;
    cout << "t=" << res.t << " l=" << res.l << " b=" << res.b << " r=" << res.r << endl;   
#endif 

    /*
     *
     *   CLASSIC DYNAMIC PROGRAMMING ALGORITHMS
     *
     *
     */
#if 0
    /* Knapsack problem */
    Item items[] = {{6,30}, {3,14}, {4,16}, {2,9}};
    vector<Item> v(items, items+AS(items));
    KnapsackRepeats(10, v);
    Knapsack0_1NoRepeats(10, v);
#endif
#if 0
    /* Making Change */
    int coins[] = {1, 5, 25};
    int limits[] = {60, 1, 3};
    vector<int> vCoins(coins, coins+AS(coins));
    vector<int> vLimits(limits, limits+AS(limits));
    MakingChangeInfiniteCoins(65, vCoins);   
    MakingChangeLimitedCoins(65, vCoins, vLimits);
#endif
#if 0
    /* Box Stacking */
    Box boxes[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    vector<Box> vBoxes(boxes, boxes+AS(boxes));
    StackBoxes(vBoxes);
#endif
#if 0
    /*
     * LONGEST COMMON SUBSEQUENCE 
     *
     */
    char* S1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char* S2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    vector<char> vS1(S1, S1+strlen(S1));
    vector<char> vS2(S2, S2+strlen(S2));
    _LCS(vS1, vS2);
#endif 
#if 0
    string S1 = "EXPONENTIAL";
    string S2 = "POLYNOMIAL";
    //string S1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    //string S2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    get_edit_distance(S1, S2);
#endif
#if 0
    /*
     * BALANCED PARTITION
     */ 
    int a[] = {3,2,1,1,2,1};
    vector<int> v(a, a+AS(a));
    balanced_partition(v);
#endif 

    /*
     * RANDOM EXPERIMENTS IN AWESOME
     */
#if 0
    // clever fib - we only need to keep around the last two values by
    // overwriting the smallest one (n-2 term) on each calculation
    int fib[2] = {0,1};
    int counter = 0;
    for (int i = 2; i <= 20; ++i) {
        fib[counter++ % 2] = fib[0] + fib[1];
    }
    cout << fib[0] << endl;

#endif 
#if 1
    unique_ptr<my_map<string, int>> test(new map_oa<string, int>());
    for (int i = 0; i < 50; ++i) {
        string key_string = to_string(i);
        test->insert(key_string, i);
    }
    test->print();

#endif 
    cin.get(); // pause console before exit
    return 0;
}

