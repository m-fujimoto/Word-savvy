#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manual.h"
#include "language_study_terms.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(appTitle);
    connectDatabase();
    ui->tabWidget->setCurrentIndex(0);
    set_part_of_speech_comboBox();
    selectData();
}

MainWindow::~MainWindow()
{
    delete ui;
    closeDatabase();
}

// SQL

QSqlError MainWindow::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if (!db.open()) {
        return db.lastError();
    }
    return QSqlError();
}

QSqlError MainWindow::closeDatabase()
{
    db.close();
    QSqlDatabase::removeDatabase(databaseName);

    return QSqlError();
}

QSqlError MainWindow::selectData()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
        ui->English_add_pushButton->setDisabled(false);
        ui->English_edit_pushButton->setDisabled(true);
        ui->English_delete_pushButton->setDisabled(true);
        ui->English_number_lineEdit->setText("1");
        ui->English_checkBox->setDisabled(true);
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
        ui->Japanese_number_lineEdit->setText("1");
        ui->Japanese_add_pushButton->setDisabled(false);
        ui->Japanese_edit_pushButton->setDisabled(true);
        ui->Japanese_delete_pushButton->setDisabled(true);
        ui->Japanese_checkBox->setDisabled(true);
    } else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->Oxford_number_lineEdit->setText("1");
        ui->Oxford_edit_pushButton->setDisabled(true);
        ui->Oxford_delete_pushButton->setDisabled(true);
        ui->Oxford_checkBox->setDisabled(true);
        ui->Oxford_edit_pushButton->setDisabled(false);
        ui->Oxford_delete_pushButton->setDisabled(true);
        ui->Oxford_checkBox->setDisabled(false);

        if ((tableName == "Oxford 3000") ||(tableName == "Oxford 5000") || (tableName == "Oxford 5000 excluding Oxford 3000"))
        {
            QStringList header = { "NUMBER", "WORD", "PRONUNCIATION", "PART OF SPEECH / CEFR", "MEANING", "STAR", "DATE", "MEMO"};
            ui->Oxford_tableWidget->setHorizontalHeaderLabels(header);
            ui->Oxford_word_label->setText("WORD : ");
            ui->Oxford_part_of_speech_label->setText("PART OF SPEECH / CEFR");
        } else if (tableName == "Oxford Phrase List")
        {
            QStringList header = { "NUMBER", "PHRASE", "PRONUNCIATION", "CEFR", "MEANING", "STAR", "DATE", "MEMO"};
            ui->Oxford_tableWidget->setHorizontalHeaderLabels(header);
            ui->Oxford_word_label->setText("PHRASE : ");
            ui->Oxford_part_of_speech_label->setText("CEFR : ");

        }  else
        {
            QStringList header = { "NUMBER", "WORD", "PRONUNCIATION", "PART OF SPEECH", "MEANING", "STAR", "DATE", "MEMO"};
            ui->Oxford_tableWidget->setHorizontalHeaderLabels(header);
            ui->Oxford_word_label->setText("WORD : ");
            ui->Oxford_part_of_speech_label->setText("PART OF SPEECH : ");
        }

    }

    QSqlQuery query;
    query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH,MEANING, STAR, DATE, MEMO FROM '" + tableName + "' ORDER BY NUMBER DESC");

    int i = {0};

    if (query.exec())
    {
        ui->English_tableWidget->setRowCount(0);
        ui->Japanese_tableWidget->setRowCount(0);
        ui->Oxford_tableWidget->setRowCount(0);
        while (query.next())
        {
            number = query.value(0).toInt();
            word = query.value(1).toString();
            pronunciation = query.value(2).toString();
            part_of_speech =query.value(3).toString();
            meaning = query.value(4).toString();
            star = query.value(5).toString();
            date = query.value(6).toString();
            memo = query.value(7).toString();
            QTableWidgetItem *newItem0 = new QTableWidgetItem(tr("%1").arg(number));
            QTableWidgetItem *newItem1 = new QTableWidgetItem(tr("%1").arg(word));
            QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("%1").arg(pronunciation));
            QTableWidgetItem *newItem3 = new QTableWidgetItem(tr("%1").arg(part_of_speech));
            QTableWidgetItem *newItem4 = new QTableWidgetItem(tr("%1").arg(meaning));
            QTableWidgetItem *newItem5 = new QTableWidgetItem(tr("%1").arg(star));
            QTableWidgetItem *newItem6 = new QTableWidgetItem(tr("%1").arg(date));
            QTableWidgetItem *newItem7 = new QTableWidgetItem(tr("%1").arg(memo));

            if (ui->tabWidget->currentIndex() == 0)
            {
                ui->English_tableWidget->insertRow(i);
                ui->English_tableWidget->setItem(i, 0, newItem0);
                ui->English_tableWidget->setItem(i, 1, newItem1);
                ui->English_tableWidget->setItem(i, 2, newItem2);
                ui->English_tableWidget->setItem(i, 3, newItem3);
                ui->English_tableWidget->setItem(i, 4, newItem4);
                ui->English_tableWidget->setItem(i, 5, newItem5);
                ui->English_tableWidget->setItem(i, 6, newItem6);
                ui->English_tableWidget->setItem(i, 7, newItem7);
                if (i == 0) {
                    ui->English_number_lineEdit->setText(QString::number(number + 1));
                }
            } else if (ui->tabWidget->currentIndex() == 1)
            {
                ui->Japanese_tableWidget->insertRow(i);
                ui->Japanese_tableWidget->setItem(i, 0, newItem0);
                ui->Japanese_tableWidget->setItem(i, 1, newItem1);
                ui->Japanese_tableWidget->setItem(i, 2, newItem2);
                ui->Japanese_tableWidget->setItem(i, 3, newItem3);
                ui->Japanese_tableWidget->setItem(i, 4, newItem4);
                ui->Japanese_tableWidget->setItem(i, 5, newItem5);
                ui->Japanese_tableWidget->setItem(i, 6, newItem6);
                ui->Japanese_tableWidget->setItem(i, 7, newItem7);
                if (i == 0) {
                    ui->Japanese_number_lineEdit->setText(QString::number(number + 1));
                }
            } else if (ui->tabWidget->currentIndex() == 2)
            {
                ui->Oxford_tableWidget->insertRow(i);
                ui->Oxford_tableWidget->setItem(i, 0, newItem0);
                ui->Oxford_tableWidget->setItem(i, 1, newItem1);
                ui->Oxford_tableWidget->setItem(i, 2, newItem2);
                ui->Oxford_tableWidget->setItem(i, 3, newItem3);
                ui->Oxford_tableWidget->setItem(i, 4, newItem4);
                ui->Oxford_tableWidget->setItem(i, 5, newItem5);
                ui->Oxford_tableWidget->setItem(i, 6, newItem6);
                ui->Oxford_tableWidget->setItem(i, 7, newItem7);
                if (i == 0) {
                    ui->Oxford_number_lineEdit->setText(QString::number(number + 1));
                }
            }

            i++;
        }
    }
    return QSqlError();
}

