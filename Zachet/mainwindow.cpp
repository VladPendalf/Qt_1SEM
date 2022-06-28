#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox_row->setMinimum(1);
    ui->spinBox_column->setMinimum(1);

    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(1);

    ui->answer->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item)
{

    if (item != nullptr) //ячейка существует
    {
        bool ok;

        item->text().toDouble(&ok);

        if (!ok) //число не преобразовалось
        {
            item->setBackground(Qt::red);

            lock = true;
        }
        else
        {
            lock = false;

            if (!isSortingNow)
            {
                item->setBackground(Qt::white);
            }
        }


        ui->answer->clear();
    }
}

void MainWindow::on_spinBox_column_valueChanged(int arg1)
{
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_spinBox_row_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_pushButton_rand_clicked()
{
    ui->answer->clear();

    int row = ui->tableWidget->rowCount(); //число строк
    int column = ui->tableWidget->columnCount();

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr) //Ячейки не существует
            {
                QTableWidgetItem *ti; //объявили указатель
                ti = new QTableWidgetItem; //выделили память под ячейку
                ui->tableWidget->setItem(i,j,ti); //создали ячейку
            }
            ui->tableWidget->item(i,j)->setText(QString::number(rand()%1000-600)); //случайные числа
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
        }
    }
    //очищаем окошки вывода
    ui->answer->clear();
}

void MainWindow::on_pushButton_search_clicked()
{
    if (!lock)
    {

        double *arr;

        int size =
                ui->tableWidget->rowCount() * ui->tableWidget->columnCount(),
                i = 0;

        arr = new double[size];

        while (i < size)
        {
            for (int m = 0; m < ui->tableWidget->rowCount(); m++)
            {
                for (int n = 0; n < ui->tableWidget->columnCount(); n++)
                {
                    arr[i] = ui->tableWidget->item(m,n)->text().toDouble();
                    i++;
                }
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Bad input");
    }
}
