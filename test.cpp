#include <iostream>
#include <regex>

using namespace std;

bool checkList(const string &line) {
  regex re("^[0-9]*[1-9]\\.[ \t].*");
  return regex_match(line, re);
}
void convertlist(string &line) {
    regex orderedList("^[0-9]*[1-9]\\.[ \t]");
    bool endOfLine = false;
    bool startOfLine = false;

    if (checkList(line)) {
      line = regex_replace(line, orderedList, "");
      line = "<ol><li>" + line;
      startOfLine = true;
      return;
    }

    // 寻找 lists 的结束
    if (line.empty()
        || line.find("</li></ol>") != string::npos
        || line.find("</li><li>") != string::npos) {
      line = "</li></ol>" + line; // 新段落
      endOfLine = true;
      return;
    }
  }
int main() {
  string input = "2. kelvin Thanks guys";
  /* convertlist(input); */
  /* cout << input; */

  string heading = "#### Hello world # this is a heading";
  smatch m;
  int hCount;
  if (regex_match(heading, regex("^(#+ ).*"))) {
    regex_search(heading, m, regex("^(#+ )"));
    hCount = m.str(0).length() - 1;

    heading = regex_replace(heading, regex("^(#+ )"), "");
  }
  heading = "<h" + to_string(hCount) + ">" + heading +
    "</h" + to_string(hCount) + ">";

  cout << heading;
}
