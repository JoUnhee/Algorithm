#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<vector<char>>> c;

vector<pair<char, char>> order;
int T, N;
void change(int wh,int row,int col,vector<char> obj) {

	if(row == -1){
		for (int i = 0; i < 3; i++) {
			c[wh][i][col] = obj[i];
		}
	}
	else if (col == -1) {
		for (int i = 0; i < 3; i++) {
			c[wh][row][i] = obj[i];
		}
	}
}
vector<char> extractCol(int wh, int col) {
	return { c[wh][0][col],c[wh][1][col],c[wh][2][col] };
}
void clck_wise(int idx) {
	vector<vector<char>> ret;
	vector<char> tmp;

	tmp.push_back(c[idx][2][0]);
	tmp.push_back(c[idx][1][0]);
	tmp.push_back(c[idx][0][0]);

	ret.push_back(tmp);
	tmp.clear();

	tmp.push_back(c[idx][2][1]);
	tmp.push_back(c[idx][1][1]);
	tmp.push_back(c[idx][0][1]);
	ret.push_back(tmp);
	tmp.clear();
	tmp.push_back(c[idx][2][2]);
	tmp.push_back(c[idx][1][2]);
	tmp.push_back(c[idx][0][2]);
	ret.push_back(tmp);
	tmp.clear();

	c[idx] = ret;
}
void counter_clck_wise(int idx) {
	vector<vector<char>> ret;
	vector<char> tmp;

	tmp.push_back(c[idx][0][2]);
	tmp.push_back(c[idx][1][2]);
	tmp.push_back(c[idx][2][2]);
	ret.push_back(tmp);
	tmp.clear();

	tmp.push_back(c[idx][0][1]);
	tmp.push_back(c[idx][1][1]);
	tmp.push_back(c[idx][2][1]);

	ret.push_back(tmp);
	tmp.clear();

	tmp.push_back(c[idx][0][0]);
	tmp.push_back(c[idx][1][0]);
	tmp.push_back(c[idx][2][0]);

	ret.push_back(tmp);
	tmp.clear();

	c[idx] = ret;
}
void PrintCubeF() {
	for (int j = 0; j < 3; j++) {
		for (int k = 0; k < 3; k++) {
			printf("%c", c[0][j][k]);
		}
		printf("\n");
	}
}
void colReverse(int wh,int idx) {
	char tmp = c[wh][idx][0];
	c[wh][idx][0] = c[wh][idx][2];
	c[wh][idx][2] = tmp;
}
void rowReverse(int wh,int idx) {
	char tmp = c[wh][0][idx];
	c[wh][0][idx] = c[wh][2][idx];
	c[wh][2][idx] = tmp;
}
void rotate(char where, char dir) {
	vector<char> tmp;
	if (dir == '-') {
		rotate(where, '+');
		rotate(where, '+');
		rotate(where, '+');
	}
	else {
		if (where == 'U') {
			clck_wise(0);
			tmp = c[3][2];
			change(3, 2, -1, c[4][0]);
			colReverse(3, 2);
			change(4, 0, -1, c[1][0]);
			change(1, 0, -1, c[5][0]);
			change(5, 0, -1, tmp);
			colReverse(5, 0);
		}
		else if (where == 'D') {
			clck_wise(2);
			tmp = c[3][0];
			change(3, 0, -1, c[5][2]);
			colReverse(3, 0);
			change(5, 2, -1, c[1][2]);
			change(1, 2, -1, c[4][2]);
			change(4, 2, -1, tmp);
			colReverse(4, 2);
		}
		else if (where == 'F') {
			clck_wise(1);
			tmp = c[2][0];
			change(2, 0, -1, extractCol(5, 0));
			colReverse(2, 0);
			change(5, -1, 0, c[0][2]);
			change(0, 2, -1, extractCol(4, 2));
			colReverse(0, 2);
			change(4, -1, 2, tmp);
		}
		else if (where == 'B') {
			clck_wise(3);
			tmp = c[2][2];
			change(2, 2, -1, extractCol(4, 0));
			change(4, -1, 0, c[0][0]);
			rowReverse(4, 0);
			change(0, 0, -1, extractCol(5, 2));
			change(5, -1, 2, tmp);
			rowReverse(5, 2);
		}
		else if (where == 'L') {
			clck_wise(4);
			tmp = extractCol(3, 0);
			change(3, -1, 0, extractCol(2, 0));
			change(2, -1, 0, extractCol(1, 0));
			change(1, -1, 0, extractCol(0, 0));
			change(0, -1, 0, tmp);
		}
		else if (where == 'R') {
			clck_wise(5);
			tmp = extractCol(3, 2);
			change(3, -1, 2, extractCol(0, 2));
			change(0, -1, 2, extractCol(1, 2));
			change(1, -1, 2, extractCol(2, 2));
			change(2, -1, 2, tmp);
		}
	}
	tmp.clear();
}

void _init() {
	c = {
{{'w','w','w'},{'w','w','w'},{'w','w','w'}},
{{'r','r','r'},{'r','r','r'},{'r','r','r'}},
{{'y','y','y'},{'y','y','y'},{'y','y','y'}},
{{'o','o','o'},{'o','o','o'},{'o','o','o'}},
{{'g','g','g'},{'g','g','g'},{'g','g','g'}},
{{'b','b','b'},{'b','b','b'},{'b','b','b'}},
};

	order.clear();

}
void solve() {

	cin >> T;

	for (int i = 0; i < T; i++) {
		_init();

		cin >> N;
		for (int n = 0; n < N; n++) {
			char wh, dir;
			cin >> wh >> dir;
			order.push_back({ wh,dir });
		}

		for (int j = 0; j < order.size(); j++) {
			rotate(order[j].first, order[j].second);
		}
		PrintCubeF();
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}