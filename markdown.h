#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
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
void OrderedListConverter(const string &line) {
  regex re("^[0-9]*[1-9]\\.[ \t].*");
  if (regex_match(line, re)) {
    cout << line << endl;
  }
}

// 转换标题
void convert_heading(string &line) {
  int heading_count = count_heading(line);

  line.replace(line.find("#"), count_heading(line) + 1,
               "<h" + to_string(heading_count) + ">"); // 要考虑空格所以长度加 1
  line.insert(line.size(), "</h" + to_string(heading_count) + ">");
}

vector<string> split(const string &s, const regex pattern, int pos = -1) {
  vector<string> result(sregex_token_iterator(s.begin(), s.end(), pattern, pos),
                        sregex_token_iterator());
  return result;
}

// 转换链接
string convert_link(string &line) {
  // 链接的 regex pattern
  regex re("\\[([^\\]]*)\\]\\(([^\\]]*)\\)");
  string html_link = "<a href=\"$2\">$1</a>";
  line = regex_replace(line, re, html_link);
  return line;
}

// 访问及读 markdown 文件
string convert(string file_path) {
  ifstream mdfile; // 输入

  stringstream ss;
  mdfile.open(file_path);

  string body = "", tail = "\n";
  if (mdfile.is_open()) {

    string line; // 读文件的每行
    while (getline(mdfile, line)) {
      OrderedListConverter(line);

      // 断定是否具有 '#'
      if (count_heading(line)) {
        convert_heading(line);
        body = line;
      } else {
        body = line, tail = "<br>\n";
      }
      // 判断在某行中是否存在链接
      regex re(".*\\[.*[:alnum:]*\\]\\(.*[:alnum:]*\\)");
      if (regex_match(line, re))
        body = convert_link(line);

      ss << body << tail;
    }
    mdfile.close(); // 访问完之后要关 }
  }
  return ss.str();
}
