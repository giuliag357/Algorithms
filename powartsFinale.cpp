#include <iostream>
#include<set>
#include<list>
#include<vector>
#include<algorithm>
#include<math.h>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;

//Programma modificato partendo da quello trovato https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

ofstream out("output.txt");

// priority_queue in STL
# define INF 0x3f3f3f3f

// iPair ==> (destinazione, peso)
typedef pair<int, int> iPair;

// Grafo con lista di adiacenza
class Graph
{
	int V; //Numero di nodi

	//Salviamo vertice e peso per ogni arco
	list< pair<int, int> > *adj;

public:
    // Costruttore
	Graph(int V){
	    this->V = V;
        adj = new list<iPair> [V];
	}

	// funzione per aggiungere un arco al grafo
	void addEdge(int u, int v, int w){
	    adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
	}

	// calcola le distanze minime e il vettore dei padri per la costruzione dell'albero di copertura
	int* shortestPath(int src, int* parents)
    {
        // Create a priority queue to store vertices
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

        //crea un vettore delle distanze inizializzando tutte le distanze ad infinito
        vector<int> dist(V, INF);
        
        
        //inserire la radice(poworts) in coda e inizializza la sua distanza a 0
        pq.push(make_pair(0, src));
        dist[src] = 0;
        parents[src]= src;

        //cicla finchè la coda non è vuota
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            // 'i' per itarare sugli archi adiacenti al nodo in questione
            list< pair<int, int> >::iterator i;
            for (i = adj[u].begin(); i != adj[u].end(); ++i)
            {

                //salvo la destinazione e la distanza del nodo corrente
                int v = (*i).first;
                int weight = (*i).second;

                //se esiste un percorso più corto per andare a v passando per u
                if (dist[v] > dist[u] + weight)
                {
                    // aggiornare la distaza di v
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                    parents[v] = u;   //salvare il padre di v nel vettore dei padri

                }
            }
        }

        return parents;
    }
};

//------------------------------------------------------------------------------------------------

vector<vector<int> > adj;
int xi;

int dimSottMatrice(int x, int padre){
	int s = 0;
	
	s+=adj[x].size()-1;
	for(int i = 0; i< adj[x].size(); i++){
		if(adj[i].size() != 0 && adj[x][i] != padre)
			s+= dimSottMatrice(adj[x][i], x) ;
	}	
	return s;
}

void stampaSottoAlbero(int x, int padre){
	for(int i = 0; i< adj[x].size(); i++){
		if(adj[i].size() != 0 && adj[x][i] != padre){
			out <<endl<< adj[x][i];
			stampaSottoAlbero(adj[x][i], x);
		}
	}	
}


int trovaMaxMatrice(int P){
	int maxx = -1;
	
	int maXXX = -1;
	if(adj.size() <=1)
		return 0;
	else{
		xi = 0;		
		for(int i = 0; i< adj[P].size(); i++){
			if(adj[P][i] != P){
			
			maXXX = maxx;
			maxx = max(dimSottMatrice(adj[P][i], P), maxx);	
			if(maxx != maXXX)
				xi = adj[P][i];
			//cout << "XI "<< xi << endl;
			//cout << "MAX "<< maxx << endl;
			//cout << "adj[P][i]" << adj[P][i] << endl;
			}
		}
	
	}
	return maxx +1;
}

//------------------------------------------------------------------------------------------------


int main()
{

    int i;

	int N,M,P;
	ifstream in("input.txt");
    in >> N >> M >> P;
    
    
    
    int Pow = P;
	Graph g(N);
	adj.resize(N);
    int partenza,destinazione,peso;
	for(i = 0; i < M; i++){
        in >> partenza >> destinazione >> peso;
        g.addEdge(partenza, destinazione, peso);
	}

	int* parents = new int[N];
    parents = g.shortestPath(P, parents);
    
	
    Graph tree(N);
    for(i = 0; i < N; i++){
        if(parents[i]!= i)
            tree.addEdge(parents[i], i, 1);
    }
    
    
    
	

	for(i=0; i<N; i++) {
        if(parents[i]!= i)
            adj[parents[i]].push_back(i);
            adj[i].push_back(parents[i]);
	}
	
	/*
	for(i=0; i<N; i++) {
		cout << "parents[i] = " << parents[i] << " - i:" << i << endl;
	}
	
	for(i=0; i<N; i++) {
		cout << "i = " << i << " - i:" << i << endl;
		for(int j = 0; j < adj[i].size(); j++ )
			cout << "j = " << i << " - adj[i][j]:" << adj[i][j] << endl;
	}
	*/
	
	

    if(adj.size() > 1 ){
		out << trovaMaxMatrice(Pow);
		out <<endl<<xi;
		cout << "XI finale "<< xi << endl;
		stampaSottoAlbero(xi, Pow);
		
	}
	else
		out << 0;
	return 0;

	return 0;

}
