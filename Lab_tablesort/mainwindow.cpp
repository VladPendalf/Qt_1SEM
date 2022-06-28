#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox_row->setMinimum(1);
    ui->spinBox_row->setMaximum(200);
    ui->tableWidget->setColumnCount(1);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    btmsort_is_click = false;
    no_auto_change = true;
}

MainWindow::~MainWindow()
{
    delete ui;
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
            ui->tableWidget->cursor();
        }
    }
    else
    {
        ui->tableWidget->item(row,column)->setBackgroundColor(Qt::red);
        ui->tableWidget->cursor();
    }
}

void MainWindow::on_spinBox_row_valueChanged(int arg1)//приравнивание значения со спинбокса таблеце
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_Button_random_clicked()//кнопка рандом
{
    no_auto_change = false;

    //запись в таблицу
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

            if (ui->tableWidget->item(i,0) != nullptr)//если ячейка существует
            {
                no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(rand()%100-60));//рандом + запись
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);//меняем цвет
            }
            else//если не существует
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
                no_auto_change= true;
                ui->tableWidget->item(i,0)->setText(QString::number(rand()%100-60));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
            }

    }

    btmsort_is_click = false;
    no_auto_change = true;
}

void MainWindow::on_Button_sort_clicked()//кнопка сортировки
{
    no_auto_change = false;

    int size = ui->tableWidget->rowCount()*ui->tableWidget->columnCount(), k = 0;
    if (size <= 40000)
    {
        double arr[40000];

        bool gl = true,loc = true;

        //проверка таблицы + запись в массив
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {

                if (ui->tableWidget->item(i,0) != nullptr)
                {
                     no_auto_change = true;
                    ui->tableWidget->item(i,0)->text().toDouble(&loc);
                    if (loc) //если это число
                    {
                        arr[k] = ui->tableWidget->item(i,0)->text().toDouble();
                        k++;
                    }
                    else //если не число
                    {
                        gl = false;
                        ui->tableWidget->item(i,0)->setBackgroundColor(Qt::red);
                    }
                }
                else //если не существует ячейки
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->tableWidget->setItem(i,0,ti);
                    gl = false;
                    loc = false;
                }

        }

        if (gl && loc)
        {
            switch (ui->comboBox->currentIndex())
            {
            case 0://bubble
                ui->Report->setVisible(true);
                Bubble_sort(arr,size);
                btmsort_is_click = true;
                break;
            case 1://Quick
                ui->Report->setVisible(true);
                Quick_sort(arr,size);
                btmsort_is_click = true;
                break;
            case 2://Combo
                ui->Report->setVisible(true);
                Combo_sort(arr,size);

                btmsort_is_click = true;
                break;
            case 3://Gnome
                ui->Report->setVisible(true);
                Gnome_sort(arr,size);
                btmsort_is_click = true;
                break;
            case 4://Bogosort
                if (hz == 1)
                {
                    ui->Report->setVisible(true);
                    Bogosort(arr,size);
                    btmsort_is_click = true;
                    break;
                }
                else
                {
                    QMessageBox::warning(this,"Error","Слишком много элементов. Будет сбой программы. \nСтабильная работа при 9 элементах.\nНажмите еще раз сортировать, чтоб выполнить \nсортировку большего числа элементов.");
                    hz = 1;
                    break;
                }
            }
        }
        else
        {
            QMessageBox::warning(this,"Error","Вы ввели некорректные данные.");
        }

        no_auto_change = true;
    }
    else //слишком много элементов - уменьшаем до минимального возможного числа
    {
        int i = 1, row_count = ui->tableWidget->rowCount();
        while (size > 40000)
        {
            size = (row_count - 1);
            row_count -= 1;
            ui->spinBox_row->setValue(row_count);
            i++;
        }
        QMessageBox::warning(this,"Error","Слишком много элементов");
    }
}

