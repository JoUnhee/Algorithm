#include <string>
#include <vector>
#include <iostream>

using namespace std;
vector<string> convert(int n, vector<int> obj) {

	vector<string> ret;
	for (int i = 0; i < obj.size(); i++) {
		int cur = obj[i];
		string tmp = "";
		for (int j = 0; j < n; j++) {
			int check = (cur & (1 << (n - 1 - j)));

			if (check == 0) tmp += " ";
			else tmp += "#";
		}
		ret.push_back(tmp);
	}
	return ret;
}
vector<int> combine(vector<int> A1, vector<int> A2) {
	vector<int> ret;

	for (int i = 0; i < A1.size(); i++) {
		int cur = A1[i] | A2[i];

		ret.push_back(cur);
	}
	return ret;
}
void printArr(vector<string> obj) {
	for (int i = 0; i < obj.size(); i++) {
		cout << obj[i] << endl;
	}
}
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
	
	
	vector<string> answer;
	vector<int> obj = combine(arr1, arr2);
	answer = convert(n,obj);
	printArr(answer);
	return answer;
}
int main() {
	int n = 5;
	vector<int> a1 = {9, 20, 28, 18, 11};
	vector<int> a2 = {30, 1, 21, 17, 28};

	solution(n, a1, a2);

	//int test = 28 & 7;

	//cout << test << endl;
}