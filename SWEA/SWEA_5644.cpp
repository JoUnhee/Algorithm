#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

typedef struct BC {
	int x;
	int y;
	int C;
	int P;

	BC(int _x, int _y, int _c, int _P) : x(_x), y(_y), C(_c), P(_P) {}
};

int T, M, A;
vector<int> map[10][10];
int dx[5] = { 0,0,1,0,-1 };
int dy[5] = { 0,-1,0,1,0 };
int ret;

vector<BC> BCs;
vector<int> Am;
vector<int> Bm;

bool isInside(int x, int y) {
	return x >= 0 && x < 10 && y >= 0 && y < 10;
}
void _input() {
	cin >> M >> A;
	int dir;
	for (int i = 0; i < M; i++) {
		cin >> dir;
		Am.push_back(dir);
	}
	for (int i = 0; i < M; i++) {
		cin >> dir;
		Bm.push_back(dir);
	}

	for (int i = 0; i < A; i++) {
		int x, y, c, p;

		cin >> x >> y >> c >> p;
		BCs.push_back(BC(x-1, y-1, c, p));
	}
}
void _init() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j].clear();
		}
	}
	BCs.clear();
	Am.clear();
	Bm.clear();
	ret = 0;
}
void check(BC &obj,int num) {
	int x = obj.x;
	int y = obj.y;
	int C = obj.C;

	for (int i = 0; i < C; i++) {
		int upper = y - C + i;
		int bottom = y + C - i;
		int std = 2 * i + 1;
		int cur = std / 2;

		for (int nx = x - cur; nx <= x + cur; nx++) {
			if (isInside(nx, upper)) map[upper][nx].push_back(num);
			if (isInside(nx, bottom)) map[bottom][nx].push_back(num);

		}
	}
	int std = 2 * C + 1;
	int cur = std / 2;

	for (int nx = x - cur; nx <= x + cur; nx++) {
		if (isInside(nx, y)) map[y][nx].push_back(num);
	}
}
void print() {
	printf("---------------------------\n");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%2d", map[i][j].size());
		}
		printf("\n");
	}

}
int maxCharge(vector<int> Ac, vector<int>Bc) {
	int Ret = 0;

	if (Ac.size() >= 1 && Bc.size() >= 1) {
		
		for (int i = 0; i < Ac.size(); i++) {
			int a = Ac[i];
			for (int j = 0; j < Bc.size(); j++) {
				int b = Bc[j];
				if (a == b) Ret = max(Ret, BCs[a].P);
				else Ret = max(Ret, BCs[a].P + BCs[b].P);
			}
		}
	}
	else if (Ac.size() == 0 && Bc.size() != 0) {
	
		for (int i = 0; i < Bc.size(); i++) {
			int b = Bc[i];
			Ret = max(Ret, BCs[b].P);
		}
	}
	else if (Ac.size() != 0 && Bc.size() == 0) {
		for (int i = 0; i < Ac.size(); i++) {
			int a = Ac[i];
			Ret = max(Ret, BCs[a].P);
		}
	}

	return Ret;
}
void simul() {
	int P1x = 0;
	int P1y = 0;
	int P2x = 9;
	int P2y = 9;

	for (int i = 0; i <= M; i++) {
		int sum = 0;

		vector<int> Ac;
		vector<int> Bc;
	
		if (map[P1y][P1x].size() > 0) {
			for (int j = 0; j < map[P1y][P1x].size(); j++) Ac.push_back(map[P1y][P1x][j]);
		}
		if (map[P2y][P2x].size() > 0) {
			for (int j = 0; j < map[P2y][P2x].size(); j++) Bc.push_back(map[P2y][P2x][j]);
		}
		
		sum = maxCharge(Ac, Bc);
		//printf("%d seconds, the amount of charge is %d\n", i, sum);
		ret += sum;
		if (i != M) {
			P1x += dx[Am[i]];
			P1y += dy[Am[i]];
			P2x += dx[Bm[i]];
			P2y += dy[Bm[i]];
		}
	}
	return;
}
void solve() {
	FILE* input;
	freopen_s(&input, "input.txt", "r", stdin);

	cin >> T;

	for (int t = 1; t <= T; t++) {
		_init();
		_input();

		for (int i = 0; i < A; i++) {
			check(BCs[i],i);
		}
		simul();

		cout << "#" << t << " " << ret << endl;
	}
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();

}