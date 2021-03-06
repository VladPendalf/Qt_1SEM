#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>

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

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

    void on_spinBox_column_valueChanged(int arg1);

    void on_spinBox_row_valueChanged(int arg1);


    void on_pushButton_rand_clicked();

    void on_pushButton_search_clicked();

private:
    Ui::MainWindow *ui;

    bool lock = false;
    bool isSortingNow=false;
};
#endif // MAINWINDOW_H
