#include "CrossOverOptionsDialog.h"
#include "ui_CrossOverOptionsDialog.h"

CrossOverOptionsDialog::CrossOverOptionsDialog(QWidget* parent,
                                               const QString& text1, const QString& text2,
                                               const QString& text3, const QString& text4,
                                               const QString& internalText1, const QString& internalText2)
    : QDialog(parent),
      ui(new Ui::CrossOverOptionsDialog),
      xMin(std::make_pair(0.0, 0.0)),
      xMax(std::make_pair(0.0, 0.0)),
      yMin(std::make_pair(0.0, 0.0)),
      yMax(std::make_pair(0.0, 0.0))
{
    ui->setupUi(this);
    ui->groupBox->setTitle(text1);
    ui->groupBox_2->setTitle(text2);
    ui->groupBox_3->setTitle(text3);
    ui->groupBox_4->setTitle(text4);

    ui->label->setText(internalText1);
    ui->label_2->setText(internalText2);
    ui->label_3->setText(internalText1);
    ui->label_4->setText(internalText2);
    ui->label_5->setText(internalText1);
    ui->label_6->setText(internalText2);
    ui->label_7->setText(internalText1);
    ui->label_8->setText(internalText2);
}

std::pair<double, double> CrossOverOptionsDialog::getXmin() const
{
    return xMin;
}

std::pair<double, double> CrossOverOptionsDialog::getXmax() const
{
    return xMax;
}

std::pair<double, double> CrossOverOptionsDialog::getYmin() const
{
    return yMin;
}

std::pair<double, double> CrossOverOptionsDialog::getYmax() const
{
    return yMax;
}

void CrossOverOptionsDialog::accept()
{
    xMin = std::make_pair(ui->xMin1->value(), ui->xMin2->value());
    xMax = std::make_pair(ui->xMax1->value(), ui->xMax2->value());
    yMin = std::make_pair(ui->yMin1->value(), ui->yMin2->value());
    yMax = std::make_pair(ui->yMax1->value(), ui->yMax2->value());
    QDialog::accept();
}

void CrossOverOptionsDialog::reject()
{
    ui->xMin1->setValue(xMin.first);
    ui->xMin2->setValue(xMin.second);
    ui->xMax1->setValue(xMax.first);
    ui->xMax2->setValue(xMax.second);

    ui->yMin1->setValue(yMin.first);
    ui->yMin2->setValue(yMin.second);
    ui->yMax1->setValue(yMax.first);
    ui->yMax2->setValue(yMax.second);
    QDialog::reject();
}

CrossOverOptionsDialog::~CrossOverOptionsDialog()
{
    delete ui;
}
