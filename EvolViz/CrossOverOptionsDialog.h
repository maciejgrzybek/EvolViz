#ifndef CROSSOVEROPTIONSDIALOG_H
#define CROSSOVEROPTIONSDIALOG_H

#include <QDialog>

namespace Ui {
class CrossOverOptionsDialog;
}

class CrossOverOptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CrossOverOptionsDialog(QWidget* parent = 0,
                                    const QString& text1 = "X min", const QString& text2 = "X max",
                                    const QString& text3 = "Y min", const QString& text4 = "Y max",
                                    const QString& internalText1 = "expected", const QString& internalText2 = "variance");
    ~CrossOverOptionsDialog();

    std::pair<double, double> getXmin() const;
    std::pair<double, double> getXmax() const;
    std::pair<double, double> getYmin() const;
    std::pair<double, double> getYmax() const;

public slots:
    virtual void accept();
    virtual void reject();

private:
    Ui::CrossOverOptionsDialog* ui;
    std::pair<double, double> xMin;
    std::pair<double, double> xMax;
    std::pair<double, double> yMin;
    std::pair<double, double> yMax;
};

#endif // CROSSOVEROPTIONSDIALOG_H
