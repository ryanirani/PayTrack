#include "assignjob.h"
#include "ui_assignjob.h"
#include <QFile>
#include<QMessageBox>
#include<QTCore/QString>
#include<QDebug>

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class for a popup window to assign jobs to employees
AssignJob::AssignJob(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AssignJob)
{
    ui->setupUi(this);

}

AssignJob::~AssignJob()
{
    delete ui;
}
//often these setter methods are used to load data into a window as this setter method is always called before a window is visible
void AssignJob::SetWUID(QString WUID){
    this->WUID = WUID;

    //loading employee IDs into the id dropdown menu
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line = in.readLine();
            ui->comboBox->addItem(line);
        }
        file.close();


    }

    //loading all jobs into job dropdown menu
    QFile file2("C:\\Users\\" + WUID + "\\Desktop\\files\\jobs.txt");
    if(file2.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file2);
        while(!in.atEnd()){
            QString line = in.readLine();
            ui->comboBox_2->addItem(line);
        }
        file2.close();
    }

}
void AssignJob::on_pushButton_clicked()
{
     QString EMP = ui->comboBox->currentText();
     QString JOB = ui->comboBox_2->currentText();
     //essential for overwriting current employee jobs
     if (EMP.contains(",")){
         QString tmp = EMP.split(",").at(0);
         EMP = tmp;
     }


     QList<QString> listofIDs;

     QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\ids.txt");

     //iterating through the employee file in order to save all of the ids to be rewritten
     if ((file.open(QIODevice::ReadWrite)))
     {
         QTextStream in(&file);
         while(!in.atEnd())
         {
             QString line = in.readLine();
             if(line.contains(EMP)){
                 QString IDandJob = EMP + ", "+ JOB;
                 listofIDs.append(IDandJob);

             }
             else
             {
                 listofIDs.append(line);

         }
         file.close();
        }
     }
     else
     {
         QMessageBox::information(0, "File Does not Exist", file.errorString());
         exit(0);
     }

     //rewrite all ids with their updated jobs
     if ((file.open(QIODevice::WriteOnly| QIODevice::Text)))
     {
         QTextStream out(&file);
         for (const QString& element : listofIDs) {
             out << element << "\n"; // Write each element followed by a newline
         }
         file.close();
     }

     QMessageBox msgBox;
     msgBox.setText(tr("Job Assigned!"));
     QAbstractButton* pButtonYes = msgBox.addButton(tr("OK"), QMessageBox::YesRole);

     msgBox.exec();

     if (msgBox.clickedButton()==pButtonYes) {
         return;
     }

}



