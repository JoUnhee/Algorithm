#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
int arr[20][20];
bool visit[20];

int ans = 2e9;


void _init() {
	memset(arr, 0, sizeof(arr));
	memset(visit, 0, sizeof(visit));
	ans = 2e9;
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
}
void DFS(int idx, int cnt) {


	if (cnt == N / 2) {
		vector<int> A, B;

		for (int i = 0; i < N; i++) {
			if (visit[i]) A.push_back(i);
			else B.push_back(i);
		}

		int Asum = 0;
		int Bsum = 0;

		for (int i = 0; i < A.size(); i++) {
			int cur = A[i];

			for (int j = 0; j < A.size(); j++) {
				int obj = A[j];
				Asum += arr[cur][obj];
			}
		}
		for (int i = 0; i < B.size(); i++) {
			int cur = B[i];

			for (int j = 0; j < B.size(); j++) {
				int obj = B[j];
				Bsum += arr[cur][obj];
			}
		}

		ans = min(ans, abs(Asum - Bsum));
		return;
	}


	for (int i = idx + 1; i < N; i++) {
		if (visit[i]) continue;

		visit[i] = true;
		DFS(i, cnt + 1);
		visit[i] = false;
	}
}
void solve() {
	_init();
	_input();

	DFS(-1, 0);

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	
	solve();

}