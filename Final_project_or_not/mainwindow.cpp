#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox_row->setMinimum(1);
    ui->spinBox_column->setMinimum(2);
    ui->spinBox_row->setMaximum(2000);
    ui->spinBox_column->setMaximum(2000);
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    btmsort_is_click = false;//проверка на нажатие клавиши сортировки
    line_arr = false;//проверка на линейность
    no_auto_change = true;
    count = 0;
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
        ui->tableWidget->item(row,column)->text().toDouble(&fl);
        if (fl)
        {
            ui->tableWidget->item(row,column)->setBackgroundColor(Qt::white);
            if (ui->tableWidget->item(row,column)->text().toDouble() == ui->lineEdit_search->text().toDouble())
            {
                ui->tableWidget->item(row,column)->setBackgroundColor(Qt::green);
            }
        }
        else
        {
            ui->tableWidget->item(row,column)->setBackgroundColor(Qt::red);
        }
    }
}

void MainWindow::on_spinBox_row_valueChanged(int arg1)//приравнивание значения со спинбокса таблеце
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_spinBox_column_valueChanged(int arg1)//приравнивание значения со спинбокса таблеце
{
    ui->tableWidget->setColumnCount(arg1);
}

void MainWindow::on_Button_random_clicked()//кнопка рандом
{
    no_auto_change = false;

    //запись в таблицу
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->columnCount();j++)
        {
            if (ui->tableWidget->item(i,j) != nullptr)//если ячейка существует
            {
                ui->tableWidget->item(i,j)->setText(QString::number(rand()%10000-6000));//рандом + запись
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);//меняем цвет
            }
            else//если не существует
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
                ui->tableWidget->item(i,j)->setText(QString::number(rand()%10000-6000));
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
            }
        }
    }

    btmsort_is_click = false;
    no_auto_change = true;
}

