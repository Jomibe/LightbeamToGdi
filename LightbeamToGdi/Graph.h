#ifndef GRAPH_H
#define GRAPH_H

/*
Struktur eines Graphen, so wie er bei der Breitensuche im Buch
Algorithmen – Eine Einführung; Cormen, Leiserson, Rivest, Stein
benutzt wird
 */
#include<iostream>
#include<stdexcept>
#include "string"
#include "knoten.h"

using namespace std;

const int MAX_KNOTEN=10000;

class Graph
{
public:
    Knoten V[MAX_KNOTEN];                       // Feld aller Knoten
    int knotenzahl;                             // Anzahl, der im Graph definierten Knoten
    int Adj[MAX_KNOTEN][MAX_KNOTEN];            // Adjazentmatrix
    void ZeroGraph(int knoten=0);               // knotenzahl auf 0 setzen, Adjazentmatrix löschen
    void insert_Edge(int u, int v);   //Kante auf 1
    void Delete_Edge(Graph &G,int u, int v);    //Kante auf 0
    void Flip_Edge(Graph &G,int u, int v);      //Kante zwischen 0 und 1 wechseln
    void Graph_Debug(Graph &G);                 //Graph anzeigen
    void Insert_Random_Edge(Graph &G);          //zufällige Kante hinzufügen
    void Insert_Random_i_Edges(Graph &G,int i); //bestimmte anzahl zufälliger Kanten hinzufügen
    void ausgabe_gdi_format();          //ausgabe im .gdi gerechten Format
};

void Graph::insert_Edge(int u, int v){             //Teste ob u!= v
    if(u==v || u<1 || v<1) throw runtime_error("Kante braucht zwei verschiedene Knoten");
    //if(G.Adj[u][v]==true) throw runtime_error("Eine Kante bereits vorhanden");    //nicht notwendig
    this->Adj[u][v]=true;

};

void Graph::Delete_Edge(Graph &G,int u, int v){
    if(G.Adj[u][v]==false) throw ("Keine solche Kante vorhanden");
    G.Adj[u][v]=false;
};

void Graph::Flip_Edge(Graph &G,int u, int v){        //Teste, ob u!=v
    if(u==v || u<=1 || v<=1) throw ("Kante braucht zwei verschiedene Knoten");
    G.Adj[u][v]=!false;
};

void Graph::Graph_Debug(Graph &G){
    std::cout << "___";
    for(int i=1; i<= G.knotenzahl;i++){
        printf("|%2d", i);
    }
    std::cout << "\n";
    for(int i=1; i<=G.knotenzahl; i++){
        printf("|%2d", i);
        for(int j=1; j<=G.knotenzahl; j++){
            printf("|%2d", G.Adj[i][j]);
        }
        std::cout<<"\n";
    }
};

void Graph::Insert_Random_Edge(Graph &G){
    G.Adj[rand()%G.knotenzahl][rand()%G.knotenzahl]=!false;
};

void Insert_Random_i_Edges(Graph &G,int i){
    if(i==0) return;
    if(i<0 || i> (G.knotenzahl*G.knotenzahl)) throw ("Die Kantenzahl muss sinnvoll sein.");
    else
    for(int j=0; j<i;j++){
        G.Adj[rand()%G.knotenzahl][rand()%G.knotenzahl]=!false;
    }
};

void Graph::ausgabe_gdi_format(){
    string line ("G ");
    line +=  std::to_string(this->knotenzahl);
    std::cout  << line <<endl;
    for(int i=1; i<= this->knotenzahl;i++){
        if(this->V[i].Name != ""){
            line = "V ";
            line+= this->V[i].Name;
            //std::cout<< line << i <<endl;
            cout << "V " << i << " " << this->V[i].Name << endl;
            for(int j=1; j<=this->knotenzahl; j++){
                if(this->Adj[i][j]==1){
                    line="E "+std::to_string(i)+" ";
                    line+=std::to_string(j)+" 1";
                    std::cout<< line <<endl;
                }
            }
        }
    }
}


#endif
