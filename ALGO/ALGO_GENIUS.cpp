#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int C;
int n, k, m;

int L[50];
int pref[10];
double T[50][50];

vector<double> cal() {
	
	double cache[5][50];
	memset(cache, 0, sizeof(cache));

	cache[0][0] = 1.0;

	for(int time = 1; time <= k; time++){
		for (int song = 0; song < n; song++) {
			double& prob = cache[time%5][song];

			prob = 0;

			for (int prev = 0; prev < n; prev++) {
				prob += cache[(time - L[prev] + 5) % 5][prev] * T[prev][song];
			}
		}
	}

	vector<double> ret(n);

	for (int song = 0; song < n; song++) {
		for (int st = k - L[song] + 1; st <= k; st++) ret[song] += cache[st % 5][song];
	}
	return ret;
}

void _init() {
	memset(L, 0, sizeof(L));
	memset(pref, 0, sizeof(pref));
	memset(T, 0, sizeof(T));


}
void _input() {
	cin >> n >> k >> m;

	for (int i = 0; i < n; i++) {
		cin >> L[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> T[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> pref[i];
	}
}
void solve() {


	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		_input();
		vector<double> ans(n);

		ans = cal();

		for (int i = 0; i < m; i++) {
			printf("%.8lf ", ans[pref[i]]);
		}
		cout << "\n";
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}