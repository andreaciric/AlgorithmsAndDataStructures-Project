#pragma once
#include <iostream>
#include <stack>
using namespace std;

struct Edge {
     int otherEdge;
     int price;
     bool road;
};

struct nlp {
     int node;
     int level;
     int price;
};

class Graph {

public:

     int* indices;
     Edge* edges;
     int node_num;
     int edge_num;

     Graph(int size) {

          node_num = size;
          edge_num = 0;
          indices = new int[node_num + 1];
          for (int i = 0; i < node_num + 1; i++) indices[i] = 0;
          edges = NULL;
          cout << "Uspesno je pozvan konstruktor!" << endl;
     }

     ~Graph() {

          delete indices;
          delete edges;
          cout << "Graf je uspesno obrisan!" << endl;
     }

     void addNode();
     void deleteNode(int node);
     void addEdge(int a, int b, int p, int type);
     void deleteEdge(int a, int b);
     void printGraph();

     int primsAlgorithm();
     void minRoutes(int station);
     void minPath(int a, int b);
};

bool visitedAll(bool* vis, int num) { 
     //checks if all nodes were visited
     
     for (int i = 0; i < num; i++)
          if (!vis[i]) return false;
     return true;
}

bool visitedNode(int* vis, int num, int a) {
     //checks if particular node was visited
     
     for (int i = 0; i < num; i++)
          if (vis[i] == a) return true;
     return false;
}

void Graph::addNode() {
     //adds one node 

     node_num++;
     int* temp = new int[node_num + 1];
     for (int i = 0; i < node_num; i++) temp[i] = indices[i];
     temp[node_num] = temp[node_num - 1];
     delete indices;
     indices = temp;
}

void Graph::deleteNode(int node) {
     // deletes the node you want and all edges connected
     // int node -> index of a node you want to delete

     if (node < 0 || node >= node_num) {
          cout << "Cvor ne postoji" << endl;
          return;
     }

     int i1 = indices[node];
     int i2 = indices[node + 1];
     Edge* temparr = new Edge[edge_num * 2];
     int i3 = edge_num * 2;

     for (int i = 0; i < i3; i++)
          temparr[i] = edges[i];

     //deletes all edges connected to the node being deleted
     for (int i = i1; i < i2; i++) {
          this->deleteEdge(node, temparr[i].otherEdge); 
     }

     node_num--;
     //decreases indices in edge array bc indices of nodes after this one change
     for (int i = 0; i < edge_num * 2; i++)
          if (edges[i].otherEdge > node) edges[i].otherEdge--;

     //last edge deleted case
     if (node_num == 0) {
          delete indices;
          indices = NULL;
          return;
     }

     //moves nodes that are after the deleted one
     int* temp = new int[node_num + 1];
     for (int i = 0; i <= node_num; i++) {
          if (i < node) temp[i] = indices[i];
          else temp[i] = indices[i + 1];
     }

     delete indices;
     indices = temp;
     cout << "Uspesno je izbrisan cvor" << endl;
}

