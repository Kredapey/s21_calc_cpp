#include <gtest/gtest.h>

#include <cstring>

#include "../controller/Calculator_controller.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(CalcTest, test_1) {
  s21::CalculatorController control;
  double my_res = control.CalcStr(
      "cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(cos(6)))))))))))", "\n");
  ASSERT_FLOAT_EQ(my_res, 0.743467);
}

TEST(CalcTest, test_2) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("1e2 + 1e-09", "\n");
  ASSERT_FLOAT_EQ(my_res, 1e2 + 1e-09);
}

TEST(CalcTest, test_3) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 + 4 * 2 / (1 - 5) ^ 2", "\n");
  ASSERT_FLOAT_EQ(my_res, 3.5);
}

TEST(CalcTest, test_4) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("123.456 + 2 * 3 ^ 4", "\n");
  ASSERT_FLOAT_EQ(my_res, 285.456);
}

TEST(CalcTest, test_5) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("(8 + 2 * 5) / (1 + 3 * 2 - 4)", "\n");
  ASSERT_FLOAT_EQ(my_res, 6);
}

TEST(CalcTest, test_6) {
  s21::CalculatorController control;
  double my_res = control.CalcStr(
      "(15 / (7 - (1 + 1)) * 3 - (2 + (1 + 1 - 1 + 1 * 2 / 2)) + 15 / (7 - (1 "
      "+ 1)) * 3 - (2 + (1 + 1 + 1 - 1 * 2 / 2)))",
      "\n");
  ASSERT_FLOAT_EQ(my_res, 10);
}

TEST(CalcTest, test_7) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("cos(1 * 2) - 1", "\n");
  ASSERT_FLOAT_EQ(my_res, -1.41614683655);
}

TEST(CalcTest, test_8) {
  s21::CalculatorController control;
  double my_res = control.CalcStr(
      "cos(15 / (7 - (1 + 1)) * 3 - (2 + (1 + 1 - 1 + 1 * 2 / 2)) + 15/(7 - (1 "
      "+ 1)) * 3 - (2 + (1 + 1 + 1 - 1 * 2 / 2 ))) - 1",
      "\n");
  ASSERT_FLOAT_EQ(my_res, -1.83907152908);
}

TEST(CalcTest, test_9) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("sin(cos(5))", "\n");
  ASSERT_FLOAT_EQ(my_res, 0.27987335076);
}

TEST(CalcTest, test_10) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("2.33 mod 1", "\n");
  ASSERT_FLOAT_EQ(my_res, 0.33);
}

TEST(CalcTest, test_11) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 + 4 * 2 / 1 - 5 + 2 ^ 2", "\n");
  ASSERT_FLOAT_EQ(my_res, 10);
}

TEST(CalcTest, test_12) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 + 4 * 2 / x - 5 + 2 ^ 2", "2.5");
  ASSERT_FLOAT_EQ(my_res, 5.2);
}

TEST(CalcTest, test_13) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("asin(2 * x)", "0.0003");
  ASSERT_FLOAT_EQ(my_res, 0.0006);
}

TEST(CalcTest, test_14) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("acos(2 * x)", "0.0019");
  ASSERT_FLOAT_EQ(my_res, 1.5669963);
}

TEST(CalcTest, test_15) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("atan(2 * x)", "0.0019");
  ASSERT_FLOAT_EQ(my_res, 0.0037999817);
}

TEST(CalcTest, test_16) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("tan(2 * x)", "0.004");
  ASSERT_FLOAT_EQ(my_res, 0.00800017);
}

TEST(CalcTest, test_17) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("sqrt(2 * x)", "25");
  ASSERT_FLOAT_EQ(my_res, 7.0710678);
}

TEST(CalcTest, test_18) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("ln(10 * x)", "2");
  ASSERT_FLOAT_EQ(my_res, 2.9957323);
}

TEST(CalcTest, test_19) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("log(10 * x)", "2");
  ASSERT_FLOAT_EQ(my_res, 1.30103);
}

TEST(CalcTest, test_20) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 - (-3)", "\n");
  ASSERT_FLOAT_EQ(my_res, 6);
}

