#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* next;
};

void Display(struct Node *p){
    if(p!=NULL){
        cout << p->data << endl;
        Display(p->next);
    }
}

int Count(struct Node *p){
    int c = 0;
    while (p!=0){
        c++;
        p = p->next;
    }
    return c;
}

int SumList(struct Node *p){
    int s = 0;
    while(p!=0){
        s += p->data;
        p = p->next;
    }
    return s;
}

int findmax(struct Node *p){
    int maxNum = INT32_MIN;
    while(p) {
        if(p->data > maxNum) {
            maxNum=p->data;
        }
        p = p->next;
    }
    return maxNum;
}

Node* searchNode(Node *p, int key){
    while(p!=0){
        if(key == p->data) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}

// insert new element
void insertNode(struct Node *p, int index, int x){
    struct Node *t;

    if(index < 0 || index > Count(p)){
        cout << "invalid index..." << endl;
        return;
    }

    t = new Node;
    t->data = x;
    t->next = nullptr;

    if(index==0){
        t->next=p;
        p = t;
    }
    else{
        for(int i=0; i<index-1;i++){
            p=p->next;
        }
        t->next=p->next;
        p->next = t;
    }
}

int main()
{
    int A[] = {3, 5, 7, 10, 15};

    Node *head = new Node;
    Node *temp;
    Node *last;

    head->data = A[0];
    head->next = nullptr;
    last = head;

    for(int i=1; i<5; i++){
        temp = new Node;
        temp->data = A[i];
        temp->next = nullptr;

        last->next = temp;
        last = temp;
    }

    Node *p = head;
    Display(p);

//    cout << "The number of the nodes in the list is " << Count(p) << endl;
//    cout << "The sum of the list is " << SumList(p) << endl;
//    cout << "The max number of the list is " << findmax(p) << endl;

    insertNode(head,0,10);
    Display(p);


//    while(p!=nullptr) {
//        cout << p->data << endl;
//        p = p->next;
//    }
    return 0;
}
