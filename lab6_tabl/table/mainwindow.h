#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_AddRow_clicked();

    void on_DelRow_clicked();

    void on_AddCol_clicked();

    void on_DelCol_clicked();

    void on_GetSum_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_SetRandom_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
