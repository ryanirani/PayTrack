#include "schdule.h"
#include "ui_schdule.h"
#include<QFile>
#include<QMessageBox>
#include<QString>
#include<QComboBox>
//UI design, code, and comments by Jarif Yasir and Ryan Irani
//Class for employee scheduling window
Schdule::Schdule(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Schdule)
{
    ui->setupUi(this);
}
Schdule::~Schdule()
{
    delete ui;
}
//typical setter method is used to instantiated the windows user input menus
void Schdule::SetWUID(QString WUID){
    this->WUID = WUID;

    //Start Time combo box
    for(int i = 1; i<= 12; i++){
        ui->comboBox->addItem(QString::number(i) + ":00");
    }

    //End times to combo box
    for(int i = 1; i<= 12; i++){
        ui->comboBox_2->addItem(QString::number(i) + ":00");
    }

    //AM/PM combo Box
    ui->comboBox_3->addItem("AM");
    ui->comboBox_3->addItem("PM");
    ui->comboBox_5->addItem("AM");
    ui->comboBox_5->addItem("PM");


    //Employee ID combo Box
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt"); // PASTE PATH HERE
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            ui->comboBox_4->addItem(line);

        }

    }
}

void Schdule::on_pushButton_3_clicked()
{
//Schedule txt file
    QFile schdule("C:\\Users\\" + WUID + "\\Desktop\\files\\Schedule.txt"); // PASTE PATH HERE

//
    QString emp = ui->comboBox_4->currentText();


//Time and Date Variables
    QString startTime = ui->comboBox->currentText();
    QString startAMPM = ui->comboBox_3->currentText();
    QString endTime = ui->comboBox_2 ->currentText();
    QString endAMPM = ui->comboBox_5->currentText();

//Date
    QString date = ui->dateEdit->date().toString("dd/MM/yyyy");

    if (schdule.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream in(&schdule);
        int count = 0;
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(line == date){
                in <<"\n";
                in << emp + "     " + startTime + " " + startAMPM + " - " + endTime + endAMPM;
                count +=1;
                return;
            }
        }

        //If date not already on Calender
        if(count == 0)
        {
            in <<"\n";
            in << "-----------------------------------";
            in << "\n";
            in << date + "\n";
            in << emp + "     " + startTime + " " + startAMPM + " - " + endTime + endAMPM;
        }


    }
    else
    {
        QMessageBox::information(0,"File not found. Read the README file", schdule.errorString());
    }


}

void Schdule::on_pushButton_clicked()
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


void Schdule::on_pushButton_2_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\Schedule.txt"); //Put Path here
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


void Schdule::on_pushButton_4_clicked()
{
    close();
}

