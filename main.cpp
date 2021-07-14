#include "markdown.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

int main() {
  string mdfile = "./input.md";

  ofstream htmlfile;                      // 输出对象
  htmlfile.open("target.html", ios::out); // 最后要保存为 html 文件

  if (htmlfile.is_open()) {
    htmlfile << convert(mdfile);
    htmlfile.close();
  }
}
