#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <regex>

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

// 转换标题
void convert_heading(string *line) {
  int heading_count = count_heading(*line);

  line->replace(line->find("#"), count_heading(*line)+1, "<h"+to_string(heading_count)+">"); // 要考虑空格所以长度加 1
  line->insert(line->size(), "</h"+to_string(heading_count)+">");
}

vector<string> split(string s, regex pattern, int pos = -1) {
  vector<string> result(
      sregex_token_iterator(s.begin(), s.end(), pattern, pos),
      sregex_token_iterator()
  );
  return result;
}

// 转换链接
// 利用 regex 实现这个操作
string convert_link(string &line) {
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

      // 断定是否具有 '#'
      if (count_heading(line)) {
        convert_heading(&line);
        body = line;
      } else {
        body = line, tail = "<br>\n";
      }
      // 判断在某行中是否存在链接
      if(regex_match(line, regex(".*\\[.*[:alnum:]*\\]\\(.*[:alnum:]*\\)"))) {
        body = convert_link(line);
      }
      ss << body << tail;
    }
    mdfile.close(); // 访问完之后要关 }
  }
  return ss.str();
}
