#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <stack>
#include <string>

#include "mymodel.h"

namespace s21 {
class Controller {
 private:
  std::string my_string;

 public:
  explicit Controller(std::string const &str = "") : my_string(str) {}
  std::pair<std::string, double> Calcroller();
};

}  // namespace s21
#endif  // SRC_CONTROLLER_H_