TEST(CalcTest, test_21) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 - (+3)", "\n");
  ASSERT_FLOAT_EQ(my_res, 0);
}

TEST(CalcTest, test_22) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("-3 - (-3)", "\n");
  ASSERT_FLOAT_EQ(my_res, 0);
}

TEST(CalcTest, test_23) {
  s21::CalculatorController control;
  double my_res = control.CalcStr("3 - (-3)", "\n");
  ASSERT_FLOAT_EQ(my_res, 6);
  control.Reset();
  ASSERT_FLOAT_EQ(control.GetData(), 0);
}

TEST(CalcTest, test_24) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 - (-3)", "3");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 - (-3)");
}

TEST(CalcTest, test_25) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 - (-3) +", "3");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 - (-3) + 3");
}

TEST(CalcTest, test_26) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("", ".");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "0.");
}

TEST(CalcTest, test_27) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "(");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 * (");
}

TEST(CalcTest, test_28) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3.", ".");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3.");
}

TEST(CalcTest, test_29) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3e", "e");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3e");
}

TEST(CalcTest, test_30) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "3");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "33");
}

TEST(CalcTest, test_31) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("(", "3");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "(3");
}

TEST(CalcTest, test_32) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "e");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3e");
}

TEST(CalcTest, test_33) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", ".");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3.");
}

TEST(CalcTest, test_34) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("(", ".");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "(0.");
}

TEST(CalcTest, test_35) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", ".");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 + 0.");
}

TEST(CalcTest, test_36) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "+");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 +");
}

TEST(CalcTest, test_37) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", "-");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 -");
}

TEST(CalcTest, test_38) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 *", "/");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 /");
}

TEST(CalcTest, test_39) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", "m");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 mod");
}

TEST(CalcTest, test_40) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 mod", "-");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 -");
}

TEST(CalcTest, test_41) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 mod", "*");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 *");
}

TEST(CalcTest, test_42) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "m");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 mod");
}

TEST(CalcTest, test_43) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "*");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 *");
}

TEST(CalcTest, test_44) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("(1 + 2 + (3 - 2)", ")");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "(1 + 2 + (3 - 2))");
}

TEST(CalcTest, test_45) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", "(");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 + (");
}

TEST(CalcTest, test_46) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("", "cos");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "cos(");
}

TEST(CalcTest, test_47) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", "cos");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 + cos(");
}

TEST(CalcTest, test_48) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3", "x");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 * x");
}

TEST(CalcTest, test_49) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("", "x");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "x");
}

TEST(CalcTest, test_50) {
  s21::CalculatorController control;
  std::string my_res = control.CheckVal("3 +", "x");
  const char* str = my_res.c_str();
  ASSERT_STREQ(str, "3 + x");
}

TEST(CreditCalcTest, test_1) {
  s21::CalculatorController control;
  double ov_pay = 0.0, overpayment = 0.0, full_sum = 100000, perc = 5,
         first_mon_pay = 0.0, last_mon_pay = 0.0, month_payment = 0.0;
  int time = 3;
  control.CalcCredit(1, month_payment, ov_pay, overpayment, time, full_sum,
                     perc, first_mon_pay, last_mon_pay);
  ASSERT_DOUBLE_EQ(month_payment, 2997.0897104665569);
  ASSERT_DOUBLE_EQ(ov_pay, 107895.22957679605);
  ASSERT_DOUBLE_EQ(overpayment, 7895.2295767960459);
}

TEST(CreditCalcTest, test_2) {
  s21::CalculatorController control;
  double ov_pay = 0.0, overpayment = 0.0, full_sum = 100000, perc = 5,
         first_mon_pay = 0.0, last_mon_pay = 0.0, month_payment = 0.0;
  int time = 3;
  control.CalcCredit(0, month_payment, ov_pay, overpayment, time, full_sum,
                     perc, first_mon_pay, last_mon_pay);
  ASSERT_DOUBLE_EQ(first_mon_pay, 3194.4444444444443);
  ASSERT_DOUBLE_EQ(last_mon_pay, 2789.3518518518517);
  ASSERT_DOUBLE_EQ(ov_pay, 107708.33333333333);
  ASSERT_DOUBLE_EQ(overpayment, 7708.3333333333285);
}
