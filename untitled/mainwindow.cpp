#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->numOfColumns->setMaximum(MAX_MAS);
    ui->numOfRows->setMaximum(MAX_MAS);
    ui->mainTable->setColumnCount(1);
    ui->mainTable->setRowCount(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_randomFill_clicked()
{
        hz = false;
        int row = ui->mainTable->rowCount();
        int col = ui->mainTable->columnCount();


        for (int i=0; i<row;i++)
        {
            for (int j=0; j<col;j++)
            {
                if (ui->mainTable->item(i,j)==nullptr) //Ячейка не определена
                {
                    QTableWidgetItem * ti; //объявили указатель на ячейку
                    ti = new QTableWidgetItem; //Выделили память (создали ячейку)
                    ui->mainTable->setItem(i,j,ti); //занесли созданную ячейку в таблицу

                }
                if ((maxRand - minRand) != 1){
                    ui->mainTable->item(i,j)->setText(QString::number(rand()%100-60)); //случайные числа от maxRand до minRand
                    ui->mainTable->item(i,j)->setBackgroundColor(Qt::white);
                }
                ui->textOut->setText("Rand");

            }

        }
}

void MainWindow::on_getMinButton_clicked()
{
    tableIsOk = isTableOK(); //проверка
    if (tableIsOk){
        float min = ui->mainTable->item(0,0)->text().toFloat();
        for (int i = 0; i< ui->mainTable->rowCount(); ++i){
            for (int j=0; j< ui->mainTable->columnCount(); ++j){
                if (ui->mainTable->item(i,j)->text().toFloat() < min){
                    min = ui->mainTable->item(i,j)->text().toFloat();
                }
            }
        }
        ui->textOut->setText("Минимум = " + QString::number(min));
    }
    else{
        ui->textOut->setText("Сначала корректно заполните таблицу");
    }
}

void MainWindow::on_getMaxButton_clicked()
{
    tableIsOk = isTableOK(); //проверка
    if (tableIsOk){
        float max = ui->mainTable->item(0,0)->text().toFloat();
        for (int i = 0; i< ui->mainTable->rowCount(); ++i){
            for (int j=0; j< ui->mainTable->columnCount(); ++j){
                if (ui->mainTable->item(i,j)->text().toFloat() > max){
                    max = ui->mainTable->item(i,j)->text().toFloat();
                }
            }
        }
        ui->textOut->setText("Максимум = " + QString::number(max));
    }
    else{
        ui->textOut->setText("Сначала корректно заполните таблицу");
    }
}

void MainWindow::on_getAvrButton_clicked()
{
    tableIsOk = isTableOK(); //проверка
    if (tableIsOk){
        sum = 0;
        for (int i = 0; i< ui->mainTable->rowCount(); ++i){
            for (int j=0; j< ui->mainTable->columnCount(); ++j){
                sum+=ui->mainTable->item(i,j)->text().toFloat();
            }
        }
        ui->textOut->setText("Среднее значение = " + QString::number(sum/(ui->mainTable->rowCount() * ui->mainTable->columnCount())));
    }
    else{
        ui->textOut->setText("Сначала корректно заполните таблицу");
    }
}

void MainWindow::on_sortButton_clicked()
{
    int num_of_elements = (ui->mainTable->rowCount())* (ui->mainTable->columnCount());

    int type = ui->typeOfSorting->currentIndex();
    int size = ui->mainTable->rowCount()*ui->mainTable->columnCount(), k = 0;
    if (size <= 200)
    {
        double arr[200];

        bool loc = true;

        //проверка таблицы + запись в массив
        for (int i = 0; i < ui->mainTable->rowCount();i++)
        {
            for (int j = 0; j < ui->mainTable->columnCount();j++)
            {
                if (ui->mainTable->item(i,j) != nullptr)
                {
                    ui->mainTable->item(i,j)->text().toDouble(&loc);
                    if (loc) //если это число
                    {
                        arr[k] = ui->mainTable->item(i,j)->text().toDouble();
                        k++;
                    }
                    else //если не число
                    {

                        ui->mainTable->item(i,j)->setBackgroundColor(Qt::red);
                    }
                }
                else //если не существует ячейки
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->mainTable->setItem(i,j,ti);

                    loc = false;
                }
            }
        }


            switch (type) {
            case 0:
                bubbleSort();
                break;
            case 1:
                fastSort();
                break;
            case 2:
                combSort();
                break;
            case 3:
                gnomeSort();
                break;
            case 4:
                if (num_of_elements > 9)
                {
                    if (!hz)
                        QMessageBox::warning(this,"Error","Слишком много элементов. Будет сбой программы. \nСтабильная работа при 9 элементах.\nНажмите еще раз сортировать, чтоб выполнить \nсортировку большего числа элементов.");
                    else
                        Bogosort(arr,size);
                    hz = true;
                    break;
                }
                else
                {
                    Bogosort(arr,size);
                    break;
                }
                break;
            }
        }
        else{
            ui->textOut->setText("Сначала корректно заполните таблицу");
        }
}

