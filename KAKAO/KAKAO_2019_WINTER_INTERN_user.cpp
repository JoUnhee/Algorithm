#include <string>
#include <vector>
#include<iostream>

using namespace std;
bool visited[1 << 8];

bool isPossible(string a, string b)
{
	if (a.size() != b.size())return false;
	for (int i = 0; i < a.size(); i++)
	{
		if (!(a[i] == b[i] || a[i] == '*' || b[i] == '*'))return false;
	}
	return true;
}

void dfs(int bannedIdx, int N, int bits, const vector<vector<int>>& v)
{
	if (bannedIdx == N)
	{
		visited[bits] = true;
		return;
	}
	for (auto next : v[bannedIdx])
	{
		if (bits & (1 << next))continue;
		dfs(bannedIdx + 1, N, bits | (1 << next), v);
	}
}

int solution(vector<string> user_id, vector<string> banned_id) {
	int answer = 0;
	vector<vector<int>>v(banned_id.size());
	for (int i = 0; i < banned_id.size(); i++)
	{
		string banned = banned_id[i];
		for (int j = 0; j < user_id.size(); j++)
		{
			string user = user_id[j];
			if (isPossible(banned, user))
				v[i].push_back(j);
		}
	}
	dfs(0, banned_id.size(), 0, v);
	for (int i = 0; i < (1 << 8); i++)
		if (visited[i])answer++;

	return answer;
}

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	ios::sync_with_stdio(false);
	vector<string> u = { "frodo", "fradi", "crodo", "abc123", "frodoc" };
	vector<string> b = { "fr*d*", "*rodo", "******", "******" };

	solution(u, b);

	cout << solution(u, b) << endl;
}