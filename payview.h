#ifndef PAYVIEW_H
#define PAYVIEW_H

#include <QDialog>

namespace Ui {
class PayView;
}

class PayView : public QDialog
{
    Q_OBJECT

public:
    explicit PayView(QWidget *parent = nullptr);
    ~PayView();
    void SetWUID(QString WUID);
    QString toString();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::PayView *ui;
    QString WUID;
};

#endif // PAYVIEW_H
