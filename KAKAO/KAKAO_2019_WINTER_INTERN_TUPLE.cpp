#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
vector<string> split(string s) {

	vector<string> ret;
	int cur = s.find('{', 0);

	while (cur != string::npos) {
		string tmp = "";
		int idx = s.find('}',cur);

		tmp = s.substr(cur, idx - cur+1);
		cout << tmp << endl;

		ret.push_back(tmp);
		cur = s.find('{', idx);
	}
	return ret;
}
int pow(int howmany) {
	int ret = 1;

	for (int i = 0; i < howmany; i++) {
		ret *= 10;
	}
	return ret;
}
int convert(string obj) {

	int ret = 0;

	for (int i = 0; i < obj.size(); i++) {
		int tmp = obj[i] - '0';
		ret += (tmp * pow(obj.size() - i-1));
	}
	return ret;
}
vector<vector<int>> change(vector<string> s) {
	vector<vector<int>> ret;

	for (int i = 0; i < s.size(); i++) {
		string cur = s[i];
		vector<int> elem;
		string tmp = "";
		for (int j = 1; j < cur.size(); j++) {
			
			char chrcCur = cur[j];

			if (chrcCur >= '0' && chrcCur <= '9') tmp += chrcCur;
			else if (chrcCur == ',' || chrcCur == '}') {
				elem.push_back(convert(tmp));
				tmp.clear();
			}
		}

		ret.push_back(elem);
	}
	return ret;
}
bool cmp(vector<int> A, vector<int> B) {
	return A.size() < B.size();
}
vector<int> solution(string s) {
	vector<int> answer;
	vector<string> t;
	vector<vector<int>> obj;

	s.erase(s.begin());
	s.erase(s.end()-1);
	cout << s << endl;
	
	t = split(s);
	obj = change(t);
	
	sort(obj.begin(), obj.end(),cmp);

	bool visit[100001];
	memset(visit, 0, sizeof(visit));

	for (int i = 0; i < obj.size(); i++) {
	
		for (int j = 0; j < obj[i].size(); j++) {
			int cur = obj[i][j];

			if (visit[cur]) continue;

			answer.push_back(cur);
			visit[cur] = true;
		}
	}

	return answer;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	string s = "{{4,2,3},{3},{2,3,4,1},{2,3}}";
	
	

	solution(s);
}