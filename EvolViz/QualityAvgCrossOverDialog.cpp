#include "QualityAvgCrossOverDialog.h"
#include "ui_QualityAvgCrossOverDialog.h"

QualityAvgCrossOverDialog::QualityAvgCrossOverDialog(QWidget* parent, const QString& text)
    : QDialog(parent),
      ui(new Ui::QualityAvgCrossOverDialog),
      normalizator(-2.0)
{
    ui->setupUi(this);
    ui->label->setText(text);
}

QualityAvgCrossOverDialog::~QualityAvgCrossOverDialog()
{
    delete ui;
}

double QualityAvgCrossOverDialog::getNormalizator() const
{
    return normalizator;
}

void QualityAvgCrossOverDialog::accept()
{
    normalizator = ui->doubleSpinBox->value();
    QDialog::accept();
}

void QualityAvgCrossOverDialog::reject()
{
    ui->doubleSpinBox->setValue(normalizator);
    QDialog::reject();
}
