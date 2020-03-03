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
{0,1,2,3,4,5},// 0�� ��� ��ġ
{0,2,3,4,5,8},// 1�� ��ġ
{0,3,4,5,8,9},// 2��
{0,4,5,8,9,10},// 3��
{0,5,8,9,10,11},// 4��
{0,6,7,20,21,22},// 5��
{0,7,20,21,22,19},// 6��
{0,20,21,22,19,23},// 7��
{0,9,10,11,12,15},// 8��
{0,10,11,12,15,16},// 9��
{0,11,12,15,16,17},// 10��
{0,12,15,16,17,18},// 11��
{0,13,14,20,27,28},// 12��
{0,14,20,27,28,29},// 13��
{0,20,27,28,29,30},// 14��
{0,16,17,18,19,23},// 15��
{0,17,18,19,23,24},// 16��
{0,18,19,23,24,25},// 17��
{0,19,23,24,25,26},// 18��
{0,23,24,25,26,29},// 19��
{0,27,28,29,30,30},// 20��
{0,22,19,23,24,25},// 21��
{0,19,23,24,25,26},// 22��
{0,24,25,26,29,30},// 23��
{0,25,26,29,30,30},// 24��
{0,26,29,30,30,30},// 25��
{0,29,30,30,30,30},// 26��
{0,28,29,30,30,30},// 27��
{0,29,30,30,30,30},// 28��
{0,30,30,30,30,30},// 29��
{0,30,30,30,30,30},// 30�� (����)
};
pair<int, int> CacheForSet[31] = {
	{-1,-1},// 0�� ��� ��ġ
{24,30},// 1�� ��ġ
{18,30},// 2��
{12,30},// 3��
{6,30},// 4��
{0,30},// 5��
{5,25},// 6��
{10,20},// 7��
{0,24},// 8��
{0,18},// 9��
{0,12},// 10��
{0,6},// 11��
{0,0},// 12��
{5,5},// 13��
{10,10},// 14��
{6,0},// 15��
{12,0},// 16��
{18,0},// 17��
{24,0},// 18��
{30,0},// 19��
{15,15},// 20��
{20,10},// 21��
{25,5},// 22��
{30,6},// 23��
{30,12},// 24��
{30,18},// 25��
{30,24},// 26��
{20,20},// 27��
{25,25},// 28��
{30,30},// 29��
{-1,-1},// 30�� (����)
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