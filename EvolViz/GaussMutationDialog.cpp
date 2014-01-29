#include "GaussMutationDialog.h"
#include "ui_GaussMutationDialog.h"

MutationOptionsDialog::MutationOptionsDialog(const QString& text1,
                                         const QString& text2,
                                         const QString& text3,
                                         const QString& text4,
                                         QWidget* parent)
    : QDialog(parent),
      ui(new Ui::GaussMutationDialog),
      x1(0.0),
      x2(0.3),
      y1(0.0),
      y2(0.3)
{
    ui->setupUi(this);

    ui->label->setText(text1);
    ui->label_2->setText(text2);
    ui->label_3->setText(text3);
    ui->label_4->setText(text4);
}

void MutationOptionsDialog::accept()
{
    x1 = ui->expectedX->value();
    x2 = ui->varianceX->value();
    y1 = ui->expectedY->value();
    y2 = ui->varianceY->value();
    QDialog::accept();
}

void MutationOptionsDialog::reject()
{
    ui->expectedX->setValue(x1);
    ui->varianceX->setValue(x2);
    ui->expectedY->setValue(y1);
    ui->varianceY->setValue(y2);
    QDialog::reject();
}

MutationOptionsDialog::~MutationOptionsDialog()
{
    delete ui;
}

double MutationOptionsDialog::getX1() const
{
    return ui->expectedX->value();
}

double MutationOptionsDialog::getX2() const
{
    return ui->varianceX->value();
}

double MutationOptionsDialog::getY1() const
{
    return ui->expectedY->value();
}

double MutationOptionsDialog::getY2() const
{
    return ui->varianceY->value();
}
