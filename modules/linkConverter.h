#include <string>
#include <regex>

using namespace std;

class LinkConverter {
  LinkConverter(string &line) {
    regex re("\\[([^\\]]*)\\]\\(([^\\]]*)\\)");
    string html_link = "<a href=\"$2\">$1</a>";
    line = regex_replace(line, re, html_link);
  }
}