bool MainWindow::isTableOK()
{
    bool ans=true;
    for (int i = 0; i< ui->mainTable->rowCount(); ++i){
        for (int j=0; j< ui->mainTable->columnCount(); ++j){
            bool castIsOk;
            if (ui->mainTable->item(i,j) != nullptr){
                ui->mainTable->item(i,j)->text().toFloat(&castIsOk);
                if (!castIsOk){
                    ans = false;
                    ui->mainTable->scrollToItem(ui->mainTable->item(i,j));
                    ui->mainTable->editItem(ui->mainTable->item(i,j));
                    break;
                }
            }
            else{
                ui->mainTable->scrollToItem(ui->mainTable->item(i,j));
                ui->mainTable->editItem(ui->mainTable->item(i,j));
                ans = false;
                break;
            }

        }
    }
    if (ui->mainTable->rowCount() + ui->mainTable->columnCount() == 0){
        ans = false;
    }
    return ans;
}



void MainWindow::on_mainTable_itemChanged(QTableWidgetItem *item)
{
    if (item != nullptr){
            bool ok;
            item->text().toFloat(&ok);
            if (!ok){
                item->setBackground(Qt::red);
            }
            else{
                if (!isSortingNow)
                    item->setBackground(Qt::white);
            }
        }
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

void MainWindow::bubbleSort()
{
        int size = ui->mainTable->rowCount() * ui->mainTable->columnCount();
        int mas[size];
        for (int i = 0; i < ui->mainTable->rowCount(); ++ i) {
            for (int j=0; j < ui->mainTable->columnCount() ; ++j)
                mas[i*ui->mainTable->columnCount() +j] = ui->mainTable->item(i,j)->text().toFloat();
        }
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (mas[j] > mas[j + 1]) {
                    std::swap(mas[j], mas[j+1]);
                }
            }
        }

        for(int i = 0, k = 0; i < ui->mainTable->rowCount(); ++i)
            for(int j = 0; j < ui->mainTable->columnCount(); ++j)
                ui->mainTable->item(i,j)->setText(QString::number(mas[k++]));
        ui->textOut->setText(ui->textOut->toPlainText() + "\n" + "Сортировка завершена");
}

void qsortRecursive(float *mas, int size) {
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    float mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В левой части массива пропускаем(оставляем на месте) элементы, которые меньше центрального
        while(mas[i] < mid) {
            i++;
        }
        //В правой части пропускаем элементы, которые больше центрального
        while(mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            std::swap(mas[i],mas[j]);

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        qsortRecursive(&mas[i], size - i);
    }
}

