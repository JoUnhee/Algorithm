#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef struct info {
	int num;
	int x;
	int y;

	info(int _num, int _x, int _y) : num(_num), x(_x), y(_y) {}
};
class Node {
public:
	int num, x, y;
	Node* left;
	Node* right;
	Node(info obj) {
		x = obj.x;
		y = obj.y;
		num = obj.num;
		left = NULL;
		right = NULL;
	}
	void insert_right(Node* obj) {
		if (right != NULL) return;
		right = obj;
	}
	void insert_left(Node* obj) {
		if (left != NULL) return;
		left = obj;
	}
	void insert(Node* obj) {
		if (obj->x < x) {
			if (left == NULL) insert_left(obj);
			else {
				left->insert(obj);
			}
		}
		else if (obj->x > x) {
			if (right == NULL) insert_right(obj);
			else {
				right->insert(obj);
			}
		}
	}
};

bool cmp(info A, info B) {
	if (A.y == B.y) {
		return A.x < B.x;
	}
	return A.y > B.y;
}
void preorder(Node* cur,vector<int>& list) {
	if (cur == NULL) return;
	printf("%2d", cur->num);
	list.push_back(cur->num);
	if (cur->left != NULL) preorder(cur->left,list);
	if (cur->right != NULL) preorder(cur->right,list);
}
void postorder(Node* cur, vector<int>& list) {
	if (cur == NULL) return;
	if (cur->left != NULL) postorder(cur->left, list);
	if (cur->right != NULL) postorder(cur->right, list);
	printf("%2d", cur->num);
	list.push_back(cur->num);
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {

	vector<info> q;
	for (int i = 0; i < nodeinfo.size(); i++) {
		q.push_back(info(i + 1, nodeinfo[i][0], nodeinfo[i][1]));
	}
	sort(q.begin(), q.end(), cmp);

	Node* root = new Node(q[0]);

	for (int i = 1; i < q.size(); i++) {
		root->insert(new Node(q[i]));
	}
	
	vector<vector<int>> answer(2);
	preorder(root,answer[0]);
	printf("\n");
	postorder(root, answer[1]);
	return answer;
}

int main() {
	vector<vector<int>> nodeinfo;

	nodeinfo.push_back({ 5,3 });
	nodeinfo.push_back({ 11,5 });
	nodeinfo.push_back({ 13,3 });
	nodeinfo.push_back({ 3,5 });
	nodeinfo.push_back({ 6,1 });
	nodeinfo.push_back({ 1,3 });
	nodeinfo.push_back({ 8,6 });
	nodeinfo.push_back({ 7,2 });
	nodeinfo.push_back({ 2,2 });
	solution(nodeinfo);
}