QSqlError MainWindow::insertData()
{
    QDate today = QDate::currentDate();
    date = today.toString();
    bool flag = true;

    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
        number = ui->English_number_lineEdit->text().toInt();
        word = ui->English_word_lineEdit->text();
        pronunciation = ui->English_pronunciation_lineEdit->text();
        part_of_speech = ui->English_part_of_speech_comboBox->currentText();
        meaning = ui->English_meaning_lineEdit->text();
        star = ui->English_star_comboBox->currentText();
        memo = ui->English_textEdit->toPlainText();

    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
        number = ui->Japanese_number_lineEdit->text().toInt();
        word = ui->Japanese_word_lineEdit->text();
        pronunciation = ui->Japanese_pronunciation_lineEdit->text();
        part_of_speech = ui->Japanese_part_of_speech_comboBox->currentText();
        meaning = ui->Japanese_meaning_lineEdit->text();
        star = ui->Japanese_star_comboBox->currentText();
        memo = ui->Japanese_textEdit->toPlainText();
    }

    if (word == "") {
        flag = false;
        QMessageBox msgBox;
        msgBox.setText("The WORD is required.");
        msgBox.exec();
    }

    if (flag)
    {
        QSqlQuery tablequery;
        if (tablequery.exec("CREATE TABLE IF NOT EXISTS '" + tableName + "'"" (NUMBER INTEGER, WORD TEXT, PRONUNCIATION TEXT, PART_OF_SPEECH TEXT, MEANING TEXT, STAR TEXT, DATE TEXT, MEMO TEXT)"))    {

        QSqlQuery query;
        query.prepare("INSERT INTO '" + tableName + "'"" (NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH ,MEANING, STAR, DATE, MEMO) "
                                                 "VALUES (:number, :word, :pronunciation, :part_of_speech, :meaning, :star, :date, :memo)");
        query.bindValue(0, number);
        query.bindValue(1, word);
        query.bindValue(2, pronunciation);
        query.bindValue(3, part_of_speech);
        query.bindValue(4, meaning);
        query.bindValue(5, star);
        query.bindValue(6, date);
        query.bindValue(7, memo);

        if (query.exec())
        {
            QMessageBox msgBox;
            msgBox.setText("The WORD was successfully recorded.");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("The WORD was NOT recorded.");
            msgBox.exec();
        }
      }
    }
    return QSqlError();
}

