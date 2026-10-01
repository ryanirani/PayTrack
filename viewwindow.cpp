#include "viewwindow.h"
#include "ui_viewwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>

//UI Design by Jarif Yasir
//Code by Jarif Yasir and Ryan Irani
//class for the 'Employee VIEW' button accessible through manager mode
ViewWindow::ViewWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewWindow)
{
    ui->setupUi(this);
}

ViewWindow::~ViewWindow()
{
    delete ui;
}

void ViewWindow::SetWUID(QString WUID){
    this->WUID = WUID;
}

//action listener for 'View Staff' button
void ViewWindow::on_pushButton_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt"); //Put Path here
    //no editing is done in these windows hence ReadOnly access
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"File not found", file.errorString());
    }
    else
    {
        QTextStream in(&file);
        //preferred text container for the sake of handling large files with scrolling
        ui->textBrowser->setText(in.readAll());
    }
}

//action listener for 'View Clock Ins' button
void ViewWindow::on_pushButton_2_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt"); //Put Path here
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"File not found", file.errorString());
    }
    else
    {
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
    }
}


//action listener for 'View Clock Outs' button
void ViewWindow::on_pushButton_3_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt"); //Put Path here
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"File not found", file.errorString());
    }
    else
    {
        QTextStream in(&file);
        ui->textBrowser->setText(in.readAll());
    }
}

