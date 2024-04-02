#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::setActionsForButton()
{
    ui->tBtn_init->setDefaultAction(ui->actioninit);//初始化列表
    ui->tBtn_init->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文本
    ui->tBtn_clean->setDefaultAction(ui->action_clean);      //清除列表
    ui->tBtn_clean->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文本
    ui->tBtn_insert->setDefaultAction(ui->action_insert);    //插入项
    ui->tBtn_insert->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文本
    ui->tBtn_add->setDefaultAction(ui->action_add);    //添加项
    ui->tBtn_add->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文本
    ui->tBtn_delete->setDefaultAction(ui->action_delete);    //删除当前项
    ui->tBtn_delete->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置文本

    ui->tBtn_SelAll->setDefaultAction(ui->action_SelAll);        //全选
    ui->tBtn_SelNone->setDefaultAction(ui->action_SelNone);      //空选
    ui->tBtn_SelInvs->setDefaultAction(ui->action_SelInvs);      //反选
}

void MainWindow::createSelectionMenu()
{
    QMenu* menu=new QMenu(this);
    menu->addAction(ui->action_SelAll), menu->addAction(ui->action_SelNone), menu->addAction(ui->action_SelInvs);

    //listWidget上方的tBtnSelectItem按钮
    ui->tBtn_selectItem->setPopupMode(QToolButton::MenuButtonPopup);     //菜单弹出模式，执行按钮的Action
    ui->tBtn_selectItem->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->tBtn_selectItem->setDefaultAction(ui->action_select);    //关联Action
    ui->tBtn_selectItem->setMenu(menu);                 //设置下拉菜单

    //工具栏上的下拉式菜单按钮
    QToolButton  *aBtn=new QToolButton(this);
    aBtn->setPopupMode(QToolButton::InstantPopup);      //立刻下拉菜单，按钮关联的Action不会被执行
    aBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    aBtn->setDefaultAction(ui->action_select);          //关联Action
    aBtn->setMenu(menu);       //设置下拉菜单
    ui->maintoolBar->addWidget(aBtn);   //工具栏上添加按钮

    //工具栏添加分隔条和“退出”按钮
    ui->maintoolBar->addSeparator();
    ui->maintoolBar->addAction(ui->action_exit);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("数据库名");
    db.setUserName("用户名");
    db.setPassword("密码");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "success");
    }
    else {
        QMessageBox::information(this, "infor", "open failed");
        //qDebug()<<"error open database because"<<db.lastError().text();
    }

    setCentralWidget(ui->splitter); //设置中心组件
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);    //定制快捷菜单
    setActionsForButton();
    createSelectionMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_clean_triggered()
{
    ui->listWidget->clear();
}


void MainWindow::on_actioninit_triggered()
{
    QListWidgetItem *aItem;     //每一行是一个QListWidgetItem

    QIcon aIcon;
    aIcon.addFile(":/icons/194.JPG");     //设置图标
    bool chk=ui->chkBoxListEditable->isChecked();   //是否可编辑

    ui->listWidget->clear();    //清除列表
    for (int i=0; i<10; i++)
    {
        QString str=QString("lds %1").arg(i);
        aItem=new QListWidgetItem(); //新建一个项

        aItem->setText(str);    //设置文字标签
        aItem->setIcon(aIcon);  //设置图标
        aItem->setCheckState(Qt::Checked);  //设置为选中状态
        if (chk)    //可编辑, 设置flags
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        else        //不可编辑, 设置flags
            aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        ui->listWidget->addItem(aItem);     //添加一个项
    }
}


void MainWindow::on_chkBoxListEditable_clicked(bool checked)
{
    //可编辑 QCheckBox的响应代码， 设置所有项是否可编辑
    QListWidgetItem *aItem;

    int cnt=ui->listWidget->count();//项的个数
    for (int i=0; i<cnt; i++)
    {
        aItem=ui->listWidget->item(i);//获得一个项
        if (checked) //可编辑
            aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
        else
            aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    }
}


void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString str;
    if (current != NULL)        //需要检测指针是否为空
    {
        if (previous==NULL)     //需要检测指针是否为空
            str="当前："+current->text();
        else
            str="前一项："+previous->text()+"; 当前项："+current->text();
        ui->editCutItemText->setText(str);
    }
    ui->plainTextEdit->appendPlainText("currentItemChanged()信号被发射");
}


