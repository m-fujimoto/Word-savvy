#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QFontDialog>
#include <QDesktopServices>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Menu

    void on_actionQuit_triggered();
    void on_actionFont_triggered();
    void on_actionOxford_3000_triggered();
    void on_actionOxford_5000_triggered();
    void on_actionOxford_5000_excluding_Oxford_3000_triggered();
    void on_actionOxford_Phrasal_Academic_Lexicon_triggered();
    void on_actionOxford_Phrase_List_triggered();
    void on_actionOxford_Seventh_edition_Arts_words_triggered();
    void on_actionOxford_Seventh_edition_Science_words_triggered();
    void on_actionOxford_Seventh_edition_Business_and_finance_words_triggered();
    void on_actionLanguage_study_terms_triggered();
    void on_actionManual_triggered();
    void on_actionAbout_triggered();

    // Tab

    void on_tabWidget_currentChanged(int index);

    // English

    void on_English_add_pushButton_clicked();
    void on_English_edit_pushButton_clicked();
    void on_English_delete_pushButton_clicked();
    void on_English_reset_pushButton_clicked();
    void on_English_close_pushButton_clicked();
    void on_search_English_keyword_by_word_pushButton_clicked();
    void on_search_English_keyword_by_pronunciation_pushButton_clicked();
    void on_search_English_keyword_by_memo_pushButton_clicked();
    void on_English_review_pushButton_clicked();
    void on_English_tableWidget_cellDoubleClicked(int row);

    // Japanese

    void on_Japanese_add_pushButton_clicked();
    void on_Japanese_edit_pushButton_clicked();
    void on_Japanese_delete_pushButton_clicked();
    void on_Japanese_reset_pushButton_clicked();
    void on_Japanese_close_pushButton_clicked();
    void on_search_Japanese_keyword_by_word_pushButton_clicked();
    void on_search_Japanese_keyword_by_pronunciation_pushButton_clicked();
    void on_search_Japanese_keyword_by_memo_pushButton_clicked();
    void on_Japanese_review_pushButton_clicked();
    void on_Japanese_tableWidget_cellDoubleClicked(int row);

    // Oxford

    void on_Oxford_reset_pushButton_clicked();
    void on_Oxford_close_pushButton_clicked();
    void on_Oxford_edit_pushButton_clicked();
    void on_search_Oxford_keyword_by_word_pushButton_clicked();
    void on_search_Oxford_keyword_by_pronunciation_pushButton_clicked();
    void on_search_Oxford_keyword_by_memo_pushButton_clicked();
    void on_Oxford_review_pushButton_clicked();
    void on_Oxford_tableWidget_cellDoubleClicked(int row);

    // Dictionary

    void on_actionOxford_Advanced_Learner_s_Dictionary_triggered();
    void on_actionLongman_Dictionary_triggered();
    void on_actionCambridge_Dictionary_triggered();
    void on_actionMacmillan_Dictionary_triggered();
    void on_actionCollins_Dictionary_triggered();
    void on_actionMerriam_Webster_Dictionary_triggered();
    void on_actionLexico_triggered();
    void on_actionUrban_Dictionary_triggered();
    void on_actionWeblio_triggered();
    void on_actionEijirou_triggered();
    void on_actiongoo_triggered();

private:
    Ui::MainWindow *ui;

    QString applicationName = "Word-savvy";
    QString appTitle = applicationName;
    QString sqlitedbName = "Word-savvy.db";
    QString databaseName = QCoreApplication::applicationDirPath() + "/" + sqlitedbName;
    QSqlDatabase db;
    QString tableName;
    int number;
    QString word;
    QString pronunciation;
    QString part_of_speech;
    QString meaning;
    QString memo;
    QString star;
    QString date;
    QString choice;
    QString keyword;
    QString url;

    QSqlError connectDatabase();
    QSqlError closeDatabase();
    QSqlError selectData();
    QSqlError insertData();
    QSqlError updateData();
    QSqlError deleteData();
    QSqlError setData();
    QSqlError searchData();

    void clear_English_form();
    void clear_Japanese_form();
    void clear_Oxford_form();
    void set_part_of_speech_comboBox();
};

#endif // MAINWINDOW_H
