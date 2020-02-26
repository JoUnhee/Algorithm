#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>

using namespace std;

int N;
int maxX, maxY;
pair<int,int> arr[40001];

int K;
vector<int> q;

int ret = 0;

void input() {
	cin >> N;
	int x, y;

	int x1,y1;
	int x2, y2;

	cin >> x >> y;

	for (int i = 0; i < N / 2 - 1; i++) {
		cin >> x1 >> y1 >> x2 >> y2;

		for (int j = x1; j < x2; j++) arr[j].first = y1;
	}
	
	cin >> x >> y;

	maxX = x;


	cin >> K;

	for (int i = 0; i < K; i++) {
		cin >> x1 >> y1 >> x2 >> y2;
		q.push_back(x1);
	}

}
void solve() {
	for (int i = 0; i < q.size(); i++) {
		int x = q[i];
		int h = arr[x].first;

		arr[x].second = h;
		
		for (int cur = x-1; cur >= 0; cur--) {
			h = min(h, arr[cur].first);
			arr[cur].second = max(arr[cur].second, h);
		}

		h = arr[x].first;

		for (int cur = x+1; cur < maxX; cur++) {
			h = min(h, arr[cur].first);
			arr[cur].second = max(arr[cur].second, h);
		}
	}

	for (int i = 0; i < maxX; i++) {
		ret += (arr[i].first - arr[i].second);
	}

	cout << ret << endl;
}
int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);

	input();
	solve();
	return 0;
}