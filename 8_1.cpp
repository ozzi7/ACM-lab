#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// a structure to represent an edge in graph
struct Edge {
    int src, dest,dur,cost;
};
 
// a structure to represent a graph
// struct Graph {
//     // V-> Number of vertices, E-> Number of edges
//     int V, E;
//  
//     // graph is represented as an array of edges
//     struct Edge* edge;
// };
 
struct subset {
    int parent;
    int rank;
};
 
// // Creates a graph with V vertices and E edges
// struct Graph* createGraph(int V, int E) {
//     struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );
//     graph->V = V;
//     graph->E = E;
//  
//     graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );
//  
//     return graph;
// }
bool compDur(Edge e1, Edge e2) {
  return e1.dur < e2.dur; // all dur are different
}
bool compCost(Edge e1, Edge e2) {
  return e1.cost < e2.cost; // all dur are different
}

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i) {
    // find root and make root as parent of i (path compression)
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and increment
    // its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int nofC, nofR,totCost,totDur;
	cin >> nofC >> nofR;
	totCost = 0; totDur = 0;
	//struct Graph* graph = createGraph(nofC, nofR);
	int a,b,c,d;
	vector<Edge> edges;
		vector<Edge> edgesCost;
			vector<Edge> edgesDur;
	for (int i = 0; i < nofR; i++) {
	  cin >> a >> b >> c >> d;
	  Edge e;
	  e.src = a; e.dest = b; e.dur = c; e.cost = d;
	  edges.push_back(e);	  
	}
	
	// first sort with duration
	sort(edges.begin(),edges.end(),compCost);
	
	struct subset *subsets = (struct subset*) malloc( nofC * sizeof(struct subset) );
	for (int v = 0; v < nofC; ++v) {
	    subsets[v].parent = v;
	    subsets[v].rank = 0;
	}
	for (int i = 0; i < nofR; i++) {
	  int x = find(subsets, edges[i].src);
	  int y = find(subsets, edges[i].dest);
	  if(x != y) {
	    Union(subsets,x,y);
	    edgesCost.push_back(edges[i]);
	    totCost += edges[i].cost;
	  }
	}
	
	// first sort with duration
	sort(edges.begin(),edges.end(),compDur);
	subsets = (struct subset*) malloc( nofC * sizeof(struct subset) );
	for (int v = 0; v < nofC; ++v) {
	    subsets[v].parent = v;
	    subsets[v].rank = 0;
	}
	for (int i = 0; i < nofR; i++) {
	  int x = find(subsets, edges[i].src);
	  int y = find(subsets, edges[i].dest);
	  if(x != y) {
	    Union(subsets,x,y);
	    edgesDur.push_back(edges[i]);
	    totCost += edges[i].cost;
	  }
	}
	sort(edgesDur.begin(),edgesDur.end(),compCost);
	sort(edgesCost.begin(), edgesCost.end(),compCost);
	
	bool eq = true;
	if(edgesDur.size() != edgesCost.size()) eq = false;
	else {
	  for(int u = 0; u < edgesDur.size();u++) {
	    if(edgesDur[u].cost == edgesCost[u].cost) {}
	      else
	      { eq = false;}
	  }
	}
	if(eq) cout << "yes" << endl; else cout << "no" << endl;
    }
    return 0;
}