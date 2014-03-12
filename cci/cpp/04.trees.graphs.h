#pragma once
//
// helpers
//
struct TreeNode {
    int value;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
    TreeNode(int value):value(value), left(nullptr), right(nullptr), parent(nullptr) {}
    static void Print(TreeNode* root, int indent = 0){
        if (!root) return;
        Print(root->right, indent+1);
        for (int i = 1; i <= indent; ++i) {
            cout << "  ";
        }
        cout << root->value << endl;
        Print(root->left, indent + 1);
    }
};
namespace epi_9 {
template<typename T>
TreeNode* _BuildTreeFromPreInTraversal(
    vector<T> const& pre, int pre_s, int pre_e,
    vector<T> const&  in, int  in_s, int  in_e) {
        
    if (pre_s >= pre_e || in_s >= in_e) return nullptr;

    // we want to be able to partition the root, left and right node sets
    auto it = find(begin(in) + in_s, begin(in) + in_e, pre[pre_s]);
    int left_tree_size = distance(begin(in)+in_s, it);

    TreeNode* root = new TreeNode(pre[pre_s]);
    root->left  = _BuildTreeFromPreInTraversal(
                    pre, pre_s+1, pre_s+1+left_tree_size,
                    in, in_s, distance(begin(in), it));
    root->right = _BuildTreeFromPreInTraversal(
                    pre, pre_s+1+left_tree_size, pre_e,
                    in, distance(begin(in), it)+1, in_e);
    return root;
}


TreeNode* BuildFromPreOrderSpec(vector<string> const& spec) {
    
    // go through the nodes in reverse order (would be front order if postorder)
    stack<TreeNode*> s;
    for (auto it = spec.rbegin(); it != spec.rend(); ++it) {
        if (*it == "N")
            s.emplace(nullptr);
        else {
            auto root = new TreeNode(atoi((*it).c_str()));
            root->left = s.top(); s.pop();
            root->right = s.top(); s.pop();
            s.push(root);
        }
    }
    return s.top();
}

}

namespace epi_8 {
    void PrintBinaryTreeLevelOrder(TreeNode* root) {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        size_t count = 1;
        while (!q.empty()) {
            cout << q.front()->value << ' ';
            if (q.front()->left)
                q.push(q.front()->left);
            if (q.front()->right)
                q.push(q.front()->right);
            q.pop();
            if (--count == 0) {
                cout << endl;
                count = q.size();
            }
        }
    }
}
namespace epi_9 {
void PrintInOrderIterUsingParentPtr(TreeNode* root) {
    if (!root) return;
    TreeNode* curr = root, *next = nullptr, *prev = nullptr;
    while (curr) {
        // if we are starting or we have found an inorder child ...
        if (!prev || prev->left == curr || prev->right == curr) {
            // keep going left if we can
            if (curr->left) {
                next = curr->left;
            } else {
                // else, print the current value, if possible go right, else up
                cout << curr->value << " ";
                next = (curr->right ? curr->right : curr->parent);
            } 
        // just returned from left child, print current, if possible go right else up
        } else if (curr->left == prev) {
            cout << curr->value << " ";
            next = (curr->right ? curr->right : curr->parent);    
            // just returned from a right child, go up next
        } else { // curr->right == prev {
            next = curr->parent;
        }
        prev = curr;
        curr = next;
    }
}
}
/*
 * In order iterator
 */
