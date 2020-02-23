#ifndef LANGUAGE_STUDY_TERMS_H
#define LANGUAGE_STUDY_TERMS_H

#include <QMainWindow>

namespace Ui {
class Language_study_terms;
}

class Language_study_terms : public QMainWindow
{
    Q_OBJECT

public:
    explicit Language_study_terms(QWidget *parent = nullptr);
    ~Language_study_terms();

private slots:
    void on_Language_study_term_pushButton_clicked();

private:
    Ui::Language_study_terms *ui;
};

#endif // LANGUAGE_STUDY_TERMS_H