void Graph::addEdge(int a, int b, int p, int type) {
     //adds new adge with defined values
     // int a, b -> nodes in between which you want to add the edge
     // int p -> price of the edge
     // int type -> if real road exists it's 1 or if there could be road but not yet it's 0

     //checks if type is correct
     if (type < 0 || type > 1) {
          cout << "Tip puta nije korektno unet" << endl;
          return;
     }
     //checks if price is correct
     if (p <= 0) {
          cout << "Unesite validnu cenu (price > 0)" << endl;
          return;
     }
     //checks if nodes exist
     if (a < 0 || a >= node_num || b < 0 || b >= node_num) {
          cout << "Cvorovi ne postoje!" << endl;
          return;
     }
     //checks if nodes are different
     if (a == b) {
          cout << "Cvorovi su isti, moraju biti razliciti" << endl;
          return;
     }
     //sort a and b
     if (a > b) {
          int temp = a;
          a = b;
          b = temp;
     }
     //checks if edge already exists
     bool exists = false;
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i].otherEdge == b) exists = true;
     if (exists) {
          cout << "Grana vec postoji" << endl;
          return;
     }

     edge_num++;
     Edge* temp = new Edge[edge_num * 2];
     if (edge_num == 1) {                              //if there is only two nodes you only add this edge 
          temp[0].otherEdge = b;
          temp[1].otherEdge = a;
          temp[0].price = temp[1].price = p;
          temp[0].road = temp[1].road = type;
     }
     else {
          int i = 0;
          //copy all values in edges before first node in indices
          while (i < a) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j] = edges[j];
               i++;
          }
          //add values to edges in the place of first node in indices
          bool added = false;
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < b) temp[j] = edges[j];
               else {
                    if (!added) {
                         added = true;
                         temp[j].otherEdge = b;
                         temp[j].price = p;
                         temp[j].road = type;
                    }
                    temp[j + 1] = edges[j];
               }
          }
          if (!added) {
               temp[indices[i + 1]].otherEdge = b;
               temp[indices[i + 1]].price = p;
               temp[indices[i + 1]].road = type;
          }
          i++;
          //copy all values in edges between nodes a and b to a one place later bc we added one value earlier
          while (i < b) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j + 1] = edges[j];
               i++;
          }
          //add values to edges in the place of second node in indices
          added = false;
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < a) temp[j + 1] = edges[j];
               else {
                    if (!added) {
                         added = true;
                         temp[j + 1].otherEdge = a;
                         temp[j + 1].price = p;
                         temp[j + 1].road = type;
                    }
                    temp[j + 2] = edges[j];
               }
          }
          if (!added) {
               temp[indices[i + 1] + 1].otherEdge = a;
               temp[indices[i + 1] + 1].price = p;
               temp[indices[i + 1] + 1].road = type;
          }
          i++;
          //copy all values in edges after second node to a two places later bc we added two values earlier
          while (i < node_num) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j + 2] = edges[j];
               i++;
          }
     }
     //changes values (addresses of other edges in edges array) in indices
     for (int i = 0; i <= node_num; i++) {
          if (i > a && i <= b) indices[i]++;
          if (i > b) indices[i] += 2;
     }
     delete edges;
     edges = temp;
}

void Graph::deleteEdge(int a, int b) {
     //deletes the edge you want
     // int a, b -> nodes in between which you want to delete the edge

     //checks if nodes exist
     if (a < 0 || a >= node_num || b < 0 || b >= node_num) {
          cout << "Cvorovi ne postoje!" << endl;
          return;
     }
     //checks if nodes are different
     if (a == b) {
          cout << "Cvorovi su isti, moraju biti razliciti" << endl;
          return;
     }
     //sorts nodes
     if (a > b) {
          int temp = a;
          a = b;
          b = temp;
     }
     //checks if edge already doesn't exist
     bool exists = false;
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i].otherEdge == b) exists = true;
     if (!exists) {
          cout << "Grana vec ne postoji" << endl;
          return;
     }

     edge_num--;
     Edge* temp = new Edge[edge_num * 2];
     if (edge_num == 0) {                              //if it was the last edge delete it
          delete edges;
          edges = NULL;
          for (int i = 0; i <= node_num; i++) indices[i] = 0;
          return;
     }
     else {
          int i = 0;
          //copy all values in edges before first node in indices
          while (i < a) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j] = edges[j];
               i++;
          }
          //delete values in edges in the place of first node in indices
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < b) temp[j] = edges[j];
               else {
                    if (j != indices[i + 1] - 1) temp[j] = edges[j + 1];
               }
          }
          i++;
          //copy all values in edges before second node in indices to a one palce before bc one value was deleted 
          while (i < b) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j - 1] = edges[j];
               i++;
          }
          //delete values in edges in the place of second node in indices
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < a) temp[j - 1] = edges[j];
               else {
                    if (j != indices[i + 1] - 1) temp[j - 1] = edges[j + 1];
               }
          }
          i++;
          //copy all values in edges after second node in indices to a two palces before bc two value were deleted 
          while (i < node_num) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j - 2] = edges[j];
               i++;
          }
     }
     //changes values (addresses of other edges in edges array) in indices
     for (int i = 0; i <= node_num; i++) {
          if (i > a && i <= b)
               indices[i]--;
          if (i > b)
               indices[i] -= 2;
     }
     delete edges;
     edges = temp;
}

