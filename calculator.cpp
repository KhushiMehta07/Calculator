#include "calculator.h"
#include "ui_calculator.h"

#include <QPushButton>
#include <QStringList>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::Calculator),
    firstNumber(0),
    currentOperator(""),
    waitingForSecondNumber(false)
{
    ui->setupUi(this);

    ui->display->setText("0");

    // Number buttons
    connect(ui->btn0, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn1, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn2, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn3, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn4, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn5, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn6, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn7, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn8, &QPushButton::clicked,
            this, &Calculator::numberClicked);
    connect(ui->btn9, &QPushButton::clicked,
            this, &Calculator::numberClicked);

    // Operators
    connect(ui->btnAdd, &QPushButton::clicked,
            this, &Calculator::operatorClicked);

    connect(ui->btnSubstract, &QPushButton::clicked,
            this, &Calculator::operatorClicked);

    connect(ui->btnMultiply, &QPushButton::clicked,
            this, &Calculator::operatorClicked);

    connect(ui->btnDivide, &QPushButton::clicked,
            this, &Calculator::operatorClicked);

    // Equal
    connect(ui->btnEqual, &QPushButton::clicked,
            this, &Calculator::equalClicked);

    // Clear
    connect(ui->btnClear, &QPushButton::clicked,
            this, &Calculator::clearClicked);
}

Calculator::~Calculator()
{
    delete ui;
}


// ===============================
// NUMBER CLICKED
// ===============================

void Calculator::numberClicked()
{
    QPushButton *button =
        qobject_cast<QPushButton*>(sender());

    if (!button)
        return;

    QString digit = button->text();
    QString currentText = ui->display->text();

    // After pressing =
    // start a new calculation
    if (waitingForSecondNumber)
    {
        ui->display->setText(digit);
        waitingForSecondNumber = false;
        return;
    }

    // Replace initial 0
    if (currentText == "0")
    {
        ui->display->setText(digit);
    }
    else
    {
        ui->display->setText(currentText + digit);
    }
}


// ===============================
// OPERATOR CLICKED
// ===============================

void Calculator::operatorClicked()
{
    QPushButton *button =
        qobject_cast<QPushButton*>(sender());

    if (!button)
        return;

    QString op = button->text();
    QString currentText = ui->display->text();

    // If previous calculation was completed
    if (waitingForSecondNumber)
    {
        QStringList parts =
            currentText.split(" ", Qt::SkipEmptyParts);

        if (!parts.isEmpty())
        {
            firstNumber = parts.last().toDouble();
        }

        ui->display->setText(
            QString::number(firstNumber) +
            " " + op + " "
            );

        currentOperator = op;
        waitingForSecondNumber = false;

        return;
    }

    // Prevent pressing two operators together
    if (currentText.endsWith(" + ") ||
        currentText.endsWith(" - ") ||
        currentText.endsWith(" * ") ||
        currentText.endsWith(" / "))
    {
        return;
    }

    // Get first number
    QStringList parts =
        currentText.split(" ", Qt::SkipEmptyParts);

    if (!parts.isEmpty())
    {
        firstNumber = parts[0].toDouble();
    }

    currentOperator = op;

    // Show operator immediately
    ui->display->setText(
        currentText + " " + op + " "
        );

    waitingForSecondNumber = false;
}


// ===============================
// EQUAL CLICKED
// ===============================

void Calculator::equalClicked()
{
    QString expression =
        ui->display->text().trimmed();

    QStringList parts =
        expression.split(" ", Qt::SkipEmptyParts);

    // Example:
    // 10 + 10
    // parts = 10, +, 10
    if (parts.size() < 3)
        return;

    double first =
        parts[0].toDouble();

    QString op =
        parts[1];

    double second =
        parts[2].toDouble();

    double result = 0;

    // Addition
    if (op == "+")
    {
        result = first + second;
    }

    // Subtraction
    else if (op == "-")
    {
        result = first - second;
    }

    // Multiplication
    else if (op == "*")
    {
        result = first * second;
    }

    // Division
    else if (op == "/")
    {
        if (second == 0)
        {
            ui->display->setText(
                "Cannot divide by zero"
                );

            waitingForSecondNumber = true;
            return;
        }

        result = first / second;
    }

    // Show complete expression
    // Example:
    // 10 + 10 = 20
    ui->display->setText(
        QString::number(first) +
        " " +
        op +
        " " +
        QString::number(second) +
        " = " +
        QString::number(result)
        );

    firstNumber = result;
    currentOperator = "";
    waitingForSecondNumber = true;
}


// ===============================
// CLEAR CLICKED
// ===============================

void Calculator::clearClicked()
{
    ui->display->setText("0");

    firstNumber = 0;
    currentOperator = "";
    waitingForSecondNumber = false;
}