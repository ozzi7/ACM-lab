#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> result;
vector<vector<int> > graph; // first entry in every subvector = visited
vector<int> inEdges;
priority_queue<int> startNodes;

void olo() {
  while(startNodes.size() != 0) {
//     for(int z = 0; z < graph.size(); z++) {
//       cout << endl;
//       cout << "startNodes:";
//       for (int t = 0; t < graph[z].size();t++) {
//       cout << graph[z][t] << " ";}
//     }
//     cout << endl;
//     cout << endl;
//     cout << "inEdges: ";
//               for(int z = 0; z < inEdges.size(); z++) {
//       cout << endl;
//       cout << inEdges[z];}
      
    int best = startNodes.top();
    if(graph[best][0] == 0) {
      result.push_back(best);
      startNodes.pop();
      graph[best][0] = 1;
      
      // go through neighbors, add to queue
      for(int i = 1; i < graph[best].size(); i++) {
	inEdges[graph[best][i]]--;
	if(inEdges[graph[best][i]] == 0 && graph[graph[best][i]][0] == 0) {
	  startNodes.push(graph[best][i]);
	}
      }
    }
    else {
      startNodes.pop();
    }
  }
}
int main() {
    ios_base::sync_with_stdio(false);
    int n,nodeCount,depCount;
    cin >> n;
    while (n--) {
      cin >> nodeCount;
      cin >> depCount;
      
      result.clear();
      startNodes = priority_queue<int>();
      graph = vector<vector<int> >(nodeCount,vector<int>(1,0));
      inEdges = vector<int>(nodeCount,0);
      
      int t1,t2;
      for(int i = 0 ; i <depCount; i++) {
	cin >>t1 >> t2;
	graph[t2-1].push_back(t1-1);
	inEdges[t1-1]++;
      }
      for(int j = 0; j <graph.size(); j++) {
	if(inEdges[j] == 0) {startNodes.push(j);}
      }
      olo();
      
      for(int u = 0; u < result.size(); u++) {
	cout << result[u]+1 << endl;
      }
    }
    return 0;
}