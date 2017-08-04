#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, t;
    int sum, o, e;
    int temp;
    vector<int> a;

    // nof numbers
    cin >> n;
    o = 0; e = 0; sum = 0;
    for (int i = 0; i < n; i++) {	  
	cin >> t;
	if(t == 0) {
	  sum += 1 + e;
	  e++;
	}
	else {
	  sum += o;
	  temp = o;
	  o = e;
	  e = temp;
	  o++;
	}
    }
    cout << sum << endl;
    
    return 0;
}
