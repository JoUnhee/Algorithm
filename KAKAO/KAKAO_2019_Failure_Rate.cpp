#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int cnt[502];
double rate[502];

bool cmp_stages(int& A, int& B) {
	return A < B;
}
bool forsort(pair<int, double> A, pair<int, double> B) {
	if (A.second == B.second) return A.first < B.first;
	return A.second > B.second;
}
vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	int sz = stages.size();

	sort(stages.begin(), stages.end(), cmp_stages);
	for (int i = 0; i < sz; i++) {
		cnt[stages[i]]++;
	}

	int prev = -1;
	int mo = sz;
	for (int i = 0; i < stages.size(); i++) {
		if (prev != -1) {
			if (prev == stages[i]) continue;
			mo -= cnt[prev];
			prev = stages[i];

			if (stages[i] < N + 1) rate[stages[i]] = (double)cnt[prev] / mo;
			else if (stages[i] == N + 1) continue;
		}
		else {
			rate[stages[i]] = (double)cnt[stages[i]] / mo;
			prev = stages[i];
		}
	}
	vector<pair<int, double>> q;
	for (int i = 1; i <= N; i++) {
		q.push_back({ i,rate[i] });
	}

	sort(q.begin(), q.end(), forsort);

	for (int i = 0; i < N; i++) {
		answer.push_back(q[i].first);
	}
	return answer;
}