#include "jobremove.h"
#include "ui_jobremove.h"
#include<QFile>
#include<QMessageBox>

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class to remove jobs from the job list text file
jobRemove::jobRemove(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::jobRemove)
{
    ui->setupUi(this);
}

jobRemove::~jobRemove()
{
    delete ui;
}

void jobRemove::SetWUID(QString WUID){
    this->WUID = WUID;
}


void jobRemove::on_pushButton_clicked()
{
    //take manager input
    QString ID = ui->lineEdit->text();
    //data structure to store and rewrite IDs to text file after each removal
    QList<QString> listofIDs;

    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\jobs.txt");//Put path here

    //adding all jobs that arent meant to be removed to a list
    if ((file.open(QIODevice::ReadWrite)))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(!line.contains(ID)){
                listofIDs.append(line);

            }

        }
        file.close();
    }
    else
    {
        QMessageBox::information(0, "File Does not Exist", file.errorString());
        exit(0);
    }

    //rewrite all jobs from the list except the one requested to be removed
    if ((file.open(QIODevice::WriteOnly| QIODevice::Text)))
    {
        QTextStream out(&file);
        for (const QString& element : listofIDs) {
            out << element << "\n"; // Write each element followed by a newline
        }
        file.close();
    }

    QMessageBox msgBox;
    msgBox.setText(tr("Job Removed!"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

    msgBox.exec();
    if (msgBox.clickedButton()==pButtonYes) {
        return;
    }

}

