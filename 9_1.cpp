#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
	int nofChars,nofChars2;
	cin >> nofChars >> nofChars2;
	vector<char> mainS;
	vector<char> matchS;
	char temp;
	for(int i = 0; i < nofChars; i++) {
	  cin >> temp;
	  mainS.push_back(temp);
	}
	for(int j = 0; j < nofChars2; j++) {
	  cin >> temp;
	  matchS.push_back(temp);
	}
	
	// setup prefix table
	vector<int> prefix = vector<int>(nofChars2,0);
	prefix[0] = 0;
	int k = 0;
	for(int i = 1; i < nofChars2; i++) {
	  while(k > 0 && matchS[i] != matchS[k]) { k = prefix[k-1]; }
	  if(matchS[k] == matchS[i]) { k++; }
	  prefix[i] = k;
	}
	
	vector<int> toDelete = vector<int>(nofChars,0);
	
	int matches = 0;
	int nofMatches = 0;
	for(int k = 0; k < nofChars;k++) {
	  while(matches > 0 && mainS[k] != matchS[matches]) { matches = prefix[matches-1];}
	  if(matchS[matches] == mainS[k]) {matches++;}
	  if(matches == nofChars2) {
	    // found occurrence at k-matches+1 ( first of match)
	    for(int u = k-matches+nofChars2; u >= k-matches+1 && toDelete[u] == 0;u--) {
	      toDelete[u] = 1;
	    }
	    matches = prefix[matches-1];
	    nofMatches++;
	  }
	}
	cout << nofMatches << endl;
	for(int a = 0; a < nofChars; a++) {
	  if(toDelete[a]) cout << "*";
	  else cout << mainS[a];
	}
	cout << endl;
    }
    return 0;
}