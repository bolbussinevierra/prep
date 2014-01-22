//
// helpers
//
#include <iostream>
#include <memory>
#include <map>
#include <stack>
#include <assert.h>
#include <vector>
using namespace std;

struct TreeNode {
    int value;
    TreeNode * left;
    TreeNode * right;
    TreeNode(int value):value(value), left(NULL), right(NULL) {}
};

struct LinkedListNode {
    TreeNode* value;
    LinkedListNode * next;
    LinkedListNode(TreeNode* value):value(value), next(NULL){}
};

void PrintList(LinkedListNode* head){
    if(!head) return;

    do{
        printf("%d ", head->value->value); 
        head = head->next;
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
//
HRESULT GetLevelsLinkedLists(TreeNode * root, vector<LinkedListNode*>& result){
    assert(root);
    LinkedListNode* head = new LinkedListNode(root);
    LinkedListNode* tail = head;
    vector<TreeNode*> levelNodes;
    levelNodes.push_back(root);

    while (levelNodes.size() > 0) {
        result.push_back(head);
        
        vector<TreeNode*> parents(levelNodes);
        levelNodes.clear();
        head = NULL;
        tail = NULL;

        for (size_t i = 0; i < parents.size(); i++){
            if (parents[i]->left){
                if (!head) {
                    head = new LinkedListNode(parents[i]->left);
                    tail = head;
                } else {
                    tail->next = new LinkedListNode(parents[i]->left);
                    tail = tail->next;
                }
                levelNodes.push_back(parents[i]->left);
            }
            if (parents[i]->right) {
                if (!head) {
                    head = new LinkedListNode(parents[i]->right);
                    tail = head;
                } else {
                    tail->next = new LinkedListNode(parents[i]->right);
                    tail = tail->next;
                }
                levelNodes.push_back(parents[i]->right);
            }
        }
    }
    return S_OK;
}

//
// 4.5
//
bool _IsBST(TreeNode* root, int& lastValue, bool& lastValueSet){
    if (!root)
        return true;

    if (!_IsBST(root->left, lastValue, lastValueSet))
        return false;

    if (!lastValueSet) {
        lastValueSet = true;
    }
    else if (root->value <= lastValue) {
        return false;
    }
    lastValue = root->value;
    printf("lastSeen = %d ", lastValue); 

    if (!_IsBST(root->right, lastValue, lastValueSet))
        return false;

    return true;
}
bool IsBST(TreeNode* root){
    int lastValue = 0;
    bool lastValueSet = false;
    printf("\n");
    return _IsBST(root, lastValue, lastValueSet);
}

