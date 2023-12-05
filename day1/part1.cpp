#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

int main() {
	int ans = 0;
	std::ifstream file("doc.txt");
	std::string line;
	while (getline(file, line)) {
		for (int i = 0; i < line.size(); ++i) {
			if (line[i] - '0' <= 9) {
				ans += 10 * (line[i] - '0');
				break;
			}
		} 
		for (int i = line.size()-1; i >= 0; --i) {
			if (line[i] - '0' <= 9) {
				ans += line[i] - '0';
				break;
			}
		}
	} 
	file.close();
	printf("ans: %d\n", ans);
	return 0;
}
