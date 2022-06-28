#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.14159265

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fl_gl = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    bool Fl; QString str;

    double AB = 0.0;

    str = ui->O_X_1->text();

    //тысяча и 1 проверка; весь функционал внизу

    X_1 = str.toDouble(&Fl);
    if (Fl) // если первый аргумент норм
    {
        str.clear();
        str = ui->O_Y_1->text();
        Y_1 = str.toDouble(&Fl);
        if (Fl) // если второй норм
        {
            str.clear();
            str = ui->O_X_2->text();
            X_2 = str.toDouble(&Fl);
            if (Fl) // если третий норм
            {
                str.clear();
                str = ui->O_Y_2->text();
                Y_2 = str.toDouble(&Fl);
                if (Fl)// если четвертый
                {
                    str.clear();
                    str = ui->alpha->text();
                    alp = str.toInt(&Fl);
                    if (Fl && (alp >= 0)) //если угол норм
                    {
                        str.clear();
                        str = ui->beta->text();
                        bet = str.toInt(&Fl);
                        if (Fl && (bet >=  0)) // если второй угол норм
                        {
                            AB = sqrt(pow( ( X_2 - X_1 ) , 2 ) + pow( ( Y_2 - Y_1 ) , 2 ) );
                            // считаем площадь и периметр
                            if (AB >=  __DBL_MIN__) // нулевой вектор
                                S(alp,bet , AB);
                            else
                            {
                                Fl =false;
                                ui->O_X_1->clear();
                                ui->O_X_2->clear();
                                ui->O_Y_1->clear();
                                ui->O_Y_2->clear();
                                QMessageBox::warning(this, "Ошибка", "Вы ввели координаты нулевого вектора!");
                            }
                        }
                        else
                        {
                            Fl = false;
                            ui->beta->clear();
                            QMessageBox::warning(this, "Ошибка", "Треугольник не существует");
                        }
                    }
                    else
                    {
                        Fl = false;
                        ui->alpha->clear();
                        QMessageBox::warning(this, "Ошибка", "Треугольник не существует");
                    }
                }
                else
                {
                    Fl = false;
                    ui->O_Y_2->clear();
                    QMessageBox::warning(this, "Ошибка", "Некорректные данные в Y");
                }

            }
            else
            {
                Fl = false;
                ui->O_X_2->clear();
                QMessageBox::warning(this, "Ошибка", "Некорректные данные в X");
            }
        }
        else
        {
            Fl = false;
            ui->O_Y_1->clear();
            QMessageBox::warning(this, "Ошибка", "Некорректные данные в Y");
        }
    }
    else
    {
        Fl = false;
        ui->O_X_1->clear();
        QMessageBox::warning(this, "Ошибка", "Некорректные данные в X");
    }
}
void MainWindow::S(double alpha, double beta, double AB)
{
    double  BC = 0.0,
            AC = 0.0,
            perimetr = 0.0,
            res = 0.0;
    int gamma = 0;
    gamma = 180 - alpha - beta;

    if (gamma < __DBL_MIN__) // проверка на 0
    {
        ui->alpha->clear();
        ui->beta->clear();
        QMessageBox::warning(this, "Ошибка", "Ошибка при вычислении 3-его угла.");
    }
    else
    {

        BC = fabs( AB * sin( beta * PI / 180 ) / sin( gamma * PI / 180 ) ); // выводим стороны из теоремы синуса

        AC = fabs( AB * sin( alpha * PI / 180 ) / sin( gamma * PI / 180 ) );// выводим стороны из теоремы синуса

        perimetr = ( AB + BC + AC );
        res = (pow(AB,2)* sin( gamma * PI / 180)*sin( beta * PI / 180 ))/(2*sin( alpha * PI / 180 )) ;
        if (!qIsInf(perimetr)) // проверок много не бывает
        {
            if (!qIsNaN(perimetr))
            {
                fl_gl =true;
                if (fl_gl)
                {
                    ui->Perimetr->setNum(abs(perimetr));
                    if (!qIsInf(res))
                    {
                        if (!qIsNaN(res))
                        {
                            ui->Square->setNum(res); //великая формула Герона
                        }
                        else
                        {
                            ui->Square->setText("Невозможно подсчитать площадь");
                        }
                    }
                }
                else
                {
                    ui->Perimetr->setText("Невозможно подсчитать периметр");
                }

            }
        }
    }
}
