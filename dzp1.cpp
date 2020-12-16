#include <iostream>
#include "graph.h"

using namespace std;

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
                         if (g->node_num == 0) g = NULL;
                    }
                    break;
               case 4: 
                    cout << "Unesite granu koju dodajete oblika (a,b) gde su a i b cvorovi koje grana povezuje i cenu" << endl;
                    int a, b, p1;
                    cin >> a >> b >> p1;
                    g->addEdge(a, b, p1);
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