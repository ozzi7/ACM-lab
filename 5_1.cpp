#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int nofCoins,nofTests;
        cin >> nofCoins >> nofTests;
	vector<int> coins;
	vector<int> tests;
	coins.clear();
	tests.clear();
	int test,coin;
	
	// read coins
        for(int i = 0 ; i <nofCoins; i++) {
	  cin >> coin;
	  coins.push_back(coin);
	}
	// read tests
	for(int i = 0 ; i <nofTests; i++) {
	  cin >> test;
	  tests.push_back(test);
	}
	int size = *max_element(begin(tests),end(tests))+1;
	vector<int> v = vector<int> (size,0);
	
	//for(int s = 0; s < v.size(); s++) { cout << v[s] << " ";}
	//fill out array
	for(int i = 1; i < size; i++) {
	  vector<int> temp;
	  temp.clear();
	  for(int z = 0; z < nofCoins; z++) {
	    if((i - coins[z]) > 0) {
	      if(v[i-coins[z]] != 0) {
		temp.push_back(v[i-coins[z]]);
	      }
	    }
	    else if((i - coins[z]) == 0) {
	      temp.push_back(v[i-coins[z]]);
	    }
	  }/*
	  	for(int s = 0; s < v.size(); s++) { cout << v[s] << " ";}
	  	cout << "\n";*/
	  if(temp.size() != 0) {
	    v[i] = 1+ (*min_element(begin(temp), end(temp)));
	  }
	  else {
	    v[i] = 0;
	  }
	}
	
	//output
	for(int u = 0 ; u <nofTests; u++) {
	  if(v[tests[u]] != 0) { cout << v[tests[u]] << "\n";}
	  else {cout << "not possible" << "\n";}
	}
    }
    return 0;
}