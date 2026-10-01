#include "addname.h"
#include "ui_addname.h"
#include<QString>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<QDir>
#include<QDebug>
#include<QString>
#include<QTextStream>

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class for an input window to add employee IDs to the database, accessible from 'Employees ADD' button in manager mode (dialog2)
//each window class requires the following two constructors to inherit their respective parent class
AddName::AddName(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddName)
{
    ui->setupUi(this);
}

AddName::~AddName()
{
    delete ui;
}
//This setter method is seen throughout each .cpp class
//its essential for each class to receive the users windows user name as it is required in the filepath
void AddName::SetWUID(QString WUID){
    this->WUID = WUID;
}
//setter method thats used for adding ids to the manager id file instead of the basic employee id file
void AddName::SetMgMode(bool addMg){
    this->addMg = addMg;
}
//button listener function to add IDs to ids.txt when the user clicks "Add"
void AddName::on_pushButton_clicked()
{
    //receive input from user
    QString ID = ui->lineEdit->text();
    QString fileName;
    if (!addMg){
        fileName = "C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt";
    } else {
        fileName = "C:\\Users\\" + WUID + "\\Desktop\\files\\mg_ids.txt";
    }
    QFile file(fileName);
    QTextStream in(&file);

    //left as ReadWrite for future overlap prevention
    if ((file.open(QIODevice::ReadWrite | QIODevice::Append)))
    {
        //append file with new ID
        QTextStream stream(&file);
        stream<<"\n" +ID;
        file.close();
        return;

    }
    else
    {
        QMessageBox::information(0, "error", file.errorString());
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(tr("ID added!"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        return;
    }



}



//closes add name window
void AddName::on_pushButton_2_clicked()
{
    close();
}

