#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinColumn->setMinimum(1);
    ui->lineEdit->setReadOnly(true);

    row_size = 1;
    ui->tableWidget->setRowCount(row_size);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableWidget_cellChanged( int row, int column)
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
            no_auto_change = false;
            ui->tableWidget->item(row,column)->setBackgroundColor(Qt::red);
        }
    }
}

void MainWindow::on_spinColumn_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    no_auto_change = false;


    int size = ui->spinColumn->value();

    double res = 0;

    double *arr;
    arr = new double[size];

    bool fl_loc, fl_gl = true;

    for (int j = 0 ; j < size;j++)
    {
        if (ui->tableWidget->item(0,j) != nullptr)
        {
            arr[j] = ui->tableWidget->item(0,j)->text().toDouble(&fl_loc);
        }
        else
        {
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(0,j,ti);
            arr[j] = ui->tableWidget->item(0,j)->text().toDouble(&fl_loc);
        }
        if (fl_loc)
        {
            ui->tableWidget->item(0,j)->setBackgroundColor(Qt::white);
        }
        else
        {
            fl_gl =false;
            ui->tableWidget->item(0,j)->setBackgroundColor(Qt::red);
        }
    }

    //запись массива в ячейки
    for (int i = 0; i < size; i++)
    {
        if (ui->tableWidget->item(0,i) == nullptr)
        {
            //создаем ячейку, если её нет
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(0,i,ti);
        }
        if (ui->tableWidget->item(0,i)->text().toDouble(&fl_loc) == true)
        {
            ui->tableWidget->item(0,i)->setText(QString::number(arr[i]));
            ui->tableWidget->item(0,i)->setBackgroundColor(Qt::white); //окрашиваем в белый
        }
    }

    if (fl_gl)
    {
        for (int i = 0; i < size; i++)
        {
            if (i % 2 == 0)
            {
                res += arr[i];
            }
        }
        ui->lineEdit->setText(QString::number(res));
    }
    else
    {
        QMessageBox::warning(this,"Error","Ошибка в данных!");
    }

    no_auto_change = true;
    delete [] arr;
    arr = nullptr;
}
