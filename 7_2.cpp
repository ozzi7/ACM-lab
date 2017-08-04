#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

/* Solution idea:
 * Go through all vertices from lowest to highest cost. For each vertex $v$ that is
 * not yet reachable from some police station, put a police station there and remove
 * all police station reachable from $v$, using a DFS.
 */

// Locations ordered by increasing cost.
struct Loc {
    int loc, cost;
    bool operator<(const Loc &other) const {
	return cost < other.cost;
    }
};

// Compute the solution.
// n :: number of vertices
// m :: number of edges
// adj :: adjacency list
// locs :: list of locations with cost
int solve(int n, int m, const vector< vector<int> > &adj, const vector<Loc> &locs) {
    vector<int> police(n,0);
    vector<int> covered(n,0);
    vector<Loc> sorted_locs(locs);
    stack<int> s;
    int cost = 0;

    // Sort the vertices by increasing cost.
    sort(sorted_locs.begin(), sorted_locs.end());
    // Now go through the vertices from lowst to highest cost.
    for (int k = 0; k < n; k++) {
        // i is the name of the current vertex.
	int i = sorted_locs[k].loc;
	if (!covered[i]) {
	    // Do a DFS to to remove all stations reachable from i.
	    vector<int> visited(n,0);
	    s.push(i);
	    visited[i] = 1;
	    while (!s.empty()) {
		int cur = s.top();
		s.pop();
		visited[cur] = 1;
		// If the vertex has a police station, remove it.
		if (police[cur]) {
		    police[cur] = 0;
		    cost -= locs[cur].cost;
		}
		// Mark the vertex as covered.
		covered[cur] = 1;
		// Push univisited neighbours onto the stack.
		for (int j = 0; j < adj[cur].size(); j++) {
		    if (!visited[adj[cur][j]]) {
			s.push(adj[cur][j]);
		    }
		}
	    }
	    // Put a police station in i, modify total cost accordingly.
	    police[i] = 1;
	    cost += locs[i].cost;
	}
    }
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int n, m;
	// Adjacency list representing the directed graph.
	vector< vector<int> >adj;
	// Vector holding all locations and their costs.
	vector<Loc> locs;

	cin >> n >> m;
	// Read the graph, fill adjacency list.
	adj = vector< vector<int> >(n);
	for (int i = 0; i < m; i++) {
	    int u, v;
	    cin >> u >> v;
	    adj[u-1].push_back(v-1);
	}
        // Fill the location vector.
	locs = vector<Loc>(n);
	for (int i = 0; i < n; i++) {
	    Loc l;
	    l.loc = i;
	    cin >> l.cost;
	    locs[i] = l;
	}
        // Output the solution.
	cout << solve(n, m, adj, locs) << endl;
    }
    return 0;
}
