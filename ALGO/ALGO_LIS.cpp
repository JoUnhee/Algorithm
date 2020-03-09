#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

vector<int> S;
int cache[100];

int DFS(int cur) {
	int& ret = cache[cur];

	if (ret != -1) return ret;
	ret = 1;

	for (int idx = cur + 1; idx < S.size(); idx++) {
		if (S[cur] < S[idx]) {
			ret = max(ret, DFS(idx) + 1);
		}
	}
	return ret;
}
int main() {

	int size = 0;

	cin >> size;

	for (int i = 0; i < size; i++) {
		int num;
		cin >> num;
		S.push_back(num);
	}

	memset(cache, -1, sizeof(cache));

	int maxL = 0;

	for (int i = 0; i < size; i++) {
		maxL = max(maxL, DFS(i));
	}

	cout << maxL << endl;
	return maxL;
}