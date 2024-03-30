#include <QApplication>

#include "./view/calculatorview.h"

int main(int argc, char *argv[]) {
  setlocale(LC_NUMERIC, "C");
  QApplication a(argc, argv);
  s21::CalculatorView w;
  w.show();
  return a.exec();
}
