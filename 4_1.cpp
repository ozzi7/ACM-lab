#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> maidens;
vector<int> princes;
    
bool comp1(int one, int two) {
  return one < two;
}

bool comp2(int one, int two) {
  return one > two;
}
    
int main() { 

    int n,nofPrinces,nofMaiden;  
    //maidens.reserve(100000);
    //princes.reserve(100000);
    cin >> n;
    for(int k = 0; k < n; k++) {
      cin >> nofMaiden;
      cin >> nofPrinces;
      
      // read data
      int t1 = 0;
      maidens.clear();
      princes.clear();

      for (int i = 0; i < nofMaiden; i++) {
	  cin >> t1;
	  maidens.push_back(t1);
      }    
      for (int j = 0; j < nofPrinces; j++) { 
	  cin >> t1;
	  princes.push_back(t1);
      }    
      if(nofPrinces < nofMaiden) {cout << "Impossible!\n";}
      else {
	sort(maidens.begin(), maidens.end(),comp2);
	sort(princes.begin(), princes.end(),comp1);
//     	for(int u = 0; u < nofMaiden; u++) {cout << "\n Maiden: " << maidens[u];}
// 	for(int u = 0; u < nofPrinces; u++) {cout << "\n Princes: " << princes[u];}
	int b; int a; 
	a = 0; b = 0;
	for(a = 0; a < nofMaiden; a++) {
	  if(b < nofPrinces) {
	    if(maidens[a] + princes[b] < 5000) {
	      a--;
	    }
	    b++;
	  }
	  else {
	    a = nofMaiden+1;
	  }
	}
	int sum = 0;
	if(a == nofMaiden) { 
	  for(int q = 0; (q < nofMaiden) && (q < nofPrinces); q++) {
	    sum += princes[(nofPrinces-q)-1];
	  }
	  cout << sum << "\n";
	}
	else {cout << "Impossible!\n";}
// 	cout << "a: " << a << " b: " << b;
// 
// 	cout << "\nnofprinces " << nofPrinces;
// 	cout << "nofmaiden " << nofMaiden;
     }
    }
    return 0;
}
