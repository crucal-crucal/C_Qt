#include "Src/include/MyTextEditByCode.h"

#include "Src/include/MyHighlighter.h"

MyTextEditByCode::MyTextEditByCode(QWidget *parent) : QWidget{parent} {
  this->initWidget();
  this->initFont();
  this->initConnection();
  this->initHighlighter();
  this->highlightCurrentLine();
}

void MyTextEditByCode::initWidget() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QWidget *horizontalLayoutWidget = new QWidget();
  // 竖向布局
  QVBoxLayout *verticalLayout = new QVBoxLayout(this);
  verticalLayout->setSpacing(0);
  verticalLayout->setMargin(0);
  // 横向布局
  QHBoxLayout *horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
  horizontalLayout->setSpacing(0);
  horizontalLayout->setMargin(0);

  textEdit = new QTextEdit();
  textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  textEdit->setLineWrapMode(QTextEdit::NoWrap);

  textBrowser = new QTextBrowser();
  textBrowser->setMaximumWidth(25);
  textBrowser->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  scrollBar = new QScrollBar();
  scrollBar->setOrientation(Qt::Horizontal);

  horizontalLayout->addWidget(textBrowser);
  horizontalLayout->addWidget(textEdit);

  verticalLayout->addWidget(horizontalLayoutWidget);
  verticalLayout->addWidget(scrollBar);
}

void MyTextEditByCode::initFont() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mFont = QFont("Consolas", 14);
  textEdit->setFont(mFont);
  QTextBlockFormat format;
  format.setLineHeight(QFontMetrics(mFont).height() * 1.1,
                       QTextBlockFormat::FixedHeight);
  QTextCursor cursor = textEdit->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);

  textBrowser->setFont(mFont);
}

void MyTextEditByCode::initConnection() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 文本修改
  connect(textEdit, &QTextEdit::textChanged, this,
          &MyTextEditByCode::onTextEditChanged, Qt::UniqueConnection);

  // 滚动条同步
  connect(textEdit->horizontalScrollBar(), &QAbstractSlider::valueChanged, this,
          &MyTextEditByCode::onTextEditHorizontalScrollBarChanged,
          Qt::UniqueConnection);
  connect(textEdit->verticalScrollBar(), &QAbstractSlider::valueChanged, this,
          &MyTextEditByCode::onTextEditVerticalScrollBarChanged,
          Qt::UniqueConnection);
  connect(scrollBar, &QAbstractSlider::valueChanged, this,
          &MyTextEditByCode::onScrollBarChanged, Qt::UniqueConnection);
  connect(textBrowser->verticalScrollBar(), &QAbstractSlider::valueChanged,
          this, &MyTextEditByCode::onTextBrowserHorizontalScrollBarChanged,
          Qt::UniqueConnection);

  // 行高亮
  connect(textEdit, &QTextEdit::cursorPositionChanged, this,
          &MyTextEditByCode::highlightCurrentLine, Qt::UniqueConnection);
}

void MyTextEditByCode::initHighlighter() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  new MyHighlighter(textEdit->document());
}

void MyTextEditByCode::highlightCurrentLine() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QList<QTextEdit::ExtraSelection> extraSelections;

  QTextEdit::ExtraSelection selection;
  selection.format.setBackground(QColor(0, 100, 100, 20));
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = textEdit->textCursor();

  //  selection.cursor.clearSelection();

  extraSelections.append(selection);

  textEdit->setExtraSelections(extraSelections);
}

void MyTextEditByCode::onTextEditHorizontalScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  scrollBar->setMaximum(textEdit->horizontalScrollBar()->maximum());
  scrollBar->setMinimum(textEdit->horizontalScrollBar()->minimum());
  scrollBar->setPageStep(textEdit->horizontalScrollBar()->pageStep());
  scrollBar->setValue(value);
}

void MyTextEditByCode::onTextEditVerticalScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  textBrowser->verticalScrollBar()->setMaximum(
      textEdit->verticalScrollBar()->maximum());
  textBrowser->verticalScrollBar()->setMinimum(
      textEdit->verticalScrollBar()->minimum());
  textBrowser->verticalScrollBar()->setPageStep(
      textEdit->verticalScrollBar()->pageStep());
  textBrowser->verticalScrollBar()->setValue(value);
}

void MyTextEditByCode::onTextBrowserHorizontalScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  textEdit->verticalScrollBar()->setValue(value);
}

void MyTextEditByCode::onScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  textEdit->horizontalScrollBar()->setValue(value);
}

void MyTextEditByCode::onTextEditChanged() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  int lineCountOfTextEdit = textEdit->document()->lineCount();

  QString text = textBrowser->toPlainText();
  int lineCountOftTextBrowser = text.trimmed().split("\n").size();

  if (lineCountOftTextBrowser > lineCountOfTextEdit) {
    for (int i = lineCountOftTextBrowser; i > lineCountOfTextEdit; i--) {
      text.chop((QString::number(i) + "\n").size());
    }
  } else if (lineCountOftTextBrowser == 1 && text.size() < 1) {
    text = "1\n";
  } else if (lineCountOftTextBrowser < lineCountOfTextEdit) {
    for (int i = lineCountOftTextBrowser; i < lineCountOfTextEdit; i++) {
      text += QString::number(i + 1) + "\n";
    }
  }
  textBrowser->setMaximumWidth(25 +
                               QString::number(lineCountOfTextEdit).size() * 7);
  textBrowser->setText(text);

  QTextBlockFormat format;
  format.setLineHeight(QFontMetrics(mFont).height() * 1.1,
                       QTextBlockFormat::FixedHeight);
  format.setAlignment(Qt::AlignRight);

  QTextCursor cursor = textBrowser->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);
}
