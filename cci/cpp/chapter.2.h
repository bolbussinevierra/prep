//
// helpers
//
#include <iostream>
#include <memory>
#include <map>
using namespace std;

#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])

struct Node
{
    int data;
    Node* next;
    Node* previous;
    Node(int data):data(data), next(NULL), previous(NULL) {}
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
    Node *head = NULL;
    Node *current = NULL;
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
//
// helpers
//

//
// 2.1
//
void RemoveDuplicates(Node *head){
    Node* current = head;
    map<int, int> seen;
    Node *previous = NULL;
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
    Node *runner = NULL;
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