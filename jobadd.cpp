#include "jobadd.h"
#include "ui_jobadd.h"
#include<QFile>
#include<QMessageBox>

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//Class to add different jobs with either an hourly or flate rate pay
JobAdd::JobAdd(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JobAdd)
{
    ui->setupUi(this);
}

JobAdd::~JobAdd()
{
    delete ui;
}

void JobAdd::SetWUID(QString WUID){
    this->WUID = WUID;
}

void JobAdd::on_pushButton_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\Jobs.txt");

    //writes jobs in a format that makes printing payouts simple by using special characters to breakdown the QString
    // $ character seperates the title from pay rate, / character seperates the pay rate from the pay type indicator
    if(file.open(QIODevice::Append))
    {
        QTextStream in(&file);
        //hourly rate
        QString H = "/H/";
        //flat rate
        QString F = "/F/";
        if (ui->radioButton->isChecked()){
            in<< "\n"+ ui->lineEdit->text() + "$" + ui->lineEdit_2->text() + H;
        }
        if (ui->radioButton_2->isChecked()){
            in<< "\n" + ui->lineEdit->text() + "$" + ui->lineEdit_2->text()+ F;
        }



    }
    else
    {
        QMessageBox::information(0,"File not found", file.errorString());
    }

    QMessageBox msgBox;
    msgBox.setText(tr("Job Added!"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        return;
    }

}

