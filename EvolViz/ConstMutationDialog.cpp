#include "ConstMutationDialog.h"
#include "ui_ConstMutationDialog.h"

ConstMutationDialog::ConstMutationDialog(QWidget* parent)
    : QDialog(parent),
      ui(new Ui::ConstMutationDialog),
      x(0.0),
      y(0.0)
{
    ui->setupUi(this);
}

void ConstMutationDialog::accept()
{
    x = ui->X->value();
    y = ui->Y->value();
    QDialog::accept();
}

void ConstMutationDialog::reject()
{
    ui->X->setValue(x);
    ui->Y->setValue(y);
    QDialog::reject();
}

ConstMutationDialog::~ConstMutationDialog()
{
    delete ui;
}

double ConstMutationDialog::getX() const
{
    return x;
}

double ConstMutationDialog::getY() const
{
    return y;
}
