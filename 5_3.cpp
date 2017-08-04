#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    while (n--) {
        int numberCount;
	int step;
        cin >> numberCount;
	cin >> step;
	vector<int> numbers = vector<int> (numberCount,0);
	vector<long long> result = vector<long long>(numberCount,0);
	int number;
	
        for(int i = 0 ; i <numberCount; i++) {
	  cin >> number;
	  numbers[i] = number;
	}
		
	long long minIndex = 0;
	vector<long long>::iterator minIndexIter;
	result[0] = 0;
	for(int i = 1; i < numberCount; i++) {
	  if(i - step > minIndex) { // we went past min index
	    // find new min
	    minIndexIter = min_element(result.begin()+(i-step),result.begin() + i);
	    minIndex = minIndexIter - result.begin();
	  }
	  else if(result[i-1] < result[minIndex]) { // the new element in range is smallest
	    minIndex = i-1;
	  }
	  result[i] = result[minIndex] + numbers[i];
	}

	cout << result[numberCount-1] << "\n";

    }
    return 0;
}