void MainWindow::on_action_insert_triggered()
{
    //    QIcon aIcon;
    //    aIcon.addFile(":/images/icons/check2.ico");  //图标
    QIcon aIcon(":/icons/194.JPG");   //定义图标变量并直接赋值

    bool chk=ui->chkBoxListEditable->isChecked(); //是否可编辑

    QListWidgetItem* aItem=new QListWidgetItem("Inserted Item"); //创建一个项
    aItem->setIcon(aIcon);      //设置图标
    aItem->setCheckState(Qt::Checked);  //设置为checked
    if (chk)    //可编辑，设置标志
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->insertItem(ui->listWidget->currentRow(),aItem); //在当前行的前面插入一个项
}


void MainWindow::on_action_add_triggered()
{
    QIcon aIcon(":/icons/194.JPG");       //定义图标
    bool chk=ui->chkBoxListEditable->isChecked();   //是否可编辑

    QListWidgetItem* aItem=new QListWidgetItem("Added Item"); //创建一个Item
    aItem->setIcon(aIcon);              //设置图标
    aItem->setCheckState(Qt::Checked);  //设置为checked
    if (chk)    //可编辑，设置标志
        aItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);
    else
        aItem->setFlags(Qt::ItemIsSelectable |Qt::ItemIsUserCheckable |Qt::ItemIsEnabled);

    ui->listWidget->addItem(aItem);     //添加一个项
}


void MainWindow::on_action_delete_triggered()
{
    int row=ui->listWidget->currentRow();   //当前行号

    QListWidgetItem* aItem=ui->listWidget->takeItem(row); //移除指定行的项，但不delete
    delete aItem;   //需要手工删除对象
}


void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu* menuList=new QMenu(this); //创建菜单

    //添加Actions创建菜单项
    menuList->addAction(ui->actioninit);
    menuList->addAction(ui->action_clean);
    menuList->addAction(ui->action_insert);
    menuList->addAction(ui->action_add);
    menuList->addAction(ui->action_delete);
    menuList->addSeparator();
    menuList->addAction(ui->action_SelAll);
    menuList->addAction(ui->action_SelNone);
    menuList->addAction(ui->action_SelInvs);

    menuList->exec(QCursor::pos()); //在鼠标光标位置显示快捷菜单

    delete menuList;    //菜单显示完后，需要删除对象
}


//全选
void MainWindow::on_action_SelAll_triggered()
{
    int cnt=ui->listWidget->count();    //项的总数
    for (int i=0; i<cnt; i++)
    {
        QListWidgetItem *aItem=ui->listWidget->item(i);
        aItem->setCheckState(Qt::Checked);   //设置为选中
    }
}


//空选
void MainWindow::on_action_SelNone_triggered()
{
    QListWidgetItem *aItem;

    int cnt=ui->listWidget->count();
    for (int i=0; i<cnt; i++)
    {
        aItem=ui->listWidget->item(i);
        aItem->setCheckState(Qt::Unchecked);
    }
}

//反选
void MainWindow::on_action_SelInvs_triggered()
{
    QListWidgetItem *aItem;
    int cnt=ui->listWidget->count();    //项的总数
    for (int i=0; i<cnt; i++)
    {
        aItem=ui->listWidget->item(i);  //获取一个项
        if (aItem->checkState()!=Qt::Checked)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::on_tBtnSortAsc_clicked()
{
    if(ui->listWidget->isSortingEnabled())
    ui->listWidget->sortItems(Qt::AscendingOrder);
}


void MainWindow::on_tBtnSortDes_clicked()
{
    if(ui->listWidget->isSortingEnabled())
    ui->listWidget->sortItems(Qt::DescendingOrder);     //降序排序
}


void MainWindow::on_chkBoxSorting_clicked(bool checked)
{
    ui->listWidget->setSortingEnabled(checked);         //是否允许排序
}


void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ui->plainTextEdit->appendPlainText(QString("currentRowChanged()信号被发射，currentRow=%1").arg(currentRow));
}


void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{
    ui->plainTextEdit->appendPlainText("currentTextChanged()信号被发射，currentText="+currentText);
}


void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemActivated()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemChanged()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemEntered(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemEntered()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemPressed()信号被发射，"+item->text());
}


void MainWindow::on_listWidget_itemSelectionChanged()
{
    ui->plainTextEdit->appendPlainText("itemSelectionChanged()信号被发射");
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->plainTextEdit->appendPlainText("itemClicked()信号被发射，"+item->text());
}


void MainWindow::on_tBtnClearText_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_tBtnAddLine_clicked()
{
    ui->plainTextEdit->appendPlainText("");
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    ui->plainTextEdit->appendPlainText("itemClicked()信号被发射，"+item->text());
}


void MainWindow::on_action_exit_triggered()
{
    this->close();
}

