#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string line;
int pos = 0;
int gridSize = 0;
struct Point {
  // x holds S[i] and y is basically R0, R1,..
  int x,y;
};
Point resultH;
Point resultV;
vector<vector<Point> > SRLines;
vector<Point> SR;
vector<string> grid;
	
// compares only 1 character
bool comp1(Point a, Point b) {
  // 2 overflows not possible we only sort elements that need sorting
  if(pos + a.x > gridSize) {
    return false; // if overflow with index A then index B comes before
  }
  else if(pos + b.x > gridSize) {
    return true; // overflow with index B so A comes first
  }
  else if(line[pos + a.x]-line[pos + b.x] == 0) {
    // no overflow, equal chars, return the shorter string
    return (a.x > b.x);
  }
  else {
    // no overflow, we can actually sort lexographically
    return (line[pos + a.x] - line[pos + b.x] < 0);
  }
}
bool contains(string in, string what) {
      bool match = true;
  if(in.size() < what.size())
    return false;
  else {
    for(int i = 0;i < what.size(); i++) {
      if(in[i] == what[i]){}
      else{
	match = false;
      break;
      }
    }
  }
  return match;
}
int compString(string one, string two, int currentIndex) {
  // return if one comes before two
   //cout << "Comparing: " << one << " with " << two << endl;
  int maxIndex = max(one.size(), two.size());
  for(int i = 0; i < maxIndex; i++) {
    if(one[i]-two[i] < 0){ return -1;}
    else if(one[i]-two[i] >0 ){return 1;}
   }
   if(one.size() > two.size())
     return 1;
   else  { // match.. find best match
     if(pos < gridSize) {
      //cout << "H " << pos+1 << " " << SRLines[pos][min].x+1 << endl;
       currentIndex++;
             if(currentIndex != gridSize) {
      while(contains(grid[pos].substr(SRLines[pos][currentIndex].x,(gridSize-(SRLines[pos][currentIndex].x))),one)) {currentIndex++;if(currentIndex == gridSize) break;} // sequential search for longest match
	     }
      currentIndex--;
      resultH.y = pos+1;
      resultH.x = SRLines[pos][currentIndex].x+1;
      return 0;
    }
    else {
      currentIndex++;
      if(currentIndex != gridSize) {
      while(contains(grid[pos].substr(SRLines[pos][currentIndex].x,(gridSize-(SRLines[pos][currentIndex].x))),one)) {currentIndex++; if(currentIndex == gridSize) break;} // sequential search for longest match
      }
      currentIndex--;
      resultV.y = SRLines[pos][currentIndex].x+1;
      resultV.x = pos+1-gridSize;
      //cout << "V " << SRLines[pos][min].x+1 << " " << pos+1-gridSize << endl;
    return 0; }
   }
}

