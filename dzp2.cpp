#include <iostream>
#include "graph.h"

using namespace std;

int main() {

     int menu = 1;
     Graph* g = NULL;

     while (menu != 0) {

          cout << "\n***********************************************************************************************************************" << endl;
          cout << "Unesite broj opcije koju zelite da izvrsite: \n\n 1. Kreiranje prazne strukture\n 2. Dodavanje cvora u graf\n 3. Uklanjanje cvora iz grafa\n 4. Dodavanje grane izmedju dva cvora u grafu\n 5. Uklanjanje grane izmedju dva cvora u grafu\n 6. Ispis reprezentacije grafa\n 7. Brisanje grafa iz memorije\n 8. Prikazi minimalnu cenu za izgradnju metroa\n 9. Pronalazenje najkrace rute\n 0. Izlaz\n" << endl;
          cin >> menu;

          if (menu < 0 || menu > 9) {
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
               cout << "Unesite vrednosti grane redom: cvorovi koje grana povezuje, cena i tip (0 - neizgradjen, 1 - izgradjen)" << endl;
               int a, b, p1, type1;
               cin >> a >> b >> p1 >> type1;
               g->addEdge(a, b, p1, type1);
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
          case 8:
               if (g == NULL) cout << "Graf nije definisan" << endl;
               else {
                    int val = g->primsAlgorithm();
                    if (val == 0) cout << "U grafu ima manje od dva cvora" << endl;
                    else cout << "Minimalna cena izgradnje metroa je " << val << endl;
               }
               break;
          case 9:
               if (g == NULL) cout << "Graf nije definisan" << endl;
               else {
                    cout << "Unesite poziciju vatrogasne stanice" << endl;
                    int station;
                    cin >> station;
                    g->minRoutes(station);
               }
               break;
          case 0: break;
          }
     }

}