#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<stack>
#include<unordered_map>
using namespace std;

struct street {
  int from;
  int to;
};

// key: visited nodes + last node, target: list of paths already strings
unordered_multimap <string, string> preC; // lookup O(1), map: O(logn)
int start, endNode;
int counter;
int counter2;
vector<street> streets;
vector<int> indices(30); // ith entry points to first street with from node i
vector<int> streetsFromNode(30); // how many streets come from node i
vector<int> visited(30);
vector<int> visitedHelper(30);
vector<string> allPaths;
vector<int> path(30); 
bool comp(street one, street two) {
  if(one.from == two.from) {
    return one.to < two.to;
  }
  return one.from < two.from;
}

bool isStuck(int node) {
  if(node == endNode) {return false;}
  else {
    int count = 0;
    for(int i =indices[endNode]; i < streetsFromNode[endNode]+indices[endNode];i++) {
      if(visited[streets[i].to] && node != streets[i].to) { count++;} // target node is trapped
    }
    if(count == streetsFromNode[endNode]) { return true;}
    for(int k = indices[node]; k < streetsFromNode[node]+indices[node];k++) {
      if(!visitedHelper[streets[k].to]) {
	visitedHelper[streets[k].to] = true;
	if(!isStuck(streets[k].to)) {
	  return false;
	}
      }
    }
  }
  return true;
}

