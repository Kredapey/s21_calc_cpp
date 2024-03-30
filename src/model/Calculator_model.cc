#include "Calculator_model.h"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace s21 {

void CalculatorModel::MainCalc(std::string expr, std::string x) {
  setlocale(LC_NUMERIC, "C");
  std::string str = ReversePolishNotation(expr, x);
  data_ = CalcPolNot(str);
}

std::string CalculatorModel::ReversePolishNotation(std::string expr,
                                                   std::string x) {
  std::stack<char> polStack;
  std::string resStr;
  std::size_t unaryFlag = 0;
  int countOpBr = 0, countClBr = 0;
  CalcNumBr(expr, countOpBr, countClBr);
  CheckErrors(expr, countOpBr, countClBr);
  x = '(' + x + ')';
  char prev = '\n';
  for (size_t pos = 0; (pos = expr.find("x", pos)) != expr.npos;
       pos += x.length())
    expr = expr.replace(pos, 1, x);
  for (auto v : expr) {
    if ((v >= '0' && v <= '9') || v == '.' || v == 'x' || v == 'e') {
      resStr.push_back(v);
    } else {
      if (unaryFlag == 1 &&
          (v == ' ' && ((prev >= '0' && prev <= '9') || prev == ')' ||
                        prev == '.' || prev == 'x')) &&
          polStack.size() > 0) {
        resStr.push_back(polStack.top());
        polStack.pop();
        unaryFlag = 0;
      }
    }
    if (v == '+' || v == '-' || v == '*' || v == '/' || v == '^' || v == 'm') {
      if (prev != 'e') resStr.push_back(' ');
      unaryFlag = ParseOperators(resStr, polStack, v, prev);
    }
    if (v == '(') {
      if (StackTopNotFunc(polStack))
        polStack.push(v);
      else
        polStack.push('~');
    }
    if (v == ')' && polStack.size() != 0) {
      IfClBrFind(resStr, polStack);
    }
    if (prev == 'l' || prev == 'a' || prev == 'c' || prev == 's' ||
        prev == 't') {
      ParseFunc(polStack, v, prev);
    }
    prev = v;
  }
  while (polStack.size() != 0) {
    if (polStack.top() == '(') {
      throw std::invalid_argument("ошибка в выражении");
    }
    resStr.push_back(' ');
    resStr.push_back(polStack.top());
    polStack.pop();
  }
  std::string res(resStr.begin(), resStr.end());
  return res;
}

std::size_t CalculatorModel::ParseOperators(std::string& resStr,
                                            std::stack<char>& polStack, char op,
                                            char prev) {
  std::size_t res = 0;
  if (op == '^') {
    polStack.push(op);
  } else if (op == '*' || op == '/' || op == 'm') {
    if (polStack.size() > 0) {
      if (polStack.top() == '*' || polStack.top() == '/' ||
          polStack.top() == 'm' || polStack.top() == '^') {
        resStr.push_back(polStack.top());
        polStack.pop();
      }
    }
    polStack.push(op);
  } else if (op == '+' || op == '-') {
    if (prev == ')' || (prev >= '0' && prev <= '9') || prev == 'x' ||
        prev == '.' || prev == ' ') {
      if (polStack.size() > 0) {
        if (polStack.top() == '*' || polStack.top() == '/' ||
            polStack.top() == 'm' || polStack.top() == '^' ||
            polStack.top() == '+' || polStack.top() == '-') {
          resStr.push_back(polStack.top());
          polStack.pop();
        }
      }
      polStack.push(op);
    } else if (prev == 'e') {
      resStr.push_back(op);
    } else {
      if (op == '+') {
        polStack.push('p');
      } else {
        polStack.push('w');
      }
      res = 1;
    }
  }
  return res;
}

void CalculatorModel::ParseFunc(std::stack<char>& polStack, char op,
                                char prev) {
  if (prev == 'c' && op == 'o') {
    if (polStack.size() == 0) {
      polStack.push(prev);
    } else {
      if (polStack.size() > 0 && polStack.top() != 'z') polStack.push(prev);
    }
  } else if (prev == 's') {
    if (op == 'i') {
      if (polStack.size() == 0) {
        polStack.push(op);
      } else {
        if (polStack.size() > 0 && polStack.top() != 'x') polStack.push(op);
      }
    } else if (op == 'q') {
      polStack.push(op);
    }
  } else if (prev == 't') {
    if (polStack.size() == 0) {
      polStack.push(prev);
    } else {
      if (polStack.size() > 0 && polStack.top() != 'v' &&
          polStack.top() != 'q' && polStack.top() != '~') {
        polStack.push(prev);
      }
    }
  } else if (prev == 'a') {
    if (op == 'c') {
      polStack.push('z');
    } else if (op == 's') {
      polStack.push('x');
    } else if (op == 't') {
      polStack.push('v');
    }
  } else if (prev == 'l') {
    if (op == 'n') {
      polStack.push(op);
    } else if (op == 'o') {
      polStack.push(op);
    }
  }
}

