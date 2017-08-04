#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
#include<stack>
using namespace std;

struct cNumber {
  int numb;
  int coolness;
};

vector<int> tempvalidNumbers;
vector<int> possibleLowPer; // valid lower
     
bool comp (cNumber one, cNumber two) {
  if(one.coolness == two.coolness) { return one.numb < two.numb;}
  return one.coolness > two.coolness;
}

bool checkkkker(int i) {
  for(int multiplier = 2; multiplier <= 98765/tempvalidNumbers[i]; multiplier++) {
    if(possibleLowPer[multiplier*tempvalidNumbers[i]]) {
      return true;
    }
  }
}
int main() {
    int n;
    vector<cNumber> testset;
    vector<int> validNumbers;
    // generate all lower permutations
    int f1,f2,f3,f4,f5;
    int temp;

    for(int z = 0; z <= 99999; z++) {
      temp = z;
      f1 = z%10; temp = z/10;
      f2 = temp%10; temp = temp/10;
      f3 = temp%10; temp = temp/10;
      f4 = temp%10; temp = temp/10;
      f5 = temp%10; temp = temp/10;
      if(f1 != f2 && f1 != f3 && f1 != f4 && f1 != f5 && f2 != f3 && f2 != f4 && f2 != f5
	&& f3 != f4 && f3 != f5 && f4 != f5) {
	possibleLowPer.push_back(1);
	tempvalidNumbers.push_back(z);
      }
      else {
	possibleLowPer.push_back(0);
      }
    }
    
    for(int i = 0; i < tempvalidNumbers.size(); i++) {
      // only add to validNumbers if there is a multiple which is also valid
      if(checkkkker(i)) {
	validNumbers.push_back(tempvalidNumbers[i]);
      }
    }
    
    
    cin >> n;
    for(int k = 0; k < n; k++) {
      int noftests;
      int t1;
      cin >> noftests;
      testset.clear();
      for(int m = 0; m < noftests; m++) {
	cin >> t1;
	testset.push_back(cNumber());
	testset[m].numb = t1;
	testset[m].coolness = 0;
      }
      // find coolest number in testset
      for(int u = 0; u < testset.size(); u++) {   // go through input numbers 
	for(int c = 0; c < validNumbers.size();c++) { // check all multiples
	    int temp2 = validNumbers[c]*testset[u].numb;
	    if(!(temp2 < 1234)) { // check if valid range
	      if(!(temp2 > 98765)) { // break if too high
		if(possibleLowPer[temp2]) { // check if 5 diff. digits
		  // check if digits different from lower
		  int myints[] = {0,1,2,3,4,5,6,7,8,9};
		  int temp = validNumbers[c];
	  
		  // delete used digits from digits
		  for(int j = 0; j < 5; j++) {
		    myints[temp%10] = -1;
		    temp = temp/10;
		  }
		  // check if temp2 is valid number
		  int f1,f2,f3,f4,f5;
		  f1 = temp2%10; temp2 = temp2/10;
		  f2 = temp2%10; temp2 = temp2/10;
		  f3 = temp2%10; temp2 = temp2/10;
		  f4 = temp2%10; temp2 = temp2/10;
		  f5 = temp2%10; temp2 = temp2/10;
		  if(myints[f1] != -1 && myints[f2] != -1 && myints[f3] != -1  && myints[f4] != -1 
		    && myints[f5] != -1) {
		    testset[u].coolness++;
		  }
		}
	      }
	      else {
		c = validNumbers.size();
	      }
	    }
	  }
	}
	sort(testset.begin(), testset.end(), comp);
	cout << testset[0].numb << " " << testset[0].coolness << "\n";
    } 
    return 0;
}