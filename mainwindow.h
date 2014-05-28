#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    float *mass;//исходный массив
    int size;//размер массива
    float *newmass;//результат

public slots:
    // функция записывающая данные в файл
    void Write(QString Filename);
    // функция, считывающая данные из файла
     void Read(QString Filename);
     //функция, заменяющая исходный массив на массив соответствующий требованиям по заданию
     void mainfunc();

private slots:

     //выход
     void on_action_triggered();
    //считывание информации из файла
     void on_ReadFileButton_clicked();
    //замена массива
     void on_MainButton_clicked();
    //запись результатов в файл
     void on_WriteFileButton_clicked();
    //о программе
     void on_about_triggered();

     void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QString rFile;//путь к файлу
    QString wFile;//путь к файлу

};
#endif // MAINWINDOW_H
