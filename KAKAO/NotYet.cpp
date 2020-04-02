#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

vector<vector<string>> obj;
vector<vector<string>> ans;

bool check(string A, string B) {

	if (A.size() != B.size()) return false;

	for (int i = 0; i < A.size(); i++) {
		if (A[i] == '*') continue;
		else if (A[i] != B[i]) return false;

	}
	return true;
}
bool isSame(vector<string> A, vector<string> B) {

	if (A.size() != B.size()) return false;

	for (int i = 0; i < A.size(); i++) {
		if (A[i] != B[i]) return false;
	}
	return true;
}
int cnt() {
	int ret = 0;

	for (int i = 0; i < ans.size(); i++) {
		sort(ans[i].begin(), ans[i].end());
	}

	sort(ans.begin(), ans.end());

	vector<vector<string>> tmp;
	for (auto cur : ans) {
		bool flag = false;
		for (int i = 0; i < cur.size(); i++) {
			for (int j = i + 1; j < cur.size(); j++) {
				if (cur[i] == cur[j]) {
					flag = true;
					break;
				}
			}
			if (flag) break;
		}
		if (!flag) tmp.push_back(cur);
	}
	tmp.erase(unique(tmp.begin(), tmp.end()),tmp.end());
	return tmp.size();

}
void DFS(int idx, vector<string>& sum) {
	if (idx == obj.size()) {
		ans.push_back(sum);
		return;
	}
	for (int i = 0; i < obj[idx].size(); i++) {
			sum.push_back(obj[idx][i]);
			DFS(idx + 1, sum);
			sum.pop_back();
	}
}

bool isContain(vector<string> s, string obj) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == obj) return true;
	}
	return false;
}

int solution(vector<string> user_id, vector<string> banned_id) {
	int answer = 0;

	vector<vector<string>> Canbe;

	for (int i = 0; i < banned_id.size(); i++) {
		vector<string> tmp;
		string& st = banned_id[i];
		for (int j = 0; j < user_id.size(); j++) {
			string& obj = user_id[j];
			if (check(st, obj)) {
				tmp.push_back(obj);
			}
		}
		if (!tmp.empty()) Canbe.push_back(tmp);
	}
	bool visit[9];
	memset(visit, 0, sizeof(visit));
	for (int i = 0; i < Canbe.size(); i++) {
		for (int j = i + 1; j < Canbe.size(); j++) {
			if (isSame(Canbe[i], Canbe[j])) visit[i] = visit[j] = true;
		}
	}

	for (int i = 0; i < Canbe.size(); i++) {
		if (visit[i]) continue;
		obj.push_back(Canbe[i]);
	}


	vector<string> tmp;

	DFS(0, tmp);

	answer = cnt();
	return answer;
}

int main() {
	vector<string> user;
	vector<string> ban;

	user = { "frodo", "fradi", "crodo", "abc123", "frodoc" };
	ban = { "fr*d*", "*rodo","******","******" };

	solution(user, ban);
}