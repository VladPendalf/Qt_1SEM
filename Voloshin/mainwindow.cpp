#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->result->setReadOnly(true);
    ui->precision->clear();
    ui->number->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    double In_num, res;

    int precis = 0;

    bool fl;

    ui->number->text().toDouble(&fl);
    if (fl == true)
    {
        In_num = ui->number->text().toDouble(&fl);

        ui->precision->text().toInt(&fl);
        if (fl == true)
        {
            precis = ui->precision->text().toInt(&fl);

            res = ((In_num * pow(10.0, precis))/pow(10.0,precis));

            ui->result->setText(QString::number(res));
        }
        else
        {
            QMessageBox::warning(this,"Error","У вас ошибка в точности!");
            ui->precision->clear();
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","У вас ошибка в числе!");
        ui->number->clear();
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->precision->clear();
    ui->number->clear();
    ui->result->clear();
}
