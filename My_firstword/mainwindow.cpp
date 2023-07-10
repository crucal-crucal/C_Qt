#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLabel *Lab_fontsize = new QLabel("字体大小", this);
    ui->toolBar->insertWidget(ui->actionQuit, Lab_fontsize);

    QSpinBox *fontsize = new QSpinBox();
    fontsize->setValue(ui->plainTextEdit->font().pointSize());
    ui->toolBar->insertWidget(ui->actionQuit, fontsize);
    //addwidget直接添加在最后

    ui->toolBar->insertSeparator(ui->actionQuit);//分割线
    connect(fontsize, QOverload<int>::of(&QSpinBox::valueChanged), [=](int x){
        QFont font(ui->plainTextEdit->font());//获取当前Edit的字体
        font.setPixelSize(x);//更改当前字体的size
        ui->plainTextEdit->setFont(font);//实现该字体
    });

    QLabel *Lab_font = new QLabel("字体", this);
    ui->toolBar->insertWidget(ui->actionQuit, Lab_font);

    QFontComboBox *font_combox = new QFontComboBox();
    ui->toolBar->insertWidget(ui->actionQuit, font_combox);
    ui->toolBar->insertSeparator(ui->actionQuit);//分割线
    connect(font_combox, &QFontComboBox::currentFontChanged, this, [=](const QFont &font){
        //QFont font(ui->plainTextEdit->font());//获取当前Edit的字体
        //font.setFamily(s);//把字体改为s
        QFont t=font;
        t.setPointSize(ui->plainTextEdit->font().pointSize());
        ui->plainTextEdit->setFont(t);//实现该字体
    });

    //label = new QLabel(this->subtext, this);
    label = new QLabel;
    ui->statusbar->addWidget(label);
    //ui->statusbar->addAction(ui->actionOpen);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionItalic_triggered(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setItalic(checked);//斜体
    ui->plainTextEdit->setFont(font);
}


void MainWindow::on_actionBold_triggered(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setBold(checked);//粗体
    ui->plainTextEdit->setFont(font);
}


void MainWindow::on_actionUnderline_triggered(bool checked)
{
    QFont font=ui->plainTextEdit->font();
    font.setUnderline(checked);//下划线
    ui->plainTextEdit->setFont(font);
}


void MainWindow::on_actionabout_triggered()
{
    QMessageBox::about(this, tr("About Application"),
             tr("The <b>Application</b> example demonstrates how to "
                "write modern GUI applications using Qt, with a menu bar, "
                "toolbars, and a status bar."));
}


void MainWindow::on_actionaboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt消息框"));
}


void MainWindow::on_actionOpen_triggered()
{
    //tr("All Files(*)")
    QString fileName = QFileDialog::getOpenFileName(this,"Open File","",tr("Text File(*.txt)"));//打开文件
    //this->subtext = fileName;

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"error","打开文本失败!");
            return;
        }
        else
        {
            if(!file.isReadable())
                QMessageBox::warning(this,"error","当前文本不可读!");
            else
            {
                QString s=tr("当前文件夹：")+fileName;
                this->label->setText(s);//把文件路径放入label中
                //ui->statusbar->show();
                //label->show();
                QTextStream textStream(&file);
                ui->plainTextEdit->setPlainText(textStream.readAll());
                ui->plainTextEdit->show();
                file.close();
                flag_isOpen = 1;
                Last_FileName = fileName;
            }
        }
    }

}


void MainWindow::on_actionSave_triggered()
{
    if(flag_isNew)
    {
        if(ui->plainTextEdit->toPlainText()=="")
        {
            QMessageBox::warning(this,"error","content can not be none!",QMessageBox::Ok);
        }
        else
        {
            QFileDialog fileDialog;
            QString str = fileDialog.getSaveFileName(this,"Open File","","Text File(*.txt)");
            if(str == "")
            {
                return;
            }
            QFile filename(str);
            if(!filename.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Error!");
                return;
            }
            else
            {
                QTextStream textStream(&filename);
                QString str = ui->plainTextEdit->toPlainText();
                textStream << str;
                Last_FileContent =str;
            }
            QMessageBox::information(this,"Ssve File","Save File Success",QMessageBox::Ok);
            filename.close();
            flag_isNew = 0;
            Last_FileName = str;
        }
    }
    else
    {
        if(flag_isOpen)
        {
            QFile file(Last_FileName);
            if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"error","Open File Faile");
                return;
            }
            else
            {
                QTextStream textString(&file);
                QString str = ui->plainTextEdit->toPlainText();
                textString << str;
                Last_FileContent = str;
                QMessageBox::information(this,"Ssve File","Save File Success",QMessageBox::Ok);
                file.close();
            }
        }
        else
        {
            QMessageBox::warning(this,"Warning","Please new or open a file");
            return;
        }
    }

}


void MainWindow::on_actionSave_as_triggered()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,"Open File","",tr("All Files(*)"));
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"error","open file failure!");
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QString str = ui->plainTextEdit->toPlainText();
        //textStream<<str;
        QMessageBox::warning(this,"tip","Save File Success!");
        Last_FileContent = str;
        Last_FileName = fileName;
        flag_isNew = 0;
        file.close();
    }

}


void MainWindow::on_actionnew_triggered()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setHidden(false);
    flag_isNew = 1;
    flag_isOpen = 1;
}


void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