QSqlError MainWindow::updateData()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
        number = ui->English_number_lineEdit->text().toInt();
        word = ui->English_word_lineEdit->text();
        pronunciation = ui->English_pronunciation_lineEdit->text();
        part_of_speech = ui->English_part_of_speech_comboBox->currentText();
        meaning = ui->English_meaning_lineEdit->text();
        star = ui->English_star_comboBox->currentText();
        memo = ui->English_textEdit->toPlainText();
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
        number = ui->Japanese_number_lineEdit->text().toInt();
        word = ui->Japanese_word_lineEdit->text();
        pronunciation = ui->Japanese_pronunciation_lineEdit->text();
        part_of_speech = ui->Japanese_part_of_speech_comboBox->currentText();
        meaning = ui->Japanese_meaning_lineEdit->text();
        star = ui->Japanese_star_comboBox->currentText();
        memo = ui->Japanese_textEdit->toPlainText();
    } else if (ui->tabWidget->currentIndex() == 2)
    {
        number = ui->Oxford_number_lineEdit->text().toInt();
        word = ui->Oxford_word_lineEdit->text();
        pronunciation = ui->Oxford_pronunciation_lineEdit->text();
        part_of_speech = ui->Oxford_part_of_speech_comboBox->currentText();
        meaning = ui->Oxford_meaning_lineEdit->text();
        star = ui->Oxford_star_comboBox->currentText();
        memo = ui->Oxford_textEdit->toPlainText();
    }

    QDate today = QDate::currentDate();
    date = today.toString();
    bool flag = true;

    if (word == "") {
        flag = false;
        QMessageBox msgBox;
        msgBox.setText("The WORD is required.");
        msgBox.exec();
    }

    if (flag)
    {
        QSqlQuery query;
        query.prepare("UPDATE '" + tableName + "' SET NUMBER = ?, WORD = ?, PRONUNCIATION = ?, PART_OF_SPEECH = ?, MEANING = ?, STAR = ?, DATE = ?, MEMO = ? WHERE NUMBER = ?");

        query.bindValue(0, number);
        query.bindValue(1, word);
        query.bindValue(2, pronunciation);
        query.bindValue(3, part_of_speech);
        query.bindValue(4, meaning);
        query.bindValue(5, star);
        query.bindValue(6, date);
        query.bindValue(7, memo);
        query.bindValue(8, number);

        if (query.exec())
        {
            QMessageBox msgBox;
            msgBox.setText("The WORD was successfully updated.");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("The WORD was NOT updated.");
            msgBox.exec();
        }
    }
    return QSqlError();
}

