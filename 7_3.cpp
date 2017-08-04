#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int > > graph;
vector<int> depth;
vector<int> low;
vector<int> visited;

void dfs(int v,int dep) {
  visited[v] = 1;
  depth[v] = dep;
  int lowest = v;
  for(int u = 0; u < graph[v].size(); u++) {
    if (!visited[u]) {
      dfs(u, dep+1);
    }
    if(depth[low[u]] <= depth[lowest]) {
      lowest = low[u]; // found lower neighbor, point to same node as this neighbor
      // -> only 1 step and not visited yet
    }
    if (depth[u] <= depth[lowest]) {	// its a backedge which is better
      if (depth[u] <= depth[v]-1) {
	lowest = u; // point to backedge
      }
    }
  }
  low[v] = lowest;
}
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int nofloc, nofbridges;
	cin >> nofloc >> nofbridges;
	graph = vector<vector<int> >(nofloc,vector<int>());
	vector<pair<int,int> > result;
	depth.clear(); visited.clear(); low.clear();
	
	for (int i = 0; i < nofbridges; i++) {
	    int u, v;
	    cin >> u >> v;
	    graph[u-1].push_back(v-1);
	    graph[v-1].push_back(u-1);
	}
	
	for(int j = 0; j < nofloc; j++) {
	  low.push_back(j);
	  visited.push_back(0);
	  depth.push_back(0);
	}
	dfs(0,0); // 0 is root

	
	for(int i = 0; i < depth.size(); i++) {
	  cout << "Node " << i << ": " << "Depth: " << depth[i];
	  cout << " Low: " << low[i] << endl;
	}
	for(int a = 0; a < graph.size(); a++) {
	  // cycle islands
	  for(int b = 0; b < graph[a].size(); b++) {
	    // cycle bridges
	    if(graph[a][b] < a && graph[a][b] != 0 && a != 0) {
	      if(low[graph[a][b]] == graph[a][b]) {
		result.push_back(make_pair(a,b));
	      }
	    }
	  }
	}
	cout << result.size() << endl;
	for(int z = 0; z < result.size(); z++) {
	  cout << result[z].first+1 << " " <<  result[z].second+1 << endl;
	}
    }
    return 0;
}