#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();

private:
    QLineEdit *display;

    QString firstNumberStr;
    QString secondNumberStr;
    char op = 0;
    bool waitingForSecond = false;
    bool resultDisplayed = false;
};

#endif // MAINWINDOW_H
