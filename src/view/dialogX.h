#ifndef CPP3_SMARTCALC_V2_SRC_VIEW_DialogX_H
#define CPP3_SMARTCALC_V2_SRC_VIEW_DialogX_H

#include <QDialog>
#include <QDoubleValidator>

#include "ui_dialogX.h"

namespace s21 {

class DialogX : public QDialog {
  Q_OBJECT

 public:
  explicit DialogX(QWidget *parent = nullptr);
  QString getX();
  ~DialogX();

 private slots:
  void on_enter_button_clicked();

 private:
  Ui::DialogX *ui_;
};
}  // namespace s21
#endif  // CPP3_SMARTCALC_V2_SRC_VIEW_DialogX_H
