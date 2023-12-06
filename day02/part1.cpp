#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

int parse_num(std::string* str) {
	int num = 0, c = 0;
	for (char ch: *str) {
		if (isdigit(ch)) {
			num = num*10 + ch - '0';
			++c;
		}
		else break;
	}
	*str = str->substr(c);
	return num;
}

std::string parse_str(std::string* str) {
	std::string x = "";
	for (char ch: *str) {
		if (isalpha(ch)) x.push_back(ch);
		else break;
	}
	*str = str->substr(x.size());
	return x;
}

int color_index(const std::string color) {
	if (color == "red") return 0;
	if (color == "green") return 1;
	return 2;
}

int main() {
	std::ifstream file("doc.txt");
	std::string line;
	int ans = 0, cubes[3] = {12, 13, 14};
	while(getline(file, line)) {
		line = line.substr(5); // eat 'Game '
		int game_no = parse_num(&line);
		line = line.substr(2); // eat ': '
		bool flag = true;
		while (!line.empty()) {
			int tmp[3] = {0, 0, 0};
			while (!line.empty()) {
				int count = parse_num(&line);
				line = line.substr(1); // eat ' '
				std::string color = parse_str(&line);
				tmp[color_index(color)] += count;
				if (line.empty()) break;
				if (line[0] == ';') {
					line = line.substr(2); // eat '; '
					break;
				}
				line = line.substr(2); // eat ', '
			}
			for (int i = 0; i < 3; ++i) { 
				if (tmp[i] > cubes[i]) {
					flag = false;
					break;
				}
			}
		}
		if (flag) ans += game_no;
	}
	file.close();
	printf("ans: %d\n", ans);
	return 0;
}
