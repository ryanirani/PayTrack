#ifndef JOBREMOVE_H
#define JOBREMOVE_H

#include <QDialog>

namespace Ui {
class jobRemove;
}

class jobRemove : public QDialog
{
    Q_OBJECT

public:
    explicit jobRemove(QWidget *parent = nullptr);
    ~jobRemove();
    void SetWUID(QString WUID);

private slots:

    void on_pushButton_clicked();

private:
    Ui::jobRemove *ui;
    QString WUID;
};

#endif // JOBREMOVE_H
