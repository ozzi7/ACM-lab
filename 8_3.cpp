#include <iostream>
#include <queue>
#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> r, p; // ranks,parents
vector<int> treeCost;

int findSet(int i){
  // if i is parent of i (i is root) return i, else return parent
	return i == p[i] ? i : (p[i] = findSet(p[i]));
}

struct Edge {
  int from;
  int to;
  int cost;
};
bool comp(Edge e1, Edge e2) {
  if(e1.cost != e2.cost) { return e1.cost < e2.cost; }
  else if(e1.from != e2.from) { return e1.from < e2.from;}
  else if(e1.to != e2.to) {return e1.to < e2.to;}
}
void unionSet(int h, int k,int edgeCost){
  if(r[h] > r[k]){ // h is bigger tree
	  p[k] = h; // put tree k under tree h root
	  treeCost[h] = treeCost[h] + treeCost[k] + edgeCost;
  }else{ // k is bigger or they are same
	  p[h] = k; // put tree h under tree k root
	  if(r[h] == r[k]) { r[k]++; } // increase rank if trees were same size before
	  treeCost[k] = treeCost[k] + treeCost[h]+edgeCost;
  }
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int c; cin >> c;
	while(c--){
		int n, m; cin >> n >> m;
		vector<Edge> vE;
		
		p = vector<int>(n,0);
		for(int i = 0; i < n; i++) {p[i] = i;}
		r = vector<int>(n,1);
		treeCost = vector<int>(n,0);
		vector<int> res;
		
		for(int i = 0; i < m; ++i){
			int a,b,e; cin >> a >> b >> e;
			Edge edge;
			edge.from = a; edge.to = b; edge.cost = e;
			vE.push_back(edge);
		}
		sort(vE.begin(),vE.end(),comp);
		
// 		for(int g = 0; g < n; g++) { cout << p[g] << " ";}
// 		cout << endl;
// 		for(int g = 0; g < n; g++) { cout << r[g] << " ";}
// 		cout << endl;
// 		for(int g = 0; g < n; g++) { cout << treeCost[g] << " ";}
// 	
// 		cout << endl;
// 		cout << "size ve "<< vE.size() << endl;
		
		for(int i = 0; i < vE.size();i++) {
// 		  cout << endl << "from: " << vE[i].from << " to" << vE[i].to << endl;
		  int x = findSet(vE[i].from);
		  int y = findSet(vE[i].to);
// 		  cout << endl << "x: " << x << " y" << y << endl;
		  if(x!=y) {
		    unionSet(x,y,vE[i].cost);			
		  }
// 		    for(int g = 0; g < n; g++) { cout << p[g] << " ";}
// 		    cout << endl;
// 		    for(int g = 0; g < n; g++) { cout << r[g] << " ";}
// 		    cout << endl;
// 		    for(int g = 0; g < n; g++) { cout << treeCost[g] << " ";}
// 		    cout << endl;
		}
		
		for(int u = 0; u < n; u++) {
		  int x = findSet(u);
		  res.push_back(x); // put all roots in res
		}
// 		for(int g = 0; g < n; g++) { cout << p[g] << endl;}
// 		for(int g = 0; g < n; g++) { cout << r[g] << endl;}
// 		for(int g = 0; g < n; g++) { cout << treeCost[g] << endl;}
		int min = __INT_MAX__;
		for(int a = 0; a < res.size(); a++){
		  if(min > treeCost[res[a]] && treeCost[res[a]] != 0) { min = treeCost[res[a]];} // find minimum (might be > 1000000)
		}
		int count = 0;
		sort(res.begin(),res.end());
		if(res.size() != 0) {
		  int first = res[0];
		  if(treeCost[first] <= 1000000 && treeCost[first] != 0) {count++;}
		  for(int a = 1; a < res.size(); a++){
		    if(res[a] != first && treeCost[res[a]] <= 1000000 && treeCost[res[a]] != 0) {count++;first = res[a];}
		  }
		}
		cout << count << " " << min << endl;
	}
	return 0;
}