void Graph::printGraph() {
     //prints all graph values

     //checks if graph is empty
     if (node_num == 0) {
          cout << "\nBroj cvorova je " << node_num << endl;
          return;
     }

     //print
     cout << "\nBroj cvorova je " << node_num << endl;
     cout << "Broj grana je " << edge_num << endl;
     cout << endl;

     cout << "Indices:    ";
     for (int i = 0; i <= node_num; i++) cout << indices[i] << " ";
     cout << endl;
     cout << "Edges:      ";
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i].otherEdge << " ";
     cout << endl;
     cout << "Prices:     ";
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i].price << " ";
     cout << endl;
     cout << "Road type:  ";
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i].road << " ";
     cout << endl;
     cout << endl;

     //prints all edges
     bool* printed = new bool[node_num - 1];
     for (int i = 0; i < node_num; i++) printed[i] = false;

     for (int i = 0; i < node_num; i++) {
          for (int j = indices[i]; j < indices[i+1]; j++)
               if (!printed[edges[j].otherEdge]) {
                    cout << "Grana (" << i << "," << edges[j].otherEdge << ") ima cenu " << edges[j].price << " i ";
                    if (edges[j].road == 1) cout << "izgradjen je drumski put" << endl;
                    else cout << "nije izgradjen drumski put" << endl;
               }
          printed[i] = true;
     }
}

int Graph::primsAlgorithm() {
     //gets minimum spanning tree visiting all nodes in graph 
     //using Prim's algorithm that finds a minimum spanning tree for a weighted undirected graph

     int p = 0; //start minimum price
     if (node_num <= 1) return 0;

     bool *visited = new bool[node_num];
     for (int i = 0; i < node_num; i++) visited[i] = false;

     //get random start node
     int start = rand() % node_num;
     visited[start] = true;

     //checks for minimum weight edges between visited and not visited nodes until all nodes are visited
     while (!visitedAll(visited, node_num)) {
          int minPriceNode = -1;
          int minPrice = INT_MAX;
          for (int i = 0; i < node_num; i++) {
               if (visited[i]) {
                    for (int j = indices[i]; j < indices[i + 1]; j++) {
                         if (!visited[edges[j].otherEdge]) {
                              if (minPrice > edges[j].price)
                              {
                                   minPrice = edges[j].price;
                                   minPriceNode = edges[j].otherEdge;
                              }
                         }
                    }
               }
          }
          visited[minPriceNode] = true;
          p += minPrice;
     }
     cout << "Pocinje se od cvora " << start << endl;
     return p;
}

