#include<iostream>

using namespace std;

struct linkedlist_node {
    struct linkedlist_node *next;
    int data;
};

struct linkedlist {
    struct linkedlist_node * head;
    struct linkedlist_node * tail;
};

void printList(linkedlist * l){

    if(l->head==NULL){
        cout << "nothing in list" << endl;
    }
    struct linkedlist_node * temp = l->head;
    while(temp!= NULL){

        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "end of list" << endl;
}

void AddNode(linkedlist * l, int data){
    struct linkedlist_node * temp = new linkedlist_node;
    temp->data = data;
    temp->next = NULL;

    if(l->head == NULL){
        l->head = temp;
    }
    else{
        l->tail->next = temp;
    }    
    l->tail = temp;
}

int main(void)
{
    struct linkedlist l;
    l.head = NULL;
    l.tail = NULL;

    AddNode(&l, 5);
    AddNode(&l, 2);
    AddNode(&l, 11);

    printList(&l);
}
