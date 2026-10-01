#ifndef JOBADD_H
#define JOBADD_H

#include <QDialog>

namespace Ui {
class JobAdd;
}

class JobAdd : public QDialog
{
    Q_OBJECT

public:
    explicit JobAdd(QWidget *parent = nullptr);
    ~JobAdd();
    void SetWUID(QString WUID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::JobAdd *ui;
    QString WUID;
};

#endif // JOBADD_H
