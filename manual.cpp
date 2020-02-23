#include "manual.h"
#include "ui_manual.h"

Manual::Manual(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manual)
{
    ui->setupUi(this);
    setWindowTitle("Word-savvy Manual");
}

Manual::~Manual()
{
    delete ui;
}

void Manual::on_manual_pushButton_clicked()
{
    this->close();
}