bool binSearch(int pos, int min, int max, string word) {
   cout << "Min: " << min << " Max: " << max << endl;
  if(min != max) {
    if(compString(word, grid[pos].substr(SRLines[pos][(min+max)/2].x,(gridSize-(SRLines[pos][(min+max)/2].x))),(min+max)/2) == -1) {
           // cout << SRLines[pos][(min+max)/2].x << " " << (gridSize-(SRLines[pos][(min+max)/2].x)) << endl;
      return binSearch(pos, min, (min+max)/2-1,word);
    } else if(compString(word, grid[pos].substr(SRLines[pos][(min+max)/2].x,(gridSize-(SRLines[pos][(min+max)/2].x))),(min+max)/2) == 1){
            //cout << "debug" << endl;
      // cout << SRLines[pos][(min+max)/2].x << " " << (gridSize-(SRLines[pos][(min+max)/2].x)) << endl;
      return binSearch(pos, (min+max)/2+1, max, word);
    }
    else if(compString(word, grid[pos].substr(SRLines[pos][(min+max)/2].x,(gridSize-(SRLines[pos][(min+max)/2].x))),(min+max)/2) == 0) {
      return true; // already found match
    } 
  }
  return false;
}
void binSearcher(string word) {
  // search second half of SRLines first (vertical)
  resultH.y = -1; resultH.x = -1; resultV.x = -1; resultV.y = -1;
  for(int i = SRLines.size()/2; i < SRLines.size(); i++) {
//     cout << "SEARCH: " << i << endl;
    if(binSearch(i,0,gridSize-1,word))
    {break;}
  }
  
  for(int i = 0; i < SRLines.size()/2; i++) {
//           cout << "SEARCH: " << i << endl;
    if(binSearch(i,0,gridSize-1,word))
      break;
  }
  
  if(resultH.y != -1 && resultV.y != -1) {
    // vertical and horizontal match
    if(resultH.y < resultV.y) {
      cout << "H " << resultH.y << " " << resultH.x << endl;
    }
    else if(resultH.y > resultV.y) {
      cout << "V " << resultV.y << " " << resultV.x << endl;
    }
    else {
      if(resultH.x < resultV.x) {
	cout << "H " << resultH.y << " " << resultH.x << endl;
      }
      else {
	cout << "V " << resultV.y << " " << resultV.x << endl;
      }
    }
  }
  else if(resultH.y != -1) {
    cout << "H " << resultH.y << " " << resultH.x << endl;
  }
  else if(resultV.y != -1) {
    cout << "V " << resultV.y << " " << resultV.x << endl;
  }
  
}
int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while (t--) {
	int nofWords;
	cin >> gridSize >> nofWords;
	
	vector<string> words;
	SRLines.clear();
	SR.clear();
	grid.clear();
	pos = 0;
	
	string tempS;	
	// read words
	for(int i = 0; i < nofWords; i++) {
	  cin >> tempS;
	  words.push_back(tempS);
	}
	// read grid
	for(int j = 0; j < gridSize; j++) {
	  cin >> tempS;
	  grid.push_back(tempS);
	}
	
	// calculate vertical grid from horizontal grid
	for(int j = 0; j < gridSize; j++) {
	  string t = "";
	  for(int k = 0; k < gridSize; k++) {
	    t += grid[k][j];
	  }
	  grid.push_back(t);
	}
		
	// main algo, runs for each line in grid
	for(int f = 0; f < gridSize*2; f++) {
	  line = grid[f];
	  // setup S in SR
	  SR.clear();
	  for(int i = 0; i < gridSize; i++) {
	    Point a; a.x = i; a.y = 0;
	    SR.push_back(a);
	  }
	  
	  pos = 0;
	  sort(SR.begin(), SR.end(), comp1);
	  
	  // calculate R0, R1, etc until done
	  for(int u = 0; u < gridSize-1; u++) {
	    // check what needs to be sorted again
	    int count = 0;
	    SR[0].y = 0;
	    for(int i = 1; i < gridSize; i++) {
	      if(SR[i].x + u < gridSize && SR[i-1].x + u < gridSize) {
		  if(line[SR[i].x+u] == line[SR[i-1].x+u]) {
		    // we need to sort them further
		    SR[i].y = count;
		  } else {
		    // already sorted
		    count++; SR[i].y = count;
		  }
	      }
	      else {
		// one of them has no character at this position so already sorted
		count++; SR[i].y = count;
	      }
	    }
	    
	    pos = u+1; // for next sort cycle to know which character we are at
	    // sort again
	    int indexS = 0; 
	    int indexE = 1;
	    while(indexE < gridSize) {
	      if(SR[indexS].y == SR[indexE].y) {
		indexE++;
	      } else if(indexE-indexS > 1){
		sort(SR.begin() + indexS, SR.begin()+ indexE-1, comp1);
		//cout << "Sorting: " << "line " << f << " from " << indexS << " to " << indexE-1 << endl;
		indexS = indexE;
		indexE = indexE+1;
	      }
	      else {
		indexS = indexE;
		indexE = indexE+1;
	      }
	    }
	    if(indexE -indexS >1) {
		sort(SR.begin() + indexS, SR.end(), comp1);
		//cout << "Sorting: " << "line " << f << " from " << indexS << " to " << gridSize << endl;
	    }
	  }
	  SRLines.push_back(SR);
	}
	
	// debug
// 	for(int r = 0; r < SRLines.size();r++)
// 	{
// 	  for(int a = 0; a < gridSize; a++) {
// 	    cout << SRLines[r][a].x << " ";
// 	  }
// 	  cout << endl;
// 	}
// 	cout << endl;
	
	// check if solution exists
	for(int d = 0; d < nofWords;d++) {
// 	  cout << "Word: " << d << endl;
	  binSearcher(words[d]);
	}
    }
    return 0;
}