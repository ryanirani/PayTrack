#ifndef VIEWPAYSTUB_H
#define VIEWPAYSTUB_H

#include <QDialog>

namespace Ui {
class ViewPayStub;
}

class ViewPayStub : public QDialog
{
    Q_OBJECT

public:
    explicit ViewPayStub(QWidget *parent = nullptr);
    ~ViewPayStub();
    void setText(QString toString);

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewPayStub *ui;
};

#endif // VIEWPAYSTUB_H