bool CalculatorModel::StackTopNotFunc(std::stack<char>& polStack) const {
  bool result = true;
  if (polStack.size() != 0) {
    if (polStack.top() == 'c' || polStack.top() == 'i' ||
        polStack.top() == 'q' || polStack.top() == 't' ||
        polStack.top() == 'z' || polStack.top() == 'x' ||
        polStack.top() == 'v' || polStack.top() == 'n' ||
        polStack.top() == 'o') {
      result = false;
    }
  }
  return result;
}

double CalculatorModel::CalcPolNot(std::string expr) {
  std::stack<double> calcStack;
  std::string tempRes;
  double result = 0.0;
  char prev = '\n';
  for (auto ch : expr) {
    if ((ch >= '0' && ch <= '9') || ch == '.' || ch == 'e' ||
        ((ch == '-' || ch == '+') && prev == 'e')) {
      tempRes.push_back(ch);
    } else {
      if (tempRes.size() != 0) {
        calcStack.push(std::stof(tempRes));
        tempRes.clear();
      }
    }
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ||
        ch == 'm') {
      IfOpBrFind(calcStack, prev, ch);
    }
    if (IsFunc(ch)) {
      if (calcStack.size() != 0) {
        double num = calcStack.top();
        calcStack.pop();
        double res = ChooseFunc(num, ch);
        calcStack.push(res);
      }
    }
    if (ch == 'w' || ch == 'p') {
      double num = calcStack.top();
      if (ch == 'w')
        num *= -1;
      else
        num = fabs(num);
      calcStack.pop();
      calcStack.push(num);
    }
    prev = ch;
  }
  if (calcStack.size() != 0) {
    result = calcStack.top();
    calcStack.pop();
  }
  if (tempRes.size() != 0) {
    result = std::stof(tempRes);
  }
  return result;
}

double CalculatorModel::ChooseOp(double firstNum, double secondNum, char ch) {
  double result = 0.0;
  switch (ch) {
    case '+':
      result = AddOperatorCalc(firstNum, secondNum);
      break;
    case '-':
      result = MinOperatorCalc(firstNum, secondNum);
      break;
    case '*':
      result = MultOperatorCalc(firstNum, secondNum);
      break;
    case '/':
      result = DivOperatorCalc(firstNum, secondNum);
      break;
    case '^':
      result = DegOperatorCalc(firstNum, secondNum);
      break;
    case 'm':
      result = ModOperatorCalc(firstNum, secondNum);
      break;
  }
  return result;
}

double CalculatorModel::AddOperatorCalc(double firstNum, double secondNum) {
  return secondNum + firstNum;
}

double CalculatorModel::MinOperatorCalc(double firstNum, double secondNum) {
  return secondNum - firstNum;
}

double CalculatorModel::DivOperatorCalc(double firstNum, double secondNum) {
  return secondNum / firstNum;
}

double CalculatorModel::MultOperatorCalc(double firstNum, double secondNum) {
  return secondNum * firstNum;
}

double CalculatorModel::ModOperatorCalc(double firstNum, double secondNum) {
  return fmod(secondNum, firstNum);
}

double CalculatorModel::DegOperatorCalc(double firstNum, double secondNum) {
  return pow(secondNum, firstNum);
}

bool CalculatorModel::IsFunc(char ch) const {
  bool result = false;
  if (ch == 'c' || ch == 'i' || ch == 'q' || ch == 't' || ch == 'z' ||
      ch == 'x' || ch == 'v' || ch == 'n' || ch == 'o') {
    result = true;
  }
  return result;
}

double CalculatorModel::ChooseFunc(double num, char ch) {
  double result;
  switch (ch) {
    case 'c':
      result = CosFuncCalc(num);
      break;
    case 'i':
      result = SinFuncCalc(num);
      break;
    case 'q':
      result = SqrtFuncCalc(num);
      break;
    case 't':
      result = TanFuncCalc(num);
      break;
    case 'z':
      result = AcosFuncCalc(num);
      break;
    case 'x':
      result = AsinFuncCalc(num);
      break;
    case 'v':
      result = AtanFuncCalc(num);
      break;
    case 'n':
      result = LnFuncCalc(num);
      break;
    case 'o':
      result = LogFuncCalc(num);
      break;
  }
  return result;
}

