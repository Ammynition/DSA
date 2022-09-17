#include<iostream>
#include<set>
#include<priorityQueue.h>
#include<unordered_map>
using namespace std;

struct graph_node {
    struct graph_node *next;
    int data;
    struct linkedEdge * edge;
};

struct graph {
    struct graph_node * head;
    struct graph_node * tail;
};

struct linkedEdge {
    int weight;
    struct graph_node * path;
    struct linkedEdge * next;
};

void printList(graph * l){

    if(l->head==NULL){
        cout << "nothing in list" << endl;
    }
    struct graph_node * node = l->head;
    while(node!= NULL){

        cout <<"Data: " << node->data << " " << endl;
        struct linkedEdge * nodeEdge = node->edge;
        while(nodeEdge!=NULL){
            cout << "    Edge: " << nodeEdge->path->data;
            cout << "Weight: " << nodeEdge->weight << endl;
            nodeEdge = nodeEdge->next;
        }
        node = node->next;
    }
    cout << "end of list" << endl;
}

void AddNode(graph * l, int data){
    struct graph_node * temp = new graph_node;
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

void AddEdge(graph * l, int dataFrom, int dataTo,  int weight){

    //traverse to 3, add an edge traverse until we hit 2, point the path to 2, 
    //point it to next
    struct linkedEdge * newEdge = new linkedEdge;
    newEdge->weight = weight;
    newEdge->next = NULL;
    struct graph_node * nodeTrav = l->head;
    struct graph_node * toPath = NULL;
    struct graph_node * fromPath = NULL;
    while(nodeTrav != NULL ){
        if(nodeTrav->data == dataFrom){
            fromPath = nodeTrav;       
        }
        if(nodeTrav->data == dataTo){
            toPath = nodeTrav;
        }
        if(toPath != NULL && fromPath!=NULL){
            break;
        }
        nodeTrav = nodeTrav->next;
    }
    newEdge->next = fromPath->edge;
    fromPath->edge=newEdge;
    newEdge->path = toPath;
    
}

void HasPath(graph *l, int pathFrom, int pathTo){
    bool canTravel = false;
    //can we go from 7 to 3? no
    //can we go from 3 to 7? yes
    //2 to 3? no
    //traverse through linkededge path 
    //struct linkedEdge * edge = NULL;

   set<struct graph_node * > upnext;
   set<struct graph_node * > visited;
   set<struct graph_node * >::iterator it;
   struct graph_node * fromNode = l->head;
   while(fromNode != NULL){
       if(fromNode->data == pathFrom){
           break;
       }
       fromNode = fromNode->next;
   }
   upnext.insert(fromNode);
   visited.insert(fromNode);
   while(upnext.size() != 0){
       it = upnext.begin();
       if((*it)->data == pathTo){
            canTravel = true;
            break;
       }
       //check if in visited, if not, add to upnext
       struct linkedEdge * edges = (*it)->edge;
       while (edges!=NULL) {
           if(visited.find(edges->path)==visited.end()){
                visited.insert(edges->path);
                upnext.insert(edges->path);
           }
           edges=edges->next;
       }
       upnext.erase((*it));
   }
   //up next contains the edges we are going to visit
   //visit contains the edges we've already visited
   //if we've already visited it, don't go again

    


    cout << "can we travel from " << pathFrom << "to " << pathTo << "? " << canTravel << endl;
}

graph_node * findNode(graph * graph, int data){

    graph->head

}

std::vector<int> FindPath(graph * graph, int start, int end){

    graph * head = graph;
    //two unordered maps, dist & prev
    std::unordered_map<int, int> distance;
    distance[start] = 0;
    std::unordered_map<int, int> previous;
    priorityQueue<int> pathfinder = new priorityQueue<int>;
    pathfinder.enqueue(start, 0);
    //for each node in the graph, todo: check for circular graph?
    
    while(!pathfinder.empty()){
       int currentnode = pathfinder.dequeue();
       
       {

       }
        
    }


}


int main(void)
{
    struct graph l;
    l.head = NULL;
    l.tail = NULL;

    AddNode(&l, 3);
    AddNode(&l, 11);
    AddNode(&l, 2);
    AddNode(&l, 15);
    AddNode(&l, 7);
    AddEdge(&l, 2, 7, 5);
    AddEdge(&l, 3, 2, 4);
    AddEdge(&l, 7, 15, 1);
    AddEdge(&l, 11, 2, 4);
    AddEdge(&l, 2, 11, 7);
    printList(&l);
    HasPath(&l, 7, 3);
    HasPath(&l, 3, 7);
    HasPath(&l, 2, 3);
    HasPath(&l, 3, 11);
    HasPath(&l, 11, 2);
    HasPath(&l, 11, 3);
    HasPath(&l, 3, 15);
    return 0;
}
