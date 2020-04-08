#include <string>
#include <vector>
using namespace std;

string makeLower(string obj) {
	string ret = "";

	for (int i = 0; i < obj.size(); i++) {
		char& cur = obj[i];

		if (cur >= 'A' && cur <= 'Z') {
			ret += (cur + 32);
		}
		else {
			ret += cur;
		}
	}
	return ret;
}
bool check(string obj) {
	for (int i = 0; i < 2; i++) {
		if (obj[i] >= 'a' && obj[i] <= 'z') continue;
		else return false;
	}
	return true;
}
vector<string> PartialUnion(string obj) {
	vector<string> ret;

	int sz = obj.size();

	for (int i = 0; i < sz - 1; i++) {
		string cur = obj.substr(i, 2);

		if (check(cur)) ret.push_back(cur);
	}
	return ret;
}
int FindInter(vector<string> A, vector<string> B) {
	int cnt = 0;
	bool visitB[1000];
	memset(visitB, 0, sizeof(visitB));
	bool visitA[1000];
	memset(visitA, 0, sizeof(visitA));
	for (int i = 0; i < A.size(); i++) {
		
		string& pa = A[i];
		for (int j = 0; j < B.size(); j++) {
			if (visitA[i]) break;
			if (visitB[j]) continue;

			string& pb = B[j];

			if (pa == pb) {
				cnt++;
				visitA[i] = true;
				visitB[j] = true;
			}
		}
	}
	return cnt;
}
int solution(string str1, string str2) {
	int answer = 0;

	string A = makeLower(str1);
	string B = makeLower(str2);

	vector<string> PA = PartialUnion(A);
	vector<string> PB = PartialUnion(B);

	int Inter = FindInter(PA, PB);
	int sum = PA.size() + PB.size() - Inter;
	int rate;
	if (sum == 0 && Inter == 0) rate = 1 * 65536;
	else rate = (int)(((double)Inter / sum) * 65536);
	answer = rate;
	return answer;
}

int main() {
	string A = "E=M*C^2";
	string B = "e=m*c^2";
	solution(A, B);
}