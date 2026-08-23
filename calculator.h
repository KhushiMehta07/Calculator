#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void numberClicked();
    void operatorClicked();
    void equalClicked();
    void clearClicked();

private:
    Ui::Calculator *ui;

    double firstNumber;
    QString currentOperator;
    bool waitingForSecondNumber;
};

#endif // CALCULATOR_H