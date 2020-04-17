#include <string>
#include <vector>

using namespace std;

vector<string> split(string Dart) {

	vector<string> ret;
	int idx = 0;
	int sz = Dart.size();
	string temp = "";
	while (idx < sz) {
		char& cur = Dart[idx];

		if (idx != 0 && idx < sz - 1) {

			char& next = Dart[idx + 1];
			// 시행 구분점 : 숫자가 나오면
			if (next >= '0' && next <= '9'&& (temp+cur).size() >= 2) {
				ret.push_back(temp + cur);
				temp.clear();
			}
			else {
				temp += cur;
			}
		}
		else if (idx == sz - 1) {
			ret.push_back(temp+ cur);
		}
		else temp += cur;
		idx++;
	}
	return ret;
}
vector <pair<int, char>> Convert(vector<string> obj) {
	vector<pair<int, char>> ret;

	
	for (int i = 0; i < obj.size(); i++) {
		string stobj = obj[i];
		int tmp = 0;
		pair<int, char> elem;
		for (int idx = 0; idx < stobj.size(); idx++) {
			
			char& cur = stobj[idx];

			if (cur >= '0' && cur <= '9') {
				tmp *= 10;
				tmp += (cur - '0');
			}
			else if (cur == '#') {
				elem.first *= -1;
				elem.second = cur;
			}
			else if (cur == '*') {
				elem.second = cur;
			}
			else if (cur == 'S') {
				elem.first = tmp;
			}
			else if (cur == 'D') {
				elem.first = tmp * tmp;
			}
			else if (cur == 'T') {
				elem.first = tmp * tmp * tmp;
			}
		}
		ret.push_back(elem);
		elem.first = 0;
		elem.second = 0;
	
	}
	return ret;
}
int solution(string dartResult) {
	int answer = 0;

	vector<string> SplitResult = split(dartResult);
	vector<pair<int,char>> Cnvt = Convert(SplitResult);

	for (int i = 0; i < Cnvt.size(); i++) {
		int& num = Cnvt[i].first;
		char& op = Cnvt[i].second;

		if (op == '*') {
			if (i > 0) {
				Cnvt[i - 1].first *= 2;
			}
			num *= 2;
		}
	}

	for (int i = 0; i < Cnvt.size(); i++) {
		answer += Cnvt[i].first;
	}
	return answer;
}

int main() {
	string dart = "1D#2S*3S";
	solution(dart);

}