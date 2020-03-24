#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

const int M = 1000000000 + 100;
int skip;

int bino[201][201];
/*
*	k��° �� ����ϱ� ���ν���
*
*	1. ����� ��������� ����� ����� ���� ���� ���� Ž�� �˰����� �����ϰ�, �޸������̼��� ������ ����� ���� ���� ���� ��ȹ�� �˰������� ��ȯ
*	2. ��� ����� ���������� �����ϸ� skip���� �ǳʶٰ� ù ��° ���� ��ȯ�ϴ� ��� ȣ�� �Լ��� ����. ��� �Լ��� �� �����鿡 �� �� �ִ� �����ϳ��� ����ϸ鼭 �� ���� �������� �� ��������� ���� �� M�� �ǳ� �پ�� �� ���� �� skip�� ��
*	a) M <= skip : M���� ���� ��� �츮�� ���ϴ� �亸�� �տ� �����Ƿ�, �̵��� �ǳ� �ڴ�. ��� skip�� M ��ŭ ���ҽ�Ų��.
*	b) M > skip : M���� ���߿��� �츮�� ���ϴ� ���� �����Ƿ�, �� ���� �����Ѵ�. M���� ���߿� skip���� �ǳʶ� ���� �츮�� ���ϴ� ���̴�. �� ���� �信 �߰��ϰ� ��� ȣ��� ���� ������ �κ��� �����.
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