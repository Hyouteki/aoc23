#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::ifstream file("doc.txt");
	std::string line;
	std::vector<std::vector<char>> ds;
	while (getline(file, line)) {
		std::vector<char> tmp;
		for (char ch: line) tmp.push_back(ch);
		ds.push_back(tmp);
	}
	int m = ds.size(), n = ds[0].size(), ans = 0;
	auto is_valid = [m, n](const int a, const int b) {
		return 0 <= a && a < m && 0 <= b && b < n;
	};
	auto is_special = [](const char ch) {
		return !isdigit(ch) && ch != '.';
	};
	std::vector<std::vector<int>> dirs = {{0, 1}, {0, -1}, 
		{-1, -1}, {-1, 0}, {-1, 1}, {1, -1}, {1, 0}, {1, 1}};
	int i = 0;
	while (i < m) {
		int cur = 0;
		bool add = false;
		for (int j = 0; j < n; ++j) {
			if (isdigit(ds[i][j]))
				cur = cur*10 + ds[i][j] - '0';
			else {
				if (add) {
					ans += cur;
					add = false;
				}
				cur = 0;
				continue;
			}
			if (add) continue;
			for (std::vector<int> dir: dirs) {
				int a = i + dir[0], b = j + dir[1];
				if (is_valid(a, b) && is_special(ds[a][b])) {
					add = true;
					break;
				}
			}
		}
		if (add) ans += cur;
		++i;
	}
	printf("ans: %d\n", ans);
	return 0;
}
