#include "viewpaystub.h"
#include "ui_viewpaystub.h"
#include "loginwindow.h"
#include <QString>
#include <QFile>
#include <QFileDialog>
//UI design, code, and comments by Jarif Yasir and Ryan Irani
//simple popup window class for viewing the employee paystubs within the program without exporting to a file
ViewPayStub::ViewPayStub(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewPayStub)
{
    ui->setupUi(this);
}

ViewPayStub::~ViewPayStub()
{
    delete ui;
}
void ViewPayStub::setText(QString toString){
    ui->textBrowser->setText(toString);
}


