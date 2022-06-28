#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>

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
    void on_tableWidget_cellChanged(int row, int column);

    void on_spinColumn_valueChanged(int arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change;
    int row_size;
};
#endif // MAINWINDOW_H
