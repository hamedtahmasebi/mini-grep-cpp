#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]) {
  char *file_path = argv[1];
  char *pattern = argv[2];

  ifstream input_file(file_path);

  if (!input_file.is_open()) {
    cerr << "Error while trying to open the file" << endl;
    return 1;
  }

  vector<string> content;
  string line;
  while (getline(input_file, line)) {
    content.push_back(line);
  }

  for (size_t i = 1; i <= content.size(); ++i) {
    string line = content[i - 1];
    string::size_type pos = line.find(pattern);
    if (pos == string::npos) {
      continue;
    }
    printf("%zu: %s\n", i, &line[0]);
  }

  input_file.close();
}
