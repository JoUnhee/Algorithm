#include<cstring>
#include<iostream>

using namespace std;
typedef struct horse {
	int type;
	int whe;
};
horse horses[8];
string Tmap[32];
string map[32] = {
"..----..----..----..----..----..",
"..    ..    ..    ..    ..    ..",
"| \\                          / |",
"|  \\                        /  |",
"|   \\                      /   |",
"|    ..                  ..    |",
"..   ..                  ..   ..",
"..     \\                /     ..",
"|       \\              /       |",
"|        \\            /        |",
"|         ..        ..         |",
"|         ..        ..         |",
"..          \\      /          ..",
"..           \\    /           ..",
"|             \\  /             |",
"|              ..              |",
"|              ..              |",
"|             /  \\             |",
"..           /    \\           ..",
"..          /      \\          ..",
"|         ..        ..         |",
"|         ..        ..         |",
"|        /            \\        |",
"|       /              \\       |",
"..     /                \\     ..",
"..   ..                  ..   ..",
"|    ..                  ..    |",
"|   /                      \\   |",
"|  /                        \\  |",
"| /                          \\ |",
"..    ..    ..    ..    ..    ..",
"..----..----..----..----..----.."
};
int cache[31][6] = {
{0,1,2,3,4,5},// 0번 출발 위치
{0,2,3,4,5,8},// 1번 위치
{0,3,4,5,8,9},// 2번
{0,4,5,8,9,10},// 3번
{0,5,8,9,10,11},// 4번
{0,6,7,20,21,22},// 5번
{0,7,20,21,22,19},// 6번
{0,20,21,22,19,23},// 7번
{0,9,10,11,12,15},// 8번
{0,10,11,12,15,16},// 9번
{0,11,12,15,16,17},// 10번
{0,12,15,16,17,18},// 11번
{0,13,14,20,27,28},// 12번
{0,14,20,27,28,29},// 13번
{0,20,27,28,29,30},// 14번
{0,16,17,18,19,23},// 15번
{0,17,18,19,23,24},// 16번
{0,18,19,23,24,25},// 17번
{0,19,23,24,25,26},// 18번
{0,23,24,25,26,29},// 19번
{0,27,28,29,30,30},// 20번
{0,22,19,23,24,25},// 21번
{0,19,23,24,25,26},// 22번
{0,24,25,26,29,30},// 23번
{0,25,26,29,30,30},// 24번
{0,26,29,30,30,30},// 25번
{0,29,30,30,30,30},// 26번
{0,28,29,30,30,30},// 27번
{0,29,30,30,30,30},// 28번
{0,30,30,30,30,30},// 29번
{0,30,30,30,30,30},// 30번 (도착)
};
pair<int, int> CacheForSet[31] = {
	{-1,-1},// 0번 출발 위치
{24,30},// 1번 위치
{18,30},// 2번
{12,30},// 3번
{6,30},// 4번
{0,30},// 5번
{5,25},// 6번
{10,20},// 7번
{0,24},// 8번
{0,18},// 9번
{0,12},// 10번
{0,6},// 11번
{0,0},// 12번
{5,5},// 13번
{10,10},// 14번
{6,0},// 15번
{12,0},// 16번
{18,0},// 17번
{24,0},// 18번
{30,0},// 19번
{15,15},// 20번
{20,10},// 21번
{25,5},// 22번
{30,6},// 23번
{30,12},// 24번
{30,18},// 25번
{30,24},// 26번
{20,20},// 27번
{25,25},// 28번
{30,30},// 29번
{-1,-1},// 30번 (도착)
};
int CharToIdx(string horse) {
	if (horse == "A") return 0;
	if (horse == "B") return 1;
	if (horse == "C") return 2;
	if (horse == "D") return 3;
	if (horse == "a") return 4;
	if (horse == "b") return 5;
	if (horse == "c") return 6;
	if (horse == "d") return 7;
}
char idxToChar(int idx) {
	if (idx == 0) return 'A';
	if (idx == 1) return 'B';
	if (idx == 2) return 'C';
	if (idx == 3) return 'D';
	if (idx == 4) return 'a';
	if (idx == 5) return 'b';
	if (idx == 6) return 'c';
	if (idx == 7) return 'd';
}
void Print() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			printf("%c", Tmap[i][j]);
		}
		printf("\n");
	}
}
void _init() {
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			Tmap[i]+= map[i].at(j);
		}
	}

	for (int i = 0; i < 8; i++) {
		horses[i].type = i;
		horses[i].whe = 0;
	}
}
void _input(int& idx,int& cnt) {
	string horse;
	string yut;

	cin >> horse >> yut;
	idx = CharToIdx(horse);
	for (int i = 0; i < yut.size(); i++) {
		if (yut[i] == 'F') cnt++;
	}

	if (cnt == 0) cnt = 5;
	return;
}
bool Group(int obj) {
	return obj >= 0 && obj <= 3;
}
void move(int idx, int Forward) {
	int cur = horses[idx].whe;
	int nextWhe = cache[cur][Forward];
	bool group = Group(idx);

	horses[idx].whe = nextWhe;
	for (int i = 0; i < 8; i++) {
		if (horses[i].whe == cur && horses[i].whe != 0) {
			horses[i].whe = nextWhe;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (horses[i].whe == nextWhe) {
			if (group != Group(i)) {
				horses[i].whe = 0;
			}
		}
	}
	

}
pair<int, int> ConvertForSet(int type, int whe) {
	int cusor = type % 4;
	int x, y;
	y = CacheForSet[whe].first;
	x = CacheForSet[whe].second;
	
	if (y == -1 || x == -1) return { y,x };

	if (cusor == 1) {
		x ++;
	}
	else if (cusor == 2) {
		y ++;
	}
	else if (cusor == 3) {
		x++, y++;
	}

	return { y,x };
}
void Setting() {
	for (int i = 0; i < 8; i++) {
		int whe = horses[i].whe;

		pair<int, int> cusor = ConvertForSet(i, whe);

		int x = cusor.second;
		int y = cusor.first;

		if (x == -1 || y == -1) continue;

		Tmap[y][x] = idxToChar(i);
	}

}

void solve() {
	int N;

	cin >> N;

	for (int i = 0; i < N; i++) {
		int horse, forward;
		horse = forward = 0;
		_input(horse, forward);

		move(horse, forward);
	}
	Setting();
	Print();
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	_init();
	solve();

}