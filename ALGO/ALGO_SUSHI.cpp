#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
int n, m, price[20], pref[20];
int money[201];

void _input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> price[i] >> pref[i];
		price[i] /= 100;
	}
	m /= 100;
}
void _init() {
	memset(price, 0, sizeof(price));
	memset(pref, 0, sizeof(pref));
	memset(money, 0, sizeof(money));
}
int sushi() {

	int ret = 0;
	money[0] = 0;

	for (int b = 1; b <= m; b++) {
		int Maxpref = 0;

		for (int i = 0; i < n; i++) {
			if (b < price[i]) continue;
			Maxpref = max(Maxpref, money[(b - price[i]) % 201] + pref[i]);
		}
		money[b % 201] = Maxpref;
		ret = max(ret, Maxpref);
	}
	return ret;

}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	int C;

	cin >> C;

	for (int t = 1; t <= C; t++) {
		_init();
		_input();

		cout << sushi() << endl;
	}

}