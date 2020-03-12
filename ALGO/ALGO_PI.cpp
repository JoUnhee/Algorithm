#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
string input;
int cache[10001];
int check(int st, int howmany) {
	vector<int> q;

	for (int i = st; i < st + howmany; i++) {
		q.push_back(input[i] - '0');
	}
	int dif = q[1] - q[0];
	bool flag = false;
	for (int idx = 2; idx < howmany; idx++) {
		if (dif == q[idx] - q[idx - 1]) flag = true;
		else { 
			flag = false; 
			break;
		}
	}
	if (flag) {
		if (dif == 0) return 1;
		if (dif == 1 || dif == -1) return 2;
		if (dif > 1 || dif < -1) return 5;
	}
	
	int num1 = q[0];
	int num2 = q[1];

	flag = false;

	for (int idx = 2; idx < howmany; idx++) {
		if (q[idx - 1] == num1 && q[idx] == num2) flag = true;
		else if (q[idx - 1] == num2 && q[idx] == num1) flag = true;
		else {
			flag = false;
			break;
		}
	}
	if (flag) return 4;

	return 10;
}
int DFS(int idx) {
	
	if (idx >= input.size()) {
		return 0;
	}
	int& ret = cache[idx];
	if (ret != -1) return ret;
	ret = 9876543231;

	for (int i = 3; i <= 5; i++) {
		if (idx + i <= input.size()) {
			ret = min(ret, DFS(idx + i) + check(idx, i));
		}
	}
	return ret;
}
int main() {
	memset(cache, -1, sizeof(cache));
	cin >> input;
	cout << DFS(0) << endl;
}