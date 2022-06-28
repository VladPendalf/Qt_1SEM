#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> // библиотека с окошками сообщений
#include <math.h>

namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    void S( double, double, double);

    double X_1 = 0.0,
    X_2 = 0.0,
    Y_1 = 0.0,
    Y_2 = 0.0;

    int alp = 0.0,
    bet = 0.0;

    bool fl_gl;
};
#endif // MAINWINDOW_H
