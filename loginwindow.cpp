#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "dialog.h"
#include "dialog2.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include<QTextStream>
#include<QMessageBox>
#include <QInputDialog>
#include <QDir>


//UI Design by Jarif Yasir
//Code by Jarif Yasir and Ryan Irani
//class for the initial login window to prompt users to input their ID and open their needed window based on access level
//this is the main window that keeps the program running
loginWindow::loginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;
}
//initial run prompt window for user to enter their windows id to be used to access all text files
void loginWindow::SetWUID(){
    QString text = QInputDialog::getText(this, tr("Initial Setup"),
                                         tr("Windows Username for Filepaths:"), QLineEdit::Normal,
                                         QDir::home().dirName());
    WUID = text;
}
//action listener for the login button
void loginWindow::on_pushButton_clicked()
{

    QString ID = ui->lineEdit->text();
    QFile empFile("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt");//Put file path here
    //no need to write to the ID file at this point
    if(!empFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "File not Found", empFile.errorString());
        return;
    }
    QFile mgFile("C:\\Users\\" + WUID + "\\Desktop\\files\\mg_ids.txt");
    if(!mgFile.open(QIODevice::ReadOnly)){
        QMessageBox::information(0, "File not Found", mgFile.errorString());
        return;
    }

    QTextStream inEmp(&empFile);
    QTextStream inMg(&mgFile);
    //iterate through ID text file for user input
    QString readAllEmp = inEmp.readAll();
    QString readAllMg = inMg.readAll();

    if(readAllEmp.contains(ID)){
        Dialog emp;
        emp.SetWUID(WUID);;
        emp.SetID(ID);
        emp.setModal(true);
        emp.exec();
    } else if (readAllMg.contains(ID)){
        Dialog2 mg;
        mg.SetWUID(WUID);
        mg.setModal(true);
        mg.exec();
    } else if (ID.contains("mg")){
        QMessageBox::information(0, "Wrong ID", mgFile.errorString());
    } else {
        QMessageBox::information(0, "Wrong ID", empFile.errorString());
    }

}