void Graph::minPath(int a, int b) {
     //gets minimum weight path between two nodes
     // int a, b -> nodes between you want to search paths

     //creates stack to go through the graph
     stack <nlp*> s;
     nlp* first = new nlp();
     first->level = 0;
     first->node = a;
     first->price = 0;
     s.push(first);
     
     int minPrice = INT_MAX;
     int* minVector = new int[node_num]; //minimum path from a to b
     int* currVector = new int[node_num]; //current path
     int** allVectors = new int* [node_num]; //stores all paths with minimum price
     
     for (int i = 0; i < node_num; i++) {
          minVector[i] = currVector[i] = -1;
          allVectors[i] = NULL;
     }
     //start node
     currVector[0] = minVector[0] = a;

     //until we search all paths 
     while (!s.empty()) {
          //get the last node from stack that you want to process
          nlp* top = s.top();
          for (int i = 0; i < node_num; i++)                //correct current path if node not on path it's -1
               if (i > top->level) currVector[i] = -1;
          s.pop();
          currVector[top->level] = top->node;

          //check if the node is the wanted destination
          if (top->node == b) {              
               if (top->price <= minPrice) {                        //change min path if found min or equal                                     
                    for (int i = 0; i < node_num; i++) minVector[i] = currVector[i];
                    if (top->price < minPrice) {                      //if min delete all stored paths with larger price
                         minPrice = top->price;
                         for (int i = 0; i < node_num; i++) {
                              delete allVectors[i];
                              allVectors[i] = NULL;
                         }
                         allVectors[0] = new int[node_num];
                         for (int i = 0; i < node_num; i++) allVectors[0][i] = minVector[i];        //store new min path
                    } else {                                          //if found price is equal to min add new path
                         int k = 0;
                         while (allVectors[k] != NULL) k++;
                         allVectors[k] = new int[node_num];
                         for (int j = 0; j < node_num; j++) allVectors[k][j] = minVector[j];
                    }
               } 
          } else {                                //if we didn't reach wanted destination yet add new nodes to the route
               if (top->price < minPrice) {            //check if all other path values are larger          
                    for (int i = indices[top->node]; i < indices[top->node + 1]; i++) {       
                         if (!visitedNode(currVector, node_num, edges[i].otherEdge)) {
                              nlp* temp = new nlp();                       //pushes neighbour edges to the stack
                              temp->level = top->level + 1;
                              temp->node = edges[i].otherEdge;
                              temp->price = top->price + edges[i].price;
                              s.push(temp);
                         }
                    }
               } 
          }
     }
     //counts how many not real roads are in the path
     int* roads = new int[node_num];
     for (int i = 0; i < node_num; i++) roads[i] = 0;
     for (int i = 0; i < node_num; i++) 
          if (allVectors[i] != NULL) {                           
               for (int j = 0; j < node_num - 1; j++)
                    if (allVectors[i][j + 1] != -1)
                         for (int k = indices[j]; k < indices[j + 1]; k++)
                              if (edges[k].otherEdge == allVectors[i][j + 1])
                                   if (edges[k].road == 0) roads[i]++;
          }

     //sorts paths (those with more real roads first)
     for (int i = 0; i < node_num; i++)
          for (int j = 0; j < node_num; j++) {
               if (allVectors[i] != NULL && allVectors[j] != NULL) {
                    if (roads[i] < roads[j]) {
                         int* temp = allVectors[i];
                         allVectors[i] = allVectors[j];
                         allVectors[j] = temp;
                         int tempp = roads[i];
                         roads[i] = roads[j];
                         roads[j] = tempp;
                    }
               }
          }
     //print found paths
     cout << "-------------------------------------------------------------" << endl;
     cout << "Ukupna cena udaljenosti cvora " << a << " od cvora " << b << " iznosi " << minPrice << endl;
     for (int i = 0; i < node_num; i++)
          if (allVectors[i] != NULL) {
               cout << "\nPutanja " << i << ": ";
               for (int j = 0; j < node_num; j++)
                    if (allVectors[i][j] != -1) cout << allVectors[i][j] << " ";
               cout << "ima " << roads[i] << " neizgradjena drumska puta" << endl;
          }

     for (int i = 0; i < node_num; i++) {
          delete allVectors[i];
          allVectors[i] = NULL;
     }
}

void Graph::minRoutes(int station) {
     //gets minimum weight path from one node you choose to another for every other node
     // int station -> the node you want to measure paths from 

     //checks if node exists
     if (station < 0 || station > node_num) {
          cout << "Cvor ne postoji" << endl;
          return;
     }

     //checks if there is less then two nodes (only one edge)
     if (node_num <= 1) {
          cout << "Postoji manje od dva cvora" << endl;
          return;
     }

     //for each pair of nodes gets min path
     for (int i = 0; i < node_num; i++)
          if (i != station) minPath(station, i);

}