QSqlError MainWindow::deleteData()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
    }

    QSqlQuery query;
    query.prepare("DELETE FROM  '" + tableName + "' WHERE NUMBER = ?");
    query.bindValue(0,number);

    if (query.exec())
    {
        QMessageBox msgBox;
        msgBox.setText("The WORD was successfully deleted.");
        msgBox.exec();
    }
    return QSqlError();
}

QSqlError MainWindow::setData()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
        ui->English_add_pushButton->setDisabled(true);
        ui->English_edit_pushButton->setDisabled(false);
        ui->English_delete_pushButton->setDisabled(false);
        ui->English_checkBox->setDisabled(false);
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
        ui->Japanese_add_pushButton->setDisabled(true);
        ui->Japanese_edit_pushButton->setDisabled(false);
        ui->Japanese_delete_pushButton->setDisabled(false);
        ui->Japanese_add_pushButton->setDisabled(true);
        ui->Japanese_checkBox->setDisabled(false);
    } else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->Oxford_edit_pushButton->setDisabled(false);
        ui->Oxford_delete_pushButton->setDisabled(true);
        ui->Oxford_checkBox->setDisabled(false);
    }

    QSqlQuery query;
    query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH , MEANING, STAR , DATE, MEMO FROM '" + tableName + "' WHERE NUMBER = ?");
    query.bindValue(0,number);

    if (query.exec())
    {
        while (query.next())
        {
            number = query.value(0).toInt();
            word = query.value(1).toString();
            pronunciation = query.value(2).toString();
            part_of_speech = query.value(3).toString();
            meaning = query.value(4).toString();
            star = query.value(5).toString();
            date = query.value(6).toString();
            memo = query.value(7).toString();

            if (ui->tabWidget->currentIndex() == 0)
            {
                ui->English_number_lineEdit->setText(QString::number(number));
                ui->English_word_lineEdit->setText(word);
                ui->English_pronunciation_lineEdit->setText(pronunciation);
                ui->English_part_of_speech_comboBox->setCurrentText(part_of_speech);
                ui->English_meaning_lineEdit->setText(meaning);
                ui->English_star_comboBox->setCurrentText(star);
                ui->English_textEdit->setText(memo);
            } else if (ui->tabWidget->currentIndex() == 1)
            {
                ui->Japanese_number_lineEdit->setText(QString::number(number));
                ui->Japanese_word_lineEdit->setText(word);
                ui->Japanese_pronunciation_lineEdit->setText(pronunciation);
                ui->Japanese_part_of_speech_comboBox->setCurrentText(part_of_speech);
                ui->Japanese_meaning_lineEdit->setText(meaning);
                ui->Japanese_star_comboBox->setCurrentText(star);
                ui->Japanese_textEdit->setText(memo);
            } else if (ui->tabWidget->currentIndex() == 2)
            {
                ui->Oxford_number_lineEdit->setText(QString::number(number));
                ui->Oxford_word_lineEdit->setText(word);
                ui->Oxford_pronunciation_lineEdit->setText(pronunciation);
                ui->Oxford_part_of_speech_comboBox->setCurrentText(part_of_speech);
                ui->Oxford_meaning_lineEdit->setText(meaning);
                ui->Oxford_star_comboBox->setCurrentText(star);
                ui->Oxford_textEdit->setText(memo);
            }
        }
    }
    return QSqlError();
}

