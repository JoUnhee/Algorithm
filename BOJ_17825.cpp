#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int dice[10];
int turns[10];
int plates[33][6] = {
{0,1,2,3,4,5},
{2,2,3,4,5,9},
{4,3,4,5,9,10},
{6,4,5,9,10,11},
{8,5,9,10,11,12},
{10,6,7,8,20,29},
{13,7,8,20,29,30},
{16,8,20,29,30,31},
{19,20,29,30,31,32},
{12,10,11,12,13,14},
{14,11,12,13,14,15},
{16,12,13,14,15,16},
{18,13,14,15,16,17},
{20,18,19,20,29,30},
{22,15,16,17,24,25},
{24,16,17,24,25,26},
{26,17,24,25,26,27},
{28,24,25,26,27,28},
{22,19,20,29,30,31},
{24,20,29,30,31,32},
{25,29,30,31,32,32},
{26,20,29,30,31,32},
{27,21,20,29,30,31},
{28,22,21,20,29,30},
{30,23,22,21,20,29},
{32,26,27,28,31,32},
{34,27,28,31,32,32},
{36,28,31,32,32,32},
{38,31,32,32,32,32},
{30,30,31,32,32,32},
{35,31,32,32,32,32},
{40,32,32,32,32,32},
{0,32,32,32,32,32}
};

int ret;
void simul() {

	int pos[4] = { 0,0,0,0 };
	int capacity[35];
	int res = 0;
	memset(capacity, 0, sizeof(capacity));
	capacity[0] = 4;
	for (int turn = 0; turn < 10; turn++) {

		int horse = turns[turn];
		int& cur_pos = pos[horse];
		int move = dice[turn];
		int next_pos = plates[cur_pos][move];
		int score = plates[next_pos][0];

		if (capacity[next_pos] > 0 && next_pos != 0 && next_pos != 32) {
			return;
		}
		else {
			res += score;
			capacity[next_pos]++;
			capacity[cur_pos] --;
			cur_pos = next_pos;
		}
	}

	if (ret < res) {
		ret = res;
	}
}
void DFS(int idx) {
	if (idx >= 10) {
		simul();
		return;
	}
	else {
		for (int i = 0; i < 4; i++) {
			turns[idx] = i;
			DFS(idx + 1);
		}
	}
	return;
}
void init() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	ret = 0;
	memset(turns, 0, sizeof(turns));
	memset(dice, 0, sizeof(dice));
}
void input() {
	init();
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}
}
void solve() {

	input();
	DFS(0);
	cout << ret << endl;
}
int main() {

	solve();

	return 0;
}
