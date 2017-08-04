#include <iostream>
#include <algorithm>
#include "assert.h"
#include <stdexcept>

using namespace std;
int gcd(int a, int b) {
  int c = a % b;
  while(c != 0) {
    a = b;
    b = c;
    c = a % b;
  }
  return b;
}
int main() {
    int n, width,small,big;
    long long lcm;
    int nofbig = 0;
    cin >> n;
    for (int i = 0; i < n; i++) { // go through cases	  
	cin >> width;
	cin >> small;
	cin >> big;
	
	nofbig = 0;
	lcm = ((long long)big) * ((long long)small);
	lcm = lcm/((long long)gcd(big,small));
	long long div = ((long long)width) /lcm;
	if(div >= 1) {
	  nofbig = (((div-1)*lcm)/big);
	  width = (width - ((div-1)*lcm)); // might not change anything
	}
	// bruteforce rest
	int bestRest = __INT_MAX__;
	int bestnofbig = 0;
	int bestnofsmall = 0;
	if(width % big == 0) {
	  cout << 0 << " " << (nofbig + (width/big)) << " " << 0 << endl;
	}
	else {
	  for(int i = (width/big); i>=0; i--) { // max i big
	      int temp = (width - (i*big));
	      int j = temp/small; // max j small
	      int temp2 = temp - (j*small);
	      if(temp2 < bestRest) { // new best
		bestRest = temp2;
		bestnofbig = i;
		bestnofsmall = j;
	      }
	    }
	    if(bestRest != __INT_MAX__) {
	      cout << bestnofsmall << " " << (nofbig + bestnofbig) << " " << bestRest << endl;
	    }
	    else {
	      cout << 0 << " " << 0 << " " << width << endl;
	    }
	}
    }
    return 0;
}