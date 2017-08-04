#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<stack>
using namespace std;

int main() {
    int num;
    int n;
    vector<int> rows;
    cin >> num;
    for(int i = 0; i < num; i++) {
      cin >> n;
      rows.clear();
      rows.resize(n+1);
      if(n== 2 || n == 3) {
	cout << "Impossible\n";
      }
      else if(n == 4) {
	rows[1] = 2;
	rows[2] = 4;
	rows[3] = 1;
	rows[4] = 3;
	for(int l = 1; l < rows.size()-1; l++) {
	  cout << rows[l] << " ";
	}
	cout << rows[rows.size()-1];
	cout << "\n";
      }
      else if(n == 1) {
	cout << 1 << "\n";
      }
      else {
	if(n%2 == 0 && ((n-2) % 6 != 0)) {
	  for(int k = 1; k <= n/2; k++) {
	    rows[k]=(k*2);
	  }
	  for(int k = n/2+1; k <= n; k++) {
	    rows[k]=(((2*k)-n)-1);
	  }
	}
	else if(n%2 == 0 && ((n-2)%6 == 0)) {
	  for(int k = 1; k <= n/2; k++) {
	    rows[k]=(2*k+(n/2)-3)%n + 1;
	  }
	  for(int k = n/2+1; k <= n; k++) {
	    rows[k] = n-(2*(n-k+1)+(n/2)-3)%n;
	  }
	}
	else {
	  n--;
	  if(n%2 == 0 && ((n-2) % 6 != 0)) {
	    for(int k = 1; k <= n/2; k++) {
	      rows[k]=(k*2);
	    }
	    for(int k = n/2+1; k <= n; k++) {
	      rows[k]=(((2*k)-n)-1);
	    }
	  }
	  else if(n%2 == 0 && ((n-2)%6 == 0)) {
	    for(int k = 1; k <= n/2; k++) {
	      rows[k]=(2*k+(n/2)-3)%n + 1;
	    }
	    for(int k = n/2+1; k <= n; k++) {
	      rows[k] = n-(2*(n-k+1)+(n/2)-3)%n;
	    }
	  }
	  rows[n+1] = n+1;
	}
	for(int l = 1; l < rows.size()-1; l++) {
	  cout << rows[l] << " ";
	}
	cout << rows[rows.size()-1];
	cout << "\n";
      }
    }
    return 0;
}