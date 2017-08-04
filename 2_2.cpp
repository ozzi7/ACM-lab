#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

struct pair2 {
  int initialM;
  int initialMPrime;
};

int main() {
    int n;  
    cin >> n;
    for(int k = 0; k < n; k++) {   
      int nofdigits = 0;
      int t1 = 0;
      string integerString;
      vector<int> count(10);
      
      cin >> nofdigits;
      cin >> integerString;
      for (int i = 0; i < nofdigits; i++) {
	if(integerString[i] != '\n') {
	  count[integerString[i] - '0']++;
	  count[integerString[i] - '0']++;
	}
      }
      
      // go through all combination of first digits since we dont want 0 at beginning
      vector<pair2> firstNumbers;
      int initialM = 10;
      int initalMPrime = 10;
      for(int z = 1; z < 10; z++) {
	for(int v = z; v < 10; v++) {
	  if(count[z] != 0 && count[v] != 0) {
	    firstNumbers.push_back(pair2());
	    firstNumbers[firstNumbers.size()-1].initialM = z;
	    firstNumbers[firstNumbers.size()-1].initialMPrime = v;
	  }
	}
      }
      
      int max;
      int totalMax = 0;
      vector<int> countOld = count;
      for(int h = 0; h < firstNumbers.size(); h++) { // bruteforce initial numbers max 81 possibilities
	count = countOld;
	count[firstNumbers[h].initialM]--;
	count[firstNumbers[h].initialMPrime]--; // remove from search
	max = 0;
	
	// should only use (0,0) if we get 10 without 0
	// check if 9 is needed for 10, then use more zeros
	bool isWayToGet10With9 = false; // (1,9)
	bool isWayToGet10Without9 = false; // (2,8) (3,7) etc

	if(count[1] >= 1 && count[9] >= 1) {isWayToGet10With9 = true;}
	if(count[2] >= 1 && count[8] >= 1) {isWayToGet10Without9 = true;}
	else if(count[3] >= 1 && count[7] >= 1) {isWayToGet10Without9 = true;}
	else if(count[4] >= 1 && count[6] >= 1) {isWayToGet10Without9 = true;}
	else if(count[5] >= 2) {isWayToGet10Without9 = true;}
	
	if(count[9] >= count[0] && isWayToGet10Without9) { 
	  // dont use (0,0) unless we dont have any other pair than 09 to get 9 (we cant have first 0)
	  // never mind catched at beginning..
	}
	else if(count[9] == count[0] && !isWayToGet10Without9 && isWayToGet10With9) {
	  // we need one of the 9s, we can use one (0,0) (better than use it with a 9)
	  if(count[0] >= 2){
	    max += 1; count[0] = count[0] - 2;
	  }
	}
	else if(count[9] > count[0] && !isWayToGet10Without9 && isWayToGet10With9) { /* dont use any*/}
	else if(!isWayToGet10Without9 && !isWayToGet10With9) {
	  // use all, we are doomed anyway
	  max += count[0] / 2;
	  count[0] = count[0] - max*2; // all 0 are used up
	}
	else if(count[9] < count[0] && isWayToGet10Without9) {
	  // use only the 0s which are too many
	  max += (count[0] - count[9]) / 2;
	  count[0] = count[0] - max*2;
	}
	else if(count[9]+1 < count[0] && !isWayToGet10Without9 && isWayToGet10With9 ) {
	  // use the ones which are too many, we already know there is at least one 9
	  int temp = count[0] - (count[9] -1); // this many 0 can be used
	  max += temp / 2;
	  count[0] = count[0] - max*2;
	}

	// check which number limits a 9 pair
	bool isLimitZero = false;
	bool isLimitOne = false;
	bool isLimitTwo = false;
	bool isLimitThree = false;
	bool isLimitFour = false;
	bool isLimitFive = false;
	bool isLimitSix = false;
	bool isLimitSeven = false;
	bool isLimitEight = false;
	bool isLimitNine = false;
	
	if(count[0] <= count[9]) { isLimitZero = true;}     
	if(count[1] <= count[8]) { isLimitOne = true;}
	if(count[2] <= count[7]) { isLimitTwo = true;}
	if(count[3] <= count[6]) { isLimitThree = true;}
	if(count[4] <= count[5]) { isLimitFour = true;}
	if(count[8] <= count[1]) { isLimitEight= true;}
	if(count[7] <= count[2]) { isLimitSeven = true;}
	if(count[6] <= count[3]) { isLimitSix = true;}
	if(count[5] <= count[4]) { isLimitFive = true;}
	if(count[9] <= count[0]) { isLimitNine = true;}
	
  /*       	            for(int k = 0; k < 10; k++) { cout << count[k] << " ";}
	cout << "\n"*/;  
	// first assuming we dont have to give up any 9 pair, find best one from extra numbers  
	int useIndexI = 10;
	if(!isLimitOne && !isLimitNine && count[9] >= 1 && count[1] >= 1) {useIndexI = 1;}
	else if(!isLimitTwo && !isLimitEight && count[2] >= 1 && count[8] >= 1) {useIndexI = 2;}
	else if(!isLimitThree && !isLimitSeven && count[3] >= 1 && count[7] >= 1) {useIndexI = 3;}
	else if(!isLimitFour && !isLimitSix && count[4] >= 1 && count[5] >= 1) {useIndexI = 4;}
	else if(count[4]+1 < count[5] && count[5] >= 2) {useIndexI = 5;} // we need two 5s

	// we couldn't find an optimal one, but we still need one if there is one, break up only one 10 pair
	if(useIndexI == 10){
	  // we might destroy 2 at once or only 1, choose better
	  if(count[1] >= 1 && count[9] >= 1) {
	    if((isLimitOne && !isLimitNine) || (isLimitNine && !isLimitOne)) {
	      // index 2 destroys only 1
	      useIndexI = 1;
	    }
	  }
	  else if(count[2] >= 1 && count[8] >= 1){
	    if((isLimitTwo && !isLimitEight) || (isLimitEight && !isLimitTwo)) {
	      // index 2 destroys only 1
	      useIndexI = 2;
	    }
	  }
	  else if(count[3] >= 1 && count[7] >= 1){
	    if((isLimitThree && !isLimitSeven) || (isLimitSeven && !isLimitThree)) {
	      // index 3 destroys only 1
	      useIndexI = 3;
	    }
	  }
	  else if(count[4] >= 1 && count[6] >= 1){
	    if((isLimitFour && !isLimitSix) || (!isLimitFour && isLimitSix)) {
	      // index 4 destroys only 1
	      useIndexI = 4;
	    }
	  }
	  else if(count[5] >= 2) {
	    if(count[5] == count[4]+1) {
	      // index 5 destroys only 1
	      useIndexI = 5;
	    }
	  }
	}
	
	// we need to destroy 2 pairs, anyone will do if there is one
	if(useIndexI == 10) {
	  if(count[2] >= 1 && count[8] >= 1){
	    useIndexI = 2;
	  }
	  else if(count[3] >= 1 && count[7] >= 1){
	    useIndexI = 3;
	  }
	  else if(count[4] >= 1 && count[6] >= 1){
	    useIndexI = 4;
	  }
	  else if(count[5] >= 2) {
	    useIndexI = 5;
	  }
	  else if(count[1] >= 1 && count[9] >= 1) {
	    useIndexI = 1;
	  }
	}
	
	if(useIndexI == 10) {
	  // no combination yields 10, max 0 already reached
	}
	else { // generated 10
	  max++;
	  count[useIndexI]--;
	  count[10-useIndexI]--;

	  // fill up rest with 9
	  max += min(count[0], count[9]) + min(count[1],count[8]) + min(count[2],count[7]) +
		min(count[3],count[6]) + min(count[4],count[5]);
	}
	
	//cout << " [" << max << "] ";
	// calculate real number of zero using the initial 2 numbers we took away
	if(max == nofdigits-1) { // all zeros 
	  if(countOld[0]/2 == max && (firstNumbers[h].initialM + firstNumbers[h].initialMPrime == 10)) { // we have all (0,0) and no overflow
	    max++;
	  }
	  else if(firstNumbers[h].initialM + firstNumbers[h].initialMPrime + 1 == 10) {
	    max++;
	  }
	}
	// check if new max found
	if(max > totalMax) {
	  totalMax = max;
	}
      }
      cout << totalMax << endl;
    }
}