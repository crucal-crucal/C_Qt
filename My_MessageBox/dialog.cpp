#include "dialog.h"
#include "ui_dialog.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <windows.h>
#include <iostream>
#include <QMessageBox>

#define MESSAGE \
    Dialog::tr("<p>Message boxes have a caption, a text, " \
               "and any number of buttons, each with standard or custom texts." \
               "<p>Click a button to close the message box. Pressing the Esc button " \
               "will activate the detected escape button (if any).")
#define MESSAGE_DETAILS \
    Dialog::tr("If a message box has detailed text, the user can reveal it " \
               "by pressing the Show Details... button.")

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    //connect(ui->Btn_aboutQt, SIGNAL(clicked(bool)), qApp, SLOT(aboutQt()));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_Btn_openfile_clicked()
{
    QString curPath = QDir::currentPath();
    QString afilname = QFileDialog::getOpenFileName(this, "open a file",
                                                    curPath,
                                                    "程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    if(!afilname.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(afilname);
    }
}


void Dialog::on_Btn_directory_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     curPath);
    //this, 名，打开路径
    if(!dir.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(dir);
    }
}


void Dialog::on_Btn_save_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               tr("1.txt"),
                               tr("All Files(*)"));
    //this,名字，要保存的文件名，要保存的文件类型
    if(!fileName.isEmpty())
    {
        ui->plainTextEdit->appendPlainText(fileName);
    }
}


void Dialog::on_Btn_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "选择颜色");//界面名称：“选择颜色”
    //获取调色板，设置颜色
    QPalette plet =ui->plainTextEdit->palette();
    plet.setColor(QPalette::Text, color);
    ui->plainTextEdit->setPalette(plet);
}


void Dialog::on_Btn_font_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("Fantasy", 12), this);
    if(ok)
    {
        ui->plainTextEdit->setFont(font);
    }
}


void Dialog::on_Btn_message_clicked()
{
    int numFiles = 100;//进度
    QProgressDialog progress("Copying files...", "Abort Copy", 0, numFiles, this);
    progress.setWindowModality(Qt::WindowModal);

    for (int i = 0; i < numFiles; i++) {
        progress.setValue(i);

        if (progress.wasCanceled())
            break;
        //... copy one file
        Sleep(100);//休息
    }
    progress.setValue(numFiles);
}


void Dialog::on_Btn_close_clicked()
{
    this->close();
}


void Dialog::on_Btn_clean_clicked()
{
    ui->plainTextEdit->clear();
}


void Dialog::on_Btn_inptstring_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                         tr("QInputDialog::getText()"), tr("Username:"),
                                            QLineEdit::Normal, QDir::home().dirName(), &ok);
    /*double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                            tr("Amount:"), 0, -1e8, 1e8, 5, &ok,
                                            Qt::WindowFlags(), 1);*/
    //this,tr,tr,起点，下限，上限，小数点位，点击ok，windowflags，精度

    //QString text1 = QString::number(d, 10, 5);
    //QString text1 = QString("%1").arg(d);
    if(ok)
    {
        ui->plainTextEdit->appendPlainText(text);
    }
}


void Dialog::on_Btn_inptint_clicked()
{
    bool ok;
    auto d = QInputDialog::getInt(this, tr("QInputDialog::getInt()"),
                                  tr("Percentage:"), 0, -1e8, 1e8, 1, &ok);
    if(ok)
    {
        ui->plainTextEdit->appendPlainText(QString::fromStdString(std::to_string(d)));
    }
}


void Dialog::on_Btn_inptdouble_clicked()
{
    bool ok;
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                            tr("Amount:"), 0, -1e8, 1e8, 5, &ok,
                                            Qt::WindowFlags(), 1);
    //this,tr,tr,起点，下限，上限，小数点位，点击ok，windowflags，精度
    if(ok)
    {
        ui->plainTextEdit->appendPlainText(QString::fromStdString(std::to_string(d)));
    }
}


void Dialog::on_Btn_openfiles_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
                             this,
                             "Select one or more files to open",
                             "F:",
                             tr("All Files(*)"));
    if(!files.isEmpty())
    {
        for (auto c:files)
            ui->plainTextEdit->appendPlainText(c);
    }
}


void Dialog::on_pushButton_10_clicked()
{
    QStringList items;
    items << tr("Monday") << tr("Tuesday") << tr("Wednesday") << tr("Thursday") << tr("Friday");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                         tr("Season:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
        ui->plainTextEdit->appendPlainText(item);
}


void Dialog::on_Btn_question_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("QMessageBox::question()"),
                                    MESSAGE,
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
        ui->plainTextEdit->appendPlainText(tr("Yes"));
    else if (reply == QMessageBox::No)
        ui->plainTextEdit->appendPlainText(tr("No"));
    else
        ui->plainTextEdit->appendPlainText(tr("Cancel"));
}


void Dialog::on_Btn_information_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this, tr("QMessageBox::information()"), MESSAGE);
    if (reply == QMessageBox::Ok)
        ui->plainTextEdit->appendPlainText(tr("Ok"));
    else
        ui->plainTextEdit->appendPlainText(tr("Escape"));
}


void Dialog::on_Btn_warning_clicked()
{
    QMessageBox msgBox(QMessageBox::Warning, tr("QMessageBox::warning()"),
                       MESSAGE, { }, this);
    msgBox.setDetailedText(MESSAGE_DETAILS);
    msgBox.addButton(tr("Save &Again"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("&Continue"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::AcceptRole)
        ui->plainTextEdit->appendPlainText(tr("Save Again"));
    else
        ui->plainTextEdit->appendPlainText(tr("Continue"));
}


void Dialog::on_Btn_critical_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this, tr("QMessageBox::critical()"),
                                    MESSAGE,
                                    QMessageBox::Abort | QMessageBox::Retry | QMessageBox::Ignore);
    if (reply == QMessageBox::Abort)
        ui->plainTextEdit->appendPlainText(tr("Abort"));
    else if (reply == QMessageBox::Retry)
        ui->plainTextEdit->appendPlainText(tr("Retry"));
    else
        ui->plainTextEdit->appendPlainText(tr("Ignore"));
}



void Dialog::on_Btn_about_clicked()
{
    QMessageBox::about(this, tr("About Application"),
             tr("The <b>Application</b> example demonstrates how to "
                "write modern GUI applications using Qt, with a menu bar, "
                "toolbars, and a status bar."));
}


void Dialog::on_Btn_aboutQt_clicked()
{
    QMessageBox::aboutQt(this, tr("About Qt消息框"));
}

