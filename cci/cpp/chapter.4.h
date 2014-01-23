//
// helpers
//
#include <iostream>
#include <memory>
#include <map>
#include <stack>
#include <assert.h>
#include <vector>
#include <limits>
using namespace std;

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
    TreeNode* n = new TreeNode(items[mid]);
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
    TreeNode * s = InOrderSuccessor(root);
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

#if 0
//
// DEPRECATED BELOW HERE
//
bool _IsBST_NotGoodEnough(TreeNode* root, int& lastValue, bool& lastValueSet){
    if (!root)
        return true;

    if (!_IsBST_NotGoodEnough(root->left, lastValue, lastValueSet))
        return false;

    if (!lastValueSet) {
        lastValueSet = true;
    }
    else if (root->value <= lastValue) {
        return false;
    }
    lastValue = root->value;
    printf("lastSeen = %d ", lastValue); 

    if (!_IsBST_NotGoodEnough(root->right, lastValue, lastValueSet))
        return false;

    return true;
}
bool IsBST_NotGoodEnough(TreeNode* root){
    int lastValue = 0;
    bool lastValueSet = false;
    printf("\n");
    return _IsBST_NotGoodEnough(root, lastValue, lastValueSet);
}
#endif
