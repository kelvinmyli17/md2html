#include <string>
#include <regex>

using namespace std;

class LinkConverter {
public:
    const regex re("\\[([^\\]]*)\\]\\(([^\\]]*)\\)");
    string html_link = "<a href=\"$2\">$1</a>";
  LinkConverter(string &line) {
    line = regex_replace(line, re, html_link);
  }
}
