#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, int> dic;

void _init() {
	dic.clear();
	string cha = "A";
	for (int i = 0; i < 26; i++) {
		dic[cha] = i + 1;
		cha[0]++;
	}
	return;
}
vector<int> solution(string msg) {
	vector<int> answer;

	_init();

	int sz = msg.size();
	int curIdx = 27;
	for (int i = 0; i < sz; i++) {
		
		string obj = "";
		int j = 0;
		for (j = sz - i; j > 0; j--) {
			obj = msg.substr(i, j);

			if (dic.find(obj) == dic.end()) continue;
			else break;

		}
		if (i + j < sz) {
			if (dic.find(obj) != dic.end()) {
				answer.push_back(dic[obj]);
				obj = msg.substr(i, j + 1);
				dic[obj] = curIdx;
				curIdx++;
				i = i + j - 1;
			}
		}
		else if(i + j >= sz){
			if (dic.find(obj) != dic.end()) {
				answer.push_back(dic[obj]);
				break;
			}
		}
	}


	for (int i = 0; i < answer.size(); i++) {
		printf("%3d", answer[i]);
	}
	printf("\n");
	return answer;
}
int main() {

	string m = "ABABABABABABABAB";
	solution(m);
}