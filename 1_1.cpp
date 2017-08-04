#include<iostream>

using namespace std;

int main() {
    int n, count;
    float temp;

    // nof testcases
    cin >> n;
    for (int i = 0; i < n; i++) {	  
	float sum = 0;
	cin >> count;
	for (int j = 0; j < count; j++) {
	  cin >> temp;
	  sum += temp;
	}
	cout << sum << endl;
    }
    return 0;
}