string convertVtoS(int addNode) {
  string temp;
  for(int i = 0; i < 30; i++) {
    temp.append(to_string(visited[i]));
    temp.append(" ");
  }
  temp.append(to_string(addNode));
  return temp;
}
string convertVtoSWithoutAddingNode() {
  string temp;
  for(int i = 0; i < 29; i++) {
    temp.append(to_string(visited[i]));
    temp.append(" ");
  }
  temp.append(to_string(visited[29]));
  return temp;
}
string convertPathtoS() {
  string temp;
  for(int i = 0; i < 30; i++) {
    if(path[i] != -1 && path[i+1] != -1) {
      temp.append(to_string(path[i]));
      temp.append(" "); // todo: check spaces
    }
    else if(path[i] != -1 && path[i+1] == -1) {
      temp.append(to_string(path[i]));
    }
  }
  return temp;
}
void calcSubtree(int node, int depth) {
    // returns number of paths assuming path is fixed up until node
    visitedHelper = visited;
    visitedHelper[node] = true;
    if(isStuck(node)) {
      return; // somehow store this information as well?
    }
    int result = 0;
    visited[node] = true;
    for(int k = indices[node]; k < streetsFromNode[node]+indices[node];k++) {
      // all paths from this node using the free nodes are calculated
      
      
      if(!visited[streets[k].to]) {  
	for(int m = 0; m < allPaths.size(); m++) {
	  cout << allPaths[m] << "\n";
	  }      
      cout << allPaths.size() << ""; 
      
	string tempVisited = convertVtoS(streets[k].to); // string with visited (includes current) + target -> finds all paths starting in next node to endnode
	string tempPath1 = convertPathtoS(); // current path without last node
	string tempPath2;
	
		    cout << "\nvisited: \n";   
	    for (int e = 0; e < 30;e++) {
	      cout << visited[e] << " ";
	    }
	    cout << "\npath: ";
	    for (int e = 0; e < 10;e++) {
	      cout << path[e] << " ";
	    }
	    cout<< "\n\n\n";
	
	
	
	if(preC.find(tempVisited) != preC.end()) { // check if we have seen these node combinations
	  //we have seen these visited nodes and this next node before
	  pair <unordered_multimap <string, string >::iterator, unordered_multimap <string, string >::iterator> range;
	  range = preC.equal_range(tempVisited);
	
	  for(unordered_multimap <string, string >::iterator iter = range.first; iter != range.second; ++iter) {
	    // cycle through elements of bucket
	    // dont call subtree, add current path append all in hashmap of visited+node
// 	    cout << "current node: " << node <<"\n"; 
// 	    cout << "iter->first: \n" << iter->first << "\n";
// 	    cout << "iter->second: " << iter->second << "\n";
// 	    cout << "visited: \n";   
// 	    for (int e = 0; e < 30;e++) {
// 	      cout << visited[e] << " ";
// 	    }
// 	    cout << "\npath: ";
// 	    for (int e = 0; e < 10;e++) {
// 	      cout << path[e] << " ";
// 	    }
// 	    cout << "\npath without last node: " << tempPath1 <<endl;	
//  
// 	        for(int m = 0; m < allPaths.size(); m++) {
// 	  cout << allPaths[m] << "\n";
// 	  }      
//       cout << allPaths.size() << "\n\n\n"; 
// 	

	
	
	    tempPath2 = tempPath1; // current path without last node	  
	    tempPath2.append(" ");tempPath2.append(iter->second); // current path without node, append node and append rest paths ( rest path without current)
	    	    allPaths.push_back(tempPath2);
	    tempPath2 = ""; // reset
	    tempPath2.append(to_string(node)); tempPath2.append(" "); tempPath2.append(iter->second); // temppath2 is path including this node TO target
	    visited[node] = false; //append current, but its not visited
	    preC.insert(make_pair<string,string>(convertVtoS(node),(string)tempPath2)); // insert the paths including this node into set with visited (without current)
	    visited[node] = true;
	  }
	}
	else if(streets[k].to == endNode) { // we found root node, return "" for hash call
	  tempPath2 = tempPath1;
	  if(tempPath2.empty()) {
	    tempPath2.append(to_string(node)); tempPath2.append(" "); tempPath2.append(to_string(endNode)); // = path so far + node + endnode
	  }
	  else {
	    tempPath2.append(" "); tempPath2.append(to_string(node)); tempPath2.append(" "); tempPath2.append(to_string(endNode)); // = path so far + node + endnode
	  }
	  visited[node] = false; // current node not visited for hash
	  string tempXY = to_string(node); tempXY.append(" "); tempXY.append(to_string(endNode));
	  preC.insert(make_pair<string,string>(convertVtoS(node),(string)tempXY)); // insert the paths including this node into set with visited (without current)
	  allPaths.push_back(tempPath2);
	  visited[node] = true; // not needed
	}
	else { // we have never been here, continue normal search
	  path[depth] = node;
	  calcSubtree(streets[k].to, depth+1);
	  path[depth] = -1;
	}
      }
    }
    visited[node] = false;
}
int main() {
    int n,nofCrossings,nofStreets;  
    cin >> n;
    for(int k = 0; k < n; k++) {
      cin >> nofCrossings;
      cin >> nofStreets;
      cin >> start;
      cin >> endNode;
      
      // read data
      int t1,t2;
      streets.clear();
      indices.clear();
      fill(streetsFromNode.begin(), streetsFromNode.end(), 0);
      fill(visited.begin(), visited.end(), false);
      fill(path.begin(), path.end(), -1);
      preC.clear();
      allPaths.clear();
      for (int i = 0; i < nofStreets*2; i=i+2) {	  
	  cin >> t1; cin >> t2;
	  streets.push_back(street());
	  streets[i].from = t1;
	  streets[i].to = t2;
	  // other direction
	  streets.push_back(street());
	  streets[i+1].from = t2;
	  streets[i+1].to = t1;
      }    
      
      sort(streets.begin(), streets.end(), comp);
      
      // create indices
      int currentNode = -1;
      for(int i = 0; i < nofStreets*2; i++){
	if(currentNode != streets[i].from) {
	  currentNode = streets[i].from;
	  indices.push_back(i);
	  streetsFromNode[streets[i].from]++;
	}
	else{streetsFromNode[streets[i].from]++;};
      }  
   
      // calculate and output
      path[0] = start;
      calcSubtree(start,0);
      for(int m = 0; m < allPaths.size(); m++) {
	/*int z = 0;
	int flag = -1;
	for(; z < 29; z++) {
	  if((allPaths[m][z] != -1) && (allPaths[m][z+1] != -1)) {
	    cout << allPaths[m][z] << " ";
	  }
	  else {
	    if(flag == -1) { flag = z;}
	  }
	}
	if(flag == -1){cout << allPaths[m][29] << "\n";}
	else {cout << allPaths[m][flag] << "\n";}*/
	cout << allPaths[m] << "\n";
      }      
      cout << allPaths.size() << "\n"; 
//       	  pair <unordered_multimap <string, string >::iterator, unordered_multimap <string, string >::iterator> range;
// 	  range = preC.equal_range(convertVtoS(start)); // find 00000 -> all paths having 0 visited starting from node 0
// 	
// 	  for(unordered_multimap <string, string >::iterator iter = range.first; iter != range.second; ++iter) {
// 	    cout << iter->second << "\n";
// 	  }
// 	  cout << preC.bucket_size(preC.bucket(convertVtoS(start))) << "\n";
    }
    return 0;
}