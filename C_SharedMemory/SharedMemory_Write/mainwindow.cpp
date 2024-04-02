#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Write");
    m_SharedMemory = new QSharedMemory(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicked()
{
    // 设置内存 Key 为 crucal
    m_SharedMemory->setKey("crucal");

    // 如果对象已经链接该内存，解除
    if (m_SharedMemory->isAttached()) {
        m_SharedMemory->detach();
    }

    QString str = QFileDialog::getOpenFileName(this, "open", "", "");
    QImage img;
    img.load(str);
    ui->label->setPixmap(QPixmap::fromImage(img));

    // 将图片缓存到 buffer中
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    QDataStream out(&buffer);
    out << img;
    int size = buffer.size();
    // 创建指定大小的内存，自动 attach
    if (!m_SharedMemory->create(size)) {
        qDebug() << "Unable to create shared memory segment.\n" << m_SharedMemory->errorString();
        return;
    }

    m_SharedMemory->lock();
    char *to = static_cast<char*>(m_SharedMemory->data());
    const char *from = buffer.data().data();
    memcpy(to, from, qMin(m_SharedMemory->size(), size));
    m_SharedMemory->unlock();
}

