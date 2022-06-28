#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_MAX 200

#include <QList>
#include <algorithm>
#include <math.h>
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

    void on_spinRow_valueChanged(int arg1);

    void on_spinColumn_valueChanged(int arg1);

    void on_Sort_of_table_currentIndexChanged(int index);

    void on_ButtonRand_clicked();

    void on_Button_Sort_clicked();

private:
    Ui::MainWindow *ui;
    bool no_auto_change;
    bool click;
    bool nothing;
    int min,mid,max;
    //если массив упорядочен с начала
    /*void Bubble_sort(int *arr, int , int);
    void Quick_sort(int *arr, int , int);
    void Comb_sort(int *arr, int , int);
    void Gnome_sort(int *arr, int , int);
    void Bogosort_sort(int *arr, int , int);
    */
};
#endif // MAINWINDOW_H
