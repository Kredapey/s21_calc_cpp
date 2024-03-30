#include "dialogX.h"

namespace s21 {
DialogX::DialogX(QWidget* parent) : QDialog(parent), ui_(new Ui::DialogX) {
  ui_->setupUi(this);
  QDoubleValidator* doubler = new QDoubleValidator(0);
  ui_->x_edit->setValidator(doubler);
}

QString DialogX::getX() { return ui_->x_edit->text(); }

DialogX::~DialogX() { delete ui_; }

void DialogX::on_enter_button_clicked() { close(); }
}  // namespace s21
