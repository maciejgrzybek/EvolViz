#include "RandomInitializationDialog.h"
#include "ui_RandomInitializationDialog.h"

RandomInitializationDialog::RandomInitializationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomInitializationDialog)
{
    ui->setupUi(this);
}

RandomInitializationDialog::~RandomInitializationDialog()
{
    delete ui;
}

int RandomInitializationDialog::getXmin() const
{
    return ui->xmin->value();
}

int RandomInitializationDialog::getXmax() const
{
    return ui->xmax->value();
}

int RandomInitializationDialog::getYmin() const
{
    return ui->ymin->value();
}

int RandomInitializationDialog::getYmax() const
{
    return ui->ymax->value();
}
