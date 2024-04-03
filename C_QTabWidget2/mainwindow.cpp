
#include "./ui_mainwindow.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);

    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [&](int idx) {
        QWidget *wg = ui->tabWidget->widget(idx);
        QString name = ui->tabWidget->tabText(idx);
        m_widget.emplaceBack(wg), m_name.emplaceBack(name);
        //        m_widget.enqueue(wg),
        //        m_name.enqueue(name);//于上面效果相同，不一样的是，emplaceback不会进行任何不必要的复制或移动操作
        ui->tabWidget->removeTab(idx);
        ui->pushButton->setEnabled(true);
    });

    connect(ui->pushButton, &QPushButton::clicked, this, [&]() {
        //        ui->tabWidget->addTab(m_widget.front(), m_name.front());
        //        m_widget.pop_front(), m_name.pop_front();//这两句跟下面那一句等价
        ui->tabWidget->addTab(m_widget.dequeue(), m_name.dequeue());
        if (m_widget.empty()) {
            ui->pushButton->setDisabled(true);
        }
    });
}

MainWindow::~MainWindow() { delete ui; }
