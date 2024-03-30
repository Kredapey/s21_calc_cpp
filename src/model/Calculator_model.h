#ifndef CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATOR_MODEL_H
#define CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATOR_MODEL_H

#include <cmath>
#include <cstddef>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

namespace s21 {

class CalculatorModel {
 public:
  CalculatorModel() = default;
  void MainCalc(std::string expr, std::string x);
  std::string CheckValid(std::string str, std::string ch);
  double GetData() const;
  void Reset();
  void CreditCalc(int type, double& monthPayment, double& overallPayment,
                  double& overpayment, int time, double fullSum, double percent,
                  double& firstMonPay, double& lastMonPay);

 private:
  double data_ = 0;
  std::string ReversePolishNotation(std::string expr, std::string x);
  std::size_t ParseOperators(std::string& resVec, std::stack<char>& polStack,
                             char op, char prev);
  void ParseFunc(std::stack<char>& polStack, char op, char prev);
  bool StackTopNotFunc(std::stack<char>& polStack) const;
  bool IsFunc(char ch) const;
  double CalcPolNot(std::string expr);
  double ChooseOp(double firstNum, double secondNum, char ch);
  double AddOperatorCalc(double firstNum, double secondNum);
  double MinOperatorCalc(double firstNum, double secondNum);
  double MultOperatorCalc(double firstNum, double secondNum);
  double ModOperatorCalc(double firstNum, double secondNum);
  double DivOperatorCalc(double firstNum, double secondNum);
  double DegOperatorCalc(double firstNum, double secondNum);
  double ChooseFunc(double num, char ch);
  double CosFuncCalc(double num);
  double SinFuncCalc(double num);
  double TanFuncCalc(double num);
  double AcosFuncCalc(double num);
  double AsinFuncCalc(double num);
  double AtanFuncCalc(double num);
  double SqrtFuncCalc(double num);
  double LnFuncCalc(double num);
  double LogFuncCalc(double num);
  std::string CheckValidNum(std::string str, char num);
  std::string CheckValidOp(std::string str, char op);
  std::string CheckValidBr(std::string str, char op);
  std::string CheckValidFn(std::string str, std::string op);
  void IfClBrFind(std::string& resStr, std::stack<char>& polStack);
  void IfOpBrFind(std::stack<double>& calcStack, char prev, char ch);
  void CheckDotAndE(std::string& str, int& dotFlag, int& eFlag);
  void CalcNumBr(std::string str, int& opBrFind, int& clBrFind);
  void CheckErrors(std::string str, int opBrFind, int clBrFind);
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_MODEL_CALCULATOR_MODEL_H