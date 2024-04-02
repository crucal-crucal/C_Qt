#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Read");
    m_SharedMemory = new QSharedMemory(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::p_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::p_clicked()
{
    m_SharedMemory->setKey("crucal");

    if (!m_SharedMemory->isAttached()) {
        if (!m_SharedMemory->attach(QSharedMemory::ReadOnly)) {
            qDebug() << "Unable to attach the SharedMemory.  " << m_SharedMemory->errorString();
            return;
        }
    }
    QBuffer buffer;
    QDataStream in(&buffer);

    m_SharedMemory->lock();
    buffer.setData(static_cast<char*>(m_SharedMemory->data()), m_SharedMemory->size());
    buffer.open(QBuffer::ReadOnly);
    QImage img;
    in >> img;
    m_SharedMemory->unlock();

    m_SharedMemory->detach();

    ui->label->setPixmap(QPixmap::fromImage(img));
}

