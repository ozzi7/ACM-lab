#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        int nofCoins,coin;
        cin >> nofCoins;
	vector<vector<int> > coins = vector<vector<int> >(nofCoins,vector<int>(nofCoins,0));
	
	// read coins
        for(int i = 0 ; i <nofCoins; i++) {
	  cin >> coin;
	  coins[0][i] =coin; // fill first row
	}
	
	for(int i = 0; i < nofCoins-1; i++) { // fill second row
	  coins[1][i] = max(coins[0][i],coins[0][i+1]);
	}		
		
	for(int row = 3-nofCoins%2; row < nofCoins; row = row + 2) {
	  for(int col = 0; col < nofCoins-row; col++) {
	    
	    coins[row][col] = max(coins[0][col]+min(coins[row-2][col+1],coins[row-2][col+2]),
				  coins[0][col+row] + min(coins[row-2][col],coins[row-2][col+1]));
	  }
	}
// 		for(int row = 0; row < nofCoins; row++) {
// 	  for(int col = 0; col < nofCoins; col++) {
// 	    cout << coins[row][col] << " ";
// 	  }
// 	  cout << endl;    }
		
	cout << coins[nofCoins-1][0] << endl;
    }
    return 0;
}