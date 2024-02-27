#include "controller.h"

namespace s21 {
std::pair<std::string, double> Controller::Calcroller() {
  std::string err = "";
  double result_double_ = 0.0;
  try {
    Model Model(my_string);
    result_double_ = Model.Result(my_string);
  } catch (const std::exception& exc) {
    err = exc.what();
  }
  std::pair<std::string, double> result_ = {err, result_double_};
  return result_;
}

}  // namespace s21
