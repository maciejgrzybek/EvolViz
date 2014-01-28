#include "PointInitializationDialog.h"
#include "ui_PointInitializationDialog.h"

PointInitializationDialog::PointInitializationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PointInitializationDialog)
{
    ui->setupUi(this);
}

PointInitializationDialog::~PointInitializationDialog()
{
    delete ui;
}

int PointInitializationDialog::getX() const
{
    return ui->x->value();
}

int PointInitializationDialog::getY() const
{
    return ui->y->value();
}
