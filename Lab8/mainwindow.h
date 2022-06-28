#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX 200

#include <QMainWindow>
#include <QMessageBox>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Button_res_clicked();

    void on_Button_random_clicked();

    void on_spinBox_Row_valueChanged(int arg1);

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
    bool no_auto_change;
};
#endif // MAINWINDOW_H
