#include "calculatorview.h"

namespace s21 {
CalculatorView::CalculatorView(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::CalculatorView) {
  ui_->setupUi(this);

  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_dot, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_x, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_e, SIGNAL(clicked()), this, SLOT(digitNumbers()));
  connect(ui_->pushButton_pl, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_min, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_div, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_mul, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_pow, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_mod, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_op_br, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_cl_br, SIGNAL(clicked()), this, SLOT(operators()));
  connect(ui_->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui_->pushButton_log, SIGNAL(clicked()), this, SLOT(funcs()));

  doubler_ = new QDoubleValidator(0);
  inter_ = new QIntValidator(0);
  ui_->lineEdit_x_max->setValidator(doubler_);
  ui_->lineEdit_x_min->setValidator(doubler_);
  ui_->lineEdit_y_max->setValidator(doubler_);
  ui_->lineEdit_y_min->setValidator(doubler_);
  ui_->perc_edit_edit->setValidator(doubler_);
  ui_->sum_credit_edit->setValidator(doubler_);
  ui_->time_edit_edit->setValidator(inter_);
}

void CalculatorView::digitNumbers() {
  QPushButton* button = (QPushButton*)sender();
  QString res = toCheck(button);
  ui_->res_label->setText(res);
}

void CalculatorView::operators() {
  QPushButton* button = (QPushButton*)sender();
  QString res = toCheck(button);
  ui_->res_label->setText(res);
}

void CalculatorView::funcs() {
  QPushButton* button = (QPushButton*)sender();
  QString res = toCheck(button);
  ui_->res_label->setText(res);
}

QString CalculatorView::toCheck(QPushButton* button) {
  if (equal_count == 1) {
    ui_->res_label->clear();
    equal_count = 0;
  }
  s21::CalculatorController control;
  std::string str = ui_->res_label->text().toUtf8().constData();
  std::string ch = button->text().toUtf8().constData();
  std::string str_res = control.CheckVal(str, ch);
  QString res = QString::fromStdString(str_res);
  return res;
}

CalculatorView::~CalculatorView() {
  delete doubler_;
  delete inter_;
  delete ui_;
}

void CalculatorView::on_pushButton_eq_clicked() {
  try {
    double res = 0.0;
    s21::CalculatorController control;
    std::string str = ui_->res_label->text().toUtf8().constData();
    if (ui_->res_label->text().contains('x')) {
      DialogX x;
      x.setModal(true);
      x.exec();
      QString x_str = x.getX();
      std::string to_func_x = x_str.toUtf8().constData();
      res = control.CalcStr(str, to_func_x);
    } else {
      res = control.CalcStr(str, "\n");
    }
    control.Reset();
    QString str_res = QString::number(res);
    ui_->res_label->clear();
    ui_->res_label->setText(str_res);
  } catch (std::invalid_argument) {
    printInvalidInput();
  } catch (std::out_of_range) {
    printInvalidInput();
  }
  equal_count = 1;
}

void CalculatorView::on_pushButton_bs_clicked() {
  QString tempRes = ui_->res_label->text();
  if (tempRes.endsWith(' ')) {
    tempRes.chop(2);
  } else {
    tempRes.chop(1);
  }
  ui_->res_label->setText(tempRes);
}

void CalculatorView::on_pushButton_ac_clicked() {
  s21::CalculatorController control;
  control.Reset();
  ui_->res_label->clear();
}

void CalculatorView::on_pushButton_graph_clicked() {
  try {
    s21::CalculatorController control;
    std::string str = ui_->res_label->text().toUtf8().constData();
    ui_->widget->clearGraphs();
    double yTemp = 0.0;
    xBegin_ = ui_->lineEdit_x_min->text().toDouble();
    xEnd_ = ui_->lineEdit_x_max->text().toDouble();
    double yMin = ui_->lineEdit_y_min->text().toDouble();
    double yMax = ui_->lineEdit_y_max->text().toDouble();
    if (xBegin_ <= xEnd_ || yMin <= yMax) {
      double diff = xEnd_ - xBegin_;
      h_ = diff / 2000;
      ui_->widget->xAxis->setRange(xBegin_, xEnd_);
      ui_->widget->yAxis->setRange(yMin, yMax);
      for (X_ = xBegin_; X_ < xEnd_; X_ += h_) {
        if (X_ > -0.00001 && X_ < 0.00001) {
          X_ = 0;
        }
        x_.push_back(X_);
        QString xq_str = QString::number(X_);
        std::string x_str = xq_str.toUtf8().constData();
        yTemp = control.CalcStr(str, x_str);
        y_.push_back(yTemp);
      }
      ui_->widget->addGraph();
      ui_->widget->graph(0)->addData(x_, y_);
      ui_->widget->replot();
      x_.clear();
      y_.clear();
      ui_->widget->setInteraction(QCP::iRangeZoom, true);
      ui_->widget->setInteraction(QCP::iRangeDrag, true);
    } else {
      printInvalidInput();
    }
  } catch (std::invalid_argument) {
    printInvalidInput();
  } catch (std::out_of_range) {
    printInvalidInput();
  }
  equal_count = 1;
}

void CalculatorView::on_credit_calc_button_clicked() {
  if (!ui_->sum_credit_edit->text().isEmpty() &&
      !ui_->time_edit_edit->text().isEmpty() &&
      !ui_->perc_edit_edit->text().isEmpty()) {
    if (ui_->time_edit_edit->text().toDouble() <= 0 ||
        ui_->perc_edit_edit->text().toDouble() <= 0 ||
        ui_->sum_credit_edit->text().toDouble() <= 0) {
      QMessageBox msBox;
      msBox.setText("Некорректные данные!");
      msBox.exec();
    } else {
      s21::CalculatorController control;
      double fullSum = ui_->sum_credit_edit->text().toDouble();
      int time = ui_->time_edit_edit->text().toDouble();
      double perc = ui_->perc_edit_edit->text().toDouble();
      double overPayment = 0.0;
      double overallPayment = 0.0;
      double monthPayment = 0.0;
      double firstMonPay = 0.0;
      double lastMonPay = 0.0;
      if (ui_->diff_box->currentText() == "Аннуитентный") {
        control.CalcCredit(1, monthPayment, overallPayment, overPayment, time,
                           fullSum, perc, firstMonPay, lastMonPay);
        ui_->month_payment->setText(QString::number(monthPayment));
        ui_->overall_payment->setText(QString::number(overallPayment));
        ui_->overpayment->setText(QString::number(overPayment));
      } else {
        control.CalcCredit(0, monthPayment, overallPayment, overPayment, time,
                           fullSum, perc, firstMonPay, lastMonPay);
        QString first = QString::number(firstMonPay);
        QString last = QString::number(lastMonPay);
        ui_->month_payment->setText(first + "-" + last);
        ui_->month_payment->setText(QString::number(overallPayment));
        ui_->overpayment->setText(QString::number(overPayment));
      }
    }
  } else {
    QMessageBox msBox;
    msBox.setText("Некорректные данные!");
    msBox.exec();
  }
}

void CalculatorView::printInvalidInput() {
  ui_->res_label->clear();
  ui_->res_label->setText("Invalid input");
}

}  // namespace s21
