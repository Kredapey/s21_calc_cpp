#include "Calculator_controller.h"

namespace s21 {

double CalculatorController::CalcStr(std::string str, std::string x) {
  model_.MainCalc(str, x);
  return model_.GetData();
}

std::string CalculatorController::CheckVal(std::string str, std::string ch) {
  str = model_.CheckValid(str, ch);
  return str;
}

void CalculatorController::Reset() { model_.Reset(); }

void CalculatorController::CalcCredit(int type, double& monthPayment,
                                      double& overallPayment,
                                      double& overpayment, int time,
                                      double fullSum, double percent,
                                      double& firstMonPay, double& lastMonPay) {
  model_.CreditCalc(type, monthPayment, overallPayment, overpayment, time,
                    fullSum, percent, firstMonPay, lastMonPay);
}

double CalculatorController::GetData() { return model_.GetData(); }

}  // namespace s21