void MainWindow::fastSort()
{
        int size = ui->mainTable->rowCount() * ui->mainTable->columnCount();
        float arr[size];
        for (int i = 0; i < ui->mainTable->rowCount(); ++ i) {
            for (int j=0; j < ui->mainTable->columnCount() ; ++j)
                arr[i*ui->mainTable->columnCount() +j] = ui->mainTable->item(i,j)->text().toFloat();
        }

        qsortRecursive(arr, size);
        for(int i = 0, k = 0; i < ui->mainTable->rowCount(); ++i)
            for(int j = 0; j < ui->mainTable->columnCount(); ++j)
                ui->mainTable->item(i,j)->setText(QString::number(arr[k++]));
        ui->textOut->setText(ui->textOut->toPlainText() + "\n" + "Сортировка завершена");
}

void MainWindow::combSort()
{
        int size = ui->mainTable->rowCount() * ui->mainTable->columnCount();
        float arr[size];
        for (int i = 0; i < ui->mainTable->rowCount(); ++ i) {
            for (int j=0; j < ui->mainTable->columnCount() ; ++j)
                arr[i*ui->mainTable->columnCount() +j] = ui->mainTable->item(i,j)->text().toFloat();
        }

        float factor = 1.2473309; // фактор уменьшения
        float step = size - 1; // шаг сортировки

        while (step >= 1)
        {
            for (int i = 0; i + step < size; i++)
            {
                if (arr[i] > arr[int(i + step)])
                {
                    std::swap(arr[i], arr[int(i + step)]);
                }
            }
            step /= factor;
        }

        for(int i = 0, k = 0; i < ui->mainTable->rowCount(); ++i)
            for(int j = 0; j < ui->mainTable->columnCount(); ++j)
                ui->mainTable->item(i,j)->setText(QString::number(arr[k++]));
        ui->textOut->setText(ui->textOut->toPlainText() + "\n" + "Сортировка завершена");
}

void MainWindow::gnomeSort()
{
        int n = ui->mainTable->rowCount() * ui->mainTable->columnCount();
        float arr[n];
        for (int i = 0; i < ui->mainTable->rowCount(); ++ i) {
            for (int j=0; j < ui->mainTable->columnCount() ; ++j)
                arr[i*ui->mainTable->columnCount() +j] = ui->mainTable->item(i,j)->text().toFloat();
        }

        int index = 0;

        while (index < n) {
            if (index == 0)
                index++;
            if (arr[index] >= arr[index - 1])
                index++;
            else {
                std::swap(arr[index], arr[index - 1]);
                index--;
            }
        }

        for(int i = 0, k = 0; i < ui->mainTable->rowCount(); ++i)
            for(int j = 0; j < ui->mainTable->columnCount(); ++j)
                ui->mainTable->item(i,j)->setText(QString::number(arr[k++]));
        ui->textOut->setText(ui->textOut->toPlainText() + "\n" + "Сортировка завершена");
}

bool correct(float *arr, int size) {
    while (size-- > 0)
        if (arr[size - 1] > arr[size])
            return false;
    return true;
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
    for (int i = 0; i < ui->mainTable->rowCount(); i++)
    {
        for (int j = 0; j < ui->mainTable->colorCount();j++)
        {
            if (ui->mainTable->item(i,j) == nullptr)
            {
                QTableWidgetItem *ti;
                ti = new QTableWidgetItem;
                ui->mainTable->setItem(i,j,ti);
            }
            else
            {
                ui->mainTable->item(i,j)->setText(QString::number(arr[k]));
                ui->mainTable->item(i,j)->setBackgroundColor(Qt::white);
                k++;
            }
        }
    }

}

void MainWindow::on_numOfColumns_valueChanged(int arg1)
{
    ui->mainTable->setColumnCount(arg1);
    ui->textOut->clear();
    hz = false;
}

void MainWindow::on_numOfRows_valueChanged(int arg1)
{
    ui->mainTable->setRowCount(arg1);
    ui->textOut->clear();
    hz = false;
}

