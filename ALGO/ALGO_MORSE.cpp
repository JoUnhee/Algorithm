#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int M = 1000000000 + 100;
int skip;

int bino[201][201];
/*
*	k번째 답 계산하기 프로시저
*
*	1. 답들을 사전순대로 만들며 경우의 수를 세는 완전 탐색 알고리즘을 설계하고, 메모이제이션을 적용해 경우의 수를 세는 동적 계획법 알고리즘으로 변환
*	2. 모든 답들을 사전순으로 생성하며 skip개를 건너뛰고 첫 번째 답을 반환하는 재귀 호출 함수를 구현. 재귀 함수는 각 조각들에 들어갈 수 있는 값을하나씩 고려하면서 이 값을 선택했을 때 만들어지는 답의 수 M과 건너 뛰어야 할 답의 수 skip을 비교
*	a) M <= skip : M개의 답은 모두 우리가 원하는 답보다 앞에 있으므로, 이들을 건너 뛴다. 대신 skip을 M 만큼 감소시킨다.
*	b) M > skip : M개의 답중에서 우리가 원하는 답이 있으므로, 이 값을 선택한다. M개의 답중에 skip개를 건너뛴 것이 우리가 원하는 답이다. 이 값을 답에 추가하고 재귀 호출로 답의 나머지 부분을 만든다.
*/
void precal() {
	memset(bino, 0, sizeof(bino));

	for (int i = 0; i <= 200; i++) {
		bino[i][i] = bino[i][0] = 1;

		for (int j = 1; j < i; j++) {
			bino[i][j] = min(M, bino[i - 1][j - 1] + bino[i - 1][j]);
		}
	}
}

void gener(int n, int m, string s) {

	if (skip < 0) return;

	if (n == 0 && m == 0) {
		if (skip == 0) cout << s << endl;

		skip--;
		return;
	}

	if (skip >= bino[n+m][n]) {
		skip -= bino[n+m][n];
		return;
	}

	if (n > 0) gener(n - 1, m, s + "-");
	if (m > 0) gener(n, m-1, s + "o");

	return;
}
string another(int n, int m, int skip) {
	if (n == 0) return string(m, 'o');

	if (skip < bino[n + m - 1][n - 1]) {
		return "-" + another(n - 1, m, skip);
	}
	return "o" + another(n, m - 1, skip - bino[n+m-1][n-1]);
}

int main() {
	int n, m, k;

	cin >> n >> m >> k;
	skip = k;
	precal();
	gener(n, m, "");
	cout << another(n, m, k) << endl;
	return 0;
}