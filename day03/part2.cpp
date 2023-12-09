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
	int m = ds.size(), n = ds[0].size();
	auto is_valid = [m, n](const int a, const int b) {
		return 0 <= a && a < m && 0 <= b && b < n;
	};
	auto is_special = [](const char ch) {
		return !isdigit(ch) && ch != '.';
	};
	std::vector<std::vector<int>> dirs = {{-1, -1}, {-1, 0}, 
		{-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
	int i = 0;
	long ans = 0;
	while (i < m) {
		for (int j = 0; j < n; ++j) {
			if (ds[i][j] != '*') continue;
			int num1 = -1, z = 0;
			for (; z < 8; ++z) {
				std::vector<int> dir = dirs[z];
				int a = i + dir[0], b = j + dir[1];
				if (!is_valid(a, b) || !isdigit(ds[a][b]))
					continue;
				int k = b;
				for (; k >= 0 && isdigit(ds[a][k]); --k);
				++k;
				int start = k;
				int num = 0;
				while (k < n && isdigit(ds[a][k])) {
					num = num*10 + ds[a][k] - '0';
					++k;
				}
				int end = k-1;
				if (start < j && j < end) z += 3;
				else if (j == start || j == end) z += 2;
				if (num1 == -1) {
					num1 = num;
					continue;
				}
				ans += num1*num;
				break;
			}
		}
		++i;
	}
	printf("ans: %d\n", ans);
	return 0;
}