QSqlError MainWindow::searchData()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        tableName = "English";
        ui->English_add_pushButton->setDisabled(true);
        ui->English_edit_pushButton->setDisabled(true);
        ui->English_delete_pushButton->setDisabled(true);
        keyword = ui->English_keyword_lineEdit->text();
        if (choice == "STAR") {
            keyword = ui->English_star_comboBox->currentText();
        }
    } else if (ui->tabWidget->currentIndex() == 1)
    {
        tableName = "Japanese";
        ui->Japanese_add_pushButton->setDisabled(true);
        ui->Japanese_edit_pushButton->setDisabled(true);
        ui->Japanese_delete_pushButton->setDisabled(true);
        keyword = ui->Japanese_keyword_lineEdit->text();
        if (choice == "STAR") {
            keyword = ui->Japanese_star_comboBox->currentText();
        }
    } else if (ui->tabWidget->currentIndex() == 2)
    {
        ui->Oxford_edit_pushButton->setDisabled(true);
        ui->Oxford_delete_pushButton->setDisabled(true);
        keyword = ui->Oxford_keyword_lineEdit->text();
        if (choice == "STAR") {
            keyword = ui->Oxford_star_comboBox->currentText();
        }
    }

    bool flag = true;
    if (keyword == "") {
        flag = false;
        QMessageBox msgBox;
        msgBox.setText("The Keyword is required.");
        msgBox.exec();
    }

    if(flag)
    {
        QSqlQuery query;
        if (choice == "WORD")
        {
            query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH, MEANING, STAR, DATE, MEMO FROM '" + tableName + "' WHERE WORD LIKE ?");
        } else if (choice == "PRONUNCIATION")
        {
            query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH, MEANING, STAR, DATE, MEMO FROM '" + tableName + "' WHERE PRONUNCIATION LIKE ?");
        } else if (choice == "STAR")
        {
            query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH, MEANING, STAR, DATE, MEMO FROM '" + tableName + "' WHERE STAR=?");
        } else if (choice == "MEMO")
        {
            query.prepare("SELECT NUMBER, WORD, PRONUNCIATION, PART_OF_SPEECH, MEANING, STAR, DATE, MEMO FROM '" + tableName + "' WHERE MEMO LIKE ?");
        }

        if (choice == "STAR") {
            query.bindValue(0,keyword);
        } else
        {
            query.bindValue(0,"%" + keyword + "%");
        }
        int i = {0};

        if (query.exec())
        {
            ui->English_tableWidget->setRowCount(0);
            ui->Japanese_tableWidget->setRowCount(0);
            ui->Oxford_tableWidget->setRowCount(0);
            while (query.next())
                {
                    number = query.value(0).toInt();
                    word = query.value(1).toString();
                    pronunciation = query.value(2).toString();
                    part_of_speech = query.value(3).toString();
                    meaning = query.value(4).toString();
                    star = query.value(5).toString();
                    date = query.value(6).toString();
                    memo = query.value(7).toString();
                    QTableWidgetItem *newItem0 = new QTableWidgetItem(tr("%1").arg(number));
                    QTableWidgetItem *newItem1 = new QTableWidgetItem(tr("%1").arg(word));
                    QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("%1").arg(pronunciation));
                    QTableWidgetItem *newItem3 = new QTableWidgetItem(tr("%1").arg(part_of_speech));
                    QTableWidgetItem *newItem4 = new QTableWidgetItem(tr("%1").arg(meaning));
                    QTableWidgetItem *newItem5 = new QTableWidgetItem(tr("%1").arg(star));
                    QTableWidgetItem *newItem6 = new QTableWidgetItem(tr("%1").arg(date));
                    QTableWidgetItem *newItem7 = new QTableWidgetItem(tr("%1").arg(memo));

                    if (ui->tabWidget->currentIndex() == 0)
                    {
                        ui->English_tableWidget->insertRow(i);
                        ui->English_tableWidget->setItem(i, 0, newItem0);
                        ui->English_tableWidget->setItem(i, 1, newItem1);
                        ui->English_tableWidget->setItem(i, 2, newItem2);
                        ui->English_tableWidget->setItem(i, 3, newItem3);
                        ui->English_tableWidget->setItem(i, 4, newItem4);
                        ui->English_tableWidget->setItem(i, 5, newItem5);
                        ui->English_tableWidget->setItem(i, 6, newItem6);
                        ui->English_tableWidget->setItem(i, 7, newItem7);
                    } else if (ui->tabWidget->currentIndex() == 1)
                    {
                        ui->Japanese_tableWidget->insertRow(i);
                        ui->Japanese_tableWidget->setItem(i, 0, newItem0);
                        ui->Japanese_tableWidget->setItem(i, 1, newItem1);
                        ui->Japanese_tableWidget->setItem(i, 2, newItem2);
                        ui->Japanese_tableWidget->setItem(i, 3, newItem3);
                        ui->Japanese_tableWidget->setItem(i, 4, newItem4);
                        ui->Japanese_tableWidget->setItem(i, 5, newItem5);
                        ui->Japanese_tableWidget->setItem(i, 6, newItem6);
                        ui->Japanese_tableWidget->setItem(i, 7, newItem7);
                    } else if (ui->tabWidget->currentIndex() == 2)
                    {
                        ui->Oxford_tableWidget->insertRow(i);
                        ui->Oxford_tableWidget->setItem(i, 0, newItem0);
                        ui->Oxford_tableWidget->setItem(i, 1, newItem1);
                        ui->Oxford_tableWidget->setItem(i, 2, newItem2);
                        ui->Oxford_tableWidget->setItem(i, 3, newItem3);
                        ui->Oxford_tableWidget->setItem(i, 4, newItem4);
                        ui->Oxford_tableWidget->setItem(i, 5, newItem5);
                        ui->Oxford_tableWidget->setItem(i, 6, newItem6);
                        ui->Oxford_tableWidget->setItem(i, 7, newItem7);
                    }
                    i++;
                }
            ui->English_number_lineEdit->setText("");
            ui->Japanese_number_lineEdit->setText("");
            ui->Oxford_number_lineEdit->setText("");
        }

    }
    return QSqlError();
}

