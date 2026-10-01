#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class loginWindow;
}
QT_END_NAMESPACE

class loginWindow : public QMainWindow
{
    Q_OBJECT

public:
    loginWindow(QWidget *parent = nullptr);
    ~loginWindow();
    void SetWUID();

private slots:
    void on_pushButton_clicked();

private:
    Ui::loginWindow *ui;
    QString WUID;
};
#endif // LOGINWINDOW_H
