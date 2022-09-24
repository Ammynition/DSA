#include "bst.h"
#include <vector>
#include <set>
BST::BST(){
    head = nullptr;
    numNodes = 0;
}

void BST::add(T data){

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

/*
10┐
  │     9
  └ 8
            7
        6 */
void BST::print(){
    treeNode<T> * current = head;
    //keep track of tabs with size of parents
    std::vector<treeNode<T> *> parents;
    std::set<treeNode<T> *> printed;
    while(current!=nullptr){
        //check right
        //if right, push to parents
        //if right is null, check if we've printed ourselves
        //if we haven't, then print, add to printed set,
        //then check left, if it's there add our selves to parent set 
        //set ourselves to left
        //then and also if there's no left
        //pop back the parent
        if(current->right!=nullptr && !printed.contains(current->right)){
            parents.push_back(current);
            current = current->right;
        }
        else{
            if(!printed.contains(current)){
                for(auto i:parents.size()){
                    std:: cout << "\t";
                }
                std::cout << current->data << std::endl;
                printed.insert(current);
            }
            if(current->left!=nullptr && !printed.contains(current->left)){
                parents.push_back(current);
                current = current->left;
            }
            else{
                if(parents.empty()){
                    break;
                }
                current = parents.pop_back();
            }

        }
    }

}


