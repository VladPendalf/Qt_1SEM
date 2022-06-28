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
    void on_ButtonAddRow_clicked();

    void on_ButtonDelRow_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_ButtonGetSum_clicked();

    void on_ButtonAddColumn_clicked();

    void on_ButtonRandom_clicked();

    void on_ButtonDelColumn_clicked();

    void on_tableWidget_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
