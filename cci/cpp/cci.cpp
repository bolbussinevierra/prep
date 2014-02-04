// cci.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#if 0
#include "01.arrays.strings.h"
#endif
#if 0
#include "02.linked.lists.h"
#endif
#if 0
#include "03.stacks.queues.h"
#endif
#if 0
#include "04.trees.graphs.h"
#endif
#if 0
#include "05.bits.h"
#endif
#if 0
#include "07.math.and.probability.h"
#endif
#if 0
#include "09.recursion.and.dp.h"
#endif
#if 0
#include "10.scalability.and.mem.limits.h"
#endif
#if 0
// chapter 11 - grouped with 17 as 17 uses sorting functions in it
#endif
#if 0
#include "13.c.and.cplusplus.h"
#endif
#if 0
#include "11.sorting.and.searching.h"
#include "17.moderate.h"
#endif
#if 0
#include "18.hard.h"
#endif
#if 1
#include "dp.h"
#endif
#if 0
#include "other.h"
#endif
int _tmain(int /*argc*/, _TCHAR* /*argv[]*/)
{
#pragma region reviewed
    srand(time(0));
#if 0
    //1.1
	bool result = IsUniqueChars(""); 

    // 1.6
    int** someArray = new int*[5];
    _FillMatrix(someArray, 5);
    RotateMatrix90(someArray, 5);
#endif
#if 0
    // 1.3
    string a = "abcd";
    string b = "bcda";
    cout << "IsPermutation(" << a << ", " << b << ")=" << std::boolalpha << IsPermutation(a, b);  
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
    //
    // 4.4
    //
    int data44[] = {1,2,3,4,5,6};
    TreeNode* tree = MakeOptimalBST(data44, AS(data44));
    
    vector<shared_ptr<LinkedListNode>> result;
    GetLevelsLinkedLists(tree, result);
    for (shared_ptr<LinkedListNode> const& list : result){
        PrintList(list.get());
    }
    
    cout << "alternative implementation" << endl;
    vector<shared_ptr<LinkedListNode>> result2;
    GetLevelsLinkedLists(tree, result2, 0); 
    for (shared_ptr<LinkedListNode> const& list : result2) {
        PrintList(list.get());
    }

    // 4.1
    cout << "Tree is balanced=" << std::boolalpha << IsBalanced(tree) << endl; 
#endif
#if 0
    //
    // 4.5
    //
    int data45[] = {1,5,4,5,6,7};
    TreeNode* tree = MakeOptimalBST(data45, AS(data45));
    vector<shared_ptr<LinkedListNode>> result2;
    GetLevelsLinkedLists(tree, result2, 0); 
    for (shared_ptr<LinkedListNode> const& list : result2 ) {
        PrintList(list.get());
    }
    cout << "IsBST=" << std::boolalpha << IsBST(tree); 
#endif 
#if 0
    //
    // 4.6
    //
    int a[] = {1,5,4,5,6,7};
    TreeNode* tree = MakeOptimalBST(a, AS(a));
    TreeNode::Print(tree);
    Test_InOrderSuccessor(tree);
#endif 
#if 0
    //
    // 4.7
    //
    int a[] = {1,2,3,4,5,6,7};
    TreeNode* tree = MakeOptimalBST(a, AS(a));
    TreeNode::Print(tree);
    int values[] ={4, 5}; 
    TreeNode* lca = LowestCommonAncestor(tree, values[0], values[1]);
    cout << "lca(" << values[0] << "," << values[1] << ")=" 
         << (lca ? to_string(lca->value) : "None") << endl;
#endif
#if 0
    //
    // 4.8
    //
    int a_tree[] = {1,2,3,4,5,6,7};
    int s_tree[] = {1,2,3};
    TreeNode* tree = MakeOptimalBST(a_tree, AS(a_tree));
    cout << "main tree:" << endl;
    TreeNode::Print(tree);
    TreeNode* subtree = MakeOptimalBST(s_tree, AS(s_tree));
    cout << "subtree:" << endl;
    TreeNode::Print(subtree);
    cout << "IsSubtree()=" << std::boolalpha << IsSubtree(tree, subtree) << endl;
#endif 
#if 0
    //
    // 4.9
    //
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    TreeNode* tree = MakeOptimalBST(a, AS(a));
    TreeNode::Print(tree);
    for (int target = 1; target <= 40; ++target) {
        cout << "paths that sum to " << target << ":\n";
        FindSum(tree,  target);
    }
#endif
#if 0
    //
    // 5.1
    //
    bitset<11> insert("10011");
    bitset<11> into("10000000000");
    int i = 2, j = 6;
    int answer = InsertBits(into.to_ulong(), insert.to_ulong(), 2, 6);
    bitset<11> result(answer);
    cout << "InsertBits(" << into.to_string() << ", " << insert.to_string() << ", " 
        << i << ", " << j << ")=" << result.to_string();
#endif 
#if 0
    //
    // 5.2
    //
    double value = 0.75;
    cout << "ToBinary(" << value << ")=" << ToBinary(value) << endl;
#endif 
#if 0
    //
    // 5.3
    //
    int num = 4;
    cout << "GetNext(" << num << ")=" << GetNextLargestInteger(num) << endl;
    cout << "GetPrev(" << num << ")=" << GetPreviousSmallestInteger(num) << endl;
#endif
#if 0
    //
    // 5.5
    //
    int a = 4, b = 5;
    cout << "SwapsNeeded(" << a << "," << b << ")=" << BitSwapsRequired(a, b) << endl;
    cout << "SwapsNeeded(" << a << "," << b << ")=" << BitSwapsRequired2(a, b) << endl;
#endif
#if 0
    //
    // 5.6
    //
    int num = 5;
    cout << "Swap(" << bitset<4>(num).to_string() << ")=" 
         << bitset<4>(SwapBits(num)).to_string() << endl;

    cout << "Swap2(" << bitset<4>(num).to_string() << ")=" 
         << bitset<4>(SwapBits2(num)).to_string() << endl;

#endif 
#if 0
    //
    // 5.7
    //
    vector<ThreeBitInt> input;
    for (int i = 0; i <= 7; ++i) 
        if (i != 7) 
            input.push_back(i);

    cout << "Missing Integer is=" << FindMissingInteger(input) << endl;
#endif 
#if 0
    //
    // 7.3
    //
    Line a(make_pair(2.0,2.0), make_pair(2.0,4.0));
    Line b(make_pair(4.0,2.0), make_pair(6.0,4.0));
    cout << "intersects=" << boolalpha << a.intersects(b) << endl; 
#endif
#if 1
    //
    // TODO: 7.5
    //
#endif 
#if 0
    //
    // 7.4
    //
    cout << minus(10, 11) << endl;
    cout << multiply(10, 11) << endl;
    cout << divide(10, 2) << endl;
    cout << divide(0, 10) << endl;
    cout << divide(0, 0) << endl;
#endif 
#if 0
    //
    // 9.1
    //
    for (int i = 10; i >=0; --i) {
        printf("WAYSDP(%d)      =%d\n",i, WaysDP(i));
        printf("WAYS(%d)        =%d\n",i, WaysExponential(i));
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
    // 9.3 
    //
    //            0   1    2  3  4  5   6  7  8  9   10
    int a1[] = {-40, -20, -1, 1, 2, 3, 5, 7, 9, 12, 13};
    int a2[] = {-10, -5,   2, 2, 2, 3, 4, 7, 9, 12, 13}; 
    vi v1(begin(a1), end(a1));
    vi v2(begin(a2), end(a2));
    cout << "Magic Index in A1 is=" << MagicIndexUnique(v1) << endl;
    cout << "Magic Index in A2 is=" << MagicIndexDuplicates(v2) << endl;
#endif 
#if 0
    //
    // 9.4
    //
    int items93[] = {1,2,3,4,5,6,7,8,9,10};
    Subsets(items93, AS(items93));
    // SubsetsIterative(items93, AS(items93));
    // SubsetsBinary(items93, AS(items93));
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
    // 9.8
    //
    // First, attempting to calculate the same way as the "ways to climb stairs" problem
    // causes us to run into problems because it double counts combinations that are the
    // same when dealing with coins (e.g [1c,5c] is the same as [5c,1c] whereas if this
    // was ways of stepping instead of coins, they would indeed be two different ways
    int amount = 27;
    int c[] = {1, 5, 10, 25};
    vi coins(begin(c), end(c));
    char * title = "Ways to make change for ";
    cout << title << amount << "=" << CountWaysToMakeChangeDP_SpaceOptimized(amount, coins) << endl;
    cout << title << amount << "=" << CountWaysToMakeChangeDP(amount, coins) << endl;
    cout << title << amount << "=" << CountWaysToMakeChangeMemoized(amount, coins);
#endif
#if 0
    //
    // 9.9
    //
    vi row_set(32, 0);
    SolveQueensColByCol(row_set, 0);
    DrawBoard(row_set);
#endif 
    //
    // 9.10 -- Box stacking problem. See solution under dp
    //
#if 0
    string expr = "1&0^1"; // answer should be two for true
    cout << f(expr, true, 0, expr.length()-1) << endl;
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
    int a113[] = {2,2,2,2,3,4,2};
    rotate(a113, AS(a113), 0);
    int l = 4;
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
#define ROWS 4
#define COLS 5
    int a116[ROWS][COLS] = 
    { {1, 22, 23, 24, 25},
      {12,33, 34, 35, 36},
      {13,44, 45, 46, 46},
      {14,55, 56, 57, 58}}; 
    int find = 35;
    bool found = SearchGrid(a116,find,COLS,ROWS,&l);
    vvi grid;
    Make2DVector(a116, ROWS, COLS, grid);
    Point p = SearchGridBinary(grid, make_pair(0, 0), 
                             make_pair(grid.size() - 1, grid[0].size() - 1), find);
    cout << "SearchGridBinary found" << find << " at "; Print(p); cout << endl;
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
    // 13.08
    //
    
    {
        smart_pointer<int> sptr1(new int(1));
        smart_pointer<int> sptr2(sptr1);
        smart_pointer<int> sptr3(new int(3));
        sptr1 = sptr3;
    }
    
    {
        // cyclic reference memory leak example
        struct Node { smart_pointer<Node> ptr; };
        
        smart_pointer<Node> a (new Node());
        smart_pointer<Node> b (new Node());
        a.get()->ptr = b;
        b.get()->ptr = a;
    }

#endif
#if 0
    //
    // 13.09
    //
    bitset<32> mem_value;
    void* mem = aligned_malloc(10, 16);
    mem_value = (long) mem;
    cout << mem_value.to_string() << endl;
    aligned_free(mem);
#endif
#if 0
    //
    // 13.10
    //
    int ** double_array = Alloc2D(5, 5);
    double_array[3][5] = 20;
    cout << double_array[3][5] << endl;
    free(double_array);
#endif
#if 0
    //
    // 17.1
    //
    int a = 5, b = 0;
    printf("swap(%d,%d)=(%d,%d)\n", a,b, get<0>(swap_opt(a, b)), get<1>(swap_opt(a, b)));
    printf("swap(%d,%d)=(%d,%d)\n", a,b, get<0>(swap_opt2(a, b)), get<1>(swap_opt2(a, b)));
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
    vector<vector<Type>> b; 
    Make2DVector(_b, BS, BS, b);
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
    // 17.5
    // 
    Result res = estimate("GGRR", "RGBY");
    printf("(hits:%d phits:%d)", res.hits, res.pseudo_hits);
#endif
#if 0
    //
    // 17.6
    //
    int a176[] = {1,2,4,7,10,11,7,12,6,7,16,18,19};
    vi v(begin(a176), end(a176));
    GetSortRange(v);
#endif
#if 0
    //
    // 17.7
    //
    cout << NumToString(11111111);
#endif 
#if 0
    //
    // 17.8
    //
    int a178[] = {2, -8, 3, -2, 4, -10};
    //int a178b[] = {-2, -8, -3, -2, -4, -10};
    vi v(begin(a178), end(a178));
    PrintMaxSumNaive(v);
    PrintMaxSumBest(v);
#endif
#if 0
    //
    // 17.9
    //
    char* a179[] = {"FOO", "bar", "CALYpso", "Calypso", "Bar"};
    vector<string> v(begin(a179), end(a179));
    SetupFrequencyTable(v);
    string lookup("Calypso");
    cout << "Frequency of " << lookup << " is=" << LookupWord(lookup) << endl;
#endif
#if 0
    //
    // 17.11
    //
    cout << rand7_cool() << endl;
    cout << rand7_cool() << endl;
    cout << rand7_cool() << endl;
    cout << rand7() << endl;
    cout << rand7() << endl;
    cout << rand7() << endl;
#endif 
#if 0
    //
    // 17.12
    //
    int a1712[] = {1,2,1,2,1,2,2};
    vi v(begin(a1712), end(a1712));
    cout << "O(N) with Hash: ArraySize=" << AS(a1712) << endl;
    PrintPairSum_O_N_UsesHashTable_HandlesDuplicates(v, 3);
    cout << "O(NLogN, NoDupeHandled) ArraySize=" << AS(a1712) << endl;
    PrintPairSum_O_NLogN_InPlace_NoDuplicates(a1712, AS(a1712), 3);
    cout << "O(NLogN  DupesHandled) ArraySize=" << AS(a1712) << endl;
    PrintPairSum_O_NLogN_InPlace_HandlesDuplicates(a1712, AS(a1712), 3);
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
    //
    // 17.13
    // 
    string w("ycatxdog");
    ParseResult result = ParseWords(w);
    cout << "inv:" << result.invalid << " parsed:" <<  result.parsed << endl;
#endif 
#if 0
    //
    // 18.1
    //
    badd(174,165);
#endif 
#if 0
    //
    //
    // 18.2
    //
    //
    Card cards[] = {{0,1}, {0,2}, {0, 3}, {0,4}, {0,5}}; 
    vector<Card> v(begin(cards), end(cards));
    ShuffleDeck_Mine(v);
#endif
#if 0
    //
    // 18.3
    //
    int a183[] = {1,2,3,4,5};
    PickM_MineBetter(vi(begin(a183), end(a183)), 3);
#endif
#if 0
    //
    // 18.4
    // 
    int n = 3222222;
    cout << "Twos between 0 and " << n << "=" << CountTwosMemoized(n) << endl;
    cout << "Twos between 0 and " << n << "=" << CountTwosBruteForce(n) << endl;
#endif
#if 0
    //
    // 18.5
    //
    char* s185[] = {"foo", "cow", "boy", "bar", "cow", "foo" };
    cout << "MinDist=" << MinDist("foo", "bar", vector<string>(begin(s185), end(s185)));
#endif
#if 0
    //
    // 18.6
    //
    int a186[] = {5,4,3,1,1,2,9,8,7,7,6,10};
    print_n_smallest(vi(begin(a186), end(a186)), 1);
    print_n_smallest(vi(begin(a186), end(a186)), 2);
    print_n_smallest(vi(begin(a186), end(a186)), 3);
    print_n_smallest(vi(begin(a186), end(a186)), 4);
    print_n_smallest(vi(begin(a186), end(a186)), 5);
    print_n_smallest(vi(begin(a186), end(a186)), 6);
    print_n_smallest(vi(begin(a186), end(a186)), 7);
    print_n_smallest(vi(begin(a186), end(a186)), 8);
    print_n_smallest(vi(begin(a186), end(a186)), 9);
    print_n_smallest(vi(begin(a186), end(a186)), 10);
#endif
#if 0
    //
    // 18.7
    //
    char* a187[] = { "cat", "cats", "catsdogcats", "catxdogcatsrat", "dog", "dogcatsdog",
        "hippopotamuses", "rat", "ratcatdogcat" };
    LongestCompoundWord_DP(vector<string>(begin(a187), end(a187)));
    LongestCompoundWord_Trie(vector<string>(begin(a187), end(a187)));
    LongestCompoundWord_Memo(vector<string>(begin(a187), end(a187)));
#endif 
#if 0
    //
    // 18.8
    // 
    char* a188[] = { "cat", "dog", "ass", "assk" };
    SearchStringIn("catfragdogasbass", vector<string>(begin(a188), end(a188)));
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
    vector<vi> v; 
    Make2DVector(s1811, DIM, DIM, v);
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
    vector<vi> v; 
    Make2DVector(s1812, DIM_ROW, DIM_COL, v);
    Rect res;
    int max_sum = Kadane2D(v, res);
    cout << "Maximum_Sum=" << max_sum << endl;
    cout << "t=" << res.t << " l=" << res.l << " b=" << res.b << " r=" << res.r << endl;   
#endif 
#pragma endregion --- move along as problems are reviewed ----------------------
#pragma region dynamic_programming
    /*
     *
     *   CLASSIC DYNAMIC PROGRAMMING ALGORITHMS
     *
     *
     */
#if 0
    /* KNAPSACK PROBLEM */
    Item items[] = {{6,30}, {3,14}, {4,16}, {2,9}};
    vector<Item> v(begin(items), end(items));
    KnapsackRepeats(10, v);
    Knapsack0_1NoRepeats(10, v);
#endif
#if 0
    /* MAKING CHANGE WITH FEWEST COINS */
    int coins[] = {1, 5, 25};
    int limits[] = {60, 1, 3};
    vi vCoins(begin(coins), end(coins));
    vi vLimits(begin(limits), end(limits));
    MakingChangeInfiniteCoins(65, vCoins);   
    MakingChangeLimitedCoins(65, vCoins, vLimits);
#endif
#if 0
    /* BOX STACKING TO ACHIEVE HIGHEST HEIGHT */
    Box boxes[] = { {4, 6, 7}, {1, 2, 3}, {4, 5, 6}, {10, 12, 32} };
    vector<Box> vBoxes(begin(boxes), end(boxes));
    StackBoxes(vBoxes);
#endif
#if 0
    /* LONGEST COMMON SUBSEQUENCE */
    char* S1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    char* S2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    vector<char> vS1(S1, S1+strlen(S1));
    vector<char> vS2(S2, S2+strlen(S2));
    _LCS(vS1, vS2);
#endif 
#if 0
    /* EDIT DISTANCE */
    string S1 = "EXPONENTIAL";
    string S2 = "POLYNOMIAL";
    //string S1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    //string S2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    GetEditDistance(S1, S2);
#endif
#if 0
    /* BALANCED PARTITION */
    int a[] = {3,2,1,1,2,1};
    vi v(begin(a), end(a));
    BalancedPartition(v);
#endif 
#if 0
    /* MAXIMUM SUBMATRIX THAT IS ALL 1 (NOT NECCESARILY SQUARE) */ 
#define DIM_ROW 4
#define DIM_COL 6
    int a_matrix[DIM_ROW][DIM_COL] = 
    { 
        {0,1,1,0,0,0},
        {0,1,1,1,1,0},
        {1,1,1,1,1,0}, 
        {1,1,1,1,1,0},
    };

    vvi v;
    Make2DVector(a_matrix, DIM_ROW, DIM_COL, v);
    Rect res;
    if(SUCCEEDED(LargestSubmatrixOfOnes(v, res))) {
        cout << "largest submatrix = "; 
        res.Print();
    }
    if(SUCCEEDED(LargestSquareSubmatrixOfOnes(v, res))) {
        cout << "largest square submatrix = "; 
        res.Print();
    }
#endif
#if 0
    /* MINIMUM NUMBER OF JUMPS - the best algorithm for this is ACTUALLY GREEDY */
    int arr1[] = {1, 3, 5, 9, 8, 2, 6, 7, 6, 8, 9}; // ans = 0, 1, 3, 9 (indexes)
    int arr2[] = {2,3,1,1,4}; // ans=0,1,4
    int arr3[] = {1,1,1,0,1}; // no path
    int arr4[] = {0,1,1}; // no path
    int arr5[] = {1,1,1}; // ans=0,1,2

    vi cases[] = {
        vi(begin(arr1), end(arr1)),
        vi(begin(arr2), end(arr2)),
        vi(begin(arr3), end(arr3)),
        vi(begin(arr4), end(arr4)),
        vi(begin(arr5), end(arr5)),
    };

    for (vi const& v : cases) {
        list<int> jumps;
        HRESULT hr = MinJumps_DP_NotIdeal_O_N2(v, jumps);
        PrintJumps(hr, jumps);
        jumps.clear();
        hr = MinJumps_Greedy_Best_O_N(v, jumps);
        PrintJumps(hr, jumps);
        cout << "-------------------\n";
    }
    
#endif
#if 0
    /* Longest Palindrome Subsequence */
    string s("CBABBABD");
    string result;
    int length = LongestPalindromeSubsequence(s, result);
    cout << "String=" << s << endl;
    cout << "LPS Length=" << length << endl;
    cout << "LPS String=" << result << endl;
#endif
#if 0
    /* Matrix Multiplication */
    int a[] = {10, 20, 30, 40, 30};
    vi v(begin(a), end(a));
    string result;
    string m_print; // simply to print the matrices
    int count = MatrixChainOrder(v, m_print, result);
    cout << "Matrices are: " << m_print << endl;
    cout << "Fewest multiplications=" << count << endl;
    cout << "Parenthesization=" << result << endl;
#endif
#if 0
    //
    // Subset Sum - is there a subset of item that sums up to a given value
    //
    int set[] = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    vi result;
    vi v(begin(set), end(set));
    bool has_subset = SubsetWithSum(v, sum, result);
    if (has_subset) {
        cout << "There is a subset with sum=" << sum << endl;
        cout << "The Subset is:";
        for (int i : result) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        cout << "There is no subset with sum=" << sum << endl;
    }
#endif
#if 0
    /*
     Largest submatrix with the largest sum
    */

    /*
        SEE Kadane2D() algorithm in the chapter 18 code
     */
#endif
#if 0
    /*
     
        DICE THROW PROBLEM - given N dice with M faces and a value x, how many ways are there
        to throw a sum of x

    */
    int sum_to = 8;
    int dice_count = 3;
    int face_count = 6;
    cout << "Given dice_count=" << dice_count << endl;
    cout << "    & face_count=" << face_count << endl;
    cout << "  ways to sum to=" << sum_to << endl; 
    cout << "              is=" << WaysToSumDiceTo(sum_to, dice_count, face_count) << endl;

#endif
#if 0
    /*
     *
     * ROD CUTTING - Best way to cut a rod to maximize cost
     *
     */
    int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
    vi p(begin(arr), end(arr));
    vi cuts;
    int best_price = CutRod(p, cuts);
    cout << "Best Price=" << best_price << endl;
    cout << "make cuts at:" ;
    for (int i : cuts) {
        cout << i << " ";
    }
#endif
#if 0
    /*
     * BEST STRATEGY FOR A GAME
     *
     */
    int arr[] = {8, 15, 3, 7};
    vi coins(begin(arr), end(arr));
    vi moves_player_one;
    vi moves_player_two;
    int score = BestStrategyForGame(coins, moves_player_one, moves_player_two);
    cout << "winning score=" << score << endl;
    Print("player_one moves", moves_player_one);
    Print("player_two moves", moves_player_two);
#endif
#pragma endregion

#pragma region other_questions
#if 0
    //
    // OTHER RANDOM QUESTIONS
    // 
    //
    /*
    design transliteration API.
    First given an english string, convert it to a corresponding foreign
    language letter.
    a -> t1
    b -> t2
    Extend the solution to support multi-char matching
    a -> t1
    aa -> t2
    ab -> t3
    b -> t4
    abc -> t5
    if the given string abcaaaabbaabc result should be
    t5 t2 t2 t4 t4 t2 t4 c
    */
    string out;
    Transliterate("abcaaaabbaabc", out); // worked first time! Gangsta.
    cout << out; 
#endif
#if 0
    /*
        Find various paths for the given word. For e.g. “cat”
    */

#define ROWS 6
#define COLS 6
    char word_table[ROWS][COLS] = { 
        'a','e','c','q','t','q', 
        'i','a','a','a','h','b',
        't','i','t','c','n','i',
        'i','a','s','t','i','i',
        'h','i','c','a','h','n',
        'o','r','q','i','n','i'};

    vvc v;
    Make2DVector(word_table, ROWS, COLS, v);
    
    PrintLetterPaths("CAT", v);
    /*
        Check if a word exists in a table. Cycles are allowed
    */
    ContainsWordDP("AHA", v);
#endif 
#if 0
    /* 
        Given a list of integers, find a number that does not have a pair
        1 2 1 3 5 -3 -2 6 2 -3 5 -2
        Here 3 does not have the pair (6 does not have one either)
    */
    int a[] = {1, 2, 1, 3, 5, -3, -2, 6, 2, -3, 5, -2};
    vi v(begin(a), end(a));
    PrintNumberMissingPair(v);
#endif
#if 0
    /*
    Given a M * N array, find one path from a cell to another cell. Rules
    1) Only up and right traversal is allowed
    2) Some cells could be marked as “Walls”. There’s no path through
    through those cells

    SAME AS CCI 9.2

    */
    list<Point> path;
    bool success = FindPath(make_pair(5,0), make_pair(0,5), path);
    if (success) 
        for_each(path.begin(), path.end(), Print);
    else 
        cout << "No Path Possible!" << endl;

#endif
#if 0
    /*
    How would you clone a doubly linked list which has Next and Random
    pointer. Next points to the next node whereas the Random node points to
    any random node
    */
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    vi v(begin(a), end(a));
    shared_ptr<Link> original = MakeLinkList(v);
    shared_ptr<Link> copy1 = CopyList_O_N_Space_O_N_Speed(original.get());
    shared_ptr<Link> copy2 = CopyList_O_1_Space_O_N_Speed(copy1.get());
    PrintList(original.get());
    PrintList(copy1.get());
    PrintList(copy2.get());
#endif
#if 0
    /*
    Given a Matix (two dim array) where each element[i][j] is greater
    than or equal to element[i-1][j-1] how would you efficiently count the
    number of negatives.
    */
#define DIM_ROW 4
#define DIM_COL 3
    int a_matrix[DIM_ROW][DIM_COL] = 
    { 
        { 0 ,  1,   0},
        { -1, -2,  -1},
        { -2, -1,   0}, 
        { -1, -3,   6},
    };
    int ans = 7;

    vvi v;
    Make2DVector(a_matrix, DIM_ROW, DIM_COL, v);
    cout << "expected=" << ans << " got=" << CountNegatives(v) << endl;
#endif 
#if 0
    /* design a stack with min */
    stack_with_min<int> s;
    for (int i = 1; i < 10; ++i) {
        s.push(rand() % 7);
        cout << " Added=" << s.top() << " min=" << s.min() << endl;
    }
    for (int i = 1; i < 10; i++) {
        int value = s.top();
        s.pop();
        cout << "Popped=" << value << " min=" << s.min() << endl;
    }

#endif
#if 0
    /* range of numbers that has the maximum sum */
    /*
        See Kadane Implementation in Chapter.18.h
    */
#endif 
#if 0
    /* Implement a function that can calculate the prime numbers upto number N */
    /* Loose bound on performance is O(nlogn) (n/2 + n/3 + n/4 ...) = n(1/2 + 1/3 + ..) */
    vi v = GetPrimesUpto(1000);
    for_each(v.begin(), v.end(), [](int n){ cout << n << endl;});
#endif 
#if 0
    /* Given a byte array, how would you eliminate duplicate entries */
    byte a[] = {'1','1','1','4','3','4','5','1','6','7','9','3'};
    vector<byte> v(begin(a), end(a));
    RemoveByteDuplicates(v);
    for_each(v.begin(), v.end(), [](byte n) { cout << n << endl;});
#endif 
#pragma endregion

#pragma region random_experiments
// -----------------------------------------------------------------------------------
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
#if 0
    vi v(21);
    for (int i = 0; i < v.size(); ++i) 
        v[i]=i;
    for_each(v.begin()+0, v.begin()+1, [](int n) { cout << n << " "; });
#endif 
#if 0
#define COUNT 50
    map_ch<string, int> test;
    // map_oa<string, int> test;
    for (int i = 0; i < COUNT; ++i) {
        string key_string = to_string(i);
        test.insert(key_string, i);
    }
    assert(test.size() == COUNT);
    test.print();
    for (int i = 0; i < COUNT; ++i) {
        string key_string = to_string(i);
        int result;
        assert(test.find(key_string, result));
    }

#endif 
#pragma endregion
    cin.get(); // pause console before exit
    return 0;
}

