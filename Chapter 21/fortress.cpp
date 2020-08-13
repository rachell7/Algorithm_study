//my_code
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
struct TreeNode {
	int x, y, r;
	TreeNode* parent;
	vector<TreeNode*> children;
};
int height(TreeNode* root) {
	int h = 0;
	for (int i = 0; i < root->children.size(); i++) {
		h = max(h, 1 + height(root->children[i]));
	}
	return h;
}
TreeNode* getnode(int x, int y, int r) {
	TreeNode* a = (TreeNode*)malloc(sizeof(TreeNode));
	a->x = x;
	a->y = y;
	a->r = r;
	a->parent = NULL;
	return a;
}
void link_children(TreeNode* a, TreeNode* b) {
	a->children.push_back(b);
	b->parent = a;
}
TreeNode* fort_tree(TreeNode* root, int x, int y, int r) {
	TreeNode* pre = root;
	int i = 0;
	int flag = 0;
	int min_x = x - r;
	int max_x = x + r;
	int min_y = y - r;
	int max_y = y + r;
	int pre_min_x = (pre->x) - (pre->r);
	int pre_max_x = (pre->x) + (pre->r);
	int pre_min_y = (pre->y) - (pre->r);
	int pre_max_y = (pre->y) + (pre->r);
	while (pre_min_x <= min_x && max_x <= pre_max_x && pre_min_y <= min_y && max_y <= pre_max_y) {
		for (i = 0; i < pre->children.size(); i++) {
			if (pre_min_x <= min_x && max_x <= pre_max_x && pre_min_y <= min_y && max_y <= pre_max_y)
			{
				pre = pre->children[i];
				pre_min_x = (pre->x) - (pre->r);
				pre_max_x = (pre->x) + (pre->r);
				pre_min_y = (pre->y) - (pre->r);
				pre_max_y = (pre->y) + (pre->r);
			}
		}
	}
	TreeNode* new_node = getnode(x, y, r);
	link_children(pre, new_node);
	return root;
}
int main() {
	int C;
	int i, j;
	int x, y, r;
	TreeNode* root = NULL;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> N;
		for (j = 0; j < N; j++) {
			cin >> x >> y >> r;
			if (j == 0)
				root = getnode(x, y, r);
			else {
				root = fort_tree(root, x, y, r);
			}
		}
	}
}
*/

//ans_code
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//Ʈ�� ����ü
struct TreeNode {
	vector <TreeNode*> children;
};
//��-���� ������ ��
int longest;
//���� ����
int n;
//�߽���ġ�� ������
int y[100], x[100], radius[100];
//����Ʈ���� ����
int height(TreeNode* root) {
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++) {
		//root�� �ڽ��� �ֻ��� ���� �ϴ� Ʈ���� ����
		heights.push_back(height(root->children[i]));
	}
	//�ڽ��� ���ٸ� 0 ��ȯ
	if (heights.empty())
		return 0;
	//ũ�� ������ ����
	sort(heights.begin(), heights.end());
	//�ڽ��� 2�� �̻��� ���
	if (heights.size() >= 2) {
		//2��°�� ū ���̿� 1��°�� ū ����(longest�� ��, ��ȯX)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	}
	//Ʈ���� ���̴� ���� ū ����Ʈ�� ������ 1�� ���� �� ��ȯ
	return heights.back() + 1;
}
//Ʈ���� ���� �� ������ ���� ���ϱ�
int solve(TreeNode* root) {
	//�ʱⰪ
	longest = 0;
	//root�� �ֻ��� ���� �ϴ� ��-�� ���
	int h = height(root);
	return max(longest, h);
}
//����
int sqr(int x) {
	return x * x;
}
//�� �� a,b������ �Ÿ�
int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
//a�� b�� �����Ѵ� (�� ���� ��ġ����: �� �߽� ������ �Ÿ�< �� ���� �������� ����)
bool encloses(int a, int b) {
	return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}
//�ڽ����� ���� Ȯ��
bool isChild(int parent, int child) {
	//�θ��� �ڽ��� �ƴ� ���
	if (!encloses(parent, child))
		return false;
	for (int i = 0; i < n; i++) {
		//�θ� �ڽĵ� �ƴϰ� �ڽ��� �ڽ��̳� child�� i ���ԵǴ� ���(��������)
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	}
	return true;
}
//Ʈ���� ���� 
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	//��� ��� ��ȸ
	for (int ch = 0; ch < n; ch++) {
		//ch�� root����� �ڽ��� ���
		if (isChild(root, ch)) {
			//ch�� ���(ret)�� �ڽĵ��� ���ȣ���� ���� ���Ѵ� 
			ret->children.push_back(getTree(ch));
		}
	}
	//�ڽ��� ���� ���(�� ���)
	return ret;
}
int main() {
	int C;
	cin >> C;
	while (C--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> x[i] >> y[i] >> radius[i];
		}
		TreeNode* root = getTree(0);
		cout << solve(root) << endl;
	}
}
*/