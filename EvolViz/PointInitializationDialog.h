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
    explicit PointInitializationDialog(QWidget* parent = 0);
    ~PointInitializationDialog();

    double getX() const;
    double getY() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::PointInitializationDialog* ui;

    double x;
    double y;    
};

#endif // POINTINITIALIZATIONDIALOG_H
