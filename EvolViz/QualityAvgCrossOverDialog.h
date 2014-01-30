#ifndef QUALITYAVGCROSSOVERDIALOG_H
#define QUALITYAVGCROSSOVERDIALOG_H

#include <QDialog>

namespace Ui {
class QualityAvgCrossOverDialog;
}

class QualityAvgCrossOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QualityAvgCrossOverDialog(QWidget *parent = 0);
    ~QualityAvgCrossOverDialog();

    double getNormalizator() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::QualityAvgCrossOverDialog* ui;
    double normalizator;
};

#endif // QUALITYAVGCROSSOVERDIALOG_H
