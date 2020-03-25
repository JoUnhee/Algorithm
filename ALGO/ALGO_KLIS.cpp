#include<algorithm>
#include<vector>
#include<iostream>
#include<cstring>

using namespace std;

const int MAX = 2000000000 + 1;

int n;
int C;
int k;


int cacheLen[501];
int cacheCnt[501];
int S[500];



int lis(int start) {
	int& ret = cacheLen[start + 1];

	if (ret != -1) return ret;

	ret = 1;

	for (int next = start + 1; next < n; next++) {
		if (start == -1 || S[start] < S[next]) ret = max(ret, lis(next) + 1);
	}
	return ret;
}
int count(int start) {

	if (lis(start) == 1) return 1;
	int& ret = cacheCnt[start + 1];

	if (ret != -1) return ret;

	ret = 0;

	for (int next = start + 1; next < n; next++) {
		if((start == -1 || S[start] < S[next]) && (lis(start) == lis(next) + 1)){

			ret = min<long long>(MAX, (long long)ret + count(next));
		}
	}
	return ret;
}
void reconst(int start, int skip, vector<int>& list) {
	if (start != -1) list.push_back(S[start]);

	vector<pair<int, int>> follwer;

	for (int next = start + 1; next < n; next++) {
		if ((start == -1 || S[start] < S[next]) && (lis(start) == lis(next) + 1)) 
			follwer.push_back({ S[next] , next });
	}

	sort(follwer.begin(), follwer.end());

	for(int i = 0; i < follwer.size(); i++){
		int idx = follwer[i].second;
		int cnt = count(idx);

		if (cnt <= skip) skip -= cnt;
		else {
			reconst(idx, skip, list);
			break;
		}

	}
}

void _input(){

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		cin >> S[i];
	}


}
void _init() {
	memset(cacheLen, -1, sizeof(cacheLen));
	memset(cacheCnt, -1, sizeof(cacheCnt));
	memset(S, -1, sizeof(S));

}
void print(vector<int>& lis) {

	for (int i = 0; i < lis.size(); i++) {
		printf("%d ", lis[i]);
	}
	printf("\n");
}
void _solve() {

	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		_input();

		lis(-1);
		count(-1);
		vector<int> ans;
		int skip = k - 1;

		cout << lis(-1) - 1 << endl;

		reconst(-1, skip, ans);

		print(ans);
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_solve();
}

