#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int patternSize = 0;
int countOnes(int a) {
	int count = 0;
	for(int i = 0; i < patternSize; i++) {
		if(a & 1 == 1) {
			count++;
		}
		a = a >> 1;
	}
	return count;
}

int countSingles(int first, int x) {
	// counts single light bulbs to be switched
	first = first^x;
	return countOnes(first);
}

int main() {
    int n;
    cin >> n;
    while(n--) {
    	int nofBulbs,x;
    	cin >> nofBulbs >> patternSize >> x;
    	vector<int> state = vector<int>((nofBulbs/patternSize)*2,0); // 0 normal 1 flipped

		bool flipped = true;
		for(int k = 0; k < nofBulbs/patternSize; k++) {
			int bulbPattern = 0;
			// read bulb pattern
			for(int i = 0; i < patternSize; i++) {
				int bulb;
				cin >> bulb;
				bulbPattern = bulbPattern*2+ bulb;
			}
		   //cout << bulbPattern <<endl;
			int invBulbPattern = ~bulbPattern;
			if(k > 0) {
				state[k*2] = min(countSingles(bulbPattern,x) + state[(k-1)*2],countSingles(bulbPattern,x)+state[(k-1)*2+1]);
				if(flipped) {
				  if(countSingles(invBulbPattern, x) + state[(k-1)*2+1] <= 1+countSingles(invBulbPattern, x)+state[(k-1)*2]) {
					 state[k*2+1] = countSingles(invBulbPattern, x) + state[(k-1)*2+1];
					 flipped = true;
				  }
				  else {
					 state[k*2+1] = 1+countSingles(invBulbPattern, x)+state[(k-1)*2];
					 flipped = false;
				  }
				}
				else {
				  if(countSingles(invBulbPattern, x) + state[(k-1)*2+1] <= countSingles(invBulbPattern, x)+state[(k-1)*2]) {
					 state[k*2+1] = countSingles(invBulbPattern, x) + state[(k-1)*2+1];
					 flipped = true;
				  }
				  else {
					 state[k*2+1] = countSingles(invBulbPattern, x)+state[(k-1)*2];
					 flipped = false;
				  }
				}
			}
			else {
				state[k*2] = countSingles(bulbPattern,x);
				state[k*2+1] = 1+countSingles(invBulbPattern, x);
			}
			cout << state[k*2] << "/" << state[k*2+1]  << endl;
		}
		cout << min(state[(nofBulbs/patternSize)*2-2],state[(nofBulbs/patternSize)*2-1]) << endl;
    }
    return 0;
}
