#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QString>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->status->setText("Добро пожаловать!");
    ui->lineEdit_2->setEnabled(false);
    ui->WriteFileButton->setEnabled(false);
    rFile = "C:\\Users\\Alfiya\\Desktop\\KiTPO_laba1\\Data.txt";
    wFile = "C:\\Users\\Alfiya\\Desktop\\KiTPO_laba1\\Result.txt";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow :: Write(QString FilenameWrite)
{
    QString strText = ui->lineEdit_2->text();
    strText = strText.simplified();
    strText = strText.trimmed();
    if (strText == "" || strText == " " )
    {
        ui->status->setText("Нет информации для записи");
        return;
    }
    else
    {
        QFile wrFile(FilenameWrite);
        if (!wrFile.open( QFile::WriteOnly  | QFile::Text )) //открываем файл
        {
            ui->status->setText("Не удалось открыть файл");
            return;
        }
        else
        {
            QTextStream writing(&wrFile);//переменная для записи в файл
            writing << strText; //вносим текст для записи
            wrFile.flush(); //переносим данные из буфера в файл
            ui->status->setText("Результаты занесены в файл");
            wrFile.close(); //закрываем файл
        }
    }

}

void MainWindow :: Read(QString Filename)
{
    QFile readFile(Filename);
    if (!readFile.open(QFile::ReadOnly | QFile::Text))//открываем файл
    {
        ui->status->setText("Файла не существует!");
        return;
    }
    else
    {
        QTextStream myText(&readFile);// переменная для записи в файл и чтения из него
         //&myFile - аргумент передаем как ссылку на наш файл
         QString strText = myText.readAll(); //переменная для хранения все нашей считанной
         // информации
        ui->lineEdit->clear(); //предварительно очищает наше окно вывода текста
        ui->lineEdit->setText(strText);
        ui->status->setText("Данные из файла успешно прочитаны!");
        readFile.close();//закрываем файл
    }
}

void MainWindow::mainfunc()
{
    ui->lineEdit_2->clear();
    QString myText = ui->lineEdit->text().trimmed();
    myText = myText.simplified();
    ui->status->setText("Удалены лишние пробелы");
    ui->lineEdit->setText(myText);
    QStringList lst = myText.split(" ");//разбиваем на массив символов
    QString strmass;
    size = lst.length();
    mass = new float [size];
    newmass = new float [size];
    for(int i = 0; i<size;i++)
    {
        strmass = lst.at(i);
        mass[i] = strmass.toFloat();//переводим символы в числа
        if (mass[i] == 0 && strmass != "0" && strmass != "")
        {
            QMessageBox::critical(0,"Ошибка 1","Среди введенных данных есть недопустимые символы! Можно вводить только числа ну или адекватные числа.\n\n\n Для справки: чисел 00 или 0000 не существует!");
            return;
        }
        else

        if (mass[i] == 0 && strmass == "")
        {
            QMessageBox::critical(0,"Ошибка 2","Требуемые данные не введены! Введите числа");
            return;

        }
        else
        if (mass[i]<-2147483647)
        {
            QMessageBox::critical(0,"Ошибка 3","Вы ввели слишком маленькое число");
            return;
        }
        else
        if (mass[i]>=2147483647)
        {
            QMessageBox::critical(0,"Ошибка 4","Вы ввели слишком большое число");
            return;
        }
    }
    if(size==1)
    {
        newmass[0] = mass[0];
        ui->status->setText("Среднее арифметическое одного числа равно этому же числу");
    }
    else
        if(size == 2)
        {
            newmass[0] = (mass[0] + mass[1])/2;
            newmass[1] = (mass[1] + mass[0])/2;
        }
        else
        {
            newmass[0]=(mass[size-1] + mass[0] + mass[1])/3;
            for(int i=1;i<size;i++)
            {
                newmass[i] = (mass[i+1] + mass[i] + mass[i-1])/3;
            }
            newmass[size-1]=(mass[size-2]+mass[size-1]+mass[0])/3;
        }
    QString newm;
    for(int i = 0; i<size;i++)
    {
        newm =  QString::number(newmass[i]);
        ui->lineEdit_2->setText(ui->lineEdit_2->text() + " " + newm);
    }
    ui->WriteFileButton->setEnabled(true);
    ui->status->setText("Все прошло успешно");
    delete []mass;
    delete []newmass;
}

void MainWindow::on_action_triggered()
{
   close();
}

void MainWindow::on_ReadFileButton_clicked()
{
    Read(rFile);
    ui->lineEdit_2->clear();

}

void MainWindow::on_MainButton_clicked()
{
      mainfunc();
      ui->lineEdit_2->setEnabled(true);
}

void MainWindow::on_WriteFileButton_clicked()
{
    Write(wFile);
}

void MainWindow::on_about_triggered()
{
    QString titleText("О программе");
    QString aboutText("Программа, заменяет элементы в исходном массиве на среднее арифметическое этого элемента и его соседей. Если массив содержит один элемент, то среднее арифметическое равно этому же элементу, если элементов два");
    QMessageBox::about(this,titleText,aboutText);
}

void MainWindow::on_clearButton_clicked()
{
    ui->lineEdit->clear();
}
