#ifndef ADDNAME_H
#define ADDNAME_H

#include <QDialog>

namespace Ui {
class AddName;
}

class AddName : public QDialog
{
    Q_OBJECT

public:
    explicit AddName(QWidget *parent = nullptr);
    ~AddName();
    void SetWUID(QString WUID);
    void SetMgMode(bool addMg);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::AddName *ui;
    QString WUID;
    bool addMg;
};

#endif // ADDNAME_H
