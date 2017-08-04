#include<iostream>
#include<vector>
#include<algorithm>
#include<limits.h>
using namespace std;

struct wizard {
  int len;
  int pos;
};

bool comp(wizard one, wizard two) {
    return (one.pos < two.pos);
}

int main() {
    int n;  
    vector<wizard> wizVector;
    
    cin >> n;
    for(int k = 0; k < n; k++) {
      int nofwizards,t1,t2;
      wizVector.clear();
      
      cin >> nofwizards;
      for (int i = 0; i < nofwizards; i++) {	  
	  cin >> t1; cin >> t2;
	  wizVector.push_back(wizard());
	  wizVector[i].len = t1;
	  wizVector[i].pos = t2;
      }
      
      sort(wizVector.begin(), wizVector.end(), comp);

      // main algorithm     
      int maxOccupied = wizVector[0].pos;
      int maxPrevious = INT_MIN;
      int maxW = 1;
      for(int j = 1; j < wizVector.size(); j++) {
	if(wizVector[j].pos >= maxOccupied) { // take new
	  if(maxOccupied + wizVector[j].len <= wizVector[j].pos) {
	    // most left shifted
	    maxPrevious = maxOccupied;
	    maxOccupied = wizVector[j].pos;
	  }
	  else {
	    maxPrevious = maxOccupied;
	    maxOccupied = maxOccupied + wizVector[j].len;
	  }
	  maxW++;
	}
	else { // check if replace old
	  if(maxPrevious + wizVector[j].len <= wizVector[j].pos) { // we can fit it left shifted
	    if(wizVector[j].pos <= maxOccupied) { // its better than best
	      maxOccupied = wizVector[j].pos;
	    }
	    else {}
	  }
	  else { // we cant left shift it completely
	    if(maxPrevious + wizVector[j].len <= maxOccupied) {
	      maxOccupied = maxPrevious + wizVector[j].len;
	    }
	  }
	}
      }
      cout << maxW << endl;
    }
    return 0;
}
