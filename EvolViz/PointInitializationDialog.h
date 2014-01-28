#ifndef POINTINITIALIZATIONDIALOG_H
#define POINTINITIALIZATIONDIALOG_H

#include <QDialog>

namespace Ui {
class PointInitializationDialog;
}

class PointInitializationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PointInitializationDialog(QWidget *parent = 0);
    ~PointInitializationDialog();

    int getX() const;
    int getY() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    int x;
    int y;

    Ui::PointInitializationDialog *ui;
};

#endif // POINTINITIALIZATIONDIALOG_H
