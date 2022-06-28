#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    no_auto_change = true; // флаг

    ui->spinBox_Row->setMaximum(MAX); //ограничение спинбокса, чтоб не рванул
    ui->spinBox_Row->setMinimum(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Button_res_clicked() //вывод результат
{
    no_auto_change = false;

    int arr[MAX+1][2]; //массив элементов
    int arr_size = ui->spinBox_Row->value(); //текущий размер

    bool fl_loc, fl_gl;

    //чтение массива
    fl_gl = true;

    for (int i = 0; i < arr_size ;i++ )
    {
        if ((ui->tableWidget->item(i,0) != nullptr) && (ui->tableWidget->item(i,1) != nullptr))
        {
            arr[i][0] = ui->tableWidget->item(i,0)->text().toInt(&fl_loc);
            if (fl_loc)
            {
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                arr[i][1] = ui->tableWidget->item(i,1)->text().toInt(&fl_loc);
                if (fl_loc)
                {
                     ui->tableWidget->item(i,1)->setBackgroundColor(Qt::white);
                }
                else
                {
                     ui->tableWidget->item(i,1)->setBackgroundColor(Qt::red);
                     fl_gl = false;
                }
            }
            else
            {
                 ui->tableWidget->item(i,0)->setBackgroundColor(Qt::red);
                 ui->tableWidget->item(i,1)->setBackgroundColor(Qt::red);
                 fl_gl = false;
            }
        }
        else //ячейки нет - значит создаём её
        {
            if (ui->tableWidget->item(i,1) == nullptr)
            {
                fl_loc = false;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,1,ti);
            }
            if (ui->tableWidget->item(i,0) == nullptr)
            {
                fl_loc = false;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
            }
        }
    }


    //работа с массивом  (Реализация площади Гаусса)
    if (fl_gl && fl_loc)
    {
        double left_sum = 0, right_sum = 0;//результат
        int perimetr = 0;

        for (int i = 0; i < arr_size - 1; i++)
        {
            left_sum += (arr[i][0]*arr[i+1][1]);
            right_sum += (arr[i+1][0]*arr[i][1]);

            perimetr += ((sqrt(pow(arr[i+1][0] - arr[i][0],2) + pow(arr[i+1][1] - arr[i][1],2))));
        }
        perimetr += ((sqrt(pow(arr[arr_size-1][0] - arr[arr_size-2][0],2) + pow(arr[arr_size-1][1] - arr[arr_size-2][1],2))));
        left_sum += arr[arr_size-1][0]*arr[0][1];
        right_sum += arr[0][0]*arr[arr_size-1][1];

    //Вывод ответа ->
    QMessageBox answer;

    answer.setText(" Площадь = " + QString::number(((left_sum - right_sum)/2)) + "\n Периметр = " + QString::number(perimetr));

    answer.exec();
    }
    else
    {
        QMessageBox::warning(this,"Ошибка"," Вы ввели что-то кроме чисел в таблицу.");
    }
    no_auto_change = true;
}

void MainWindow::on_Button_random_clicked()//чтоб не вводить 200 значений...
{
    no_auto_change = false;

    int arr[MAX][2]; //объявление массива в MAX элементов
    int arr_size = ui->spinBox_Row->value(); //текущий размер

    for (int i = 0; i < arr_size; i++) //рандомайзер
    {
        arr[i][0] = rand()%101 - 60;
        arr[i][1] = rand()%101 - 60;
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
        ui->tableWidget->item(i,0)->setText(QString::number(arr[i][0]));
        ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
        if (ui->tableWidget->item(i,1) ==nullptr)
        {
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->tableWidget->setItem(i,1,ti);
        }
        ui->tableWidget->item(i,1)->setText(QString::number(arr[i][1]));
        ui->tableWidget->item(i,1)->setBackgroundColor(Qt::white);

    }

    no_auto_change = true;
}

void MainWindow::on_spinBox_Row_valueChanged(int arg1) //работа со спинбоксом
{
    ui->tableWidget->setRowCount(arg1);//устанавливаем кол-во строк
}

void MainWindow::on_tableWidget_cellChanged(int row, int column) //работа с таблицей
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
