#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

bool cmp(int A, int B) {
	return A < B;
}

int main() {
	
	int n = 0;
	
	vector<int> rusia = {3000,2700,2800,2200,2500,1900};
	vector<int> korea = {2800,2750,2995,1800,2600,2000};
	
	n = rusia.size();
	
	sort(rusia.begin(), rusia.end(), cmp);
	sort(korea.begin(), korea.end(), cmp);

	int ko = 0;
	int ru = 0;
	int win = 0;

	while (ko < n && ru <n) {
		int& KO = korea[ko];
		int& RU = rusia[ru];

		if (KO > RU) {
			win++;
			ru++;
		}
		ko++;
	}

	cout << win << endl;
}