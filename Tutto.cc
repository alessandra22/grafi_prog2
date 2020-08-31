#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

struct adj_node{
  int node;
  float weight;
  adj_node *next;
};

typedef adj_node * adj_list;

typedef struct{
  adj_list *nodes;
  int dim;
 } graph;
 
graph new_graph(int n){
  graph g;
  g.dim = n;
  g.nodes = new adj_list[n];
  for(int i=0; i<n; i++)
    g.nodes[i] = NULL;
  return g;
}

void add_arc(graph &g, int u, int v, float w){ //Arco diretto
  adj_node *t = new adj_node;
  t->node = v-1;
  t->weight = w;
  t->next = g.nodes[u-1];
  g.nodes[u-1] = t;
}
 
void add_edge(graph &g, int u, int v, float w){ //Arco indiretto
  add_arc(g,u,v,w);
  add_arc(g,v,u,w);
}
 
int get_dim(graph g){ 
  return g.dim; 
} 
 
adj_list get_adjlist(graph g, int u){
  return g.nodes[u-1]; 
}
 
int get_adjnode(adj_list l){ 
  return l->node+1; 
} 
 
adj_list get_nextadj(adj_node *n){ 
  return n->next; 
}
 
void add(graph &g, int u, int v, float w, bool d){
 if(d)
  add_arc(g,u,v,w);
 else
  add_edge(g,u,v,w);
}

graph g_build(ifstream &g, bool d, bool w){
  int n;
  g>>n;
  graph G = new_graph(n);
  
  int u,v;
  if(w){
    float w;
    while(g>>u>>v>>w)
      add(G,u,v,w,d);
  } 
  else {
    while(g>>u>>v)
      add(G,u,v, 1.0, d);
  }
}

void stampagrafo(graph G){
 adj_list tmp;
 for (int i=1; i<=get_dim(G); i++) {
  tmp=get_adjlist(G,i);
  cout << i;
  while (tmp) {
   cout << " --> " << get_adjnode(tmp);
   tmp=get_nextadj(tmp);
  }
  cout << endl;
 }
}

int main(int argc, char *argv[]) {
 if (argc<3) {
  cout << "Usage: " << argv[0] << " filename directed weighted\n";
   exit(0);
 };
 
 ifstream g;
 g.open(argv[1]);
 cout << argv[1] << " " << argv[2] << " " << argv[2]<<endl;
 int directed = atoi(argv[2]); //atoi = da stringa a intero
 int weighted = atoi(argv[3]);
 
 /*Chiamata a g_build che costruisce un grafo*/
 graph G=g_build(g, directed, weighted);

 cout<<G.dim<<endl;
 stampagrafo(G);
}
