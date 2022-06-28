#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_comboBox_LogOp_currentIndexChanged(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_LogOp_currentIndexChanged(int ) // Выбор операции
{
    my_func();
}

void MainWindow::on_comboBox_OP1_currentIndexChanged(int ) // Считывание значения с первой кнопки
{  
    my_func();
}

void MainWindow::on_comboBox_OP2_currentIndexChanged(int ) // Считывание значения со второй кнопки
{
    my_func();
}

void MainWindow::my_func() // считывание значений
{

    QPalette pal;
    pal=ui->centralWidget->palette(); //считали палитру

    int LogOp = 0;

    bool  res = false;


    LogOp = ui->comboBox_LogOp->currentIndex();// приравнивание индекса переменной

    switch (LogOp)
    {
    case 0: //конъюнкция
        ui->comboBox_OP2->setVisible(true);
        res = ((ui->comboBox_OP1->currentIndex()) && (ui->comboBox_OP2->currentIndex()));
        break;
    case 1: //дизъюнкция
        ui->comboBox_OP2->setVisible(true);
        res = ((ui->comboBox_OP1->currentIndex() > 0) || (ui->comboBox_OP2->currentIndex() > 0));
        break;
    case 2: //отрицание
        ui->comboBox_OP2->setVisible(false);
        res = !(ui->comboBox_OP1->currentIndex() > 0);
        break;
    case 3: //сложение по модулю (XOR)
        ui->comboBox_OP2->setVisible(true);
        res = !(ui->comboBox_OP1->currentIndex() == ui->comboBox_OP2->currentIndex());
        break;
    case 4: //Следование
        ui->comboBox_OP2->setVisible(true);
        res = !(ui->comboBox_OP1->currentIndex() > 0 && !(ui->comboBox_OP2->currentIndex() > 0));
        break;
    case 5: //эквивалентность
        ui->comboBox_OP2->setVisible(true);
        res = (ui->comboBox_OP1->currentIndex() == ui->comboBox_OP2->currentIndex());
        break;
    }
    if (res) // если результат - истина
    {
        pal.setColor(QPalette::Window,Qt::green);
        ui->centralWidget->setAutoFillBackground(true); //разрешаем автозаливку
        ui->centralWidget->setPalette(pal); //присваиваем измененную палитру
    }
    else //если результат - ложь
    {
        pal.setColor(QPalette::Window,Qt::red);
        ui->centralWidget->setAutoFillBackground(true); //разрешаем автозаливку
        ui->centralWidget->setPalette(pal); //присваиваем измененную палитру
    }
}
