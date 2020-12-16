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

     for (int i = 0; i < num; i++)
          if (!vis[i]) return false;
     return true;
}

bool visitedNode(int* vis, int num, int a) {
     
     for (int i = 0; i < num; i++)
          if (vis[i] == a) return true;
     return false;
}

void Graph::addNode() {

     node_num++;
     int* temp = new int[node_num + 1];
     for (int i = 0; i < node_num; i++) temp[i] = indices[i];
     temp[node_num] = temp[node_num - 1];
     delete indices;
     indices = temp;
}

void Graph::deleteNode(int node) {

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

     for (int i = i1; i < i2; i++) {
          this->deleteEdge(node, temparr[i].otherEdge); //menja se edges u toku petlje i onda pri drugom poyivanju budu rubbish vrednosti
     }

     node_num--;
     for (int i = 0; i < edge_num * 2; i++)
          if (edges[i].otherEdge > node) edges[i].otherEdge--;

     if (node_num == 0) {
          delete indices;
          indices = NULL;
          return;
     }

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

     if (type < 0 || type > 1) {
          cout << "Tip puta nije korektno unet" << endl;
          return;
     }

     if (p <= 0) {
          cout << "Unesite validnu cenu (price > 0)" << endl;
          return;
     }

     if (a < 0 || a >= node_num || b < 0 || b >= node_num) {
          cout << "Cvorovi ne postoje!" << endl;
          return;
     }

     if (a == b) {
          cout << "Cvorovi su isti, moraju biti razliciti" << endl;
          return;
     }

     if (a > b) {
          int temp = a;
          a = b;
          b = temp;
     }

     bool exists = false;
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i].otherEdge == b) exists = true;
     if (exists) {
          cout << "Grana vec postoji" << endl;
          return;
     }

     edge_num++;
     Edge* temp = new Edge[edge_num * 2];
     if (edge_num == 1) {
          temp[0].otherEdge = b;
          temp[1].otherEdge = a;
          temp[0].price = temp[1].price = p;
          temp[0].road = temp[1].road = type;
     }
     else {
          int i = 0;
          while (i < a) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j] = edges[j];
               i++;
          }
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
          while (i < b) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j + 1] = edges[j];
               i++;
          }
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
          while (i < node_num) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j + 2] = edges[j];
               i++;
          }
     }
     for (int i = 0; i <= node_num; i++) {
          if (i > a && i <= b) indices[i]++;
          if (i > b) indices[i] += 2;
     }
     delete edges;
     edges = temp;
}

void Graph::deleteEdge(int a, int b) {

     if (a < 0 || a >= node_num || b < 0 || b >= node_num) {
          cout << "Cvorovi ne postoje!" << endl;
          return;
     }

     if (a == b) {
          cout << "Cvorovi su isti, moraju biti razliciti" << endl;
          return;
     }

     if (a > b) {
          int temp = a;
          a = b;
          b = temp;
     }

     bool exists = false;
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i].otherEdge == b) exists = true;
     if (!exists) {
          cout << "Grana vec ne postoji" << endl;
          return;
     }

     edge_num--;
     Edge* temp = new Edge[edge_num * 2];
     if (edge_num == 0) {
          delete edges;
          edges = NULL;
          for (int i = 0; i <= node_num; i++) indices[i] = 0;
          return;
     }
     else {

          int i = 0;
          while (i < a) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j] = edges[j];
               i++;
          }

          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < b) temp[j] = edges[j];
               else {
                    if (j != indices[i + 1] - 1) temp[j] = edges[j + 1];
               }
          }
          i++;
          while (i < b) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j - 1] = edges[j];
               i++;
          }
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j].otherEdge < a) temp[j - 1] = edges[j];
               else {
                    if (j != indices[i + 1] - 1) temp[j - 1] = edges[j + 1];
               }
          }
          i++;
          while (i < node_num) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j - 2] = edges[j];
               i++;
          }
     }

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

     if (node_num == 0) {
          cout << "\nBroj cvorova je " << node_num << endl;
          cout << "Graf ima nula cvorova\n" << endl;
          return;
     }

     cout << "\nBroj cvorova je " << node_num << endl;
     cout << "Broj grana je " << edge_num << endl;
     cout << endl;
     cout << "Indices: ";
     for (int i = 0; i <= node_num; i++) cout << indices[i] << " ";
     cout << endl;
     cout << "Edges:   ";
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i].otherEdge << " ";
     cout << endl;
     cout << "Prices:  ";
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i].price << " ";
     cout << endl;
}

int Graph::primsAlgorithm() {

     int p = 0;

     if (node_num <= 1) return 0;

     bool *visited = new bool[node_num];
     for (int i = 0; i < node_num; i++) visited[i] = false;

     int start = rand() % node_num;
     visited[start] = true;

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

     stack <nlp*> s;
     nlp* first = new nlp();
     first->level = 0;
     first->node = a;
     first->price = 0;
     s.push(first);
     int minPrice = INT_MAX;
     int* minVector = new int[node_num];
     int* currVector = new int[node_num];
     for (int i = 0; i < node_num; i++) {
          minVector[i] = currVector[i] = -1;
     }
     currVector[0] = minVector[0] = a;

     while (!s.empty()) {
          
          nlp* top = s.top();
          for (int i = 0; i < node_num; i++)
               if (i > top->level) currVector[i] = -1;
          s.pop();
          currVector[top->level] = top->node;

          //cout << "Ovde sam se zaglavio" << top->node << endl;

          if (top->node == b) {
               if (top->price <= minPrice) {                                              //menjanje minimalnog vektora!
                    for (int i = 0; i < node_num; i++) minVector[i] = currVector[i];
                    minPrice = top->price;
               } else {
                                                                                          //dosli smo do kraja al je put duzi
               }
          } else {
               if (top->price < minPrice) {                                               //dodavanje cvorova koji nisu bili na ruti
                    for (int i = indices[top->node]; i < indices[top->node + 1]; i++) {
                         if (!visitedNode(currVector, node_num, edges[i].otherEdge)) {
                              nlp* temp = new nlp();
                              temp->level = top->level + 1;
                              temp->node = edges[i].otherEdge;
                              temp->price = top->price + edges[i].price;
                              s.push(temp);
                         }
                    }
               } else {
                                                                                          //dosli smo prethodno do cilja i to na kraci nacin!
               }
          }

     }

     cout << "Ukupna cena udaljenosti cvora " << a << " od cvora " << b << " iznosi " << minPrice << endl;
     cout << "Putanja: ";
     for (int i = 0; i < node_num; i++)
          if (minVector[i] != -1) cout << minVector[i] << " ";
     cout << endl;

}

void Graph::minRoutes(int station) {

     if (station < 0 || station > node_num) {
          cout << "Cvor ne postoji" << endl;
          return;
     }

     if (node_num <= 1) {
          cout << "Postoji manje od dva cvora" << endl;
          return;
     }

     for (int i = 0; i < node_num; i++)
          if (i != station) minPath(station, i);

}