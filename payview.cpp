#include "payview.h"
#include "ui_payview.h"
#include "viewpaystub.h"
#include<QFile>
#include<QMessageBox>
#include<dialog2.h>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include<QTime>
#include <QFileDialog>

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class to view and export employees worked hours and respective payroll
//allows manager to reset employees worked shifts at the end of each cycle
PayView::PayView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PayView)
{
    ui->setupUi(this);
}

PayView::~PayView()
{
    delete ui;
}
//loads employee ids with typical setter method
void PayView::SetWUID(QString WUID){
    this->WUID = WUID;
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt"); // PASTE PATH HERE
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine().split(",").at(0);
            ui->comboBox->addItem(line);
        }
        file.close();
    }
}

//action listener for viewing a desired employees worked hours
void PayView::on_pushButton_clicked()
{

    QString emp = ui->comboBox->currentText();

    QFile clockfile("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt");

//Getting clock in/out time
    if (!clockfile.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0, "File not Found", clockfile.errorString());
    }
    else
    {
        //while loop to calculate an employees worked hours from strictly their shifts
        int netH;
        int netM;
        QTextStream in(&clockfile);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line.contains(emp) && line.contains("*"))
            {
                QString timePart = line.split("-").at(1);
                QStringList timeList = timePart.split('/');
                QTime clockIn1 = QTime::fromString(timeList.at(0), "hh:mm:ss");
                QTime clockOut2 = QTime::fromString(timeList.at(1), "hh:mm:ss");
                int hourIn = clockIn1.hour();
                int minuteIn = clockIn1.minute();
                int hourOut = clockOut2.hour();
                int minuteOut = clockOut2.minute();
                netH = netH + (hourOut - hourIn);
                netM = netM + (minuteOut - minuteIn);

            }
            //while loop to readjust for each shift if an employee clocked in at a time with a larger minute
            //value then when they clocked out i.e. 04:45:00/10:15:00
            while (netM < 0){
                netM += 60;
                netH -= 1;
            }
        }
        QString msg = emp + "has worked " + QString::number(netH) + " hours and "+ QString::number(netM) + " minutes this week.";
        QMessageBox::information(nullptr, "Work hours this week", msg);

    }


}
//function to return a formatted string containing a list of hour many hours
//each employee worked during their shifts. only shows employees with completed shifts
//displays calculated employee payout if they are assigned a job
QString PayView::toString(){
    //String that will be constantly updated with paystub data and returned by function
    QString payStub = "**************************************************************\n";
    QFile ids("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt");
    QFile clockFile("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt");
    if (ids.open(QIODeviceBase::ReadOnly)){
        QTextStream idRead(&ids);
        while (!idRead.atEnd()){
            QString currEmp = idRead.readLine();
            QString tmp = currEmp;
            //partitions employee id if they are assigned a job
            if(currEmp.contains(",")){
                QString tmp2 = currEmp.mid(0, currEmp.indexOf(","));
                currEmp = tmp2;
            }
            //data types to track an employees net hours and net shifts completed
            double netH = 0;
            int totalShifts = 0;
            if (clockFile.open(QIODeviceBase::ReadOnly) && !currEmp.isEmpty()){
                QTextStream clock(&clockFile);
                while (!clock.atEnd()){
                    QString shift = clock.readLine();
                    //checks if shift is completed and from the current employee the program is writing payout for
                    if (shift.contains(currEmp) && shift.contains("*")){
                        //writes employee name at the top of the section before writing their shifts and payout
                        if(!payStub.contains(currEmp)){
                            payStub += currEmp + "\n";
                        }
                        //using special character indicated to breakdown the shift times
                        QString shiftTime = shift.split("|").at(1);
                        payStub += shiftTime + " = ";
                        QString timePart = shift.split("-").at(1);
                        QStringList timeList = timePart.split('/');
                        QTime clockIn1 = QTime::fromString(timeList.at(0), "hh:mm:ss");
                        QTime clockOut2 = QTime::fromString(timeList.at(1), "hh:mm:ss");
                        int hourIn = clockIn1.hour();
                        int minuteIn = clockIn1.minute();
                        int hourOut = clockOut2.hour();
                        int minuteOut = clockOut2.minute();
                        double shiftNet;
                        //accounts for overnight shifts
                        if (hourIn > hourOut){
                            shiftNet = 24 - hourIn + hourOut;
                        } else {
                            shiftNet = hourOut - hourIn;
                        }
                        if (minuteIn > minuteOut){
                            int tmp = 60 - minuteIn + minuteOut;
                            shiftNet += 0.5 * (tmp/30);
                        } else {
                            int tmp = minuteOut - minuteIn;
                            shiftNet += 0.5 * (tmp/30);
                        }
                        //updates net worked hours/shifts
                        totalShifts++;
                        netH += shiftNet;
                        payStub += QString::number(shiftNet) + "\n" ;
                    }
                }
                payStub += "Total current worked hours: " + QString::number(netH) + "\n";
                //calculates employees payout based on worked hours if they are assigned a job
                if (tmp.contains("$")){
                    QString pay = tmp.split("$").at(1);
                    double payRate = pay.split("/").at(0).toDouble();
                    double netPay = 0;
                    //paid per shift if they work a flat rate job
                    if (pay.contains("F")){
                        netPay = payRate * totalShifts;
                    //paid per hour if they work an hourly rate job
                    } else if (pay.contains("H")){
                        netPay = payRate * netH;
                    }
                    payStub += "Net pay: " + QString::number(netPay) + "\n";
                }
                payStub += "**************************************************************\n";
                clockFile.close();
            }
        }
    }
    return payStub;
}
//function to get the manager to select a desired file that the paystubs will be written to
void PayView::on_pushButton_2_clicked(){
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save Paystubs"));
    QFile clockFile("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt");
    QList<QString> clockList;
    if (!filePath.isEmpty()){
        QFile exportFile(filePath);
        //writes paystub contents to file if the desired file opens successfully
        if (exportFile.open(QIODevice::WriteOnly)){
            QTextStream payStream(&exportFile);
            payStream << this->toString();
            exportFile.close();
            //prompts manager to remove the completed shifts from the list, useful for resetting for next payout cycle
            QMessageBox resetHours;
            resetHours.setText("Do you want to reset all Employee's current worked hours?");
            resetHours.setInformativeText("Paystubs have been saved to " + filePath);
            resetHours.setStandardButtons(QMessageBox::Reset|QMessageBox::No);
            resetHours.setDefaultButton(QMessageBox::Reset);
            int choice = resetHours.exec();
            switch (choice) {
            case QMessageBox::Reset:
                if (clockFile.open(QIODevice::ReadOnly)){
                    QTextStream read(&clockFile);
                    //iterates through employee clock in/out file and saves all incomplete shifts to be rewritten to file
                    while (!clockFile.atEnd()) {
                        QString line = read.readLine();
                        if (!line.contains("*") && !line.isEmpty()){
                            clockList.append(line);
                        }
                    }
                    clockFile.close();
                }
                if ((clockFile.open(QIODevice::WriteOnly| QIODevice::Text)))
                {
                    QTextStream out(&clockFile);
                    for (const QString& element : clockList) {
                        out << element + "\n";
                    }
                    clockFile.close();
                }
                break;
            case QMessageBox::Cancel:
                break;
            }
        }
    }
}

void PayView::on_pushButton_3_clicked()
{
    ViewPayStub view;
    view.setText(toString());
    view.setModal(true);
    view.exec();
}

