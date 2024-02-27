#include "mymodel.h"

namespace s21 {
Model::Model(std::string str_) {
  if (str_.length() > 255) {
    throw std::out_of_range("The expression is too long");
  }
}

int Model::Priority(char symb_) {
  int res = 0;
  switch (symb_) {
    case '+':
    case '-':
      res = 1;
      break;
    case '*':
    case '/':
    case 'm':
      res = 2;
      break;
    case '^':
      res = 3;
      break;
    case 's':
    case 'c':
    case 't':
    case 'k':
    case 'u':
    case 'g':
    case 'q':
    case 'n':
    case 'l':
      res = 4;
      break;
    case ')':
      res = -1;
      break;
    case '(':
      res = 10;
      break;
  }
  return res;
}

double Model::TopPop(std::stack<double> &d) {
  double dig1 = d.top();
  d.pop();
  return dig1;
}

void Model::Calc(std::stack<double> &d, std::stack<char> &o, char symb_,
                 int *error_) {
  if (!o.empty() && !d.empty() && *error_ == 0) {
    int prior = Priority(symb_);
    char prev = o.top();
    if (prior <= Priority(prev) && prev != '(') {
      double res = 0;
      double d1;
      double d2;
      switch (prev) {
        case '+':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = d2 + d1;
          o.pop();
          break;
        case '-':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = d2 - d1;
          o.pop();
          break;
        case '*':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = d2 * d1;
          o.pop();
          break;
        case '/':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = d2 / d1;
          o.pop();
          break;
        case '^':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = pow(d2, d1);
          o.pop();
          break;
        case 'm':
          d1 = TopPop(d);
          d2 = TopPop(d);
          res = fmod(d2, d1);
          o.pop();
          break;
        case 's':
          d1 = TopPop(d);
          res = sin(d1);
          o.pop();
          break;
        case 'c':
          d1 = TopPop(d);
          res = cos(d1);
          o.pop();
          break;
        case 't':
          d1 = TopPop(d);
          res = tan(d1);
          o.pop();
          break;
        case 'k':
          d1 = TopPop(d);
          res = acos(d1);
          o.pop();
          break;
        case 'u':
          d1 = TopPop(d);
          res = asin(d1);
          o.pop();
          break;
        case 'g':
          d1 = TopPop(d);
          res = atan(d1);
          o.pop();
          break;
        case 'q':
          d1 = TopPop(d);
          res = sqrt(d1);
          o.pop();
          break;
        case 'n':
          d1 = TopPop(d);
          res = log(d1);
          o.pop();
          break;
        case 'l':
          d1 = TopPop(d);
          res = log10(d1);
          o.pop();
          break;
      }
      d.push(res);
      Calc(d, o, symb_, error_);
    } else if (prev == '(' && symb_ == ')') {
      o.pop();
    }
  }
}

int Model::ParsCalc(const std::string &str_, std::stack<double> &d,
                    std::stack<char> &o, int *error_) {
  const std::string operand_ = kOperands;
  const std::string symb_ = kSymbols;
  const std::vector<std::string> array_ = kFunctions;
  for (unsigned int i = 0; i < str_.size() && *error_ == 0; i++) {
    if (operand_.find(str_[i]) != std::string::npos) {
      if ((str_[i] == '+' || str_[i] == '-') && (!i || str_[i - 1] == '('))
        d.push(0.0);
      Calc(d, o, str_[i], error_);
      if (str_[i] != ')') o.push(str_[i]);
    } else if (atof(&str_[i]) || str_[i] == '0') {
      d.push(atof(&str_[i]));
      while (isdigit(str_[i + 1]) || str_[i + 1] == '.') {
        i++;
      }
    } else if (*error_ == 0) {
      for (unsigned int j = 0; j < array_.size(); j++) {
        if ((str_.compare(i, array_[j].size(), array_[j])) == 0) {
          Calc(d, o, symb_[j], error_);
          o.push(symb_[j]);
          i = i + array_[j].size() - 1;
          break;
        }
      }
    } else {
      *error_ = 1;
    }
  }
  while (!o.empty() && *error_ == 0) {
    Calc(d, o, o.top(), error_);
  }
  if (!o.empty() && d.size() != 1) *error_ = 1;
  return *error_;
}

int Model::Validation(const std::string &str_, int *error_) {
  int rbr_count = 0;
  int lbr_count = 0;
  const std::vector<std::string> array_ = kFunctions;
  for (unsigned int i = 0; i < str_.size() && *error_ == 0; i++) {
    for (unsigned int j = 0; j < array_.size() && *error_ == 0; j++) {
      if ((str_.compare(i, array_[j].size(), array_[j])) == 0) {
        if (j == 0 &&
            (i == 0 || (i && (!isdigit(str_[i - 1]) && str_[i - 1] != ')')))) {
          *error_ = 1;
        } else if (j == 0 && ((!isdigit(str_[i + 3]) && str_[i + 3] != '(') ||
                              i + 2 == str_.size() - 1)) {
          *error_ = 1;
        } else if ((i != 0 &&
                    (j > 0 && strchr("(-+*/^", str_[i - 1]) == NULL)) ||
                   i + array_[j].size() - 1 == str_.size() - 1) {
          *error_ = 1;
        } else {
          i = i + array_[j].size() - 1;
        }
      }
    }
    if (isdigit(str_[i])) {
      if (i > 0 && strchr("(-+*/^d.", str_[i - 1]) == NULL) {
        *error_ = 1;
      }
      int dot = 0;
      while (isdigit(str_[i + 1]) ||
             (i < str_.size() - 1 && str_[i + 1] == '.')) {
        if (str_[i] == '.') dot++;
        i++;
        if (dot > 1) *error_ = 1;
      }
    } else if (str_[i] == '.' &&
               (!i || i == str_.size() - 1 ||
                (i && i < str_.size() - 1 &&
                 (!isdigit(str_[i - 1]) || !isdigit(str_[i + 1]) ||
                  i == str_.size() - 1)))) {
      *error_ = 1;
    } else if ((str_[i] == '+' || str_[i] == '-') &&
               ((i && !isdigit(str_[i - 1]) &&
                 strchr("()", str_[i - 1]) == NULL) ||
                i == str_.size() - 1)) {
      *error_ = 1;
    } else if (strchr("*/^", str_[i]) &&
               (i == 0 || i == str_.size() - 1 ||
                ((i > 0) && !isdigit(str_[i - 1]) && str_[i - 1] != ')'))) {
      *error_ = 1;
    } else if (str_[i] == '(') {
      lbr_count++;
      if ((i && (isdigit(str_[i - 1]) || str_[i - 1] == ')')) ||
          i == str_.size() - 1) {
        *error_ = 1;
      }
    } else if (str_[i] == ')') {
      rbr_count++;
      if (!i || (i < str_.size() - 1 && isdigit(str_[i + 1])) ||
          lbr_count < rbr_count) {
        *error_ = 1;
      }
    }
  }
  if (rbr_count != lbr_count) *error_ = 1;
  return *error_;
}

double Model::Result(const std::string &str_) {
  double result_double_ = 0.0;
  int err_ = 0;
  int *error_ = &err_;
  Validation(str_, error_);
  ParsCalc(str_, d, o, error_);
  if (*error_ != 0) {
    throw std::invalid_argument("Invalid argument");
  } else {
    result_double_ = d.top();
    d.pop();
  }
  return result_double_;
}
}  // namespace s21

// int main() {
// const std::string str_ = "6+1";
// s21::Model mod(str_);
// double a = mod.Result(str_);
// std::cout << a ;
// return 0;
// }
