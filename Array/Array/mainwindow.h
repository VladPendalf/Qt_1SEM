#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_MAX 45
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_tableWidget_cellChanged(int row, int column);

    void on_Rand_clicked();

    void on_Sum_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change;
};

#endif // MAINWINDOW_H
