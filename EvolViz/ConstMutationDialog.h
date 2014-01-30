#ifndef CONSTMUTATIONDIALOG_H
#define CONSTMUTATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ConstMutationDialog;
}

class ConstMutationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConstMutationDialog(QWidget* parent = 0, const QString& text1 = "X", const QString& text2 = "Y");
    ~ConstMutationDialog();

    double getX() const;
    double getY() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::ConstMutationDialog* ui;
    double x;
    double y;
};

#endif // CONSTMUTATIONDIALOG_H
