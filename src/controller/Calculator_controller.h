#ifndef CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCULATOR_CONTROLLER_H
#define CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCULATOR_CONTROLLER_H

#include "../model/Calculator_model.h"

namespace s21 {

class CalculatorController {
 public:
  CalculatorController(){};
  double CalcStr(std::string str, std::string x);
  std::string CheckVal(std::string str, std::string ch);
  void Reset();
  void CalcCredit(int type, double& monthPayment, double& overallPayment,
                  double& overpayment, int time, double fullSum, double percent,
                  double& firstMonPay, double& lastMonPay);
  double GetData();

 private:
  s21::CalculatorModel model_;
};

}  // namespace s21

#endif  // CPP3_SMARTCALC_V2_SRC_CONTROLLER_CALCULATOR_CONTROLLER_H