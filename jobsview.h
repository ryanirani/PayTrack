#ifndef JOBSVIEW_H
#define JOBSVIEW_H

#include <QDialog>

namespace Ui {
class JobsView;
}

class JobsView : public QDialog
{
    Q_OBJECT

public:
    explicit JobsView(QWidget *parent = nullptr);
    ~JobsView();
    void SetWUID(QString WUID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::JobsView *ui;
    QString WUID;
};

#endif // JOBSVIEW_H
