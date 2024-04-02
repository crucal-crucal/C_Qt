#include "dialog.h"
#include "ui_dialog.h"

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPalette>
#include <QProgressDialog>
#include <iostream>
#include <windows.h>

using namespace std;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    bool ok;
    QFont font = QFontDialog::getFont(
                &ok, QFont("Fantasy", 12), this);
    if(ok)
    {
        ui->QPT_edit->setFont(font);
    }
    else
    {

    }
}


void Dialog::on_Btn_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::red, this, "选择颜色");//界面名称：“选择颜色”
    //获取调色板，设置颜色
    QPalette plet =ui->QPT_edit->palette();
    plet.setColor(QPalette::Text, color);
    ui->QPT_edit->setPalette(plet);
}


void Dialog::on_Btn_input_clicked()
{
    bool ok;
    /*QString text = QInputDialog::getText(this,
                                         tr("QInputDialog::getText()"), tr("Username:"),
                                            QLineEdit::Normal, QDir::home().dirName(), &ok);*/
    double d = QInputDialog::getDouble(this, tr("QInputDialog::getDouble()"),
                                            tr("Amount:"), 0, -1e8, 1e8, 5, &ok,
                                            Qt::WindowFlags(), 1);
    //this,tr,tr,起点，下限，上限，小数点位，点击ok，windowflags，精度

    //QString text1 = QString::number(d, 10, 5);
    //QString text1 = QString("%1").arg(d);
    if(ok)
    {
        ui->QPT_edit->appendPlainText(QString::fromStdString(to_string(d)));
    }
}


void Dialog::on_Btn_progress_clicked()
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


void Dialog::on_Btn_file_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();//获取当前文件夹的路径
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    curPath,
                                                    tr("All Files(*);;Text Files (*.txt)"));
    //this,名,路径，显示类型
    ui->QPT_edit->appendPlainText(fileName);
}


void Dialog::on_Btn_existing_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                     curPath);
    //this, 名，打开路径
    if(!dir.isEmpty())
    {
        ui->QPT_edit->appendPlainText(dir);
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
        ui->QPT_edit->appendPlainText(fileName);
    }

}


void Dialog::on_Btn_massage_clicked()
{
    /*QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();*/
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    //int ret = msgBox.exec();
    int ret = QMessageBox::warning(this, tr("My Application"),
                                    tr("The document has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard
                                    | QMessageBox::Cancel,
                                    QMessageBox::Save);
}