// Menu

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
    {
        ui->English_tableWidget->setFont(font);
        ui->Japanese_tableWidget->setFont(font);
        ui->Oxford_tableWidget->setFont(font);
    }
}

void MainWindow::on_actionOxford_3000_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford 3000";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_5000_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford 5000";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_5000_excluding_Oxford_3000_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford 5000 excluding Oxford 3000";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Phrasal_Academic_Lexicon_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford Phrasal Academic Lexicon";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Phrase_List_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford Phrase List";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Seventh_edition_Arts_words_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford Seventh edition Arts words";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Seventh_edition_Science_words_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford Seventh edition Science words";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Seventh_edition_Business_and_finance_words_triggered()
{
    ui->tabWidget->setCurrentIndex(2);
    tableName = "Oxford Seventh edition Buisiness and finance words";
    ui->tabWidget->setTabText(2,tableName);
    selectData();
}

void MainWindow::on_actionOxford_Advanced_Learner_s_Dictionary_triggered()
{
    QString dictionary = "https://www.oxfordlearnersdictionaries.com/definition/english/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionLongman_Dictionary_triggered()
{
    QString dictionary = "https://www.ldoceonline.com/dictionary/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionCambridge_Dictionary_triggered()
{
    QString dictionary = "https://dictionary.cambridge.org/dictionary/english/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionMacmillan_Dictionary_triggered()
{
    QString dictionary = "https://www.macmillandictionary.com/dictionary/british/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionCollins_Dictionary_triggered()
{
    QString dictionary = "https://www.collinsdictionary.com/dictionary/english/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionMerriam_Webster_Dictionary_triggered()
{
    QString dictionary = "https://www.merriam-webster.com/dictionary/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionLexico_triggered()
{
    QString dictionary = "https://www.lexico.com/definition/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionUrban_Dictionary_triggered()
{
    QString dictionary = "https://www.urbandictionary.com/define.php?term=";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionWeblio_triggered()
{
    QString dictionary = "https://ejje.weblio.jp/content/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionEijirou_triggered()
{
    QString dictionary = "https://eow.alc.co.jp/search?q=";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actiongoo_triggered()
{
    QString dictionary = "https://dictionary.goo.ne.jp/srch/en/";
    if (ui->tabWidget->currentIndex() == 0)
    {
        url = dictionary + ui->English_word_lineEdit->text();

    } else if (ui->tabWidget->currentIndex() ==2)
    {
        url = dictionary + ui->Oxford_word_lineEdit->text();
    }
    QDesktopServices::openUrl(QUrl(url));
}

void MainWindow::on_actionLanguage_study_terms_triggered()
{
    Language_study_terms *Language_study_termsWindow = new Language_study_terms;
    Language_study_termsWindow->show();
}

void MainWindow::on_actionManual_triggered()
{
    Manual *ManualWindow = new Manual;
    ManualWindow->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.about(this,tr("About Word-savvy"),tr("<h3>Word-savvy 1.2.0</h3>"
                                             "<p>Copyright (C) 2019,2020 Word-savvy Team</p>"));
}

// Tab

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 0)
    {
        tableName = "English";
        selectData();
    } else if (index == 1)
    {
        tableName = "Japanese";
        selectData();
    } else if (index == 2) {
        tableName = "Oxford";
        ui->tabWidget->setTabText(2,tableName);
    }
}

// Compobox

void MainWindow::set_part_of_speech_comboBox()
{
    QVector<QString> term;
    term << "adjective"
         << "adverb"
         << "article"
         << "conjunction"
         << "idiom"
         << "modal verb"
         << "noun"
         << "participle"
         << "phrasal verb"
         << "preposition"
         << "pronoun"
         << "slang"
         << "taboo"
         << "verb";

    for (int var = 0; var < term.size(); ++var) {
        ui->English_part_of_speech_comboBox->addItem(term[var]);
        ui->Japanese_part_of_speech_comboBox->addItem(term[var]);
        ui->Oxford_part_of_speech_comboBox->addItem(term[var]);
    }
}

// English

void MainWindow::on_English_add_pushButton_clicked()
{
    insertData();
    selectData();
    clear_English_form();
}

void MainWindow::on_English_edit_pushButton_clicked()
{
    if (ui->English_checkBox->isChecked())
    {
        updateData();
        selectData();
        clear_English_form();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Are you sure? If so, tick the box.");
        msgBox.exec();
    }
}

void MainWindow::on_English_delete_pushButton_clicked()
{
    if (ui->English_checkBox->isChecked())
    {
        deleteData();
        selectData();
        clear_English_form();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Are you sure? If so, tick the box.");
        msgBox.exec();
    }
}

void MainWindow::on_English_reset_pushButton_clicked()
{
    selectData();
    clear_English_form();
}

void MainWindow::on_English_close_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_search_English_keyword_by_word_pushButton_clicked()
{
    choice = "WORD";
    searchData();
}

void MainWindow::on_search_English_keyword_by_pronunciation_pushButton_clicked()
{
    choice = "PRONUNCIATION";
    searchData();
}

void MainWindow::on_search_English_keyword_by_memo_pushButton_clicked()
{
    choice = "MEMO";
    searchData();
}

void MainWindow::on_English_review_pushButton_clicked()
{
    choice = "STAR";
    searchData();
}

void MainWindow::clear_English_form()
{
    ui->English_word_lineEdit->setText("");
    ui->English_pronunciation_lineEdit->setText("");
    ui->English_part_of_speech_comboBox->setCurrentIndex(0);
    ui->English_star_comboBox->setCurrentIndex(0);
    ui->English_meaning_lineEdit->setText("");
    ui->English_textEdit->setText("");
    ui->English_checkBox->setChecked(false);
    ui->English_keyword_lineEdit->setText("");
}

void MainWindow::on_English_tableWidget_cellDoubleClicked(int row)
{
    number = ui->English_tableWidget->item(row,0)->text().toInt();
    setData();
}

// Japanese

void MainWindow::on_Japanese_add_pushButton_clicked()
{
    insertData();
    selectData();
    clear_Japanese_form();
}

void MainWindow::on_Japanese_edit_pushButton_clicked()
{
    if (ui->Japanese_checkBox->isChecked())
    {
        updateData();
        selectData();
        clear_Japanese_form();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Are you sure? If so, tick the box.");
        msgBox.exec();
    }
}

void MainWindow::on_Japanese_delete_pushButton_clicked()
{
    if (ui->Japanese_checkBox->isChecked())
    {
        deleteData();
        selectData();
        clear_Japanese_form();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Are you sure? If so, tick the box");
        msgBox.exec();
    }
}

void MainWindow::on_Japanese_reset_pushButton_clicked()
{
    selectData();
    clear_Japanese_form();
}

void MainWindow::on_Japanese_close_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_search_Japanese_keyword_by_word_pushButton_clicked()
{
    choice = "WORD";
    searchData();
}

void MainWindow::on_search_Japanese_keyword_by_pronunciation_pushButton_clicked()
{
    choice = "PRONUNCIATION";
    searchData();
}

void MainWindow::on_search_Japanese_keyword_by_memo_pushButton_clicked()
{
    choice = "MEMO";
    searchData();
}

void MainWindow::on_Japanese_review_pushButton_clicked()
{
    choice = "STAR";
    searchData();
}

void MainWindow::clear_Japanese_form()
{
    ui->Japanese_word_lineEdit->setText("");
    ui->Japanese_pronunciation_lineEdit->setText("");
    ui->Japanese_part_of_speech_comboBox->setCurrentIndex(0);
    ui->Japanese_star_comboBox->setCurrentIndex(0);
    ui->Japanese_meaning_lineEdit->setText("");
    ui->Japanese_textEdit->setText("");
    ui->Japanese_checkBox->setChecked(false);
}

void MainWindow::on_Japanese_tableWidget_cellDoubleClicked(int row)
{
    number = ui->Japanese_tableWidget->item(row,0)->text().toInt();
    setData();
}

// Oxford

void MainWindow::on_Oxford_reset_pushButton_clicked()
{
    selectData();
    clear_Oxford_form();
}

void MainWindow::on_Oxford_close_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_Oxford_edit_pushButton_clicked()
{
    if (ui->Oxford_checkBox->isChecked())
    {
        updateData();
        selectData();
        clear_Oxford_form();
    } else {
        QMessageBox msgBox;
        msgBox.setText("Are you sure? If so, tick the box.");
        msgBox.exec();
    }
}

void MainWindow::on_search_Oxford_keyword_by_word_pushButton_clicked()
{
    choice = "WORD";
    searchData();
}

void MainWindow::on_search_Oxford_keyword_by_pronunciation_pushButton_clicked()
{
    choice = "PRONUNCIATION";
    searchData();
}

void MainWindow::on_search_Oxford_keyword_by_memo_pushButton_clicked()
{
    choice = "MEMO";
    searchData();
}
void MainWindow::on_Oxford_review_pushButton_clicked()
{
    choice = "STAR";
    searchData();

}

void MainWindow::clear_Oxford_form()
{
    ui->Oxford_word_lineEdit->setText("");
    ui->Oxford_pronunciation_lineEdit->setText("");
    ui->Oxford_part_of_speech_comboBox->setCurrentIndex(0);
    ui->Oxford_star_comboBox->setCurrentIndex(0);
    ui->Oxford_meaning_lineEdit->setText("");
    ui->Oxford_textEdit->setText("");
    ui->Oxford_checkBox->setChecked(false);
}

void MainWindow::on_Oxford_tableWidget_cellDoubleClicked(int row)
{
    number = ui->Oxford_tableWidget->item(row,0)->text().toInt();
    setData();  
}
