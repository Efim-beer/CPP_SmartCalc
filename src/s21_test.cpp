#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "mymodel.h"

TEST(calculator, test_1) {
  std::string str = "(103-3)/tan(0.2+0.3)*sin(0.7)+(5*cos(1)-atan(-0.5))";
  double standart =
      (103 - 3) / tan(0.2 + 0.3) * sin(0.7) + (5 * cos(1) - atan(-0.5));
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_2) {
  std::string str = "434.56837mod3.2535";
  double standart = fmod(434.56837, 3.2535);
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_3) {
  std::string str = "5-(cos(3)*21-10^0.5)";
  double standart = 5 - (cos(3) * 21 - pow(10, 0.5));
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_4) {
  std::string str = "sqrt(121)";
  double standart = sqrt(121);
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_5) {
  std::string str = "12*(tan(3))/13+13";
  double standart = 12 * (tan(3)) / 13 + 13;
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_6) {
  std::string str = "sqrt(256)+cos(7)*log(4)*ln(2)";
  double standart = sqrt(256.0) + cos(7.0) * log10(4.0) * log(2);
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_7) {
  std::string str = "13/(-2)/(-1)*(-2+12)/3";
  double standart = 13.0 / (-2.0) / (-1.0) * (-2.0 + 12.0) / 3.0;
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

TEST(calculator, test_8) {
  std::string str = "asin(0.5)+acos(0.5)+atan(0.5)+2";
  double standart = asin(0.5) + acos(0.5) + atan(0.5) + 2;
  s21::Model model(str);
  double res_ = model.Result(str);
  ASSERT_EQ(standart, res_);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
