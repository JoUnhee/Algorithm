#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
typedef struct Person {
	int x;
	int y;
	int length;

};

int T, N;
int map[10][10];
Person P[10];
Person S[10];

int ret;
int Scnt;
int Pcnt;
void _init() {
	memset(map, 0, sizeof(map));
	memset(S, 0, sizeof(S));
	memset(P, 0, sizeof(P));
	Pcnt = Scnt = 0;
	ret = 987654321;
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];

			if (map[i][j] == 1) {
				P[Pcnt].y = i;
				P[Pcnt].x = j;
				Pcnt++;
			}
			else if (map[i][j] >= 2) {
				S[Scnt].length = map[i][j];
				S[Scnt].y = i;
				S[Scnt].x = j;
				Scnt++;
			}
		}
	}
}
int simul(int state) {
	for (int p = 0; p < Pcnt; p++) {
		int step = (state >> p) & 1;
		int x = P[p].x;
		int y = P[p].y;

		int arrive = abs(x - S[step].x) + abs(y - S[step].y);
		P[p].length = arrive;
	}

	int t = 0;
	bool flag = false;
	int maxTime = 0;
	int stair[2][400];
	memset(stair, 0, sizeof(stair));

	while (t < 400) {
		for (int p = 0; p < Pcnt; p++) {

			if (t == P[p].length) {
				int step = (state >> p) & 1;
				int cursor = P[p].length+1;

				while (stair[step][cursor] >= 3) cursor++;

				for (int Tc = cursor; Tc < cursor + S[step].length; Tc++) {
					stair[step][Tc] ++;
					maxTime = max(maxTime, Tc);
				}
			
			}
			
		}
		t++;
	}


	return maxTime+1;
}
void DFS(int depth, int state) {
	if (depth >= Pcnt) {
		ret = min(ret, simul(state));
		return;
	}
	else {
		DFS(depth + 1, state);
		DFS(depth + 1, state |= (1 << depth));
	}
}
void solve() {

	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
	
		_init();
		_input();
		DFS(0,0);
		cout << "#"<< t<< " "<<  ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}