#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// a structure to represent an edge in graph
struct Edge {
    int src, dest,diff;
};
 
struct subset {
    int parent;
    int rank;
};

bool compDiff(Edge e1, Edge e2) {
  return e1.diff < e2.diff;
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
	int nofLodges,nofPaths,start,end;
	cin >> nofLodges >> nofPaths;
	cin >> start >> end;

	int a,b,c;
	vector<Edge> edges;

	for (int i = 0; i < nofPaths; i++) {
	  cin >> a >> b >> c;
	  Edge e;
	  e.src = a; e.dest = b; e.diff = c;
	  edges.push_back(e);	  
	}
	
	// first sort with duration
	sort(edges.begin(),edges.end(),compDiff);
	
	struct subset *subsets = (struct subset*) malloc( nofLodges * sizeof(struct subset) );
	for (int v = 0; v < nofLodges; ++v) {
	    subsets[v].parent = v;
	    subsets[v].rank = 0;
	}
	
	for (int i = 0; i < nofPaths; i++) {
	  int x = find(subsets, edges[i].src);
	  int y = find(subsets, edges[i].dest);
	  if(x != y) {
	    Union(subsets,x,y);
	  }
	  if(find(subsets,start) == find(subsets,end)) {
	    cout << edges[i].diff << endl;
	    goto end;
	  }
	}
	end:
	int hds = 0;
    }
    return 0;
}