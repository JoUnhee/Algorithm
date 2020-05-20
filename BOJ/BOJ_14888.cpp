#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 11
#define INF 2e9
using namespace std;

int N;

vector<int> nums;

int Min = INF;
int Max = -INF;

int PCNT, MCNT, MULCNT, DCNT;
void _init() {
	nums.clear();
	Min = INF;
	Max = -INF;
}
void _input() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		int num;
		cin >> num;

		nums.push_back(num);
	}

	cin >> PCNT >> MCNT >> MULCNT >> DCNT;
}

void cal(int idx, int sum, int pcnt, int mcnt, int mulcnt, int dcnt) {

	if (idx == N) {
		Min = min(Min, sum);
		Max = max(Max, sum);
		return;
	}

	if (pcnt > 0) cal(idx + 1, sum + nums[idx], pcnt - 1, mcnt, mulcnt, dcnt);
	if (mcnt > 0) cal(idx + 1, sum - nums[idx], pcnt, mcnt - 1, mulcnt, dcnt);
	if (mulcnt > 0) cal(idx + 1, sum * nums[idx], pcnt, mcnt, mulcnt - 1, dcnt);
	if (dcnt > 0) cal(idx + 1, sum / nums[idx], pcnt , mcnt, mulcnt, dcnt - 1);

	return;
}
void solve() {

	_init();
	_input();

	cal(1, nums[0], PCNT, MCNT, MULCNT, DCNT);

	cout << Max << endl;
	cout << Min << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	solve();
}