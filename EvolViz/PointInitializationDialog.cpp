#include "PointInitializationDialog.h"
#include "ui_PointInitializationDialog.h"

PointInitializationDialog::PointInitializationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointInitializationDialog),
    x(0),
    y(0)
{
    ui->setupUi(this);
}

PointInitializationDialog::~PointInitializationDialog()
{
    delete ui;
}

void PointInitializationDialog::accept()
{
    x = ui->x->value();
    y = ui->y->value();
    QDialog::accept();
}

void PointInitializationDialog::reject()
{
    ui->x->setValue(x);
    ui->y->setValue(y);
    QDialog::reject();
}

double PointInitializationDialog::getX() const
{
    return ui->x->value();
}

double PointInitializationDialog::getY() const
{
    return ui->y->value();
}
