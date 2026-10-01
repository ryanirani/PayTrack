#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QDialog>

namespace Ui {
class ViewWindow;
}

class ViewWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ViewWindow(QWidget *parent = nullptr);
    ~ViewWindow();
    void SetWUID(QString WUID);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ViewWindow *ui;
    QString WUID;
};

#endif // VIEWWINDOW_H
