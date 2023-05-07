#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName("Dialog");
    this->resize(800, 600);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/tu/1/editor.ico"));
    this->setWindowIcon(icon);
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName("verticalLayout");
    groupBox_Font = new QGroupBox(this);
    groupBox_Font->setTitle("字体");
    horizontalLayout = new QHBoxLayout(groupBox_Font);
    horizontalLayout->setObjectName("horizontalLayout");
    Xiahuaxian = new QCheckBox(groupBox_Font);
    Xiahuaxian->setObjectName("Xiahuaxian");
    Xiahuaxian->setText("下划线");


    horizontalLayout->addWidget(Xiahuaxian);

    Xieti = new QCheckBox(groupBox_Font);
    Xieti->setObjectName("Xieti");
    Xieti->setText("斜体");

    horizontalLayout->addWidget(Xieti);

    Cuti = new QCheckBox(groupBox_Font);
    Cuti->setObjectName("Cuti");
    Cuti->setText("粗体");

    horizontalLayout->addWidget(Cuti);


    verticalLayout->addWidget(groupBox_Font);

    groupBox_Color = new QGroupBox(this);
    groupBox_Color->setTitle("颜色");
    horizontalLayout_2 = new QHBoxLayout(groupBox_Color);
    horizontalLayout_2->setObjectName("horizontalLayout_2");
    Black = new QRadioButton(groupBox_Color);
    Black->setObjectName("Black");
    Black->setText("Black");

    horizontalLayout_2->addWidget(Black);

    Red = new QRadioButton(groupBox_Color);
    Red->setObjectName("Red");
    Red->setText("Red");

    horizontalLayout_2->addWidget(Red);

    Blue = new QRadioButton(groupBox_Color);
    Blue->setObjectName("Blue");
    Blue->setText("Blue");

    horizontalLayout_2->addWidget(Blue);


    verticalLayout->addWidget(groupBox_Color);

    plainTextEdit = new QPlainTextEdit(this);
    plainTextEdit->setObjectName("plainTextEdit");

    verticalLayout->addWidget(plainTextEdit);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName("horizontalLayout_3");
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer);

    Clear = new QPushButton(this);
    Clear->setText("Clear");
    QIcon icon_1;
    icon_1.addFile(QString::fromUtf8(":/tu/1/212.bmp"), QSize(), QIcon::Normal, QIcon::Off);
    Clear->setIcon(icon_1);

    horizontalLayout_3->addWidget(Clear);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_2);

    exit = new QPushButton(this);
    exit->setText("exit");
    QIcon icon_2;
    icon_2.addFile(QString::fromUtf8(":/tu/1/324.bmp"), QSize(), QIcon::Normal, QIcon::Off);
    exit->setIcon(icon_2);

    horizontalLayout_3->addWidget(exit);

    confirm = new QPushButton(this);
    confirm->setText("confirm");
    QIcon icon_3;
    icon_3.addFile(QString::fromUtf8(":/tu/1/322.bmp"), QSize(), QIcon::Normal, QIcon::Off);
    confirm->setIcon(icon_3);

    horizontalLayout_3->addWidget(confirm);


    verticalLayout->addLayout(horizontalLayout_3);


    //retranslateUi(this);
    QObject::connect(Clear, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));
    QObject::connect(confirm, &QPushButton::clicked, this, qOverload<>(&QWidget::close));
    QObject::connect(exit, &QPushButton::clicked, this, qOverload<>(&QWidget::close));

    QMetaObject::connectSlotsByName(this);
}

Widget::~Widget()
{
}

void Widget::on_Xiahuaxian_clicked(bool checked)
{
    QFont font=this->plainTextEdit->font();
    font.setUnderline(checked);//下划线
    this->plainTextEdit->setFont(font);
}


void Widget::on_Xieti_clicked(bool checked)
{
    QFont font=this->plainTextEdit->font();
    font.setItalic(checked);//斜体
    this->plainTextEdit->setFont(font);
}


void Widget::on_Cuti_clicked(bool checked)
{
    QFont font=this->plainTextEdit->font();
    font.setBold(checked);//粗体
    this->plainTextEdit->setFont(font);
}


void Widget::on_Black_clicked()
{
    QPalette plet =this->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::black);
    this->plainTextEdit->setPalette(plet);
}


void Widget::on_Red_clicked()
{
    QPalette plet =this->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::red);
    this->plainTextEdit->setPalette(plet);
}


void Widget::on_Blue_clicked()
{
    QPalette plet =this->plainTextEdit->palette();
    plet.setColor(QPalette::Text, Qt::blue);
    this->plainTextEdit->setPalette(plet);
}