void MainWindow::Bubble_sort(double *arr, int size)
{

    for (int i = 0; i < size-1;i++)
    {
        for (int j =0; j < size-i-1;j++)
        {
            if (arr[j] > arr[j+1])
            {
                std::swap(arr[j], arr[j+1]); //идем по массиву и меняем местами
            }
        }
    }

    //выводим массив
    int k = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

            if (ui->tableWidget->item(i,0) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
                no_auto_change = true;
            }
            else
            {
                no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(arr[k]));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                k++;
            }

    }

    ui->Report->setText("Будем идти по массиву слева направо. \nЕсли текущий элемент больше следующего, меняем их местами. \nДелаем так, пока массив не будет отсортирован. \nЗаметим, что после первой итерации самый большой элемент будет находиться в конце массива, на правильном месте. \nПосле двух итераций на правильном месте будут стоять два наибольших элемента,\n и так далее. \nОчевидно, не более чем после n итераций массив будет отсортирован. \nТаким образом, асимптотика в худшем и среднем случае – O(n2), \nв лучшем случае – O(n).");

}

void MainWindow::Quick_sort(double *arr, int end) //входят partition()
{
    long i = 0, j=end;
    double P;

    P = arr[ end >>1];

    do
    {
        while (arr[i] < P) i++;
        while (arr[j] > P) j--;

        if ( i <= j)
        {
            std::swap(arr[i],arr[j]);
            i++; j--;
        }
    } while ( i <= j);
    if (j > 0) Quick_sort(arr, j);
    if (end > i) Quick_sort(arr+i, end-i);

    //выводим массив
    int k = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

            if (ui->tableWidget->item(i,0) == nullptr)
            { no_auto_change = true;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
            }
            else
            { no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(arr[k]));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                k++;
            }

    }

    ui->Report->setText("Выберем некоторый опорный элемент. \nПосле этого перекинем все элементы, меньшие его, налево, а большие – направо. \nРекурсивно вызовемся от каждой из частей. \nВ итоге получим отсортированный массив, \nтак как каждый элемент меньше опорного стоял раньше каждого большего опорного. \nАсимптотика: O(nlogn) в среднем и лучшем случае, O(n2). \nНаихудшая оценка достигается при неудачном выборе опорного элемента.");
}


bool MainWindow::isSorted(double *arr, int size)
{
    while (--size > 0)//проверка на нужность сортировки
    {
        if (arr[size - 1] > arr[size])
        {
            return false;
        }
    }
    return true;
}

void MainWindow::Combo_sort(double *arr, int size)
{
    double k = 1.2473309; //коээфициент для стабильной работы (более-менее)
    int step = size - 1;
    while (step > 1)//подготовка к сортировки
    {
        for (int i = 0; i + step < size; i++)
        {
            if (arr[i] > arr[i + step])
            {
                std::swap(arr[i], arr[i + step]);
            }
        }
        step /= k;
    }

    bool ok = true;
    while (ok)//сама сортировка
    {
        ok = false;
        for (int i = 0; i +1 < size;i++)
        {
            if (arr[i] > arr[i+1])
            {
                std::swap(arr[i],arr[i+1]);
                ok = true;
            }
        }
    }

    //выводим массив
    int m = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

            if (ui->tableWidget->item(i,0) == nullptr)
            { no_auto_change = true;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
            }
            else
            { no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(arr[m]));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                m++;
            }

    }

    ui->Report->setText("Еще одна модификация сортировки пузырьком. \nДля того, чтобы избавиться от «черепах», будем переставлять элементы, стоящие \nна расстоянии. \nЗафиксируем его и будем идти слева направо, сравнивая элементы, \nстоящие на этом расстоянии, переставляя их, если необходимо. \nОчевидно, это позволит «черепахам» быстро добраться в \nначало массива. \nОптимально изначально взять расстояние равным длине массива, а далее делить \nего на некоторый коэффициент, равный примерно 1.247. \nКогда расстояние станет равно единице, \nвыполняется сортировка пузырьком. \nВ лучшем случае асимптотика равна O(nlogn), в худшем – O(n2).");
}

