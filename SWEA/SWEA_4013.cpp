#include<vector>
#include<iostream>
#include<cstring>

using namespace std;

int T, K;
int ans;
int visit[5];
vector<int> Mag[5];
void _input() {
	cin >> K;

	for (int i = 1; i <= 4; i++) {
		int M;
		for(int j = 0 ; j < 8; j++){
			cin >> M;
			Mag[i].push_back(M);
		}
	}
}
void _init() {
	for (int i = 0; i < 5; i++) Mag[i].clear();
	memset(visit, 0, sizeof(visit));
	ans = 0;
}
void DFS(int num, int dir) {
	if (visit[num] != 0) return;

	visit[num] = dir;
	if (dir == 0) return;

	if (num - 1 >= 1 && visit[num - 1] == 0 && Mag[num - 1][2] != Mag[num][6]) DFS(num - 1, dir * -1);
	if (num + 1 <= 4 && visit[num + 1] == 0 && Mag[num + 1][6] != Mag[num][2]) DFS(num + 1, dir * -1);
}
void rotate(int num, int dir) {
	int tmp = 0;
	if (dir == 0) return;
	else if (dir == 1) {
		tmp = Mag[num][7];
		Mag[num].pop_back();
		Mag[num].insert(Mag[num].begin(), tmp);
	}
	else if (dir == -1) {
		tmp = Mag[num][0];
		Mag[num].erase(Mag[num].begin());
		Mag[num].push_back(tmp);
	}
}
void count() {
	for (int i = 1; i <= 4; i++) {
		ans += (Mag[i][0] * (1 << i - 1));
	}
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);
	
	cin >> T;

	for (int t = 1; t <= T; t++) {
		_init();
		_input();

		for (int k = 0; k < K; k++) {
			int num, dir;
			
			cin >> num >> dir;
			DFS(num, dir);
			for (int i = 1; i <= 4; i++) rotate(i, visit[i]);
			memset(visit, 0, sizeof(visit));
		}
		count();

		cout<<"#"<<t<<" " << ans << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}