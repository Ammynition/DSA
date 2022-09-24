#include <iostream>
#include <vector>
#include <unordered_set>

template<typename T> struct treeNode{
    T data;
    treeNode * left;
    treeNode * right;
};

template <typename T> class BST {
    public:
        int numNodes;
        treeNode<T> * head;
        BST();
        void add(T data);
        void print();
        void remove(T data);
        treeNode<T> * find(T data);

};

template <typename T>
BST<T>::BST(){
    head = nullptr;
    numNodes = 0;
}

template <typename T>
void BST<T>::add(T data){

   treeNode<T> * newNode = new treeNode<T>;
   newNode->data = data;
   numNodes++;
   if(head == nullptr){
       head = newNode;
   }
   else{
       treeNode<T> * current = head;
       while(current!=nullptr){
            if(data <= current->data){
                if(current->left == nullptr){
                    current->left = newNode;
                    break;
                }
                else{
                    current = current->left;
                }
            }
            else{
                if(current->right == nullptr){
                    current->right = newNode;
                    break;
                }
                else{
                    current = current->right;
                }
            }
       }
   }
}


template <typename T>
void BST<T>::print(){
    treeNode<T> * current = head;
    //keep track of tabs with size of parents
    std::vector<treeNode<T> *> parents;
    std::unordered_set<treeNode<T> *> printed;
    while(current!=nullptr){
        //check right
        //if right, push to parents
        //if right is null, check if we've printed ourselves
        //if we haven't, then print, add to printed set,
        //then check left, if it's there add our selves to parent set 
        //set ourselves to left
        //then and also if there's no left
        //pop back the parent
        if(current->right!=nullptr && printed.find(current->right) == printed.end()){
            parents.push_back(current);
            current = current->right;
        }
        else{
            if(printed.find(current) == printed.end()){
                for(int i =0; i<parents.size(); i++){
                    std::cout << "\t";
                }
                std::cout << current->data << std::endl;
                printed.insert(current);
            }
            if(current->left!=nullptr && printed.find(current->left) == printed.end()){
                parents.push_back(current);
                current = current->left;
            }
            else{
                if(parents.empty()){
                    break;
                }
                current = parents.back();
                parents.pop_back();
            }

        }
    }
}
