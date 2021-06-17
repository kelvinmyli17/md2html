#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

// 算有多少个 '#'
int count_heading(string line) {
  int heading_count = 0;
  stringstream ss;
  string word;
  ss << line;

  while (ss >> word) {
    if (word.find("#") != string::npos) { // 意味着字符串具有 '#'
      heading_count = word.size();
    }
  }
  return heading_count;
}

void convert_heading(string *line) {
  int heading_count = count_heading(*line);

  line->replace(line->find("#"), count_heading(*line)+1, "<h"+to_string(heading_count)+">"); // 要考虑空格所以长度加 1
  line->insert(line->size(), "</h"+to_string(heading_count)+">");
}

// 访问及读 markdown 文件
string get_string(string file_path) {
  ifstream mdfile; // 输入

  stringstream ss;
  mdfile.open(file_path);

  if (mdfile.is_open()) {
    /* cout << "file is opened"; */

    string line; // 读文件的每行
    while (getline(mdfile, line)) {

      // 断定是否具有 '#'
      if (count_heading(line)) {
        convert_heading(&line);
      }
      ss << line << '\n'; // 要加上换行符
    }
    mdfile.close(); // 访问完之后要关
  }
  return ss.str();
}
