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

namespace epi_16 {
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

}

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
};

template<typename T>
void Kruskal(GraphVE<T>& g) {
    vector<Edge<T>> A; // edges of the minimum spanning tree
    union_find<T> s(g.vertices); // make all vertices into their own disjoint set
    
    // sort all the edges by weight increasingly
    sort(g.edges.begin(), g.edges.end(), [](Edge<T> const& x, Edge<T> const& y) { return x.weight < y.weight; });
    
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

template <typename T>
void Prims(GraphVE<T>& g) {

}