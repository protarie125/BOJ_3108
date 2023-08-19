#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;

class Rect {
public:
	int x1{};
	int y1{};
	int x2{};
	int y2{};
};

using vR = vector<Rect>;

vR rects;
vi root;

bool meet(const Rect& a, const Rect& b) {
	if (a.x1 < b.x1 && b.x2 < a.x2 && a.y1 < b.y1 && b.y2 < a.y2) {
		return false;
	}

	if (b.x1 < a.x1 && a.x2 < b.x2 && b.y1 < a.y1 && a.y2 < b.y2) {
		return false;
	}

	if (b.x2 < a.x1) {
		return false;
	}

	if (a.x2 < b.x1) {
		return false;
	}

	if (b.y2 < a.y1) {
		return false;
	}

	if (a.y2 < b.y1) {
		return false;
	}

	return true;
}

int par(int i) {
	if (root[i] == i) return i;

	return root[i] = par(root[i]);
}

void joint(int i, int j) {
	i = par(i);
	j = par(j);

	if (i < j) {
		root[j] = i;
	}
	else if (j < i) {
		root[i] = j;
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	cin >> n;

	rects = vR(n + 1);
	rects[0].x1 = 0;
	rects[0].y1 = 0;
	rects[0].x2 = 0;
	rects[0].y2 = 0;

	root = vi(n + 1);
	root[0] = 0;

	for (auto i = 1; i <= n; ++i) {
		auto& rect = rects[i];
		cin >> rect.x1 >> rect.y1 >> rect.x2 >> rect.y2;

		root[i] = i;
	}

	for (auto i = 0; i < n; ++i) {
		for (auto j = i + 1; j <= n; ++j) {
			if (meet(rects[i], rects[j])) {
				joint(i, j);
			}
		}
	}

	auto s = set<int>{};
	for (const auto& idx : root) {
		s.insert(par(idx));
	}

	cout << s.size() - 1;

	return 0;
}