class TreeIterator {
private:
    // TreeNode* m_pre;
    // TreeNode* m_current;
    stack<TreeNode*> nodes;
    void _SetBegin(TreeNode* root) {
        while (root) {
            nodes.push(root);
            root = root->left;
        }
    }
public:
    explicit TreeIterator(TreeNode* root) {
        _SetBegin(root);
    }
    bool HasNext() { return !nodes.empty(); }
    TreeIterator operator++() {
        if (!nodes.empty()) {
            TreeNode* top = nodes.top();
            nodes.pop();
            TreeNode* right_side = top->right;
            while (right_side) {
                nodes.push(right_side);
                right_side = right_side->left;
            }
        }
        return *this;
    }
    int operator*() {
        if (!nodes.empty())
            return nodes.top()->value;
        else
            return numeric_limits<int>::infinity();
    }
};
struct LinkedListNode {
    TreeNode* value;
    shared_ptr<LinkedListNode> next;
    LinkedListNode(TreeNode* value):value(value), next(nullptr){}
};
void PrintList(LinkedListNode* head){
    if(!head) return;
    do{
        printf("%d ", head->value->value); 
        head = head->next.get();
    }
    while(head);
    printf("%\n");
}
TreeNode* _MakeOptimalBST(int * items, int start, int end) {
    if  (end < start) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    TreeNode *n = new TreeNode(items[mid]);
    n->left = _MakeOptimalBST(items, start, mid-1);
    n->right = _MakeOptimalBST(items, mid+1, end);
    // set parent pointers
    if (n->left) n->left->parent = n;
    if (n->right) n->right->parent = n;
    return n;
}
TreeNode* MakeOptimalBST(int * items, int n){
    return _MakeOptimalBST(items, 0, n - 1);
}
//
// helpers
//
//
//
// 4.1
//
int _CheckHeight(TreeNode* node) {
    if (!node) return 0;
    int left_height = _CheckHeight(node->left);
    if (-1 == left_height) return -1;
    int right_height = _CheckHeight(node->right);
    if (-1 == right_height) return -1;
    if (abs(left_height - right_height) > 1) return -1;
    return max(left_height, right_height)+1;
}
bool IsBalanced(TreeNode* root) {
    return _CheckHeight(root) != -1;
}
//
//
// 4.4
// -- recursive
void GetLevelsLinkedLists(TreeNode * root, vector<shared_ptr<LinkedListNode>>& lists, 
                        uint level) {
    if (!root) return;
    if (lists.size() < level+1) { // level is 0 indexed
        lists.push_back(make_shared<LinkedListNode>(root));
    } 
    else {
        shared_ptr<LinkedListNode> link = make_shared<LinkedListNode>(root);
        link->next = lists[level];
        lists[level] = link;
    }
    GetLevelsLinkedLists(root->right, lists, level+1);
    GetLevelsLinkedLists(root->left, lists, level+1);
}
// -- iterative
void GetLevelsLinkedLists(TreeNode* root, vector<shared_ptr<LinkedListNode>>& result){
    if (!root) return;
    shared_ptr<LinkedListNode> head = make_shared<LinkedListNode>(root);
    shared_ptr<LinkedListNode> tail(head);
    vector<TreeNode*> level_nodes;
    level_nodes.push_back(root);
    while (level_nodes.size() > 0) {
        result.push_back(head);
        vector<TreeNode*> parents(level_nodes);
        level_nodes.clear();
        head = nullptr;
        tail = nullptr;
        for (size_t i = 0; i < parents.size(); i++){
            if (parents[i]->left){
                if (!head) {
                    head = make_shared<LinkedListNode>(parents[i]->left);
                    tail = head;
                } else {
                    tail->next = make_shared<LinkedListNode>(parents[i]->left);
                    tail = tail->next;
                }
                level_nodes.push_back(parents[i]->left);
            }
            if (parents[i]->right) {
                if (!head) {
                    head = make_shared<LinkedListNode>(parents[i]->right);
                    tail = head;
                } else {
                    tail->next = make_shared<LinkedListNode>(parents[i]->right);
                    tail = tail->next;
                }
                level_nodes.push_back(parents[i]->right);
            }
        }
    }
}
//
// 4.5
//
bool _IsBST(TreeNode* root, int min, int max) {
    if (!root) return true;
    // NOTE! there is a tricky bit of logic here. The left tree is limited by max.
    // by definition of bst, left should be equal or less than or max. Min is used
    // to contrain the RIGHT side of the tree so root needs to be strictly greater
    if (root->value <= min || root->value > max) 
        return false;
    // going left updates the max, going right updates the min
    if (!_IsBST(root->left, min, root->value) || 
        !_IsBST(root->right, root->value, max)) 
        return false;
    return true;
}
bool IsBST(TreeNode* root) {
    return _IsBST(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}
//
// 4.6
//
TreeNode* _LeftMost(TreeNode* root) {
    if (!root) return nullptr;
    while (root->left) 
        root = root->left;
    return root;
}
TreeNode* InOrderSuccessor(TreeNode* root) {
    if(!root) return nullptr;
    // if the node has a right branch, return the left most 
    // node in that branch
    if (root->right) {
        return _LeftMost(root->right);
    }
    else {
        // otherwise find the parent that root is on the LEFT side of
        TreeNode *p = root->parent;
        while (p && p->right == root) {
            root = p;
            p = p->parent;
        }
        return p; // will be nullptr if tree is fully explored (correct)
    }
}
void Test_InOrderSuccessor(TreeNode* root) {
    if (!root) return;
    Test_InOrderSuccessor(root->left);
    TreeNode *s = InOrderSuccessor(root);
    cout << "InOrderSuccessor(" << root->value << ")=" << (s ? to_string(s->value) : "nullptr") << endl;
    Test_InOrderSuccessor(root->right);
}
//
// 4.7
// - common ancestor
bool _NodeInTree(TreeNode* root, int value) {
    if (!root) return false;
    if (root->value == value) return true;
    return _NodeInTree(root->left, value) || _NodeInTree(root->right, value);
}
TreeNode* _LowestCommonAncestor(TreeNode* root, int value1, int value2) {
    if (!root) return nullptr;
    if (root->value == value1 || root->value == value2) 
        return root;
    TreeNode* lca_left = _LowestCommonAncestor(root->left, value1, value2);
    TreeNode* lca_right = _LowestCommonAncestor(root->right, value1, value2);
    if (lca_left && lca_right) return root;
    return lca_left ? lca_left : lca_right;
}
TreeNode* LowestCommonAncestor(TreeNode* root, int value1, int value2) {
    if (!_NodeInTree(root, value1) || !_NodeInTree(root, value2))
        return nullptr;
    return _LowestCommonAncestor(root, value1, value2);
}
//
// 4.8
//
bool _MatchTree(TreeNode* tree, TreeNode* subtree) {
    if (!tree && !subtree) return true;  // empty trees both match
    if (!tree || !subtree) return false; // only one of them is empty
    if (tree->value != subtree->value) return false;
    return _MatchTree(tree->left, subtree->left) && 
          _MatchTree(tree->right, subtree->right);
}
bool _IsSubtree(TreeNode* tree, TreeNode* subtree) {
    if (!tree) return false; // ran out of tree nodes on this branch without a match
    if (tree->value == subtree->value) 
        if (_MatchTree(tree, subtree)) return true;
    return _IsSubtree(tree->left, subtree) || _IsSubtree(tree->right, subtree);
}
bool IsSubtree(TreeNode* tree, TreeNode* subtree) {
    if (!subtree) return true; // empty subtree is always a subtree
    return _IsSubtree(tree, subtree);
}
//
// 4.9
//
int _depth(TreeNode* tree) {
    if (!tree) return 0;
    return 1 + max(_depth(tree->left), _depth(tree->right));
}
void _FindSum(TreeNode* tree, int target, vi& path, int level) {
    if (!tree) return;
    path[level]=tree->value;
    int sum = 0;
    for (int i = level; i >= 0; --i) {
        sum += path[i];
        if (sum == target) {
            for_each(path.begin()+i, path.begin()+level+1, [](int n) { cout << n << " "; });
            cout << endl;
        }
    }
    _FindSum(tree->left, target, path, level+1);
    _FindSum(tree->right, target, path, level+1);
}
void FindSum(TreeNode* tree, int target) {
    vi path(_depth(tree));
    return _FindSum(tree, target, path, 0);
}
tuple<TreeNode*, TreeNode*> _Find(TreeNode *root, int key) {
    if (!root) return make_tuple(nullptr, nullptr);
    TreeNode* current = root;
    TreeNode* parent = nullptr;
    while (current) {
        if (current->value == key) 
            return make_tuple(current, parent);
        else if (current->value > key) {
            parent = current;
            current = current->left;
        }
        else {
            parent = current;
            current = current->right;
        }
    }
    return make_tuple(nullptr, nullptr);
}
void _DeleteNode(TreeNode* n, TreeNode* parent) {
    if (!n) return;
    // if n has no children delete simply unlink it from its parent
    // and delete it
    if (!n->left && !n->right) {
        if (parent->left == n)
            parent->left = nullptr;
        else
            parent->right = nullptr;
    }
    // has both children, get the inorder successor, move it up to the
    // node and then go and delete the duplicate
    else if (n->left && n->right) {
        TreeNode* in_order_succ_parent = nullptr;
        TreeNode* in_order_succ = _LeftMost(n->right);
        n->value = in_order_succ->value;
        // TODO: this would be unnecesary if we change _leftMost to return
        // parent as well (I am pretending TreeNode does not have a parent
        // member for purposes of this algorithm
        tie(in_order_succ, in_order_succ_parent) = _Find(n->right, n->value);
        // if we do not get a parent for the successor we just used, this means
        // it is a child of n (which was not included in the find)
        if (!in_order_succ_parent) in_order_succ_parent = n; 
        return _DeleteNode(in_order_succ, in_order_succ_parent);
    }
    // else it has only one child
    else if (n->left || n->right) {
        if (parent->left == n) {
            parent->left = (n->left) ? n->left : n->right;
            parent->left->parent = parent;
        }
        else {
            parent->right = (n->left) ? n->left : n->right;
            parent->right->parent = parent;
        }
    }
    delete n;
    return;
}
// http://www.algolist.net/Data_structures/Binary_search_tree/Removal
void DeleteNode(TreeNode *& root, int key) {
    if (!root) return;
    TreeNode *parent = nullptr, *found = nullptr;
    tie(found, parent) = _Find(root, key);
    if (!found) return;
    assert(found->value == key);
    // check if we are deleting the root. This is a special case that requires
    // special treatment. The approach we use here is to create a dummy root,
    // hang the real root on it and then after the delete algorithm runs, 
    // restore the root
    if (found->value == root->value) {
        shared_ptr<TreeNode> dummy_root = make_shared<TreeNode>(0);
        dummy_root->left = root;
        root->parent = dummy_root.get();
        _DeleteNode(root, dummy_root.get());
        root = dummy_root->left;
    }
    else {
        return _DeleteNode(found, parent);
    }
}
/* 
    Traverse a tree inorder without extra space or recursion (Morris Algorithm)
    NlogN
*/
void MorrisInOrder(TreeNode* root) {
    if (!root) return;
    TreeNode* current = root;
    TreeNode* threader = nullptr;
    while (current) {
        if (!current->left) {
            cout << current->value << " ";
            current = current->right;
        }
        else {
            threader = current->left;
            while(threader->right && threader->right != current)
                threader = threader->right;
            // at this point threader->right is either null or it points to current
            if (!threader->right) {
                // create the thread and move left
                threader->right = current;
                current = current->left;
            }
            else { // break the thread, print the node and go right. 
                threader->right = nullptr;
                cout << current->value << " ";
                current = current->right;
            }
        }
    }
}
// ****************************************************************************
// TOPOLOGICAL SORT 
// ****************************************************************************
class Graph{
private:
    int vertice_count_;
    vector<list<int>> adj_; // list of adjacency lists
    void _TopologicalSort(int v, vector<bool>& visited, stack<int>& sort) {
        // mark the current node as visited
        visited[v] = true;

        // recur for all vertices adjacent to this vertex
        for(auto it = adj_[v].begin(); it != adj_[v].end(); ++it) 
            if (!visited[*it])
                _TopologicalSort(*it, visited, sort);

        sort.push(v);
    }

public:
    explicit Graph(int vertice_count)
        :vertice_count_(vertice_count), adj_(vertice_count, list<int>()) { }

    void AddEdge(int v, int w) {
        adj_[v].push_back(w);
    }

    void TopologicalSort() {
        stack<int> sort;

        // mark all the vertices are visited
        vector<bool> visited(vertice_count_, false);

        // call the recursive sort helper to store the topological sort
        // starting from all vertices one by one
        for (int i = 0; i < vertice_count_; ++i) 
            if (!visited[i]) 
                _TopologicalSort(i, visited, sort);

        while (!sort.empty()) {
            cout << sort.top() << " ";
            sort.pop();
        }

    }
};

BEGIN_NAMESPACE(epi_16) 
//
// 16.1
// 
vvi MakeMaze(size_t dimension, size_t walls=0) {
    vvi maze(dimension, vi(dimension, 0)); // zero unblocked

    // create some random walls
    random_device rd;
    default_random_engine e(rd());
    uniform_int_distribution<int> dist(0, dimension - 1);

    cout << "--BLOCKLIST--" << endl;
    for (int i = 0; i < walls; ++i) {
        int x = dist(e);
        int y = dist(e);
        printf("[%d, %d]\n", x, y);
        maze[x][y] = 1;
    }
    cout << "--BLOCKLIST--" << endl;
    return maze;
}

struct Coordinate {
    bool operator==(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }
    int x, y;
};

// check if cur is within the maze
bool _WithinBounds(Coordinate const& curr, vvi const& maze){
    return curr.x >= 0 && curr.x < maze.size() &&
            curr.y >= 0 && curr.y < maze[curr.x].size();
}

bool _IsFeasible(Coordinate const& curr, vvi const& maze){
    return _WithinBounds(curr, maze) && maze[curr.x][curr.y] == 0;
}

bool _SearchMazeHelper(vvi& maze, Coordinate const& curr, Coordinate const& e, vector<Coordinate>& path) {
    if (curr == e) return true; // found destination!
    if (!_WithinBounds(curr, maze)) return false; 

    const array<array<int, 2>, 4> neighbors = {
        { { { -1, 0 } }, { { 1, 0 } }, { { 0, -1 } }, { { 0, 1 } } }
    };

    for (const auto& s : neighbors) {
        Coordinate next{ curr.x + s[0], curr.y + s[1] };
        if (_IsFeasible(next, maze)) {
            // block this item to mark it as visited
            maze[curr.x][curr.y] = 1;
            path.emplace_back(next);
            if (_SearchMazeHelper(maze, next, e, path)) {
                return true; 
            }
            path.pop_back(); // back track
        }
    }
    return false;
}
vector<Coordinate> SearchMaze(vvi& maze, Coordinate const& s, Coordinate const& e) {
    // we are going to do a dfs search to find the path
    vector<Coordinate> path;
    if (_IsFeasible(s, maze)) {
        path.emplace_back(s);
        if (!_SearchMazeHelper(maze, s, e, path))
            path.pop_back();
    }
    return path; // path will be empty if we cannot find a path
}
// ----------------------------------------------------------------------------------
// 16.3
// ----------------------------------------------------------------------------------
struct vertex {
    int d = -1;
    vector<vertex*> adj;
};

struct graph {
    vector<vertex*> v_list;
};

bool _BFSPartitionStartingAt(vertex& v) {
    queue<vertex*> q;
    q.emplace(&v);

    while (!q.empty()) {
        for (vertex *& a : q.front()->adj) {
            if (a->d == -1) {
                a->d = q.front()->d + 1;
                q.emplace(a);
            }
            else if (a->d == q.front()->d) {
                return false;
            }
        }
        q.pop();
    }
    return true;
}

bool CanPartition(vector<vertex>& graph) {
    for (vertex& v : graph) { // this will cover all including disconnected components
        if (v.d == -1) { // unvisited
            v.d = 0;
            if (!_BFSPartitionStartingAt(v))
                return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------------
// 16.5
// ----------------------------------------------------------------------------------
typedef unordered_map<vertex*, unordered_set<vertex*>> closure;
void DFS(vertex* v, unordered_set<vertex*>& ex) {
    for (auto & n : v->adj) {
        if (ex.find(n) == ex.end()) {
            ex.insert(n);
            DFS(n, ex);
        }
    }
}

closure TransitiveClosure(graph const& g) {
    closure list_e;
    for (auto & v : g.v_list) {
        unordered_set<vertex*> ex;
        DFS(v, ex);
        list_e[v] = ex;
    }
    return list_e;
}

void PrintClosure(closure & c) {
    for (auto & p : c) {
        cout << p.first->d << ": ";
        for (auto & n : p.second) {
            cout << n->d << " ";
        }
        cout << endl;
    }
}

vector<vector<bool>> ConvertToClosureMatrix(graph & g) {
    vector<vector<bool>> am(g.v_list.size(), vector<bool>(g.v_list.size(), false));
    for (auto & v : g.v_list) {
        for (auto & n : v->adj) {
            am[v->d][n->d] = true;
        }
    }
    return am;
}

void PrintClosureGraph(vector<vector<bool>> const& g) {
    
    for (int i = 0; i < g.size(); ++i) {
        for (int j = 0; j < g.size(); j++) {
            if (g[i][j])
                printf("%7d", 1);
            else
                printf("%7d", 0);
        }
        cout << endl;
    }
}

vector<vector<bool>> TransitiveClosureByFloydWarshall(vector<vector<bool>> const& g) {
    vector<vector<bool>> tc(g); // starts out as a copy of the graph
    PrintClosureGraph(tc);
    for (int k = 0; k < g.size(); ++k) {
        for (int s = 0; s < g.size(); ++s) {
            for (int e = 0; e < g.size(); ++e) {
                tc[s][e] = tc[s][e] || (tc[s][k] && tc[k][e]);
            }
        }
    }
    cout << endl;
    PrintClosureGraph(tc);
    return tc;
}

END_NAMESPACE

// -------------------------------------------------------------------------------------------
// KRUSKAL'S ALGORITHM
// -------------------------------------------------------------------------------------------
template<typename T>
struct Edge {
    T a;
    T b;
    int weight = 0;
    Edge(T const& v1, T const& v2, int wgt)
        :a(v1), b(v2), weight(wgt) {}
};

template<typename T>
struct GraphVE {
    vector<T> vertices;
    vector<Edge<T>> edges;
    vector<pair<T, Edge<T>>> adjacent(T u) {
        vector<pair<T, Edge<T>>> adj;
        for (Edge<T> e : edges) {
            if (e.a == u)
                adj.emplace_back(e.b, e);
            else if (e.b == u)
                adj.emplace_back(e.a, e);
        }
        return adj;
    }
};

template<typename T>
void Kruskal(GraphVE<T>& g) {
    vector<Edge<T>> A; // edges of the minimum spanning tree
    union_find<T> s(g.vertices); // make all vertices into their own disjoint set
    
    // sort all the edges by weight increasingly
    sort(begin(g.edges), end(g.edges), [](Edge<T> const& x, Edge<T> const& y) { return x.weight < y.weight; });
    
    // consider all edges in order. For each edge, check for one whose two edges arent in the same set and
    // union them and add them to the MST
    for (Edge<T> const& e : g.edges) {
        T root_1 = s.find(e.a);
        T root_2 = s.find(e.b);
        if (root_1 != root_2) {
            A.emplace_back(e);
            s.join(root_1, root_2);
        }
    }

    // print the edges
    for_each(begin(A), end(A), [](Edge<T> const& e) {
        cout << e.a << " -- " << e.b << "  " << e.weight << endl;
    });
    
}
// -------------------------------------------------------------------------------------------
// PRIM'S ALGORITHM
// -------------------------------------------------------------------------------------------
template <typename T>
void Prims(GraphVE<T>& g) {
    vector<Edge<T>> A; // edges of the minimum spanning tree
    unordered_map<T, T> parent; // parent in a tree sense, where parent is in mst
    unordered_map<T, int> key; 

    for (auto c : g.vertices)
        key[c] = numeric_limits<int>::max();

    // pick the first node as root
    key[g.vertices.front()] = 0;
    list<T> vertices_left(begin(g.vertices), end(g.vertices));

    while (!vertices_left.empty()) { // VlogV + E if using min_heap
        auto it = min_element(begin(vertices_left), end(vertices_left), [&](T a, T b) { return key[a] < key[b]; });
        T curr = *it;
        vertices_left.erase(it); // vertices are uniquely named so we COULD also remove by value;
        
        if (parent.find(curr) != parent.end()) // this edge has a parent in the MST (on frontier) we can add it 
            A.emplace_back(parent[curr], curr, key[curr]);

        // update all the children of the new node that remain in the "wild" (not yet in mst)
        for (auto p : g.adjacent(curr)) {
            if (find(begin(vertices_left), end(vertices_left), p.first) != vertices_left.end()) {
                if (p.second.weight < key[p.first]) {
                    parent[p.first] = curr;
                    key[p.first] = p.second.weight;
                }
            }
        }
    }

    // print the edges
    for_each(begin(A), end(A), [](Edge<T> const& e) {
        cout << e.a << " -- " << e.b << "  " << e.weight << endl;
    });
}

// -------------------------------------------------------------------------------------------
// DJIKSTRA ALGORITHM - SIMILAR TO PRIMS 
// -------------------------------------------------------------------------------------------
template <typename T>
void Dijkstra(GraphVE<T>& g, T const& start) {
    unordered_map<T, T> parent; // parent in a tree sense, where parent is in mst
    unordered_map<T, int> distance; // distance from start for each vertice

    for (auto c : g.vertices)
        distance[c] = numeric_limits<int>::max();

    // start has a distance of 0 from start, obviously
    distance[start] = 0;
    parent[start] = start; // make start parent of itself so we know when we get to the beginning
    list<T> vertices_left(begin(g.vertices), end(g.vertices));

    while (!vertices_left.empty()) { // if using minheap, this would be VlogV + E complexity
        // from all the frontier nodes, get the one with the smallest distance
        auto it = min_element(begin(vertices_left), end(vertices_left), 
            [&](T a, T b) { return distance[a] < distance[b]; });
        T curr = *it;
        vertices_left.erase(it); // vertices are uniquely named so we COULD also remove by value;

        // update all the distance to children of the new node that remain in the "wild" (unvisited)
        for (auto p : g.adjacent(curr)) {
            if (find(begin(vertices_left), end(vertices_left), p.first) != vertices_left.end()) {
                if (distance[curr] + p.second.weight < distance[p.first]) {
                    parent[p.first] = curr;
                    distance[p.first] = distance[curr] + p.second.weight;
                }
            }
        }
    }

    // for each vertice, print the path from start and the distance
    for (auto v : g.vertices) {
        string path_str(1, v);
        auto c = v;
        while (parent[c] != c) {
            path_str = string(1, parent[c]) + " " + path_str;
            c = parent[c];
        }
        cout << path_str << setw(10) << "dist: " << distance[v] << endl;
    }
}

// -------------------------------------------------------------------------------------------
// BELLMAN FORD ALGORITHM - SINGLE SOURCE WITH NEGATIVE WEIGHT CYCLES 
// -------------------------------------------------------------------------------------------
template<typename T>
void BellmanFord(GraphVE<T>& g, T const& start) {
    unordered_map<T, T> parent; // parent in a tree sense, where parent is in mst
    unordered_map<T, int> distance; // distance from start for each vertice

    for (auto c : g.vertices)
        distance[c] = numeric_limits<int>::max();

    // initialize the source
    parent[start] = start;
    distance[start] = 0; 

    // do v-1 edge relaxation cycles
    for (int i = 0; i < g.vertices.size() - 1; ++i) {
        for (Edge<T> const& e : g.edges) {
            if (distance[e.a] != numeric_limits<int>::max()) {
                if (distance[e.a] + e.weight < distance[e.b]) {
                    distance[e.b] = distance[e.a] + e.weight;
                    parent[e.b] = e.a;
                }
            }
        }
    }

    // Edge detection cycle
    for (Edge<T> const& e : g.edges) {
        if (distance[e.a] + e.weight < distance[e.b]) {
            cout << "negative edge cycle detected!" << endl;
            printf("(%c - %c)\n", e.a, e.b);
            return;
        }
    }

    // For each vertice, print the path from start and the distance
    for (auto v : g.vertices) {
        string path_str(1, v);
        auto c = v;
        while (parent[c] != c) {
            path_str = string(1, parent[c]) + " " + path_str;
            c = parent[c];
        }
        cout << path_str << setw(10) << "dist: " << distance[v] << endl;
    }
}

// -------------------------------------------------------------------------------------------
// BELLMAN FORD ALGORITHM - ALL PAIRS SHORTEST PATH PROBLEM USING DP
// -------------------------------------------------------------------------------------------
bool IsInf(int val){
    return val == numeric_limits<int>::max();
}
void PrintGraph(vvi const& graph) {
    cout << "Following matrix shows the shortest distances" << endl;
    cout << "between every pair of vertices" << endl;

    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); j++) {
            if (IsInf(graph[i][j]))
                printf("%7s", "INF");
            else
                printf("%7d", graph[i][j]);
        }
        cout << endl;
    }
}

void FloydWarshall(vvi& graph) {
    //vvi distance(graph.size(), vi(graph[0].size()));

    // initialize the solution matrix same as input graph matrix (Or we can say the 
    // initial value of shortest distances are based on shortest paths without any 
    // intermediate nodes
    vvi distance(graph);

    /* consider every vertice as an intermediate vertex for every pair of vertices*/
    int vertice_count = graph.size();
    for (int k = 0; k < vertice_count; ++k) {
        for (int i = 0; i < vertice_count; ++i) {
            for (int j = 0; j < vertice_count; ++j) {

                /* if vertex k is on the shortest path from i to j */
                if (!IsInf(distance[i][k]) && !IsInf(distance[k][j])) {
                    if (distance[i][k] + distance[k][j] < distance[i][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                    }
                }

            }
        }
    }
    PrintGraph(distance);
}

struct EPIVertex {
    vector<pair<EPIVertex*, double>> edges;
};

struct EPIGraph {
    vector<EPIVertex*> v;
};

namespace epi_15 {
// pair = height, diameter
pair<double, double> ComputeHeightAndDiameter(EPIVertex* root, unordered_set<EPIVertex*>& visited) {
    double child_diameter = numeric_limits<double>::min();
    array<double, 2> height = { { 0.0, 0.0 } }; // store the max two heights. invariant h[0] >= h[1] 
    for (const auto& e : root->edges) {
        // only neccesary because we include undirected edges twice from both directions. In this implementation
        // this algorithm is order of edges. However if we keep only one edge, we can do it in Order of vertices
        // just like the book
        if (visited.find(e.first) != visited.end())
            continue;
        visited.insert(e.first);

        pair<double, double> h_d = ComputeHeightAndDiameter(e.first, visited);
        if (h_d.first + e.second > height[0]) {
            height[1] = height[0];
            height[0] = h_d.first + e.second;
        }
        else if (h_d.first + e.second > height[1]) {
            height[1] = h_d.first + e.second;
        }
        child_diameter = max(child_diameter, h_d.second);
    }
    // max of the largest child diameter, or a path with the largest two weighted heights that goes through
    // the root;
    return{ height[0], max(child_diameter, height[0] + height[1]) };
}

double ComputerDiameter(EPIGraph const& g) {
    unordered_set<EPIVertex*> visited;
    return ComputeHeightAndDiameter(g.v[0], visited).second;
}

}

namespace epi_15 {
//
// epi 15.26 
//
struct Symbol {
    char c;
    double prob;
};

struct HNode {
    Symbol* s;
    string code;
    double prob;
    shared_ptr<HNode> left, right;
    HNode(Symbol* s, string& code, double prob, shared_ptr<HNode> l, shared_ptr<HNode> r)
        :s(s), code(code), prob(prob), left(l), right(r) {}

};

void AssignHuffmanCodes(shared_ptr<HNode>& root, string const& code) {
    if (!root) return;

    if (root->s) { // root is a leaf;
        root->code = code;
    }
    else {
        AssignHuffmanCodes(root->left, code + '0');
        AssignHuffmanCodes(root->right, code + '1');
    }
}

void PrintHuffmanCodes(shared_ptr<HNode>& root) {
    if (!root) return;
    if (!root->left && !root->right)
        cout << root->s->c << ": " << root->code << endl;
    else {
        PrintHuffmanCodes(root->left);
        PrintHuffmanCodes(root->right);
    }
}

void HuffmanEncode(vector<Symbol>& symbols) {
    auto greater = [](shared_ptr<HNode> const& lhs, shared_ptr<HNode> const& rhs)
        { return lhs->prob > rhs->prob; };
    priority_queue<shared_ptr<HNode>, vector<shared_ptr<HNode>>,decltype(greater)> min_heap(greater);
        
    for (auto & s : symbols)
        min_heap.emplace(make_shared<HNode>(&s, string(), s.prob, nullptr, nullptr));

    while (min_heap.size() > 1) {
        shared_ptr<HNode> l = min_heap.top(); min_heap.pop();
        shared_ptr<HNode> r = min_heap.top(); min_heap.pop();
        min_heap.emplace(make_shared<HNode>(nullptr, string(), l->prob + r->prob, l, r));
    }
    AssignHuffmanCodes(min_heap.top(), string());
    PrintHuffmanCodes(min_heap.top());
}

}