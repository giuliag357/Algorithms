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

    set< pair<int, int> > scivoliArcobaleno;

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

    //funzione per rimuovere un arco  (non orientato)
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

    
    bool BFS(int s, int d, int *parents)
    {
        bool *visited = new bool[V];
        for(int i = 0; i < V; i++)
            visited[i] = false;

        list<int> queue;

        visited[s] = true;
        queue.push_back(s);

        list<int>::iterator i;

        while(!queue.empty())
        {
            s = queue.front();

            queue.pop_front();

            for (i = adj[s].begin(); i != adj[s].end(); ++i)
            {
                if (!visited[*i])
                {
                    visited[*i] = true;
                    parents[*i] = s;
                    queue.push_back(*i);
                }
            }
        }

        return (parents[d] == -1);

    }

    void trovaPercorso(int s, int d, int *parents){
        while (s != d){
            pair<int, int> arco = make_pair(parents[d], d);
	        this->scivoliArcobaleno.insert(arco);
            d = parents[d];
        }
    }

};


int main()
{
    //lettura file di input
    int N, M, P;
    ifstream in("input.txt");
    in >> N >> M >> P;
    Graph g(N);
    //creazione grafo dal file
    int partenza, destinazione;
    for (int i = 0; i < M; i++)
    {
        in >> partenza >> destinazione;
        g.addUnDirectedEdge(partenza, destinazione);
    }

    int vetStart[P], vetEnd[P]; //array che conterranno partenza e destinazione dei Power Up 

    //inserisco i nodi di partenza e nodi di arrivo nei rispettivi vettori
    for (int i = 0; i < P; i++)
        in >> vetStart[i] >> vetEnd[i];

    int parents[N] = {-1};

    output << "1" << endl;

    for(int i = 0; i < P; i++){
        g.BFS(vetStart[i], vetEnd[i], parents);
        g.trovaPercorso(vetStart[i], vetEnd[i], parents);
    }

    output << g.scivoliArcobaleno.size() << endl;

    set< pair<int, int> >::iterator iter;
    for (iter = g.scivoliArcobaleno.begin(); iter != g.scivoliArcobaleno.end(); ++iter) {
            output << (*iter).first << " " << (*iter).second << endl;
    }


    return 0;
}
