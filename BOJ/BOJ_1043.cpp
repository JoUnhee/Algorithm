#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

int N, M;
int cache[51][2];
bool truth[51];
vector<int> attendee[51];
int ans;

void _input() {
	cin >> N >> M;

	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		int idx;
		cin >> idx;
		truth[idx] = true;
	}

	for (int i = 0; i < M; i++) {
		cin >> num;
		for (int j = 0; j < num; j++) {
			int P;
			cin >> P;
			attendee[i].push_back(P);
		}
	}

}
bool canLie(int depth,int lie, int* Person) {

	int sz = attendee[depth].size();

	for (int i = 0; i < sz; i++) {
		int P = attendee[depth][i];
		if (truth[P] && lie == 0) return false;

		if (Person[P] == -1) continue;
		if (Person[P] != lie) return false;
	}
	return true;
}
/* lie == 1 : Áø½Ç lie == 0 °ÅÁþ*/
int DFS(int depth, int lie,int* prev) {
	
	if (depth == M - 1) {
		if (canLie(depth, lie, prev)) {
			return (lie == 1 ? 0 : 1);
		}
		return -1;
	}
	int cur[51];
	if (canLie(depth, lie, prev)) {
		for (int i = 0; i <= N; i++) {
			cur[i] = prev[i];
		}

		int sz = attendee[depth].size();
		for (int i = 0; i < sz; i++) {
			cur[attendee[depth][i]] = lie;
		}

		int next = DFS(depth + 1, 0, cur);
		int next2 = DFS(depth + 1, 1, cur);

		if (next == -1 && next2 == -1) return -1;
		else {
			return (lie == 1 ? 0 : 1) + max(next, next2);
		}
	}
	else return -1;
}
void solve() {
	int cur[51];
	for (int i = 0; i <= N; i++) {
		cur[i] = -1;
	}
	ans = DFS(0, 0, cur);
	for (int i = 0; i < N; i++) {
		cur[i] = -1;
	}
	ans = max(ans, DFS(0, 1, cur));

	if (ans == -1) ans = 0;
	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_input();
	solve();

}