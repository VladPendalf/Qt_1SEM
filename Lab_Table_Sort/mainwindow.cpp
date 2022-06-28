#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    no_auto_change = true;

    //Ограничиваем ввод строк и стобцов
    ui->spinRow->setMaximum(MAX_MAX);
    ui->spinRow->setMinimum(1);
    ui->spinColumn->setMaximum(MAX_MAX);
    ui->spinColumn->setMinimum(1);

    //окно с рекомендациями и (возможно ошибками)
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableWidget_cellChanged(int row, int column) //основная таблица
{
    //Проверяем на правильность элементы таблицы

}

void MainWindow::on_spinRow_valueChanged(int arg1)//спин строк
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_spinColumn_valueChanged(int arg1)//спин столбцов
{
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_Sort_of_table_currentIndexChanged(int)//выбор сортировки
{
    click = false;
}

void MainWindow::on_ButtonRand_clicked() // рандом ЦЫФИРОК
{
    no_auto_change = false;

    int arr[MAX_MAX][MAX_MAX];
    int sizeRow = ui->spinRow->value();//текущие строки
    int sizeColumn = ui->spinColumn->value();//текущие столбцы

    //рандомайзер
    for (int i = 0; i < sizeRow; i++)
    {
        for(int j = 0; j < sizeColumn; j++)
        {
            arr[i][j] = rand()%101 - 60;
        }
    }

    //запись массива в ячейки
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                //создаем ячейку, если её нет
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            ui->tableWidget->item(i,j)->setText(QString::number(arr[i][j]));
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white); //окрашиваем в белый
        }
    }

    no_auto_change = true;
}

void MainWindow::on_Button_Sort_clicked()
{
    int arr[MAX_MAX][MAX_MAX];
    int sizeRow = ui->spinRow->value();
    int sizeColumn = ui->spinColumn->value();

    bool fl;

    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0 ; j < sizeColumn;j++)
        {
            if (ui->tableWidget->item(i,j) != nullptr)
            {
                arr[i][j] = ui->tableWidget->item(i,j)->text().toInt(&fl);
            }
            else
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
                arr[i][j] = ui->tableWidget->item(i,j)->text().toInt(&fl);
            }
            if (fl)
            {
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
            }
            else
            {
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
            }
        }
    }

    /*
    void Bubble_sort( *arr, sizeRow, sizeColumn);
    void Quick_sort( *arr, sizeRow, sizeColumn);
    void Comb_sort( *arr, sizeRow, sizeColumn);
    void Gnome_sort( *arr, sizeRow, sizeColumn);
    void Bogosort_sort( *arr, sizeRow, sizeColumn);
    */
    switch (ui->Sort_of_table->currentIndex())
    {
    case 0: //пузырь
        for (int i = 0; i < sizeRow; i++)
        {
            for (int j = 0; j < sizeColumn; j++)
            {
                int m = i;
                int n = j + 1;
                while (true)
                {
                    if (n == sizeColumn)
                    {
                        n = 0;
                        m++;
                        if (m == sizeRow)
                        {
                            break;
                        }
                    }
                    if (arr[i][j] > arr[m][n])
                    {
                        std::swap(arr[i][j], arr[m][n]);
                    }
                    n++;
                }
            }
        }
        break;
    case 1: //быстрая
        int mid = arr[abs(sizeRow)/2][abs(sizeColumn)/2];

        break;
    case 2: //расческа
        break;
    case 3: //гномья
        break;
    case 4: //обезьянья
        break;
    }

    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeColumn; j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                //создаем ячейку, если её нет
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            ui->tableWidget->item(i,j)->setText(QString::number(arr[i][j]));
            min = arr[0][0];
            mid+=arr[i][j];
            max = arr[sizeRow][sizeColumn];
            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white); //окрашиваем в белый
        }
    }

}
