#ifndef RANDOMINITIALIZATIONDIALOG_H
#define RANDOMINITIALIZATIONDIALOG_H

#include <QDialog>

namespace Ui {
class RandomInitializationDialog;
}

class RandomInitializationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RandomInitializationDialog(QWidget *parent = 0);
    ~RandomInitializationDialog();

    int getXmin() const;
    int getXmax() const;
    int getYmin() const;
    int getYmax() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::RandomInitializationDialog *ui;
    int x1;
    int x2;
    int y1;
    int y2;
};

#endif // RANDOMINITIALIZATIONDIALOG_H
