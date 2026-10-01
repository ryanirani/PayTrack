#include "dialog.h"
#include "ui_dialog.h"
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QPropertyAnimation>
#include <QDebug>
#include<QRect>



//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class for employee clock in/out window following login
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //instantiate boolean indicator to prevent double clocking in/out
    //temporary method, only works during the same employee login session
    clockedIn = false;

    //Button Animation



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::SetWUID(QString WUID){
    this->WUID = WUID;
}
//modifier method to receive employee's ID from LoginWindow
void Dialog::SetID(QString ID){
    this->ID = ID;
}
//action listener for 'Clock In' push button
void Dialog::on_pushButton_clicked()
{
    //only works if the employee isn't already clocked in during the current login session
        QFile clockIn("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt");//Put file path here
        //no need to read clock in times as of yet
        if (!clockIn.open(QIODevice::ReadWrite)){
            QMessageBox::information(0, "error", clockIn.errorString());
            return;
        }         else {
        QTextStream clockWriter(&clockIn);
        QList<QString> clockList;
        bool check = false;
        while (!clockWriter.atEnd()){
            QString line = clockWriter.readLine();
            if (line.contains(ID) && !line.contains("*")){
                check = true;
            }
            if (check){
                break;
            }
        }
        if (!check){
            //convenient QT device for getting current world time, easy to format into QString
            QDateTime date = QDateTime::currentDateTime();
            //may need to use a different format for more optimal paystub processing for the sake of tracking hours as whole units
            QString formattedTime = date.toString("dd.MM.yyyy -hh:mm:ss");
            QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
            QString newLine = ID + "| " + formattedTimeMsg + "\n";
            clockWriter << newLine;
            clockIn.close();
        }

    }
    QMessageBox msgBox;
    msgBox.setText(tr("Clocked in!"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        return;
    }

}

//action listener for 'Clock Out' push button
void Dialog::on_pushButton_2_clicked()
{
    //only works if the employee isn't already clocked out during the current login session
        QFile clockOut("C:\\Users\\" + WUID + "\\Desktop\\files\\emp_clock.txt");//Put file path here
        QList<QString> clockList;
        //clock out times may need to be read in future overlap prevention methods, for now the bool instance variable suffices
        if (!clockOut.open(QIODevice::ReadWrite)){
            QMessageBox::information(0, "error", clockOut.errorString());
            return;
        } else {
            QTextStream clockWriter(&clockOut);
            QString newLine = "";
            while (!clockWriter.atEnd()){
                QString line = clockWriter.readLine();
                if (line.contains(ID) && !line.contains("*")){
                    //convenient QT device for getting current world time, easy to format into QString
                    QDateTime date = QDateTime::currentDateTime();
                    //may need to use a different format for more optimal paystub processing for the sake of tracking hours as whole units
                    QString formattedTime = date.toString("hh:mm:ss");
                    QByteArray formattedTimeMsg = formattedTime.toLocal8Bit();
                    QString newLine = "*" + line + "/" + formattedTimeMsg + "\n";
                    clockList.append(newLine);
                } else {
                    if (!line.isEmpty()){
                        clockList.append(line);
                    }
                }
            }
            clockOut.close();

    }
        if ((clockOut.open(QIODevice::WriteOnly| QIODevice::Text)))
        {
            QTextStream out(&clockOut);
            for (const QString& element : clockList) {
                out << element + "\n";
            }
            clockOut.close();
        }
    QMessageBox msgBox;
    msgBox.setText(tr("Clocked Out!"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        return;
    }

}
