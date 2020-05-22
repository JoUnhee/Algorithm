#include <cstring>
#include <cstdio>
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int K;

vector<pair<int, int>> order;
deque<char> q[4];

int visit[4];
int ni[2] = { -1, 1 };

int ans;
void _init() {
	order.clear();
	for (int i = 0; i < 4; i++) q[i].clear();
	memset(visit, 0, sizeof(visit));
	ans = 0;
}
void _input() {
	
	string tmp;
	for (int i = 0; i < 4; i++) {
		cin >> tmp;

		for (int j = 0; j < tmp.size(); j++) {
			char obj = tmp[j];
			q[i].push_back(obj);
		}
	}

	cin >> K;

	for (int i = 0; i < K; i++) {
		int which, dir;

		cin >> which >> dir;

		order.push_back({ which - 1,dir });
	}
}
void DFS(int cidx, int dir) {

	deque<char>& cur = q[cidx];
	visit[cidx] = dir;

	for (int i = 0; i < 2; i++) {
		int nidx = cidx + ni[i];

		if (nidx < 0 || nidx >= 4) continue;

		deque<char>& next = q[nidx];

		char c = cur[(6 + i * 4) % 8];
		char n = next[(2 + i * 4) % 8];

		if (visit[nidx] == 0 && c != n ) {
			DFS(nidx, dir * -1);
		}
	}
	
}
void printV() {
	printf("-----------\n");
	for (int i = 0; i < 4; i++) {
		printf("%3d", visit[i]);
	}
	printf("\n");
}
void rotate() {

	for (int i = 0; i < 4; i++) {
		if (visit[i] == 0) continue;

		if (visit[i] == -1) {
			char tmp = q[i].front();
			q[i].pop_front();
			q[i].push_back(tmp);
		}
		else if (visit[i] == 1) {
			char tmp = q[i].back();
			q[i].pop_back();
			q[i].push_front(tmp);
		}
	}
}
int pow(int howmany) {

	int ret = 1;

	for (int i = 1; i <= howmany;i++) {
		ret *= 2;
	}
	return ret;
}
void solve() {

	_init();
	_input();
	
	/*DFS(order[0].first, order[0].second);
	printV();*/

	for (int i = 0; i < K; i++) {
		int which = order[i].first;
		int dir = order[i].second;
		
		DFS(which, dir);
		rotate();

		memset(visit, 0, sizeof(visit));
	}

	for (int i = 0; i < 4; i++) {
		if (q[i][0] == '1') {
			ans += pow(i);
		}
	}

	cout << ans << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}