void MainWindow::on_Button_sort_clicked()//кнопка сортировки
{
    no_auto_change = false;
    btmsort_is_click = false;
    int size = ui->tableWidget->rowCount()*ui->tableWidget->columnCount(), k = 0;
    if (size <= 1000000)
    {
        double *arr;
        arr = new double[size];

        bool gl = true,loc = true;

        //проверка таблицы + запись в массив
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {
            for (int j = 0; j < ui->tableWidget->columnCount();j++)
            {
                if (ui->tableWidget->item(i,j) != nullptr)
                {
                    ui->tableWidget->item(i,j)->text().toDouble(&loc);
                    if (loc) //если это число
                    {
                        arr[k] = ui->tableWidget->item(i,j)->text().toDouble();
                        k++;
                    }
                    else //если не число
                    {
                        gl = false;
                        ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
                    }
                }
                else //если не существует ячейки
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->tableWidget->setItem(i,j,ti);
                    gl = false;
                    loc = false;
                }
            }
        }

        //линейность массива
        for (int i = 1 ; i  < size; i++)
        {
            if (arr[i-1] > arr[i])
            {
                line_arr = false;
                break;
            }
            else
            {
                line_arr = true;
            }
        }


        if (gl && loc)
        {
            switch (ui->comboBox->currentIndex())
            {
            case 0://bubble
                ui->Report->setVisible(true);
                Bubble_sort(arr,size);
                line_arr = true;
                btmsort_is_click = true;
                break;
            case 1://Quick
                ui->Report->setVisible(true);
                Quick_sort(arr,0,size-1);
                line_arr = true;
                btmsort_is_click = true;
                break;
            case 2://Combo
                ui->Report->setVisible(true);
                Combo_sort(arr,size);
                line_arr = true;
                btmsort_is_click = true;
                break;
            case 3://Gnome
                ui->Report->setVisible(true);
                Gnome_sort(arr,size);
                line_arr = true;
                btmsort_is_click = true;
                break;
            case 4://Bogosort
                if (hz == 1)
                {
                    ui->Report->setVisible(true);
                    Bogosort(arr,size);
                    line_arr = true;
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

        delete [] arr;

        no_auto_change = true;
    }
    else //слишком много элементов - уменьшаем до минимального возможного числа
    {
        int row_count = ui->tableWidget->rowCount(), column_count = ui->tableWidget->columnCount();
        while (size > 1000000)
        {
            size = (row_count - 1)*(column_count - 1);
            row_count -= 1; column_count -= 1;
            ui->spinBox_row->setValue(row_count);
            ui->spinBox_column->setValue(column_count);
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
        for (int j = 0; j < ui->tableWidget->colorCount();j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            else
            {
                ui->tableWidget->item(i,j)->setText(QString::number(arr[k]));
                k++;
            }
        }
    }

    ui->Report->setText("Будем идти по массиву слева направо. \nЕсли текущий элемент больше следующего, меняем их местами. \nДелаем так, пока массив не будет отсортирован. \nЗаметим, что после первой итерации самый большой элемент будет находиться в конце массива, на правильном месте. \nПосле двух итераций на правильном месте будут стоять два наибольших элемента,\n и так далее. \nОчевидно, не более чем после n итераций массив будет отсортирован. \nТаким образом, асимптотика в худшем и среднем случае – O(n2), \nв лучшем случае – O(n).");

}

void MainWindow::Quick_sort(double *arr, int frst, int end) //входят partition()
{
    int q;
    if (frst < end)
    {
        q = partition(arr,frst,end);
        Quick_sort(arr, frst, q-1);//вызов из левой части
        Quick_sort(arr, q+1, end);//вызов из правой части
    }

    //выводим массив
    int k = 0;
    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        for (int j = 0; j < ui->tableWidget->colorCount();j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            else
            {
                ui->tableWidget->item(i,j)->setText(QString::number(arr[k]));
                k++;
            }
        }
    }

    ui->Report->setText("Выберем некоторый опорный элемент. \nПосле этого перекинем все элементы, меньшие его, налево, а большие – направо. \nРекурсивно вызовемся от каждой из частей. \nВ итоге получим отсортированный массив, \nтак как каждый элемент меньше опорного стоял раньше каждого большего опорного. \nАсимптотика: O(nlogn) в среднем и лучшем случае, O(n2). \nНаихудшая оценка достигается при неудачном выборе опорного элемента.");
}

double MainWindow::partition(double *arr, int frst, int end)
{
    double x = *(arr+end); //в зависимости от половинки берем и меняем элементы
    int i = frst - 1;
    int j;
    for (j = frst; j < end; j++)
    {
        if (*(arr+j) <= x)
        {
            i++;
            std::swap( *(arr+i), *(arr+j));
        }
    }
    std::swap(*(arr+end), *(arr+i+1));
    return i + 1;
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
        for (int j = 0; j < ui->tableWidget->colorCount();j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            else
            {
                ui->tableWidget->item(i,j)->setText(QString::number(arr[m]));
                m++;
            }
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
        for (int j = 0; j < ui->tableWidget->colorCount();j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            else
            {
                ui->tableWidget->item(i,j)->setText(QString::number(arr[m]));
                m++;
            }
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
        for (int j = 0; j < ui->tableWidget->colorCount();j++)
        {
            if (ui->tableWidget->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->tableWidget->setItem(i,j,ti);
            }
            else
            {
                ui->tableWidget->item(i,j)->setText(QString::number(arr[k]));
                k++;
            }
        }
    }

    ui->Report->setText("Bogosort (также случайная сортировка, сортировка ружья или обезьянья сортировка) \nявляется очень неэффективным алгоритмом сортировки. \nЕё используют только в образовательных целях, \nпротивопоставляя другим, более реалистичным алгоритмам. \nЕсли bogosort использовать для сортировки колоды карт, \nто сначала в алгоритме нужно проверить, лежат ли все карты по порядку, \nи если не лежат, то случайным образом перемешать её, проверить лежат \nли теперь все карты по порядку, и повторять процесс, пока не \nотсортируется колода.");

}

void MainWindow::on_Button_min_clicked()//клавиша минимум
{
    if (btmsort_is_click)//берем самый первый элемент таблицы
    {
        ui->lineEdit->setText(QString::number(ui->tableWidget->item(0,0)->text().toDouble()));
        btmsort_is_click = false;
        no_auto_change = false;
        //ui->tableWidget->item(0,0)->setBackgroundColor(Qt::yellow);
    }
    else
    {
        QMessageBox::warning(this,"Error","Отсортируйте таблицу перед применением.");
    }
}

void MainWindow::on_Button_max_clicked()//клавиша максимума
{
    if (btmsort_is_click)//берем самый последний элемент таблицы
    {
        max = ui->tableWidget->item(ui->tableWidget->rowCount() - 1,ui->tableWidget->columnCount() - 1)->text().toDouble();
        ui->lineEdit_3->setText(QString::number(max));
        // ui->tableWidget->item(ui->tableWidget->rowCount() - 1,ui->tableWidget->columnCount() - 1)->setBackgroundColor(Qt::yellow);
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
        // ui->tableWidget->item(abs(ui->tableWidget->rowCount() / 2),abs(ui->tableWidget->columnCount()/2))->setBackgroundColor(Qt::yellow);
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

void MainWindow::on_Button_search_clicked()
{
    if (no_auto_change)
    {
        bool loc = true,gl = true;
        int k = 0, size = 0;
        size = ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
        double *arr;
        arr= new double[size];
        if (loc)
        {
            //проверка таблицы + запись в массив
            for (int i = 0; i < ui->tableWidget->rowCount();i++)
            {
                for (int j = 0; j < ui->tableWidget->columnCount();j++)
                {
                    if (ui->tableWidget->item(i,j) != nullptr)
                    {
                        ui->tableWidget->item(i,j)->text().toDouble(&loc);
                        if (loc) //если это число
                        {
                            arr[k] = ui->tableWidget->item(i,j)->text().toDouble();
                            k++;
                        }
                        else //если не число
                        {
                            ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);
                        }
                    }
                    else //если не существует ячейки
                    {
                        QTableWidgetItem *ti;
                        ti = new QTableWidgetItem;
                        ui->tableWidget->setItem(i,j,ti);
                    }
                }
            }
        }
        loc = true;
        if (gl && loc)
        {
            double res = 0,count=0;
            QString str = "Номера ячеек:";
            str.append("\n ");
            if (line_arr)//если массив упорядочен
            {
                Bin_Sort(arr, ui->lineEdit_search->text().toDouble(), (size-count));//бинарный поиск <3
            }
            else // если нет
            {
                for (int i = 0; i < (size - count); i++)
                {
                    if (arr[i] == ui->lineEdit_search->text().toDouble()) //перебор
                    {
                        res = arr[i];
                        str.append(QString::number(i+1)+";");
                        count++;
                    }

                }
                if (count != 0)
                {
                    ui->Report->setText(str + "\nВаше число встречалось -> " + QString::number(count));
                }
                else
                {
                    ui->Report->setText("Такого числа нет в таблице.");
                }
            }
        }
        delete [] arr;
        arr=nullptr;
    }
    else
    {
        QMessageBox::warning(this,"Error","Что-то не так с вашими данными.");
    }

}

void MainWindow::Bin_Sort(double *arr, double number, int size)
{
    double res = -1;
    double left = 0,
            right = size;
    QString str = "Номера ячеек:";
    str.append("\n ");
    while (left <= right)
    {
        int mid = abs(right + left)/2;
        if (number == arr[mid])
        {
            res = number;
            break;
        }
        else if (number < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid +1;
        }
    }
    if (res == -1)
    {
        ui->Report->setText("Такого числа нет в таблице.");
    }
    else
    {
        int count = 0;
        for (int i = 0; i <size; i++ )
        {
            if (res == arr[i])
            {
                str.append(QString::number(i+1)+";");
                count += 1;
            }
        }
        str.append("\nВаше число встречалось -> " + QString::number(count));
        ui->Report->setText(str);
    }
}


void MainWindow::on_Button_delete_clicked()
{
    if (btmsort_is_click)
    {
        int k = 0;
        bool loc;
        double *arr,size;
        size = ui->tableWidget->rowCount()*ui->tableWidget->columnCount();
        arr = new double[size];


        //проверка таблицы + запись в массив
        for (int i = 0; i < ui->tableWidget->rowCount();i++)
        {
            for (int j = 0; j < ui->tableWidget->columnCount();j++)
            {
                if (ui->tableWidget->item(i,j) != nullptr)
                {
                    ui->tableWidget->item(i,j)->text().toDouble(&loc);
                    if (loc) //если это число
                    {
                        arr[k] = ui->tableWidget->item(i,j)->text().toDouble();
                        k++;
                    }
                    else
                    {
                        loc = false;
                        break;

                    }
                }
                else //если не существует ячейки
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->tableWidget->setItem(i,j,ti);
                    arr[k] = 0;
                    k++;
                }
            }
        }

        if (loc)
        {
            for (int t=0;t<size ;t++ )//ищем макс элемен (мало ли)
            {
                if (arr[t]>max)
                {
                    max=arr[t];
                }
            }

            int i = 0, j = 0; k = 0;
            while (arr[k] != max) //пока элемент не максимальны, идем
            {
                while (arr[i]==arr[j])
                {
                    arr[k] = arr[i];//только 1 экземпляр
                    count++;
                    j++;
                }
                k++;
                arr[k] = arr[j];
                i=j;

            }

            QString str = " ";
            size = k+1;
            k = 0;
            for(int i = 0; i < ui->tableWidget->rowCount();i++)
            {
                for (int j = 0; j < ui->tableWidget->columnCount();j++)
                {
                    if (k < size && ui->tableWidget->item(i,j) != nullptr)
                    {
                        ui->tableWidget->item(i,j)->setText(QString::number(arr[k]));
                        k++;
                    }
                    else
                    {
                        QTableWidgetItem *ti;
                        ti = new QTableWidgetItem;
                        ui->tableWidget->setItem(i,j, ti);
                        ui->tableWidget->item(i,j)->setText(str);
                    }
                }
            }

            delete [] arr;
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Отсортируйте массив.");
    }
}
