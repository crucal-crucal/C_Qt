
#include "widget.h"
#include "ui_widget.h"

void Widget::setBtnsize()
{
    ui->tBtn_0->setMinimumSize(minsize, minsize);
    ui->tBtn_1->setMinimumSize(minsize, minsize);
    ui->tBtn_2->setMinimumSize(minsize, minsize);
    ui->tBtn_3->setMinimumSize(minsize, minsize);
    ui->tBtn_4->setMinimumSize(minsize, minsize);
    ui->tBtn_5->setMinimumSize(minsize, minsize);
    ui->tBtn_6->setMinimumSize(minsize, minsize);
    ui->tBtn_7->setMinimumSize(minsize, minsize);
    ui->tBtn_8->setMinimumSize(minsize, minsize);
    ui->tBtn_9->setMinimumSize(minsize, minsize);
    ui->tBtn_add->setMinimumSize(minsize, minsize);
    ui->tBtn_Backspace->setMinimumSize(minsize, minsize);
    ui->tBtn_changes->setMinimumSize(minsize, minsize);
    ui->tBtn_Clear->setMinimumSize(minsize, minsize);
    ui->tBtn_Clear_all->setMinimumSize(minsize, minsize);
    ui->tBtn_div->setMinimumSize(minsize, minsize);
    ui->tBtn_equal->setMinimumSize(minsize, minsize);
    ui->tBtn_Madd->setMinimumSize(minsize, minsize);
    ui->tBtn_MC->setMinimumSize(minsize, minsize);
    ui->tBtn_MR->setMinimumSize(minsize, minsize);
    ui->tBtn_MS->setMinimumSize(minsize, minsize);
    ui->tBtn_mul->setMinimumSize(minsize, minsize);
    ui->tBtn_point->setMinimumSize(minsize, minsize);
    ui->tBtn_pow->setMinimumSize(minsize, minsize);
    ui->tBtn_pow2->setMinimumSize(minsize, minsize);
    ui->tBtn_sqrt->setMinimumSize(minsize, minsize);
    ui->tBtn_sub->setMinimumSize(minsize, minsize);
}

void Widget::connect_With_number()
{
    connect(ui->tBtn_0, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_1, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_2, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_3, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_4, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_5, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_6, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_7, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_8, SIGNAL(clicked()), this, SLOT(digitClicked()));
    connect(ui->tBtn_9, SIGNAL(clicked()), this, SLOT(digitClicked()));
}

void Widget::connect_with_button()
{
    connect(ui->tBtn_Clear_all, SIGNAL(clicked()), this, SLOT(clearAll()));
    connect(ui->tBtn_add, SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    connect(ui->tBtn_sub, SIGNAL(clicked()), this, SLOT(additiveOperatorClicked()));
    connect(ui->tBtn_mul, SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
    connect(ui->tBtn_div, SIGNAL(clicked()), this, SLOT(multiplicativeOperatorClicked()));
    connect(ui->tBtn_equal, SIGNAL(clicked()), this, SLOT(equalClicked()));
    connect(ui->tBtn_point, SIGNAL(clicked()), this, SLOT(pointClicked()));
    connect(ui->tBtn_changes, SIGNAL(clicked()), this, SLOT(changeSignClicked()));
    connect(ui->tBtn_Backspace, SIGNAL(clicked()), this, SLOT(backspaceClicked()));
    connect(ui->tBtn_Clear, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->tBtn_MC, SIGNAL(clicked()), this, SLOT(clearMemory()));
    connect(ui->tBtn_MR, SIGNAL(clicked()), this, SLOT(readMemory()));
    connect(ui->tBtn_MS, SIGNAL(clicked()), this, SLOT(setMemory()));
    connect(ui->tBtn_Madd, SIGNAL(clicked()), this, SLOT(addToMemory()));
    connect(ui->tBtn_sqrt, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    connect(ui->tBtn_pow, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
    connect(ui->tBtn_pow2, SIGNAL(clicked()), this, SLOT(unaryOperatorClicked()));
}

void Widget::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}

void Widget::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}

bool Widget::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}

void Widget::SetBtnIcon(QPixmap *map, QPushButton *Btn)
{
    Btn->setIconSize(Btn->size());
    map->scaled(Btn->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Btn->setIcon(*map);
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    display->setText(tr("0"));
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);

    setBtnsize();
    ui->tBtn_mul->setText(tr("\303\227"));
    ui->tBtn_div->setText(tr("\303\267"));
    ui->tBtn_pow->setText(tr("x\302\262"));
    ui->tBtn_changes->setText(tr("\302\261"));
    connect_With_number();
    connect_with_button();
    SetBtnIcon(new QPixmap (":/images/close(1).png"), ui->Btn_close);
    SetBtnIcon(new QPixmap(":/images/min(1).png"), ui->Btn_min);
//    for (int i = 0; i < NumDigitButtons; ++i)
//        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

//    QGridLayout *mainLayout = new QGridLayout;
//    for (int i = 1; i < NumDigitButtons; ++i) {
//        int row = ((9 - i) / 3) + 2;
//        int column = ((i - 1) % 3) + 1;
//        mainLayout->addWidget(digitButtons[i], row, column);
//    }
//    mainLayout->addWidget(digitButtons[0], 5, 1);
//    setLayout(mainLayout);
}

Widget::~Widget()
{
    delete ui;
}

//QToolButton *Widget::createButton(const QString &text, const char *member)
//{
//    QToolButton *button = new QToolButton;
//    button->setText(text);
//    connect(button, SIGNAL(clicked()), this, member);
//    return button;
//}

void Widget::digitClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}

void Widget::unaryOperatorClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}

void Widget::additiveOperatorClicked()
//! [10] //! [11]
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    //! [11] //! [12]
    if (!pendingMultiplicativeOperator.isEmpty()) {
        //! [12] //! [13]
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    //! [13] //! [14]
    if (!pendingAdditiveOperator.isEmpty()) {
        //! [14] //! [15]
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    //! [15] //! [16]
    pendingAdditiveOperator = clickedOperator;
    //! [16] //! [17]
    waitingForOperand = true;
}

void Widget::multiplicativeOperatorClicked()
{
    QToolButton *clickedButton = qobject_cast<QToolButton *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}

void Widget::equalClicked()
{
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}


void Widget::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}

void Widget::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

void Widget::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}

void Widget::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}

void Widget::clearMemory()
{
    sumInMemory = 0.0;
}

void Widget::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Widget::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Widget::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}
//! [32]
//! [34]
