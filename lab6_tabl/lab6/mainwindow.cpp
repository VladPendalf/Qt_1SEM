#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ButtonAddRow_clicked()
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->spinBoxRow->setValue(ui->tableWidget->rowCount());
}

void MainWindow::on_ButtonDelRow_clicked()
{
    int row_count=ui->tableWidget->rowCount();
    if(row_count>0){
        ui->tableWidget->setRowCount(row_count-1);
    } ui->spinBoxRow->setValue(ui->tableWidget->rowCount());
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
}

void MainWindow::on_ButtonAddColumn_clicked()
{
    ui->tableWidget->setColumnCount(ui->tableWidget->columnCount()+1);
    ui->spinBoxColumn->setValue(ui->tableWidget->columnCount());
}

void MainWindow::on_ButtonDelColumn_clicked()
{
    int column_count=ui->tableWidget->columnCount();
    if(column_count>0){
        ui->tableWidget->setColumnCount(column_count-1);
    } ui->spinBoxColumn->setValue(ui->tableWidget->columnCount());
}

void MainWindow::on_ButtonGetSum_clicked()
{
    int row_count = ui->tableWidget->rowCount();
    int col_count = ui->tableWidget->columnCount();
    int sum=0;
    bool fl;

    for (int i=0;i<row_count;i++){
        for (int j=0;j<col_count;j++){
            if(ui->tableWidget->item(i,j)!=nullptr){
                sum+=ui->tableWidget->item(i,j)->text().toInt(&fl);
                if(!fl){
                    ui->tableWidget->item(i,j)->setBackgroundColor(Qt::red);

            } else {
                   ui->tableWidget->item(i,j)->setBackgroundColor(Qt::white);
                }
            } else {
                QTableWidgetItem*ti;//завели указатель
                ti = new QTableWidgetItem;//создали ячейку
                ui->tableWidget->setItem(i,j,ti);//занесли созданную ячейку в таблицу
                ui->tableWidget->item(i,j)->setBackgroundColor(Qt::magenta);
            }
        }
        }
    ui->labelSum->setNum(sum);
    }

void MainWindow::on_ButtonRandom_clicked()
{
    int row_count = ui->tableWidget->rowCount();
    int col_count = ui->tableWidget->columnCount();

    for (int i=0;i<row_count;i++){
            for (int j=0;j<col_count;j++){
                if(ui->tableWidget->item(i,j)==nullptr){ //ячейчка не определена
                    QTableWidgetItem*ti;//завели указатель
                    ti = new QTableWidgetItem;//создали ячейку
                    ui->tableWidget->setItem(i,j,ti);//занесли созданную ячейку в таблицу
                }
                ui->tableWidget->item(i,j)->setText(QString::number(rand()%200-100));
            }
        }

}



void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    bool fl;
    ui->tableWidget->item(row,column)->text().toUInt(&fl);
    if(!fl){
        //ui->tableWidget->item(row,column)->setBackground(Qt::yellow);
    } else {
        ui->tableWidget->item(row,column)->setBackground(Qt::white);
    }
}
