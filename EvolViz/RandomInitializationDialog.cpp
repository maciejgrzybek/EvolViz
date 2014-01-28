#include "RandomInitializationDialog.h"
#include "ui_RandomInitializationDialog.h"

RandomInitializationDialog::RandomInitializationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RandomInitializationDialog),
    x1(0),
    x2(0),
    y1(0),
    y2(0)
{
    ui->setupUi(this);
}

RandomInitializationDialog::~RandomInitializationDialog()
{
    delete ui;
}

void RandomInitializationDialog::accept()
{
    x1 = ui->xmin->value();
    x2 = ui->xmax->value();
    y1 = ui->ymin->value();
    y2 = ui->ymax->value();

    QDialog::accept();
}

void RandomInitializationDialog::reject()
{
    ui->xmin->setValue(x1);
    ui->xmax->setValue(x2);
    ui->ymin->setValue(y1);
    ui->ymax->setValue(y2);

    QDialog::reject();
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
