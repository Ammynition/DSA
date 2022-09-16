#include<priorityQueue.h> 

int main(void){
   
    priorityQueue <int> aqueue;
    aqueue.enqueue(1, 10);
    aqueue.enqueue(2, 12);
    aqueue.enqueue(3, 5);
    aqueue.enqueue(4, 7);
    aqueue.enqueue(5, 13);
    aqueue.printQueue();
    aqueue.updatePriority(1, 1);
    aqueue.updatePriority(3, 20);
    aqueue.printQueue();
    aqueue.dequeue();

    aqueue.printQueue();
    aqueue.dequeue();

    aqueue.printQueue();
    aqueue.dequeue();
    

    aqueue.printQueue();
    aqueue.dequeue();
    
    aqueue.printQueue();
    aqueue.dequeue();
   
    aqueue.printQueue();
    return 0;
}
