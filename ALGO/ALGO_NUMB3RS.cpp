#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int C, N, D, P, T, Q;

double Arr[50][50];
double cache[100][50];

int arr[50][50];

double ans;
void _init() {
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			Arr[i][j] = 0.0;
		}
	}
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 50; j++) {
			cache[i][j] = -1.0;
		}
	}
	memset(arr, 0, sizeof(arr));

	ans = 0.0;
}
void _input() {
	cin >> N >> D >> P;

	for (int i = 0; i < N; i++) {
		int cnt = 0;

		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 1) {
				cnt++;
			}
		}
		for (int j = 0; j < N; j++) {
			if (arr[i][j] == 1) {
				Arr[i][j] = 1.0 / cnt;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		cache[0][i] = Arr[P][i];
	}
}
double Cal(int day, int site) {
	

	if (day == 1) {
		return Arr[P][site];
	}
	double& ret = cache[day][site];
	
	if (ret != -1.0) return ret;

	ret = 0.0;

	for (int k = 0; k < N; k++) {
		if(k != site && arr[k][site] != 0) ret += (Arr[k][site] * Cal(day - 1, k));
	}

	return ret;
}
void solve() {

	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		_input();

		cin >> T;
		vector<double> ret;
		for (int i = 0; i < T; i++) {
			int obj;
			cin >> obj;

			ret.push_back(Cal(D, obj));
		}

		for (int i = 0; i < ret.size(); i++) {
			printf("%.8f ", ret[i]);
		}
		printf("\n");
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
	
}