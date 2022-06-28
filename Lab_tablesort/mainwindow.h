#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>
#include "algorithm"
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

    void on_spinBox_row_valueChanged(int arg1);

    void on_Button_random_clicked();

    void on_Button_sort_clicked();

    void on_Button_min_clicked();

    void on_Button_max_clicked();

    void on_Button_mid_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    bool no_auto_change, btmsort_is_click;
    double mid_elem;
    int hz = 0;
    void Bubble_sort(double *arr, int size);
    void Quick_sort(double *arr,int end);
    void Combo_sort(double *arr, int size);
    double partition(double *arr, int end);
    void Gnome_sort(double *arr, int size);
    void gnome_sort(double *arr, int size);
    void Bogosort(double *arr, int size);
    bool isSorted(double *arr, int size);
    void shuffle(double *arr, int size);
};
#endif // MAINWINDOW_H
