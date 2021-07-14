/**
  Markdown 格式的例子:
  1. [内容]
  2. [内容]

  HTML 格式的例子:
  <ol type="1">
    <li>[内容]</li> // 1.
    <li>[内容]</li> // 2.
  </ol>
*/

#include <regex>

using namespace std;
class OrderedListConverter {

private:
  bool startOfLine;
  bool endOfLine;

public:
  OrderedListConverter() : startOfLine(false), endOfLine(false) {}

  // 要注意: 只需要进行转换操作当且仅当 ordered lists 在行首, 否则无效
  // 所以这个函数用于判断是否满足条件
  bool IsStart(const string &line) {
    // 以数字开始的形式如 1.
    const regex re("^[0-9]*[1-9]\\.[ \t].*");
    this->startOfLine = regex_match(line, re);
    return this->startOfLine;
  }

  bool IsEnd() const {
    return this->endOfLine;
  }

  // 为了解决嵌套 lists 的问题
  bool IsStartOfNewlist(const string &line) {
    const regex newList("(?:[1-9]+[0-9]*[ \t]\\. |\\* ).*");
    this->startOfLine = regex_match(line, newList);
    return this->startOfLine;
  }

  void ConvertList(string &line) {
    const regex olist("^[\\s]*[0-9]+\\.(.*)");
    line = regex_replace(line, olist, "");

    // 若是 list 的开头, 进行操作
    if (this->startOfLine) {
      line = "<ol type='1'><li>" + line;
      return;
    }

    if (line.empty()
        || line.find("</li></ol>") != string::npos
        || line.find("</li><li>") != string::npos) {
      line = "</li></ol>" + line; // 新段落
      this->endOfLine = true;
      return;
    }

    if (IsStartOfNewlist(line)) {
      line = "</li><li>" + line;
      return;
    }
  }
};
