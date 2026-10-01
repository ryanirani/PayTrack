#ifndef ASSIGNJOB_H
#define ASSIGNJOB_H

#include <QDialog>

namespace Ui {
class AssignJob;
}

class AssignJob : public QDialog
{
    Q_OBJECT

public:
    explicit AssignJob(QWidget *parent = nullptr);
    ~AssignJob();
    void SetWUID(QString WUID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::AssignJob *ui;
    QString WUID;
};

#endif // ASSIGNJOB_H
