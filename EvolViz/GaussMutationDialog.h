#ifndef GAUSSMUTATIONDIALOG_H
#define GAUSSMUTATIONDIALOG_H

#include <QDialog>

namespace Ui {
class GaussMutationDialog;
}

class MutationOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MutationOptionsDialog(const QString& text1, const QString& text2, const QString& text3, const QString& text4, QWidget* parent = 0);
    ~MutationOptionsDialog();

    double getX1() const;
    double getX2() const;
    double getY1() const;
    double getY2() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::GaussMutationDialog* ui;
    double x1;
    double x2;
    double y1;
    double y2;
};

#endif // GAUSSMUTATIONDIALOG_H
