#include<iostream>
#include<set>
#include<priorityQueue.h>
#include<unordered_map>
#include<unordered_set>
using namespace std;

struct graph_node {
    struct graph_node *next;
    int data;
    int group;
    struct graph_edge * edge;
};

struct graph_t {
    struct graph_node * head;
    struct graph_node * tail;
};

struct graph_edge {
    int weight;
    struct graph_node * neighbor;
    struct graph_edge * next;
};

void printGraph(graph_t * l){

    if(l->head==NULL){
        cout << "nothing in list" << endl;
    }
    struct graph_node * node = l->head;
    while(node!= NULL){

        cout <<"Data: " << node->data << " " << endl;
        struct graph_edge * nodeEdge = node->edge;
        while(nodeEdge!=NULL){
            cout << "    Edge: " << nodeEdge->neighbor->data;
            cout << "Weight: " << nodeEdge->weight << endl;
            nodeEdge = nodeEdge->next;
        }
        node = node->next;
    }
    cout << "end of list" << endl;
}

void AddNode(graph_t * l, int data){
    struct graph_node * temp = new graph_node;
    temp->data = data;
    temp->next = NULL;
    temp->group = 0;
    if(l->head == NULL){
        l->head = temp;
    }
    else{
        l->tail->next = temp;
    }    
    l->tail = temp;
   
}

void AddEdge(graph_t * l, int dataFrom, int dataTo,  int weight){

    //traverse to 3, add an edge traverse until we hit 2, point the path to 2, 
    //point it to next
    struct graph_edge * newEdge = new graph_edge;
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
    newEdge->neighbor = toPath;
    
}

void HasPath(graph_t *l, int pathFrom, int pathTo){
    bool canTravel = false;
    //can we go from 7 to 3? no
    //can we go from 3 to 7? yes
    //2 to 3? no
    //traverse through linkededge path 
    //struct graph_edge * edge = NULL;

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
       struct graph_edge * edges = (*it)->edge;
       while (edges!=NULL) {
           if(visited.find(edges->neighbor)==visited.end()){
                visited.insert(edges->neighbor);
                upnext.insert(edges->neighbor);
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

graph_node * findNode(graph_t * graph, int data){
    graph_node * current = graph->head;
    while(current!=nullptr){
        if(current->data == data){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

std::vector<int> FindPath(graph_t * graph, int start, int end){

    //two unordered maps, dist & prev
    std::unordered_map<int, int> distance;
    distance[start] = 0;
    std::unordered_map<int, int> previous;
    priorityQueue<int> pathfinder;
    pathfinder.enqueue(start, 0);
    //for each node in the graph, todo: check for circular graph?
    bool found = false;
    while(!pathfinder.empty() && !found){
        graph_node * currentnode = findNode(graph, pathfinder.dequeue());
        graph_edge * currentedge = currentnode->edge;
        while(currentedge != nullptr){
            graph_node * neighbor = currentedge->neighbor;
            
            int alt = distance[currentnode->data] + currentedge->weight;
            //check if it exists in our map, if it is, is it better?
            if(distance.find(neighbor->data) == distance.end() || distance[neighbor->data] > alt ){
                distance[neighbor->data] = alt;
                previous[neighbor->data] = currentnode->data;
                pathfinder.enqueue(neighbor->data, alt);
            }
            currentedge = currentedge->next;
            
            if(neighbor->data == end){
                found = true;
                break;
            }
        }
    }
    std::vector<int> path;
    int end_node = end;
    
    while(previous.find(end_node) != previous.end()){
        path.push_back(end_node);
        end_node = previous[end_node];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}
bool disjointSet(graph_t * graph){
    //need a vector for each seperate graph
    bool listofgraphs = true;
    std::unordered_map<int, int> redirects;
    std::unordered_map<int, std::unordered_set< graph_node *> > visitedGroups;
    graph_node * nodeTrav = graph->head;
    int group_num = 1;
    while(nodeTrav!=nullptr){
        //check node group#, if it's not 0, it's already in our set
        if(nodeTrav->group == 0){
            // hasn't been added to visited before!
            //add to visited
            visitedGroups[group_num].insert(nodeTrav);
            //change group number for specific node
            nodeTrav->group = group_num;
            //check for neighbors
            //graph_edge NeighborCheck = nodeTrav->edge;
            //find visited
            //if it has a group number, it's been visited
            //check group number of graph node 
            std::unordered_set<graph_node *> upNext;
            std::unordered_set<graph_node *>::iterator it;
            upNext.insert(nodeTrav);
            while(upNext.size() != 0){
                it = upNext.begin();
                graph_edge * NeighborCheck = (*it)->edge;
                while(NeighborCheck !=nullptr){
                    if(NeighborCheck->neighbor->group == 0){
                        //not in our visited groups, add it to the same group number
                        visitedGroups[group_num].insert(NeighborCheck->neighbor);
                        upNext.insert(NeighborCheck->neighbor);
                    }
                    else{
                        if(redirects.find(group_num) == redirects.end()){
                            redirects[group_num] = NeighborCheck->neighbor->group; //if it's not mapped to anything, we're home free
                        }
                       // if(redirects.find(NeighborCheck->Neighbor->group) != redirects.end() && ){
                       //     //hold a temporary variable
                       //     int old_group_mapping = redirects[group_num];
                       //     redirects[old_group_mapping] = NeighborCheck->Neighbor->group;
                       //     redirects[group_num] = NeighborCheck->Neighbor->group;
                       // } 
                        else{
                            //check to see what it's mapped to currently, and change it 
                            //3 > 1
                            //3 -> 1
                            int current_group_mapping = redirects[group_num];
                            while(redirects.find(current_group_mapping) != redirects.end()){

                                int next_group_mapping = redirects[current_group_mapping];
                                redirects[next_group_mapping] = current_group_mapping;
                                current_group_mapping = next_group_mapping;
                            }

                        }
                    }
                    NeighborCheck = NeighborCheck->next;
                }
                upNext.erase(*it);
             }
        }   

        nodeTrav = nodeTrav->next;
    }
    for(auto i:redirects){
        std::cout << i.first << " -> " << i.second << std::endl;
    }
    return listofgraphs;

}

int main(void)
{
    struct graph_t l;
    l.head = NULL;
    l.tail = NULL;
    
    AddNode(&l, 12);
    AddNode(&l, 5);
    AddNode(&l, 7);
    AddNode(&l, 45);
    AddNode(&l, 16);
    AddNode(&l, 22);

    AddEdge(&l, 12, 5, 4);
    AddEdge(&l, 5, 7, 7);
    AddEdge(&l, 5, 45, 8);
    AddEdge(&l, 7, 12, 3);
    AddEdge(&l, 16, 22, 10);
    /*AddNode(&l, 1);
    AddNode(&l, 2);
    AddNode(&l, 3);
    AddNode(&l, 4);
    AddNode(&l, 5);
    AddEdge(&l, 1, 2, 5);
    AddEdge(&l, 1, 3, 1);
    AddEdge(&l, 3, 1, 1);
    AddEdge(&l, 2, 3, 1);
    AddEdge(&l, 3, 5, 1);

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
    printGraph(&l);
    HasPath(&l, 7, 3);
    HasPath(&l, 3, 7);
    HasPath(&l, 2, 3);
    HasPath(&l, 3, 11);
    HasPath(&l, 11, 2);
    HasPath(&l, 11, 3);
    HasPath(&l, 3, 15);
  */

    bool fred = disjointSet(&l);
  // std::vector<int> path = FindPath(&l, 1, 4);
  //  for(int it:path){
  //     std::cout << it << std::endl;
  //  }

    return 0;
}