void MainWindow::gnome_sort(double *arr, int size)
{
    int i = 0;

    while (i < size)
    {
        if (i == 0)
        {
            i++;
        }
        if (arr[i] >= arr[i - 1]) //если он больше предыдущего или он первый — смещаем указатель на позицию вправо
        {
            i++;
        }
        else
        {
            std::swap(arr[i], arr[i-1]);//иначе меняем текущий и предыдущий элементы местами и смещаемся влево
            i--;
        }
    }
    return;
}

void MainWindow::Gnome_sort(double *arr, int size)//входят gnome_sort()
{
    gnome_sort(arr,size);
    //выводим массив
    int m = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {

            if (ui->tableWidget->item(i,0) == nullptr)
            { no_auto_change = true;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
            }
            else
            { no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(arr[m]));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                m++;
            }

    }

    ui->Report->setText("Алгоритм похож на сортировку вставками. \nПоддерживаем указатель на текущий элемент, \nесли он больше предыдущего или он первый — смещаем указатель на позицию вправо, \nиначе меняем текущий и предыдущий элементы местами и смещаемся влево.");
}

void MainWindow::shuffle(double *arr, int size)
{
    for (int i = 0; i < size-1; i++) //меняем элементы
    {
        std::swap(arr[i], arr[rand()%size]);
    }
}

void MainWindow::Bogosort(double *arr,int size)//входят isSorted(), shuffle()
{
    isSorted(arr,size);
    while(!isSorted(arr, size))
    {
        shuffle(arr, size);
    }

    //выводим массив
    int k = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
            if (ui->tableWidget->item(i,0) == nullptr)
            { no_auto_change = true;
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,0,ti);
            }
            else
            { no_auto_change = true;
                ui->tableWidget->item(i,0)->setText(QString::number(arr[k]));
                ui->tableWidget->item(i,0)->setBackgroundColor(Qt::white);
                k++;
            }

    }

    ui->Report->setText("Bogosort (также случайная сортировка, сортировка ружья или обезьянья сортировка) \nявляется очень неэффективным алгоритмом сортировки. \nЕё используют только в образовательных целях, \nпротивопоставляя другим, более реалистичным алгоритмам. \nЕсли bogosort использовать для сортировки колоды карт, \nто сначала в алгоритме нужно проверить, лежат ли все карты по порядку, \nи если не лежат, то случайным образом перемешать её, проверить лежат \nли теперь все карты по порядку, и повторять процесс, пока не \nотсортируется колода.");

}

void MainWindow::on_Button_min_clicked()//клавиша минимум
{
    if (btmsort_is_click)//берем самый первый элемент таблицы
    {
        ui->lineEdit->setText(QString::number(ui->tableWidget->item(0,0)->text().toDouble()));
    }
    else
    {
        double arr[40000];
       for (int i = 0 ; i < ui->tableWidget->rowCount(); i++)
       {
           arr[i] = ui->tableWidget->item(i,0)->text().toDouble();
       }
       double res = arr[0];
       int i = 1, k;
       k = ui->tableWidget->rowCount();
       while (res < arr[i] && i < k)
       {
           res = arr[i];
                   i++;
       }
       ui->lineEdit->setText(QString::number(res));
    }
}

void MainWindow::on_Button_max_clicked()//клавиша максимума
{
    if (btmsort_is_click)//берем самый последний элемент таблицы
    {
        ui->lineEdit_3->setText(QString::number(ui->tableWidget->item(ui->tableWidget->rowCount() - 1,ui->tableWidget->columnCount() - 1)->text().toDouble()));
    }
    else
    {
        QMessageBox::warning(this,"Error","Отсортируйте таблицу перед применением.");
    }
}

void MainWindow::on_Button_mid_clicked()//клавиша среднего значения
{
    if (btmsort_is_click) //выбираем +- центральный элемент
    {
        ui->lineEdit_2->setText(QString::number(ui->tableWidget->item(abs(ui->tableWidget->rowCount() / 2),abs(ui->tableWidget->columnCount()/2))->text().toDouble()));
    }
    else
    {
        QMessageBox::warning(this,"Error","Отсортируйте таблицу перед применением.");
    }
}

void MainWindow::on_comboBox_currentIndexChanged(int)
{
    ui->Report->setVisible(false); //очищаем окно с описанием сортировок
}
