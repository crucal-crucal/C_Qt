#include "Src/include/mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::init() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    this->setWindowTitle("Demo_Notepad");
    this->setWindowIcon(QIcon(":/images/pencil.png"));
    this->setCentralWidget(ui->textEdit);

    {
        connect(ui->action_about, &QAction::triggered, this, &MainWindow::about, Qt::UniqueConnection);
        connect(ui->action_print, &QAction::triggered, this, &MainWindow::print, Qt::UniqueConnection);
        connect(ui->action_bold, &QAction::triggered, this, &MainWindow::bold, Qt::UniqueConnection);
        connect(ui->action_copy, &QAction::triggered, this, &MainWindow::copy, Qt::UniqueConnection);
        connect(ui->action_cut, &QAction::triggered, this, &MainWindow::cut, Qt::UniqueConnection);
        connect(ui->action_exit, &QAction::triggered, this, &MainWindow::exit, Qt::UniqueConnection);
        connect(ui->action_font, &QAction::triggered, this, &MainWindow::font, Qt::UniqueConnection);
        connect(ui->action_italic, &QAction::triggered, this, &MainWindow::italic, Qt::UniqueConnection);
        connect(ui->action_new, &QAction::triggered, this, &MainWindow::newFile, Qt::UniqueConnection);
        connect(ui->action_open, &QAction::triggered, this, &MainWindow::openFile, Qt::UniqueConnection);
        connect(ui->action_paste, &QAction::triggered, this, &MainWindow::paste, Qt::UniqueConnection);
        connect(ui->action_undo, &QAction::triggered, this, &MainWindow::undo, Qt::UniqueConnection);
        connect(ui->action_underline, &QAction::triggered, this, &MainWindow::underline, Qt::UniqueConnection);
        connect(ui->action_save_as, &QAction::triggered, this, &MainWindow::saveAsFile, Qt::UniqueConnection);
        connect(ui->action_redo, &QAction::triggered, this, &MainWindow::redo, Qt::UniqueConnection);
        connect(ui->action_save, &QAction::triggered, this, &MainWindow::saveFile, Qt::UniqueConnection);
    }
}

void MainWindow::newFile() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    currentFile.clear();
    ui->textEdit->clear();
}

void MainWindow::openFile() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
    QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {}
}

void MainWindow::saveFile() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::saveAsFile() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::print() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::bold(bool bold) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::italic(bool italic) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::underline(bool onderline) {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::font() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::copy() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::paste() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::cut() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::undo() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::redo() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::exit() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}

void MainWindow::about() {
#ifdef NDEBUG
    qDebug() << __func__;
#endif
}
