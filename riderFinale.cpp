#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <bits/stdc++.h>

using namespace std;

ofstream output("output.txt");

//grafo con lista di adiacenza
class Graph
{
    int V; //numero di nodi

    list<int> *adj; //lista di vicini

public:
    //costruttore
    Graph(int V)
    {
        this->V = V;            //grafo con V nodi
        adj = new list<int>[V]; //lista di adiacenza per V elementi
    }

    // funzione per aggiungere un arco al grafo (non orientato)
    void addUnDirectedEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // funzione per aggiungere un arco al grafo (orientato)
    void addDirectedEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    //funzione per rimuovere un arco  (orientato)
    void removeUnDirectedEdge(int u, int v)
    {
        adj[u].remove(v);
        adj[v].remove(u);
    }

    //funzione per rimuovere un arco  (orientato)
    void removeDirectedEdge(int u, int v)
    {
        adj[u].remove(v);
    }
};

//Funzione principale che lavora per trovare e creare l'output
bool Mario(Graph g, int * vetPartenza, int * vetDestinazione, int P, int V, set<pair<int, int>> & scivoliArcobaleno, int & partenza, int & arrivo)
{
    bool returnValue = true;

    //Ciclo che itera un numero di volte pari al numero di Power Up oppure quando non trova un percorso possibile per uno di questi
    for (int i = 0; i < P && returnValue; i++)
    {

        //Creo i vettori che conterranno il percorso finale per il Power Up 
        int * path = new int[V];
        //int * doppio = new int[V];
        partenza = vetPartenza[i]; //mi salvo il nodo di partenza del Power Up
        arrivo = vetDestinazione[i]; //mi salvo il nodo di destinazione del Power Up
        int lunghezza = -1; //lunghezza -1 nel caso non si trovi un percorso possibile tra i due nodi

        //Chiamo la funzione findPath per trovare il percorso tra partenza e destinazione

        cout << "Cerco da " << vetPartenza[i] << " a " << vetDestinazione[i];
        returnValue = g.findPath(vetPartenza[i], vetDestinazione[i], path, lunghezza);

        //Se la lunghezza è maggiore di 0, quindi ha trovato un percorso
        if (lunghezza > 0)
        {   
            cout << endl;
            //itero sull'array del percorso e rimuovo gli archi orientati nel senso opposto del percorso
            for (int i = 1; i < lunghezza; i++)
            {
                pair<int, int> arco = make_pair(path[i - 1], path[i]);
                scivoliArcobaleno.insert(arco);
                g.removeDirectedEdge(path[i], path[i - 1]);
                // cout << "rimuovo = " << path[i] << " "<< path[i - 1]<< endl;
            }
        }

        delete [] path;
        //delete [] doppio;

    }

    return returnValue;
}

int main()
{

    int i;

    //lettura file di input
    int N, M, P;
    ifstream in("inputEsempio1.txt");
    in >> N >> M >> P;
    Graph g(N);

    //creazione grafo dal file
    int partenza, destinazione;
    for (i = 0; i < M; i++)
    {
        in >> partenza >> destinazione;
        g.addUnDirectedEdge(partenza, destinazione);
    }

    int vetStart[P], vetEnd[P]; //array che conterranno partenza e destinazione dei Power Up 

    //inserisco i nodi di partenza e nodi di arrivo nei rispettivi vettori
    for (int i = 0; i < P; i++)
        in >> vetStart[i] >> vetEnd[i];

    bool visited[N] = {false};

    //set (=> no ripetizioni) che conterrà tutti gli archi che vengono definiti scivoli arcobaleno 
    set< pair <int, int> > scivoliArcobaleno;

    int inizio, arrivo;

    //funzione che trova il risultato
    bool returnValue = Mario(g, vetStart, vetEnd, P, N, scivoliArcobaleno, inizio, arrivo);

    set<pair<int, int>>::iterator iter;

    cout << "output = " << endl << returnValue << endl;
    //output << returnValue << endl;
    if(returnValue == 1) { //se la funzione Mario trova una soluzione per tutti i Power Up
         for (iter = scivoliArcobaleno.begin(); iter != scivoliArcobaleno.end(); ++iter) {
            //output << (*iter).first << " " << (*iter).second << endl;
            cout << (*iter).first << " " << (*iter).second << endl;
         }
    }
    else { //altrimenti
        //aggiunge gli archi che avevamo tolto in modo da tornare al grafo originale
        cout << scivoliArcobaleno.size() << endl;
        for (iter = scivoliArcobaleno.begin(); iter != scivoliArcobaleno.end(); ++iter) {
            pair<int, int> arco = make_pair((*iter).second, (*iter).first);
            g.addDirectedEdge(arco.first, arco.second);
            //cout << arco.first << " archi " <<  arco.second << endl;
        }

        int lunghezza = -1;
        int * path = new int[N];
        //int * doppio = new int[N];

        cout << endl << "cerco nuovo percorso da "<< inizio << " a " << arrivo << endl;
        //cerca un percorso per il Power Up che non trovava un percorso possibile
        g.findPath(inizio, arrivo,path,lunghezza);

        pair<int, int> arcoProblematico;
        bool trovato = false;

        //ciclo che cerca l'arco problematico confrontando il percorso trovato nel grafo iniziale con quello interrotto nel grafo orientato
        for(int i = 1; i < lunghezza && !trovato; i++) {
            //pair<int, int> arco = make_pair(doppio[i], doppio[i - 1]);
            for (iter = scivoliArcobaleno.begin(); iter != scivoliArcobaleno.end() && !trovato; ++iter) {
                if((*iter).first == path[i] && (*iter).second == path[i-1]) {
                    arcoProblematico = make_pair(path[i - 1], path[i]);
                    trovato = true;
                }
            }
        }
        //output << arcoProblematico.first << " " << arcoProblematico.second;
        output << arcoProblematico.first << " " << arcoProblematico.second;
        delete [] path;
        //delete [] doppio;
    }

    return 0;
}