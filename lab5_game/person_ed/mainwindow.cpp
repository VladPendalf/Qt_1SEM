#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_clear->click();// очищает значения
    ui->lineEdit_Points->setReadOnly(true);//запрещает менять текст
    ui->lineEdit_str->setMaxLength(2);
    ui->lineEdit_dex->setMaxLength(2);
    ui->lineEdit_luck->setMaxLength(2);
    ui->lineEdit_int->setMaxLength(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Практическая работа 7 Персонаж
(Факультативная) Редактор характеристик игрового персонажа.

Базовые условия работы программы:

 - ввод имени, выбор пола персонажа; ввод первичных характеристик (например, сила, ловкость, интеллект, удача; может быть  любой набор,  не менее 4-х);

 - расчет вторичных характеристик (например, здоровье, манна, урон, защита; любой набор; не менее 4-х) на основе первичных по кнопке "ввод";

 - проверка введенных первичных характеристик на целочисленные значения, ограничения каждого из них от 1 до 10, ограничение суммы всех, например,
на 20 (отобразить на форме);

- отобразить сколько доступных очков характеристик осталось при изменении значения очередного параметра;

- динамическое (во время редактирования, или непосредственно после) подсвечивание первичных характеристик в зависимости от их значения
(например, ошибка - красный, от 1 до 3 - оранжевый  {в RGB(255.135.0) - очень похож на красный, но , всё таки, чуть-чуть отличается} (, 4-7 - желтый, 8-10 - зеленый)
 */

void MainWindow::on_pushButton_clear_clicked()
{
    {   //очищаем места вывода результатов и класса
        ui->label_hp_value->clear();
        ui->label_mp_value->clear();
        ui->label_atk_value->clear();
        ui->label_def_value->clear();
        ui->label_class_value->clear();
    }

    {   //очищаем ввод результатов и класса
        ui->lineEdit_Points->setText("20");
        ui->lineEdit_dex->setText("");
        ui->lineEdit_int->setText("");
        ui->lineEdit_luck->setText("");
        ui->lineEdit_str->setText("");
    }

    ui->lineEdit_str->setVisible(true);
    points = 20;//максимум очков
    ui->lineEdit_Points->setText(QString::number(points));//преобразуем число в текст и записываем его в lineEdit
}

void MainWindow::on_pushButton_create_clicked() //кнопка создать
{
    QString name;//имя

    int leng;//длина имени

    bool flag;//признак успешности генерации

    int str,dex,intel,luck;//параметры

    str = 0;
    dex = 0;
    intel = 0;
    luck = 0;

    name.clear();
    name = ui->lineEdit_Name->text();
    leng = name.length();

    if ((leng < 3) ||(leng >20)) // Проверка имени
    {
        flag = false;
        QMessageBox::warning(this, "Ошибка", "Длина имени должа быть от 3 до 20 симоволов.");
    }
    else
        flag = true;


    if (flag) // Проверка пола
    {
        if ((!ui->radioButton_Sex_M->isChecked())&&(!ui->radioButton_Sex_W->isChecked()))
        {
            flag = false;
            QMessageBox::warning(this, "Ошибка", "Пол не выбран.");
        }
        else
            flag = true;
    }

    if (flag) //сила
    {
        str = ui->lineEdit_str->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Сила.");
        else
        {
            if ((str <1)|| (str > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Cила должна быть от 1 до 10 включительно.");
            }
        }
    }

    if (flag) //ловкость
    {
        dex = ui->lineEdit_dex->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Ловкость.");
        else
        {
            if ((dex <1)|| (dex > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Ловкость должна быть от 1 до 10 включительно.");
            }
        }
    }

    if (flag) //интеллект
    {
        intel = ui->lineEdit_int->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Интеллект.");
        else
        {
            if ((intel <1)|| (intel > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Интеллект должна быть от 1 до 10 включительно.");
            }
        }
    }

    if (flag) //удача
    {
        luck = ui->lineEdit_luck->text().toInt(&flag);
        if (!flag)
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Удача.");
        else
        {
            if ((luck <1)|| (luck > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Удача должна быть от 1 до 10 включительно.");
            }
        }
    }

    if (flag)// проверка суммы очков
    {
        int sum = points - (str+dex+intel+luck);
        ui->lineEdit_Points->setText(QString::number(sum));
        if (sum!=0)
        {
            flag = false;
            if (sum > 0)
                QMessageBox::warning(this, "Ошибка", "Нужно потратить все очки.");
            else
                QMessageBox::warning(this, "Ошибка", "Нельзя больше чем "+QString::number(points)+" очков." );
        }
    }

    if (flag)// вывод результата
    {
        // формула характеристик
        int hp,mp,atk,def;
        hp = 8*str+2*dex;
        mp = 8*intel+dex+luck;
        atk = 6*str+2*dex+2*luck;
        def = 7*dex+3*luck;

        class_person(str,intel,dex,luck); //Выбираем класс

        //вывод
        ui->label_hp_value->setNum(hp);
        ui->label_mp_value->setNum(mp);
        ui->label_atk_value->setNum(atk);
        ui->label_def_value->setNum(def);
    }
    else //очищаем значения
    {
        ui->label_hp_value->clear();
        ui->label_mp_value->clear();
        ui->label_atk_value->clear();
        ui->label_def_value->clear();
        ui->label_class_value->clear();
    }
}

void MainWindow::on_pushButton_rand_clicked() //кнопка рандом
{
    QString name;//имя

    int leng;//длина имени

    bool flag, random;
    random = false;

    int str,dex,intel,luck;//параметры
    str = 0;
    dex = 0;
    intel = 0;
    luck = 0;

    name.clear();
    name = ui->lineEdit_Name->text();
    leng = name.length();

    if ((leng < 3) ||(leng >20)) // проверка имени
    {
        flag = false;
        QMessageBox::warning(this, "Ошибка", "Длина имени должа быть от 3 до 20 симоволов.");
    }
    else
    {
        flag = true;
        while (!random) //контролируемый бесконечный цикл
        {
            if (((str + dex + intel + luck) > points) || ((str + dex + intel + luck) < points))
            {
                str = rand() % 9 + 2;
                dex = rand() % 9 + 2;
                intel = rand() % 9 + 2;
                luck = rand() % 9 + 2;
                random = false;
            }
            else
            {
                random = true;
                ui->lineEdit_str->setText(QString::number(str));
                ui->lineEdit_dex->setText(QString::number(dex));
                ui->lineEdit_int->setText(QString::number(intel));
                ui->lineEdit_luck->setText(QString::number(luck));
            }
        }

        flag = rand() % 2; //рандом пола

        if (flag == 0)
            ui->radioButton_Sex_M->click();
        else if (flag == 1)
            ui->radioButton_Sex_W->click();


        if (random)// вывод результата
        {
            int hp,mp,atk,def;
            hp = 8*str+2*dex;
            mp = 8*intel+dex+luck;
            atk = 6*str+2*dex+2*luck;
            def = 7*dex+3*luck;

            class_person(str,intel,dex,luck);

            ui->label_hp_value->setNum(hp);
            ui->label_mp_value->setNum(mp);
            ui->label_atk_value->setNum(atk);
            ui->label_def_value->setNum(def);
        }
        else
        {
            ui->label_hp_value->clear();
            ui->label_mp_value->clear();
            ui->label_atk_value->clear();
            ui->label_def_value->clear();
            ui->label_class_value->clear();
        }
    }
}

void MainWindow::class_person(int str,int intel, int dex,int luck) // Выбор персонажа в зависимости от его статов
{
    if (ui->radioButton_Sex_M->isChecked())
    {
        if ((str > 5 && intel > 5) || (str > 5 && intel > 3 && luck > 5)) //много силы и удачи( можно чуть-чуть удачи)
        {
            if ((str > 5 && intel > 5))
                ui->label_class_value->setText("Паладин-Защитник");
            else
                ui->label_class_value->setText("Паладин-Воин");
        }
        else if ( str > 6 || (str > luck && luck > 4)) //много силы и удачи
        {
            if (str > luck && luck > 4)
                ui->label_class_value->setText("Воин");
            else
                ui->label_class_value->setText("Берсерк");
        }
        else if ((intel > 5 && luck > 5) ||(intel >5 && luck > 4 && dex > 5) || intel > 8) // много интеллекта и удачи или ловкости
        {
            if ((intel > 5 && luck > 5)||(intel > 8))
                ui->label_class_value->setText("Колдун");
            else if (intel >5 && luck > 4 && dex > 5)
                ui->label_class_value->setText("Друид");
            else
                ui->label_class_value->setText("Чернокнижник");

        }
        else if (((((luck >= 5) || (str>=5)) && dex >= 6) || (( luck >= 5) && (dex > 4) && (str > 4)) || (luck >= 8)) && (luck != 10)) //много ловкости, удачи и чуть чуть силы
        {
            if (((( luck >= 5) && (dex > 4) && (str > 4)) || (luck >= 8)) && (luck != 10))
                ui->label_class_value->setText("Вор-карманник");
            else if ((str>=5) && dex >= 6)
                ui->label_class_value->setText("Разбойник");
        }
        else
            ui->label_class_value->setText("Странник");
    }
    else
    {
        if ((str > 5 && intel > 5) || (str > 5 && intel > 3 && luck > 5))
        {
            if (str > 5 && intel > 3 && luck > 5)
                ui->label_class_value->setText("Святая дева Мария");
            else
                ui->label_class_value->setText("Жрицы Артемиды");
        }
        else if (  str > 6 || (str > luck && luck > 4) ) //
        {
            if  (str > 6)
                ui->label_class_value->setText("Воительница");
            else
                ui->label_class_value->setText("Рыцарь из ордена Крови");
        }
        else if ((intel > 5 && luck > 5) ||(intel >5 && luck > 4 && dex > 5) || intel > 8) //
        {
            if (intel > 8)
                ui->label_class_value->setText("Колдунья");
            else if (intel >5 && luck > 4 && dex > 5)
                ui->label_class_value->setText("Дриада");
            else
                ui->label_class_value->setText("Чернокнижница");
        }
        else if (((((luck >= 5) || (str>=5)) && dex >= 6) || (( luck >= 5) && (dex > 4) && (str > 4)) || (luck >= 8)) && (luck != 10))
            ui->label_class_value->setText("Разбойница");
        else
            ui->label_class_value->setText("Странница");
    }
}

void MainWindow::on_lineEdit_Name_textChanged(const QString &arg1) //Цветная проверка имени
{
    QString str = arg1;
    str=str.remove(" "); //убираем пробелы

    int dlina_str=arg1.length();

    QPalette pal=ui->lineEdit_Name->palette();

    if(dlina_str<3) //проверка длины
        pal.setColor(QPalette::Text,Qt::red);
    else
        pal.setColor(QPalette::Text,Qt::green);

    ui->lineEdit_Name->setPalette(pal);
    ui->lineEdit_Name->setText(str);
}

void MainWindow::calc_and_color_points() //расчет и расскарска остатка очков
{
    int ostatok = 0;
    ostatok=points-ui->lineEdit_str->text().toInt()-ui->lineEdit_dex->text().toInt()-ui->lineEdit_int->text().toInt()-ui->lineEdit_luck->text().toInt();

    QPalette pal=ui->lineEdit_Points->palette();

    if(ostatok==0)
        pal.setColor(QPalette::Text,Qt::green);
    else
        pal.setColor(QPalette::Text,Qt::red);

    ui->lineEdit_Points->setPalette(pal);
    ui->lineEdit_Points->setText(QString::number(ostatok));
}

void MainWindow::on_lineEdit_str_textChanged(const QString &arg1)//Цветная проверка силы
{
    bool flag = false;

    int value = arg1.toInt(&flag);

    QPalette pal=ui->lineEdit_str->palette();

    /*
    if (flag && (value>1 && value<3))

    else if ()
        pal.setColor(QPalette::Text,Qt::red);
*/

    if (flag)
    {
        if ((value > 0) && (value < 4))
            pal.setColor(QPalette::Text,QColor(255,135,0));
        else if((value >3) && (value < 8))
            pal.setColor(QPalette::Text,Qt::yellow);
        else if ((value >7) && (value < 11))
            pal.setColor(QPalette::Text,Qt::green);
        else
            pal.setColor(QPalette::Text,Qt::red);
    }

    ui->lineEdit_str->setPalette(pal);
    calc_and_color_points();
}

void MainWindow::on_lineEdit_dex_textChanged(const QString &arg1)//Цветная проверка ловкости
{
    bool flag;

    int value=arg1.toInt(&flag);

    QPalette pal=ui->lineEdit_dex->palette();

    if ((value > 0) && (value < 4))
        pal.setColor(QPalette::Text,QColor(255,135,0));
    else if((value >3) && (value < 8))
        pal.setColor(QPalette::Text,Qt::yellow);
    else if ((value >7) && (value < 11))
        pal.setColor(QPalette::Text,Qt::green);
    else
        pal.setColor(QPalette::Text,Qt::red);

    ui->lineEdit_dex->setPalette(pal);
    calc_and_color_points();
}

void MainWindow::on_lineEdit_int_textChanged(const QString &arg1)//Цветная проверка ума
{
    bool flag;

    int value=arg1.toInt(&flag);

    QPalette pal=ui->lineEdit_int->palette();

    if ((value > 0) && (value < 4))
        pal.setColor(QPalette::Text,QColor(255,135,0));
    else if((value >3) && (value < 8))
        pal.setColor(QPalette::Text,Qt::yellow);
    else if ((value >7) && (value < 11))
        pal.setColor(QPalette::Text,Qt::green);
    else
        pal.setColor(QPalette::Text,Qt::red);

    ui->lineEdit_int->setPalette(pal);
    calc_and_color_points();
}

void MainWindow::on_lineEdit_luck_textChanged(const QString &arg1)//Цветная проверка удачи
{
    bool flag;

    int value=arg1.toInt(&flag);

    QPalette pal=ui->lineEdit_luck->palette();

    if ((value > 0) && (value < 4))
        pal.setColor(QPalette::Text,QColor(255,135,0));
    else if((value >3) && (value < 8))
        pal.setColor(QPalette::Text,Qt::yellow);
    else if ((value >7) && (value < 11))
        pal.setColor(QPalette::Text,Qt::green);
    else
        pal.setColor(QPalette::Text,Qt::red);

    ui->lineEdit_luck->setPalette(pal);
    calc_and_color_points();
}
