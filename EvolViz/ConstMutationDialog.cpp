#include "ConstMutationDialog.h"
#include "ui_ConstMutationDialog.h"

ConstMutationDialog::ConstMutationDialog(QWidget* parent, const QString& text1, const QString& text2)
    : QDialog(parent),
      ui(new Ui::ConstMutationDialog),
      x(0.0),
      y(0.0)
{
    ui->setupUi(this);
    ui->label->setText(text1);
    ui->label_2->setText(text2);
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
