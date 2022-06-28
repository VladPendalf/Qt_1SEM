#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    no_auto_change = true;
    ui->spinBox->setMaximum(MAX_MAX);
    ui->label_sum->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    if (no_auto_change)
    {
        bool fl;
        ui->tableWidget->item(row,column)->text().toInt(&fl);
        if (fl)
        {
            ui->tableWidget->item(row,column)->setBackgroundColor(Qt::white);
        }
        else
        {
            ui->tableWidget->item(row,column)->setBackgroundColor(Qt::red);
        }
    }
}

void MainWindow::on_Rand_clicked()
{
    no_auto_change = false;

    int arr[MAX_MAX]; // объявляем массив
    int arr_size = ui->spinBox->value(); // текущий размер

    //формирование в массиве
    for (int i = 0; i <arr_size;i++)
    {
        arr[i] = rand()%201-100;
    }

    //запись массива в таблицу
    for (int i = 0; i < arr_size;i++)
    {
        if (ui->tableWidget->item(i,0) ==nullptr)
        {
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,ti);
        }
        ui->tableWidget->item(i,0)->setText(QString::number(arr[i]));
        ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
    }

    no_auto_change = true;
}

void MainWindow::on_Sum_clicked()
{
    no_auto_change = false;

    int arr[MAX_MAX]; // объявляем массив
    int arr_size = ui->spinBox->value(); // текущий размер

    bool fl_loc, fl_gl;

    //чтение массива
    fl_gl = true;

    for (int i = 0; i < arr_size;i ++)
    {
        if (ui->tableWidget->item(i,0) !=nullptr)
        {
            arr[i] = ui->tableWidget->item(i,0)->text().toInt(&fl_loc);
        }
        else
        {
            fl_loc = false;
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,ti);
        }
        if (fl_loc)
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
        }
        else
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
            fl_gl = false;
        }
    }

    //работа с массивом
    int sum = 0;
    if (fl_gl)
    {
        for (int i = 0; i <arr_size;i++)
        {
            sum+=arr[i];
        }
    }

    //вывод результата
    if (fl_gl)
    {
        ui->label_sum->setText(QString::number(sum));
    }
    else
    {
        ui->label_sum->setText("Some errors");
    }


    no_auto_change = true;
}

void MainWindow::on_pushButton_clicked()
{
    no_auto_change = false;

    int arr[MAX_MAX]; // объявляем массив
    int arr_size = ui->spinBox->value(); // текущий размер

    bool fl_loc, fl_gl;

    //чтение массива
    fl_gl = true;

    for (int i = 0; i < arr_size;i ++)
    {
        if (ui->tableWidget->item(i,0) !=nullptr)
        {
            arr[i] = ui->tableWidget->item(i,0)->text().toInt(&fl_loc);
        }
        else
        {
            fl_loc = false;
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(i,0,ti);
        }
        if (fl_loc)
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
        }
        else
        {
            ui->tableWidget->item(i,0)->setBackgroundColor(Qt::red);
            fl_gl = false;
        }
    }

    //работа с массивом
    if (fl_gl)
    {
        for (int i = 0; i <arr_size;i++)
        {
            if (arr[i] % 2 == 0)
            {
                arr[i] +=3;
            }
            else
            {
                arr[i] += -2;
            }
        }
    }

    //вывод результата
    if (fl_gl)
    {
        for (int i = 0; i <arr_size;i++)
        {
            ui->tableWidget->item(i,0)->setText(QString::number(arr[i]));
        }
    }
    else
    {
        ui->label_sum->setText("Some errors");
    }

    no_auto_change = true;
}
