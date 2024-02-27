#ifndef SRC_MYMODEL_H_
#define SRC_MYMODEL_H_

#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {
class Model {
 private:
  std::stack<double> d;
  std::stack<char> o;
  const std::vector<std::string> kFunctions{
      "mod", "sin", "cos", "tan", "acos", "asin", "atan", "sqrt", "ln", "log"};
  const std::string kOperands = "+-/*^()";
  const std::string kSymbols = "msctkugqnl";

 public:
  Model(std::string str_);
  ~Model() {}
  int Priority(char symb_);
  void Calc(std::stack<double> &d, std::stack<char> &o, char symb_,
            int *error_);
  int ParsCalc(const std::string &str_, std::stack<double> &d,
               std::stack<char> &o, int *error_);
  int Validation(const std::string &str_, int *error_);
  double Result(const std::string &str_);
  double TopPop(std::stack<double> &d);
  // void top_pop(std::stack<double> &d, double d1, double d2);
};
}  // namespace s21
#endif  // SRC_MYMODEL_H_
