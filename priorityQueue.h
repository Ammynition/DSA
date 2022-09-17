#include<vector>
#include <iostream> 
#include <algorithm>
#include<unordered_map>
template<typename T> struct queProperties{
    T data;
    int priority;
};

template<typename T> class priorityQueue {
    public:
        std::vector <queProperties<T>> que;
        std::unordered_map <T, size_t> index_map;
        priorityQueue(){
        }
        void swap(size_t index, size_t index2){
        
           std::swap(que[index].priority, que[index2].priority);
           std::swap(que[index].data, que[index2].data);
           index_map[que[index2].data] = index2; 
           index_map[que[index].data] = index; 
    
        }
        void enqueue(T d, int p){
            queProperties <T> prop;
            prop.data = d;
            prop.priority = p;
            que.push_back(prop);
            size_t index = que.size()-1;
            index_map[d] = index;
            upHeapify(index);
        }

        T dequeue(){
        
            T head = que[0].data;
            size_t last_index = que.size()-1;
            que[0].data = que[last_index].data;
            que[0].priority = que[last_index].priority;
            que.pop_back();
            size_t index = 0;    
            downHeapify(index);
            index_map.erase(head);
            return head;

        }
 

       

        void printQueue(){
            for(auto it:que){
                std::cout << it.priority << " ";
            }

            std::cout << "\n" ;
        }
        
        bool empty(){
            return que.empty();
        }

        void updatePriority(T data, int priority){
            size_t index = index_map[data];
            
            if(index == que.size()){
                enqueue(data, priority);
                return;
            }
            //if its a higher priority down heapify, lower up heapify
            if(que[index].priority > priority){
                que[index].priority = priority;
                upHeapify(index);
            }
            else{
                que[index].priority = priority;
                downHeapify(index);
            }
        }


        void downHeapify(size_t index){


            size_t last_index = que.size()-1;
            while(true){
                size_t RightIdx = 2*index + 2;
                size_t LeftIdx = 2*index  + 1;
                if(RightIdx > last_index && LeftIdx > last_index){
                    break;
                }
                else if(RightIdx > last_index && que[index].priority > que[LeftIdx].priority){
                   swap(index, LeftIdx);
                   index = LeftIdx;
                }
               
                else if(LeftIdx > last_index && que[index].priority > que[RightIdx].priority){
                   swap(index, RightIdx);
                   index = RightIdx;
                }              
                else if(que[index].priority > que[RightIdx].priority && que[RightIdx].priority <= que[LeftIdx].priority ){
                   swap(index, RightIdx);
                   index = RightIdx;
                }

                else if(que[index].priority > que[LeftIdx].priority && que[LeftIdx].priority <= que[RightIdx].priority ){
                   swap(index, LeftIdx);
                   index = LeftIdx;
                }
                else{
                    break;
                }
            }
        }

        void upHeapify(size_t index){

            size_t parent_index = (index-1)/2;
            while(index!= 0){
                if(que[parent_index].priority > que[index].priority){
                    swap(parent_index, index);
                    index = parent_index;
                    parent_index = (index-1)/2;
                }
                else{
                    break;
                }
            }
        }


};

