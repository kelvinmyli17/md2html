#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "markdown.h"

using namespace std;

int main() {
  string mdfile_path = "./input.md";

  ofstream htmlfile; // 输出
  htmlfile.open("target.html", ios::out); // 最后要保存为 html 文件

  if (htmlfile.is_open()) {
    htmlfile << get_string(mdfile_path);
    htmlfile.close();
  }
}
