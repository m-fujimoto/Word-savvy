#ifndef MANUAL_H
#define MANUAL_H

#include <QMainWindow>

namespace Ui {
class Manual;
}

class Manual : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manual(QWidget *parent = nullptr);
    ~Manual();

private slots:
    void on_manual_pushButton_clicked();

private:
    Ui::Manual *ui;
};

#endif // MANUAL_H
