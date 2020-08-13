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
//트리 구조체
struct TreeNode {
	vector <TreeNode*> children;
};
//잎-잎의 간선의 수
int longest;
//원의 개수
int n;
//중심위치와 반지름
int y[100], x[100], radius[100];
//서브트리의 높이
int height(TreeNode* root) {
	vector<int> heights;
	for (int i = 0; i < root->children.size(); i++) {
		//root의 자식을 최상위 노드로 하는 트리의 높이
		heights.push_back(height(root->children[i]));
	}
	//자식이 없다면 0 반환
	if (heights.empty())
		return 0;
	//크기 순으로 정렬
	sort(heights.begin(), heights.end());
	//자식이 2개 이상일 경우
	if (heights.size() >= 2) {
		//2번째로 큰 높이와 1번째로 큰 높이(longest를 비교, 반환X)
		longest = max(longest, 2 + heights[heights.size() - 2] + heights[heights.size() - 1]);
	}
	//트리의 높이는 가장 큰 서브트리 높이의 1을 더한 값 반환
	return heights.back() + 1;
}
//트리의 가장 긴 간선의 길이 구하기
int solve(TreeNode* root) {
	//초기값
	longest = 0;
	//root를 최상위 노드로 하는 잎-잎 경로
	int h = height(root);
	return max(longest, h);
}
//제곱
int sqr(int x) {
	return x * x;
}
//두 원 a,b사이의 거리
int sqrdist(int a, int b) {
	return sqr(y[a] - y[b]) + sqr(x[a] - x[b]);
}
//a가 b를 포함한다 (두 원의 위치관계: 두 중심 사이의 거리< 두 원의 반지름의 차이)
bool encloses(int a, int b) {
	return radius[a] > radius[b] && sqrdist(a, b) < sqr(radius[a] - radius[b]);
}
//자식인지 여부 확인
bool isChild(int parent, int child) {
	//부모의 자식이 아닌 경우
	if (!encloses(parent, child))
		return false;
	for (int i = 0; i < n; i++) {
		//부모도 자식도 아니고 자식의 자식이나 child가 i 포함되는 경우(간접관계)
		if (i != parent && i != child && encloses(parent, i) && encloses(i, child))
			return false;
	}
	return true;
}
//트리의 생성 
TreeNode* getTree(int root) {
	TreeNode* ret = new TreeNode();
	//모든 노드 순회
	for (int ch = 0; ch < n; ch++) {
		//ch가 root노드의 자식일 경우
		if (isChild(root, ch)) {
			//ch의 노드(ret)의 자식들을 재귀호출을 통해 구한다 
			ret->children.push_back(getTree(ch));
		}
	}
	//자식이 없을 경우(잎 노드)
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