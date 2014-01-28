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

private:
    Ui::RandomInitializationDialog *ui;
};

#endif // RANDOMINITIALIZATIONDIALOG_H