double CalculatorModel::CosFuncCalc(double num) { return cos(num); }

double CalculatorModel::SinFuncCalc(double num) { return sin(num); }

double CalculatorModel::TanFuncCalc(double num) { return tan(num); }

double CalculatorModel::AcosFuncCalc(double num) { return acos(num); }

double CalculatorModel::AsinFuncCalc(double num) { return asin(num); }

double CalculatorModel::AtanFuncCalc(double num) { return atan(num); }

double CalculatorModel::SqrtFuncCalc(double num) { return sqrt(num); }

double CalculatorModel::LnFuncCalc(double num) { return log(num); }

double CalculatorModel::LogFuncCalc(double num) { return log10(num); }

double CalculatorModel::GetData() const { return data_; }

void CalculatorModel::Reset() { data_ = 0.0; }

std::string CalculatorModel::CheckValid(std::string str, std::string ch) {
  if (ch.size() != 0) {
    if ((ch.front() >= '0' && ch.front() <= '9') || ch.front() == 'x' ||
        ch.front() == '.' || ch.front() == 'e') {
      str = CheckValidNum(str, ch.front());
    }
    if (ch.front() == '+' || ch.front() == '-' || ch.front() == '*' ||
        ch.front() == '/' || ch.front() == '^' || ch.front() == 'm') {
      str = CheckValidOp(str, ch.front());
    }
    if (ch.front() == '(' || ch.front() == ')') {
      str = CheckValidBr(str, ch.front());
    }
    if (ch.front() == 'c' || ch.front() == 's' || ch.front() == 't' ||
        ch.front() == 'a' || ch.front() == 'l') {
      str = CheckValidFn(str, ch);
    }
  }

  return str;  // сделать валидацию строки
}

std::string CalculatorModel::CheckValidNum(std::string str, char num) {
  std::string res = str;
  int dotFlag = 0;
  int eFlag = 0;
  CheckDotAndE(str, dotFlag, eFlag);
  if (num != '.' && num != 'e' && num != 'x') {
    if (res.back() != 'x' && res.back() != ')') {
      if ((res.back() == '.' || (res.back() >= '0' && res.back() <= '9') ||
           res.size() == 0)) {
        res = res + num;
      } else if (res.back() == '(' || res.back() == 'e') {
        res = res + num;
      } else if (eFlag) {
        res = res + num;
      } else {
        res = res + ' ' + num;
      }
    }
  } else if (num == 'x') {
    if (res.size() == 0 || res.back() == '(') {
      res = res + num;
    } else if (res.back() == '.' || (res.back() >= '0' && res.back() <= '9') ||
               res.back() == 'x' || res.back() == ')') {
      res = res + ' ' + '*' + ' ' + num;
    } else {
      res = res + ' ' + num;
    }
  } else if (num == 'e') {
    if (res.back() != 'x' && res.back() != ')' && res.size() != 0 &&
        res.back() != '(' && res.back() != 'e') {
      res = res + num;
    }
  } else {
    if (res.back() != '.' && res.back() != ')' && res.back() != 'x' &&
        dotFlag == 0 && eFlag == 0) {
      if (res.back() >= '0' && res.back() <= '9') {
        res = res + num;
      } else if (res.back() == '(') {
        res = res + '0' + num;
      } else {
        if (res.size() != 0)
          res = res + ' ' + '0' + num;
        else
          res = res + '0' + num;
      }
    }
  }
  return res;
}

std::string CalculatorModel::CheckValidOp(std::string str, char op) {
  std::string res = str;
  if (op == '-' || op == '+') {
    if (str.back() != '.') {
      if (str.back() == '+' || str.back() == '-' || str.back() == '*' ||
          str.back() == '/' || str.back() == '^') {
        str.pop_back();
        str = str + op;
      } else if (str.back() == 'd') {
        str.pop_back();
        str.pop_back();
        str.pop_back();
        str = str + op;
      } else {
        if (str.back() != '(' && str.size() != 0 && str.back() != 'e') {
          str = str + ' ' + op;
        } else {
          str = str + op;
        }
      }
    }
  } else {
    if (str.back() != '.' && str.size() != 0 && str.back() != '(') {
      if (str.back() == '+' || str.back() == '-' || str.back() == '*' ||
          str.back() == '/' || str.back() == '^') {
        str.pop_back();
        if (op != 'm')
          str = str + op;
        else
          str = str + "mod";
      } else if (str.back() == 'd') {
        str.pop_back();
        str.pop_back();
        str.pop_back();
        if (op != 'm')
          str = str + op;
        else
          str = str + "mod";
      } else {
        if (op != 'm')
          str = str + ' ' + op;
        else
          str = str + ' ' + "mod";
      }
    }
  }
  return str;
}

