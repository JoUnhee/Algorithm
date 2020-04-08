#include <iostream>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
using namespace std;

int m;
int dst = 123456789;
map<int, int> visit;

int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
int ans;

const int INF = 987654321;
void _input() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) { 
			
			int num;
			cin >> num;

			if (num == 0) num = 9;
			m = m * 10 + num;
		}
	}
}
bool isInside(int x, int y) {
	return x >= 0 && x < 3 && y >= 0 && y < 3;
}
void solve() {
	_input();

	queue<int> q;
	visit[m] = 0;
	q.push(m);

	while (!q.empty()) {
		int cur = q.front();
		string state = to_string(cur);
		q.pop();

		if (dst == cur) break;

		int idx = state.find('9');

		int x = idx % 3;
		int y = idx / 3;

		for (int i = 0; i < 4; i++) {
 			int nx = x + dx[i];
			int ny = y + dy[i];
			int nidx = ny * 3 + nx;
			if (!isInside(nx, ny)) continue;

			string n = state;
			swap(n[idx], n[nidx]);

			int next = stoi(n);

			if (!visit.count(next)) {
				visit[next] = visit[cur] + 1;
				q.push(next);
			}
		}
	}

	
	if (visit.count(dst)) cout << visit[dst] << endl;
	else cout << -1 << endl;
}
int main() {
	solve();
}