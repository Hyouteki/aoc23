#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

bool starts_with(const std::string str, const std::string target, int start) {
	if (str.size()-start < target.size()) return false;
	for (int i = 0; i < target.size(); ++i)
		if (str.at(start + i) != target.at(i)) return false;
	return true;
}

int get_num(const std::string str, int start) {
	if (str.at(start) - '0' <= 9 && str.at(start) >= 0)
		return str.at(start) - '0';
	const std::string num_strs[10] = {"zero", "one", "two", "three", 
		"four", "five", "six", "seven", "eight", "nine"};
	for (int i = 0; i < 10; ++i)
		if (starts_with(str, num_strs[i], start)) return i;
	return -1;
}

int main() {
	int ans = 0;
	std::ifstream file("doc.txt");
	std::string line;
	while (getline(file, line)) {
		bool start = true;
		int num;
		for (int i = 0; i < line.size(); ++i) {
			int x = get_num(line, i);
			if (x == -1) continue;
			if (start) {
				ans += 10 * x;
				start = false;
			}
			num = x;
		}
		ans += num;
	} 
	file.close();
	printf("ans: %d\n", ans);
	return 0;
}
