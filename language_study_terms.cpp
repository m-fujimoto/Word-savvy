#include "language_study_terms.h"
#include "ui_language_study_terms.h"

Language_study_terms::Language_study_terms(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Language_study_terms)
{
    ui->setupUi(this);
    setWindowTitle("Language study terms");
}

Language_study_terms::~Language_study_terms()
{
    delete ui;
}

void Language_study_terms::on_Language_study_term_pushButton_clicked()
{
    this->close();
}
