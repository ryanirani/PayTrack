#include "dialog2.h"
#include "ui_dialog2.h"
#include <QString>
#include "addname.h"
#include "removename.h"
#include "viewwindow.h"
#include "schdule.h"
#include"jobadd.h"
#include"jobremove.h"
#include"jobsview.h"
#include"assignjob.h"
#include "payview.h"
#include<QMessageBox>


//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class for administrative mode (post-manager login)
Dialog2::Dialog2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::SetWUID(QString WUID){
    this->WUID = WUID;
}

//Action listener for 'Employee ADD' button
void Dialog2::on_pushButton_clicked()
{
    AddName addName;
    addName.SetMgMode(false);
    addName.SetWUID(WUID);
    addName.setModal(true);
    addName.exec();
}

//Action listener for 'Employee REMOVE' button
void Dialog2::on_pushButton_2_clicked()
{
    RemoveName removeName;
    removeName.SetMgMode(false);
    removeName.SetWUID(WUID);
    removeName.setModal(true);
    removeName.exec();
}




//Action listener for 'Employee VIEW' button
void Dialog2::on_pushButton_5_clicked()
{
    ViewWindow view;
    view.SetWUID(WUID);
    view.setModal(true);
    view.exec();
}


//Action listener for 'Employee SCHEDULE' button
void Dialog2::on_pushButton_7_clicked()
{
    Schdule assign;
    assign.SetWUID(WUID);
    assign.setModal(true);
    assign.exec();

}

//Action listener for 'MANAGERS ADD' button
void Dialog2::on_pushButton_8_clicked()
{
    AddName assign;
    assign.SetMgMode(true);
    assign.SetWUID(WUID);
    assign.setModal(true);
    assign.exec();

}

//Action listener for 'JOBS ADD' button
void Dialog2::on_pushButton_3_clicked()
{
    JobAdd job;
    job.SetWUID(WUID);
    job.setModal(true);
    job.exec();
}

//Action listener for 'JOBS REMOVE' button
void Dialog2::on_pushButton_4_clicked()
{
    jobRemove job;
    job.SetWUID(WUID);
    job.setModal(true);
    job.exec();
}

//Action listener for 'JOBS VIEW' button
void Dialog2::on_pushButton_6_clicked()
{
    JobsView view;
    view.SetWUID(WUID);
    view.setModal(true);
    view.exec();
}


//Action listener for 'JOBS ASSIGN' button
void Dialog2::on_pushButton_12_clicked()
{
    AssignJob job;
    job.SetWUID(WUID);
    job.setModal(true);
    job.exec();
}

//Action listener for 'MANAGERS REMOVE' button
void Dialog2::on_pushButton_9_clicked()
{
    RemoveName removeName;
    removeName.SetMgMode(true);
    removeName.SetWUID(WUID);
    removeName.setModal(true);
    removeName.exec();
}

//Action listener for 'PAYROLL VIEW' button
void Dialog2::on_pushButton_11_clicked()
{
    PayView PAYview;
    PAYview.SetWUID(WUID);
    PAYview.setModal(true);
    PAYview.exec();
}

//Action listeners for various help buttons:
void Dialog2::on_pushButton_16_clicked()
{
    QString message = " Button fuctions\n ADD: Add an employee\n REMOVE: Remove an employee\n VIEW: View employee list, Employee Clock in and Clock out times\n SCHEDULE: Create and View schedules";
    QMessageBox::information(this, tr("Help Window"), message);
}



void Dialog2::on_pushButton_15_clicked()
{
    QString message = " Button fuctions\n ADD: Add a job\n REMOVE: Remove a job\n VIEW: View jobs list\n ASSIGN: Assign jobs to employees";
    QMessageBox::information(this, tr("Application Name"), message);
}


void Dialog2::on_pushButton_14_clicked()
{
    QString message = " Button fuctions\n ADD: Add a Manager\n REMOVE: Remove a Manager";
    QMessageBox::information(this, tr("Help Window"), message);
}


void Dialog2::on_pushButton_13_clicked()
{
    QString message = " Button fuctions\n VIEW: View and create payroll, check employee hours this week";
    QMessageBox::information(this, tr("Help Window"), message);
}





