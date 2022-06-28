#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> // библиотека с окошками сообщений
#include <QColor> // библиотека с цветами (нужен оранжевый - FF8700 , (255.135.0))
#include <ctime>
#include <time.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void calc_and_color_points(void);

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_create_clicked();

    void on_pushButton_rand_clicked();

    void on_lineEdit_Name_textChanged(const QString &arg1);

    void on_lineEdit_str_textChanged(const QString &arg1);

    void on_lineEdit_dex_textChanged(const QString &arg1);

    void on_lineEdit_int_textChanged(const QString &arg1);

    void on_lineEdit_luck_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    int points;// для максимума очков
    void class_person(int,int,int,int);
};

#endif // MAINWINDOW_H
