#include "widget.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>

QVBoxLayout *verticalLayout;
QGroupBox *Typeface;
QHBoxLayout *horizontalLayout;
QCheckBox *Underline;
QCheckBox *Italic;
QCheckBox *Bold;
QGroupBox *Colour;
QHBoxLayout *horizontalLayout_2;
QRadioButton *Black;
QRadioButton *Red;
QRadioButton *Blue;
QPlainTextEdit *plainTextEdit;
QHBoxLayout *horizontalLayout_3;
QPushButton *Clearn;
QPushButton *Ok;
QPushButton *Exit;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    if (this->objectName().isEmpty())
        this->setObjectName("Widget");
            this->resize(816, 600);
            QIcon icon;
            icon.addFile(QString::fromUtf8(":/icons/images/editor.ico"), QSize(), QIcon::Normal, QIcon::Off);
            this->setWindowIcon(icon);
            verticalLayout = new QVBoxLayout(this);
            verticalLayout->setObjectName("verticalLayout");
            Typeface = new QGroupBox(this);
            Typeface->setTitle("字体");
            horizontalLayout = new QHBoxLayout(Typeface);
            horizontalLayout->setObjectName("horizontalLayout");
            Underline = new QCheckBox(Typeface);
            Underline->setText("下划线");

            horizontalLayout->addWidget(Underline);

            Italic = new QCheckBox(Typeface);
            Italic->setText("斜体");

            horizontalLayout->addWidget(Italic);

            Bold = new QCheckBox(Typeface);
            Bold->setText("加粗");

            horizontalLayout->addWidget(Bold);


            verticalLayout->addWidget(Typeface);

            Colour = new QGroupBox(this);
            Colour->setTitle("颜色");
            horizontalLayout_2 = new QHBoxLayout(Colour);
            horizontalLayout_2->setObjectName("horizontalLayout_2");
            Black = new QRadioButton(Colour);
            Black->setText("黑色");

            horizontalLayout_2->addWidget(Black);

            Red = new QRadioButton(Colour);
            Red->setText("红色");

            horizontalLayout_2->addWidget(Red);

            Blue = new QRadioButton(Colour);
            Blue->setText("蓝色");

            horizontalLayout_2->addWidget(Blue);


            verticalLayout->addWidget(Colour);

            plainTextEdit = new QPlainTextEdit(this);
            plainTextEdit->setObjectName("plainTextEdit");
            QFont font;
            font.setPointSize(20);
            plainTextEdit->setFont(font);

            verticalLayout->addWidget(plainTextEdit);

            horizontalLayout_3 = new QHBoxLayout();
            horizontalLayout_3->setObjectName("horizontalLayout_3");
            Clearn = new QPushButton(this);
            Clearn->setText("清楚");
            QIcon icon1;
            icon1.addFile(QString::fromUtf8(":/icons/images/212.bmp"), QSize(), QIcon::Normal, QIcon::Off);
            Clearn->setIcon(icon1);

            horizontalLayout_3->addWidget(Clearn);

            Ok = new QPushButton(this);
            Ok->setText("确认");
            QIcon icon2;
            icon2.addFile(QString::fromUtf8(":/icons/images/322.bmp"), QSize(), QIcon::Normal, QIcon::Off);
            Ok->setIcon(icon2);

            horizontalLayout_3->addWidget(Ok);

            Exit = new QPushButton(this);
            Exit->setText("清除");
            QIcon icon3;
            icon3.addFile(QString::fromUtf8(":/icons/images/324.bmp"), QSize(), QIcon::Normal, QIcon::Off);
            Exit->setIcon(icon3);

            horizontalLayout_3->addWidget(Exit);


            verticalLayout->addLayout(horizontalLayout_3);


            //retranslateUi(this);
            QObject::connect(Clearn, &QPushButton::clicked, plainTextEdit, qOverload<>(&QPlainTextEdit::clear));
            QObject::connect(Ok, &QPushButton::clicked, this, qOverload<>(&QWidget::close));
            QObject::connect(Exit, &QPushButton::clicked, this, qOverload<>(&QWidget::close));

            QMetaObject::connectSlotsByName(this);
}

Widget::~Widget()
{
}

