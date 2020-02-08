#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QTableWidget>
#include <QFontDialog>


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
    void on_actionFont_triggered();
    void on_actionAbout_triggered();
    void on_actionQuit_triggered();

    void on_English_add_pushButton_clicked();
    void on_English_edit_pushButton_clicked();
    void on_English_delete_pushButton_clicked();
    void on_English_reset_pushButton_clicked();
    void on_English_close_pushButton_clicked();
    void on_word_search_pushButton_clicked();
    void on_memo_searchpushButton_clicked();
    void on_English_tableWidget_cellDoubleClicked(int row);

    void on_Japanese_add_pushButton_clicked();
    void on_Japanese_edit_pushButton_clicked();
    void on_Japanese_delete_pushButton_clicked();
    void on_Japanese_reset_pushButton_clicked();
    void on_Japanese_close_pushButton_clicked();
    void on_Japanese_tableWidget_cellDoubleClicked(int row);
    void on_tabWidget_currentChanged();

private:
    Ui::MainWindow *ui;

    QString applicationName = "Word-savvy";
    QString appTitle = applicationName;
    QString sqlitedbName = "word-savvy.db";
    QString databaseName = QCoreApplication::applicationDirPath() + "/" + sqlitedbName;
    QSqlDatabase db;
    QString tableName;
    int number;
    QString word;
    QString pronunciation;
    QString meaning;
    QString memo;
    QString star;
    QString date;
    QString choice;

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
};

#endif // MAINWINDOW_H
