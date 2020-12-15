#include <iostream>
using namespace std;

class Graph {

public:

     int *indices;
     int *edges;
     int node_num;
     int edge_num;


     Graph(int size) {
          
          node_num = size;
          edge_num = 0;
          indices = new int[node_num+1];
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
     void addEdge(int a, int b);
     void deleteEdge(int a, int b);
     void printGraph();

};

void Graph::addNode() {

     node_num++;
     int* temp = new int[node_num + 1];
     for (int i = 0; i < node_num; i++) temp[i] = indices[i];
     temp[node_num] = temp[node_num - 1];
     delete indices;
     indices = temp;
     //cout << "Novi indices!" << endl;
     //for (int i = 0; i < node_num + 1; i++) cout << indices[i];

}

void Graph::deleteNode(int node) {

     if (node < 0 || node >= node_num) {
          cout << "Cvor ne postoji" << endl;
          return;
     }

     node_num--;
     int i1 = indices[node];
     int i2 = indices[node + 1];

     int* temparr = new int[edge_num * 2];
     int i3 = edge_num * 2;
     for (int i = 0; i < i3; i++)
          temparr[i] = edges[i];

     for (int i = i1; i < i2; i++) {
          this->deleteEdge(node, temparr[i]); //menja se edges u toku petlje i onda pri drugom poyivanju budu rubbish vrednosti
     }

     for (int i = 0; i < edge_num * 2; i++)
          if (edges[i] > node) edges[i]--;

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

void Graph::addEdge(int a, int b) {

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
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i] == b) exists = true;
     if (exists) {
          cout << "Grana vec postoji" << endl;
          return;
     }

     edge_num++;
     int* temp = new int[edge_num * 2];
     if (edge_num == 1) {
          temp[0] = b;
          temp[1] = a;
     }
     else {
          int i = 0;
          while (i < a) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j] = edges[j];
               i++;
          }
          bool added = false;
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j] < b) temp[j] = edges[j];
               else {
                    if (!added) {
                         added = true;
                         temp[j] = b;
                    }
                    temp[j + 1] = edges[j];
               }
          }
          if (!added) temp[indices[i + 1]] = b;
          i++;
          while (i < b) {
               for (int j = indices[i]; j < indices[i + 1]; j++) temp[j + 1] = edges[j];
               i++;
          }
          added = false;
          for (int j = indices[i]; j < indices[i + 1]; j++) {
               if (edges[j] < a) temp[j + 1] = edges[j];
               else {
                    if (!added) {
                         added = true;
                         temp[j + 1] = a;
                    }
                    temp[j + 2] = edges[j];
               }
          }
          if (!added) temp[indices[i + 1] + 1] = a;
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
     if (edge_num != 0) for (int i = indices[a]; i < indices[a + 1]; i++) if (edges[i] == b) exists = true;
     if (!exists) {
          cout << "Grana vec ne postoji" << endl;
          return;
     }

     edge_num--;
     int* temp = new int[edge_num * 2];
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
               if (edges[j] < b) temp[j] = edges[j];
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
               if (edges[j] < a) temp[j - 1] = edges[j];
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
     cout << "Indices:" << endl;
     for (int i = 0; i <= node_num; i++) cout << indices[i] << " ";
     cout << endl;
     cout << "Edges:" << endl;
     for (int i = 0; i < 2 * edge_num; i++) cout << edges[i] << " ";
     cout << endl;

}


int main() {
     
     int menu = 1;

     Graph* g = NULL;

     while (menu != 0) {

          cout << "\n--------------------------------------------" << endl;
          cout << "Unesite broj opcije koju zelite da izvrsite: \n\n 1. Kreiranje prazne strukture\n 2. Dodavanje cvora u graf\n 3. Uklanjanje cvora iz grafa\n 4. Dodavanje grane izmedju dva cvora u grafu\n 5. Uklanjanje grane izmedju dva cvora u grafu\n 6. Ispis reprezentacije grafa\n 7. Brisanje grafa iz memorije\n 0. Izlaz\n" << endl;
          cin >> menu;

          if (menu != 0 && menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6 && menu != 7) {
               cout << "Broj koji ste uneli nije validan!\n" << endl;
          }

          switch (menu) {
               case 1:
                    if (g != NULL) cout << "Graf je vec definisan" << endl;
                    else {
                         cout << "Unesite broj cvorova grafa" << endl;
                         int numberofnodes;
                         cin >> numberofnodes;
                         g = new Graph(numberofnodes);
                         cout << "Uspesno je kreiran graf sa " << g->node_num << " cvorova" << endl;
                    }
                    break;
               case 2: 
                    if (g == NULL) g = new Graph(1);
                    else g->addNode();
                    cout << "Uspesno je dodat cvor" << endl;
                    break;
               case 3: 
                    if (g == NULL) cout << "Graf ne postoji";
                    else {
                         cout << "Unesite broj cvora koji zelite da izbrisete" << endl;
                         int e;
                         cin >> e;
                         g->deleteNode(e);
                    }
                    break;
               case 4: 
                    cout << "Unesite granu koju dodajete oblika (a,b) gde su a i b cvorovi koje grana povezuje" << endl;
                    int a, b;
                    cin >> a >> b;
                    g->addEdge(a, b);
                    break;
               case 5: 
                    cout << "Unesite granu koju brisete oblika (a,b) gde su a i b cvorovi koje grana povezuje" << endl;
                    int c, d;
                    cin >> c >> d;
                    g->deleteEdge(c, d);
                    break;
               case 6: 
                    if (g != NULL) g->printGraph();
                    else cout << "Graf nije definisan";
                    break;
               case 7:
                    if (g == NULL) cout << "Graf nije definisan, ili je vec obrisan" << endl;
                    else delete g;
                    g = NULL;
                    break;
               case 0: break;
          }

     }

}