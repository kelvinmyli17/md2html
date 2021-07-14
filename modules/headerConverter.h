#include <iostream>
#include <regex>
#include <string>

/**
 * Markdown: 用 '#' 来表示标题, '#' 的个数描述标题的层次
 * HTML: <h1>text</h1>
 *
 * 所以我的想法是首先要判断是否存在标题 (用 regex_match)
 * 然后获取 '#' 的个数, 记为 count
 */
using namespace std;
class HeaderConverter {

  public:
  int hCount; // '#' 的个数

  // 来判断是否村在标题
  bool HaveHeading(const string &line) {
    regex re("^(#+ )(.*$)");
    return regex_match(line, re);
  }

  void ConvertHeading(string &line) {
    smatch match;
    regex heading("^(#+ )");

    if (HaveHeading(line)) {
      regex_search(line, match, heading);
      hCount = match.str(0).length() - 1; // -1 为不算空格

      // 所以 HTML 标题的形式为 <h[hCount]>text</h[hCount]>
      line = regex_replace(line, heading, "");
      line = "<h" + to_string(hCount) + ">" + line +
        "</h" + to_string(hCount) + ">";
    }
  }
}
