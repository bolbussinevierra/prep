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
    TreeNode(int value):value(value), left(NULL), right(NULL) {}
};

struct LinkedListNode {
    TreeNode* value;
    shared_ptr<LinkedListNode> next;
    LinkedListNode(TreeNode* value):value(value), next(NULL){}
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
        return NULL;
    }
    int mid = (start + end) / 2;
    TreeNode* n = new TreeNode(items[mid]);
    n->left = _MakeOptimalBST(items, start, mid-1);
    n->right = _MakeOptimalBST(items, mid+1, end);
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
                        int level) {
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
        head = NULL;
        tail = NULL;

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

