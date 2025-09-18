#include "mainwindow.h"
#include "calculator.hpp"
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(5);
    mainLayout->setContentsMargins(5,5,5,5);

    // Wyświetlacz
    display = new QLineEdit;
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);
    display->setStyleSheet("font-size: 24px;");
    mainLayout->addWidget(display);

    // Przyciski
    QWidget *buttonsWidget = new QWidget;
    QGridLayout *gridLayout = new QGridLayout(buttonsWidget);
    gridLayout->setSpacing(2);
    gridLayout->setContentsMargins(0,0,0,0);

    QStringList labels = {"7", "8", "9", "/",
                          "4", "5", "6", "*",
                          "1", "2", "3", "-",
                          "0", "=", "+", "AC"};

    int rows = 4;
    int cols = 4;
    int k = 0;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            QPushButton *btn = new QPushButton(labels[k]);
            btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // AC
            if (labels[k] == "AC") {
                btn->setStyleSheet(
                    "font-size:18px; background-color: lightcoral; border:1px solid gray;"
                    "QPushButton:hover { background-color: #e9967a; }");
                connect(btn, &QPushButton::clicked, this, &MainWindow::clearClicked);
            }
            // Operator
            else if (labels[k] == "+" || labels[k] == "-" || labels[k] == "*" || labels[k] == "/") {
                btn->setStyleSheet(
                    "font-size:18px; background-color: lightblue; border:1px solid gray;"
                    "QPushButton:hover { background-color: #add8e6; }");
                connect(btn, &QPushButton::clicked, this, &MainWindow::operatorClicked);
            }
            // "="
            else if (labels[k] == "=") {
                btn->setStyleSheet(
                    "font-size:18px; background-color: lightgreen; border:1px solid gray;"
                    "QPushButton:hover { background-color: #90ee90; }");
                connect(btn, &QPushButton::clicked, this, &MainWindow::equalsClicked);
            }
            // cyfry
            else {
                btn->setStyleSheet(
                    "font-size:18px; background-color: lightgray; border:1px solid gray;"
                    "QPushButton:hover { background-color: #d3d3d3; }");
                connect(btn, &QPushButton::clicked, this, &MainWindow::digitClicked);
            }

            gridLayout->addWidget(btn, i, j);
            k++;
        }
    }

    mainLayout->addWidget(buttonsWidget);
}

MainWindow::~MainWindow() {}

// Cyfry
void MainWindow::digitClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    // jeśli wynik jest wyświetlony, zaczynamy od nowa
    if (resultDisplayed) {
        firstNumberStr.clear();
        secondNumberStr.clear();
        op = 0;
        waitingForSecond = false;
        display->clear();
        resultDisplayed = false;
    }

    if (!waitingForSecond) {
        firstNumberStr += btn->text();
        display->setText(firstNumberStr);
    } else {
        secondNumberStr += btn->text();
        display->setText(secondNumberStr);
    }
}


// Operator
void MainWindow::operatorClicked() {
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    if (!firstNumberStr.isEmpty()) {
        op = btn->text().at(0).toLatin1();
        waitingForSecond = true;
        display->clear();
    }
}

// "="
void MainWindow::equalsClicked() {
    if (firstNumberStr.isEmpty() || secondNumberStr.isEmpty() || op == 0) return;

    float a = firstNumberStr.toFloat();
    float b = secondNumberStr.toFloat();

    Calculator calc(a, b, op);
    float result = calc.wynik();

    display->setText(QString::number(result));

    // Ustawienie flagi, że wynik jest wyświetlony
    resultDisplayed = true;

    // Reset operatora i drugiej liczby, pierwsza liczba to wynik
    firstNumberStr = QString::number(result);
    secondNumberStr.clear();
    op = 0;
    waitingForSecond = false;
}

// AC
void MainWindow::clearClicked() {
    firstNumberStr.clear();
    secondNumberStr.clear();
    op = 0;
    waitingForSecond = false;
    display->clear();
}
