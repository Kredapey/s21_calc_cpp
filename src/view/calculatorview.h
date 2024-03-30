#ifndef CPP3_SMARTCALC_V2_SRC_VIEW_CALCULATOR_VIEW_H
#define CPP3_SMARTCALC_V2_SRC_VIEW_CALCULATOR_VIEW_H

#include <QIntValidator>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QVector>

#include "../controller/Calculator_controller.h"
#include "dialogX.h"
#include "ui_calculatorview.h"

namespace s21 {

class CalculatorView : public QMainWindow {
  Q_OBJECT

 public:
  CalculatorView(QWidget *parent = nullptr);
  ~CalculatorView();

 private:
  Ui::CalculatorView *ui_;
  QString toCheck(QPushButton *button);
  void printInvalidInput();
  int equal_count = 0;
  double xBegin_, xEnd_, h_, X_, N_;
  QVector<double> x_, y_;
  QDoubleValidator *doubler_;
  QIntValidator *inter_;

 private slots:
  void digitNumbers();
  void operators();
  void funcs();
  void on_pushButton_eq_clicked();
  void on_pushButton_bs_clicked();
  void on_pushButton_ac_clicked();
  void on_pushButton_graph_clicked();
  void on_credit_calc_button_clicked();
};

}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_VIEW_CALCULATOR_VIEW_H
