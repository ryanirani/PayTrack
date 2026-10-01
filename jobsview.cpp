#include "jobsview.h"
#include "ui_jobsview.h"
#include "QFile"
#include "QMessageBox"

//UI design, code, and comments by Jarif Yasir and Ryan Irani
//class for a window to view the list of jobs
JobsView::JobsView(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JobsView)
{
    ui->setupUi(this);
}

JobsView::~JobsView()
{
    delete ui;
}

void JobsView::SetWUID(QString WUID){
    this->WUID = WUID;
}

//loads jobs from job file upon clicking and displays them
void JobsView::on_pushButton_clicked()
{
    QFile file("C:\\Users\\" + WUID + "\\Desktop\\files\\jobs.txt"); //Put Path here
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

