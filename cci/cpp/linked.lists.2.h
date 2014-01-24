//
// helpers
//
#include <iostream>
#include <memory>
#include <map>
#include <stack>
#include <assert.h>
using namespace std;

#define AS(array) sizeof(array)/sizeof(array[0]) 

struct Node
{
    int data;
    Node* next;
    Node* previous;
    Node(int data):data(data), next(nullptr), previous(nullptr) {}
};

void PrintList(Node* head){
    if(!head) return;

    do{
        printf("%d ", head->data); 
        head = head->next;
    }
    while(head);
    printf("%\n");
}

Node* MakeList(int data[], int n)
{
    Node *head = nullptr;
    Node *current = nullptr;
    for (int i = 0; i < n; ++i)
    {
        Node*n = new Node(data[i]);
        if(!head) {
            head = n;
            current = head;
        }
        else{
            current->next = n;
            current = current->next;
        }
    }
    return head;
}

void MakeCycleAt(Node* head, int at){
    Node* cycle = head;
    Node* end = head;

    int pos = 0;
    while (head->next) {
        if (pos == at) {
            cycle = head;
        }
        pos++;
        head = head->next;
    }
    end = head;

    // make the cycle
    end->next = cycle;
    printf("Made cycle with cycle.start.data = %d\n", end->next->data);
}
//
// helpers
//

//
// 2.1
//
void RemoveDuplicates(Node *head){
    Node* current = head;
    map<int, int> seen;
    Node *previous = nullptr;
    typedef pair<int, int> Int_Pair;

    while (current){
        if (seen.end() != seen.find(current->data)){
            auto_ptr<Node> temp(current);
            previous->next = current->next;
            current = current->next;
        }else{
            seen.insert(Int_Pair(current->data, 1));
            previous = current;
            current = current->next;
        }
    }
}

void  RemoveDuplicatesNoBuffer(Node *head){
    Node *current = head;
    Node *runner = nullptr;
    while (current){
        runner = current->next;
        while (runner){
            if (current->data == runner->data){
                auto_ptr<Node> temp(runner);
                current->next = runner->next;
                runner = runner->next;
            }else{
                runner = runner->next;
            }
        }
        current = current->next;
    }
}
//
// 2.2
//
Node* GetKthToLast(Node* head, int k){
    if (!head || (k <= 0)) return nullptr;

    Node* runner = head;
    for(int i = 0; i < k - 1; ++i){
        if (!runner) return nullptr;
        runner = runner->next;
    }
    if (!runner) return nullptr;

    while (runner->next){
        head = head->next;
        runner = runner->next;
    }
    return head;
}
//
// 2.4
//
Node* PartitionList(Node* head, int x) {
    if (!head) return nullptr;

    Node* beforeList = nullptr;
    Node* afterList = nullptr;

    while (head) {
        // free the node at the front of the list
        Node * next = head->next;
        head->next = nullptr;

        if (head->data < x) {
            head->next = beforeList;
            beforeList = head;
        } else {
            head->next = afterList;
            afterList = head;
        }
        head = next;
    }

    if (!beforeList) return afterList;

    Node* newHead = beforeList;
    while (beforeList->next) {
        beforeList = beforeList->next;
    }

    beforeList->next = afterList;
    return newHead;
}
//
// 2. 6
//
Node* FindCycleStart(Node* head) {
    if (!head) return nullptr;
    Node* slow = head;
    Node* fast = head;
    do {
        slow = slow->next;
        if (!fast->next) return nullptr;
        fast = fast->next->next;
    } while (slow && fast && (fast != slow));

    if (!fast) return nullptr;
    
    slow = head;    // reassign back to the front of the list
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    printf("Found cycle with data = %d\n", slow->data);
    return slow;
}

//
// 2.7
//
bool IsPalindrome(Node* head){

    assert(head);

    Node *slow = head;
    Node *fast = head;
    stack<int> s;

    while (fast && fast->next) {
        s.push(slow->data);
        fast = fast->next->next;
        slow = slow->next;
    }

    // if list is odd, fast will be valid and slow is pointing to the middle
    // (or only) element. We need to ask it to skip
    if (fast) slow = slow->next;
    
    while (!s.empty() && slow) {
        int data = s.top();
        if (data != slow->data) {
           break;
        }
        s.pop();
        slow = slow->next;
    }
    
    bool result = s.empty() && (slow == nullptr);
    printf("is%spalindrome!", result ? " " : " not ");
    return result;
}
