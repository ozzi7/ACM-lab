#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int n;  

    cin >> n;
    for(int k = 0; k < n; k++) {
      int totalD;
      int totalGasS;
      int t1,t2;
      vector<int> c,d;
      
      cin >> totalD;
      cin >> totalGasS;
      for (int i = 0; i < totalGasS; i++) {	  
	  cin >> t1; cin >> t2;
	  c.push_back(t1); d.push_back(t2);
      }
      
      // main algorithm
      bool fail;
      int currentTotalCost = 0;
      int currentPosI = 0;
      int currentGas = 100;
      
      int maxTravel = 1000;
      int cheapestGasPrice = __INT_MAX__;
      int cheapestGasI = 0;
      
      int previousGasPrice = 0;
      for(int currentPosI = 0; currentPosI <= totalGasS;) { // go through gas stations (skip to the used ones)
	
	// find cheapest gasstation in reach
	cheapestGasPrice = __INT_MAX__;
	for(int i = currentPosI; i < totalGasS && d[i] <= maxTravel; i++) {
	  if(c[i] <= cheapestGasPrice) {
	    cheapestGasPrice = c[i];
	    cheapestGasI = i;
	  }
	}
	
	// we only want minimum of gas from previous station
	if(previousGasPrice > cheapestGasPrice) {  
	  currentTotalCost += previousGasPrice*(d[cheapestGasI]-d[currentPosI]); //
	}
	else {
	  if(cheapestGasPrice == __INT_MAX__ && maxTravel < d[d.size()-1]) { // we cant reach destination there is no gasstation
	    fail = true;
	  }
	  else if(cheapestGasPrice == __INT_MAX__) {
	    if(maxTravel >= d[d.size()]){}
	    else { currentTotalCost += previousGasPrice*(d[d.size()]-maxTravel);} // 
	  }
	  // we want maximum of previous gas station
	  else{
	    currentTotalCost += previousGasPrice*(100-currentGas);
	  }
	}
	previousGasPrice = cheapestGasPrice;
	currentPosI = cheapestGasI;
	maxTravel += currentGas*10;
      }