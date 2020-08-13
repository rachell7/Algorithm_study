//my_code
/*
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
string p;
void true_or_false() {
	int i;
	stack <char> s;
	for (i = 0; i < p.size(); i++) {
		//¿­¸° °ýÈ£
		if(p[i]=='('||p[i]=='{'||p[i]=='[')
			s.push(p[i]);
		//´ÝÈù °ýÈ£
		else {
			if (s.empty()) {
				cout << "NO" << endl;
				return;
			}
			if (p[i] == ')' && s.top() == '(')
				s.pop();
			else if (p[i] == '}' && s.top() == '{')
				s.pop();
			else if (p[i] == ']' && s.top() == '[')
				s.pop();
		}
	}
	if (s.empty())
		cout << "YES" << endl;
	else
		cout << "NO" << endl;
}
int main() {
	int C;
	int i;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> p;
		true_or_false();
	}
}
*/
//ans_code
/*
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

bool wellMatched(const string& formula) {
	const string opening("({["), closing(")}]");
	stack <char> openStack;
	for (int i = 0; i < formula.size(); i++) {
		if (opening.find(formula[i]) != -1)
			openStack.push(formula[i]);
		else {
			if (openStack.empty())
				return false;
			if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			openStack.pop();
		}
	}
	return openStack.empty();

}
int main() {
	int C;
	string a;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> a;
		if (wellMatched(a))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}
*/