std::string CalculatorModel::CheckValidBr(std::string str, char op) {
  std::string res = str;
  int countOpBr = 0;
  int countClBr = 0;
  CalcNumBr(str, countOpBr, countClBr);
  if (op == '(') {
    if ((res.back() >= '0' && res.back() <= '9') || res.back() == '.' ||
        res.back() == 'x' || res.back() == ')') {
      res = res + ' ' + '*' + ' ' + op;
    } else {
      res = res + ' ' + op;
    }
  }
  if (op == ')') {
    if ((res.back() >= '0' && res.back() <= '9') || res.back() == '.' ||
        res.back() == 'x' || res.back() == ')') {
      if (countClBr < countOpBr) {
        res = res + op;
      }
    }
  }
  return res;
}

std::string CalculatorModel::CheckValidFn(std::string str, std::string fun) {
  if ((str.back() >= '0' && str.back() <= '9') || str.back() == '.' ||
      str.back() == 'x' || str.back() == ')') {
    str = str + ' ' + '*' + ' ' + fun + '(';
  } else if (str.size() == 0 || str.back() == '(') {
    str = str + fun + '(';
  } else {
    str = str + ' ' + fun + '(';
  }
  return str;
}

void CalculatorModel::CreditCalc(int type, double& monthPayment,
                                 double& overallPayment, double& overpayment,
                                 int time, double fullSum, double percent,
                                 double& firstMonPay, double& lastMonPay) {
  int month = 12 * time;
  double monthPerc = percent / (100 * 12);
  if (type == 1) {
    monthPayment = fullSum * monthPerc / (1 - pow((1 + monthPerc), -month));
    overallPayment = monthPayment * month;
    overpayment = overallPayment - fullSum;
  } else {
    double startFullSum = fullSum;
    double currentMonPay = 0;
    overallPayment = 0;
    for (int i = 1; i <= month; i++) {
      currentMonPay =
          fullSum / month + (fullSum - (i - 1) * (fullSum / month)) * monthPerc;
      if (i == 1) {
        firstMonPay = currentMonPay;
      } else if (i == month) {
        lastMonPay = currentMonPay;
      }
      overallPayment += currentMonPay;
    }
    overpayment = overallPayment - startFullSum;
  }
}

void CalculatorModel::IfClBrFind(std::string& resStr,
                                 std::stack<char>& polStack) {
  if (polStack.top() == '~') {
    polStack.pop();
  }
  if (polStack.size() > 0) {
    if (!StackTopNotFunc(polStack)) {
      resStr.push_back(' ');
      resStr.push_back(polStack.top());
      polStack.pop();
    } else {
      while (polStack.size() > 0 && polStack.top() != '(' &&
             polStack.top() != '~') {
        resStr.push_back(' ');
        resStr.push_back(polStack.top());
        polStack.pop();
        if (polStack.size() > 0 && polStack.top() == '~') {
          polStack.pop();
        }
      }
    }
  }
  if (polStack.size() > 0) polStack.pop();
}

void CalculatorModel::IfOpBrFind(std::stack<double>& calcStack, char prev,
                                 char ch) {
  if (calcStack.size() < 2 && prev != 'e') {
    throw std::invalid_argument("invalid input");
  } else {
    if (prev != 'e') {
      double firstNum = calcStack.top();
      calcStack.pop();
      double secondNum = calcStack.top();
      calcStack.pop();
      double res = ChooseOp(firstNum, secondNum, ch);
      calcStack.push(res);
    }
  }
}

void CalculatorModel::CheckDotAndE(std::string& str, int& dotFlag, int& eFlag) {
  while (str.size() != 0 &&
         ((str.back() >= '0' && str.back() <= '9') || str.back() == '.' ||
          str.back() == 'e' || str.back() == '-' || str.back() == '+')) {
    if (str.back() == '.') {
      dotFlag = 1;
      break;
    }
    if (str.back() == 'e') {
      eFlag = 1;
      break;
    }
    str.pop_back();
  }
}

void CalculatorModel::CalcNumBr(std::string str, int& opBrFind, int& clBrFind) {
  while (str.size() != 0) {
    if (str.back() == '(' || str.back() == '~') {
      ++opBrFind;
    } else if (str.back() == ')') {
      ++clBrFind;
    }
    str.pop_back();
  }
}

void CalculatorModel::CheckErrors(std::string str, int opBrFind, int clBrFind) {
  if (opBrFind != clBrFind) throw std::invalid_argument("Разное кол-во скобок");
  if (str == "-" || str == "+")
    throw std::invalid_argument("Выражение состоит только из минуса");
}

}  // namespace s21
