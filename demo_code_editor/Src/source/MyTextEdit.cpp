#include "Src/include/MyTextEdit.h"

#include "Src/include/MyHighlighter.h"
#include "ui_MyTextEdit.h"

MyTextEdit::MyTextEdit(QWidget *parent)
    : QWidget(parent), ui(new Ui::MyTextEdit) {
  ui->setupUi(this);
  this->initConnect();
  this->initFont();
  this->initHighlighter();
  this->highlightCurrentLine();
}

MyTextEdit::~MyTextEdit() { delete ui; }

void MyTextEdit::initConnect() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 文本修改
  connect(ui->textEdit, &QTextEdit::textChanged, this,
          &MyTextEdit::onTextChanged, Qt::UniqueConnection);

  // 滚动条同步
  connect(ui->textEdit->horizontalScrollBar(), &QAbstractSlider::valueChanged,
          this, &MyTextEdit::textEditHScrollBarChanged, Qt::UniqueConnection);
  connect(ui->horizontalScrollBar, &QAbstractSlider::valueChanged, this,
          &MyTextEdit::textEditHScrollBarChanged, Qt::UniqueConnection);
  connect(ui->textEdit->verticalScrollBar(), &QAbstractSlider::valueChanged,
          this, &MyTextEdit::textEditHScrollBarChanged, Qt::UniqueConnection);
  connect(ui->textBrowser->verticalScrollBar(), &QAbstractSlider::valueChanged,
          this, &MyTextEdit::textBrowserVScrollBarChanged,
          Qt::UniqueConnection);

  // 行高亮
  connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this,
          &MyTextEdit::highlightCurrentLine, Qt::UniqueConnection);
}

void MyTextEdit::initFont() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mFont = QFont("Consolas", 14);
  ui->textEdit->setFont(mFont);
  QTextBlockFormat format;
  format.setLineHeight(QFontMetrics(mFont).height() * 1.1,
                       QTextBlockFormat::FixedHeight);
  QTextCursor cursor = ui->textEdit->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);

  ui->textBrowser->setFont(mFont);
}

void MyTextEdit::initHighlighter() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  new MyHighlighter(ui->textEdit->document());
}

void MyTextEdit::textEditHScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->horizontalScrollBar->setMinimum(
      ui->textEdit->horizontalScrollBar()->minimum());
  ui->horizontalScrollBar->setMaximum(
      ui->textEdit->horizontalScrollBar()->maximum());
  ui->horizontalScrollBar->setPageStep(
      ui->textEdit->horizontalScrollBar()->pageStep());
  ui->horizontalScrollBar->setValue(value);
}

void MyTextEdit::scrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->horizontalScrollBar()->setValue(value);
}

void MyTextEdit::textEditVScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textBrowser->verticalScrollBar()->setMaximum(
      ui->textEdit->verticalScrollBar()->maximum());
  ui->textBrowser->verticalScrollBar()->setMinimum(
      ui->textEdit->verticalScrollBar()->minimum());
  ui->textBrowser->verticalScrollBar()->setPageStep(
      ui->textEdit->verticalScrollBar()->pageStep());
  ui->textBrowser->verticalScrollBar()->setValue(value);
}

void MyTextEdit::textBrowserVScrollBarChanged(int value) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->verticalScrollBar()->setValue(value);
}

void MyTextEdit::onTextChanged() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  int lineCount = ui->textEdit->document()->lineCount();
  QString line = ui->textBrowser->toPlainText();
  int currentCount = line.trimmed().split("\n").size();
  if (currentCount > lineCount) {
    for (int i = currentCount; i > lineCount; i--) {
      line.chop((QString::number(i) + "\n").size());
    }
  } else if (currentCount == 1 && line.size() < 1) {
    line += "1\n";
  } else if (currentCount < lineCount) {
    for (int i = currentCount; i < lineCount; i++) {
      line += QString::number(i + 1) + "\n";
    }
  }

  ui->textBrowser->setMaximumWidth(25 + QString::number(lineCount).size() * 7);
  ui->textBrowser->setText(line);
  QTextBlockFormat format;
  format.setLineHeight(QFontMetrics(mFont).height() * 1.1,
                       QTextBlockFormat::FixedHeight);
  format.setAlignment(Qt::AlignRight);

  QTextCursor cursor = ui->textBrowser->textCursor();
  cursor.select(QTextCursor::Document);
  cursor.mergeBlockFormat(format);
}

void MyTextEdit::highlightCurrentLine() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QList<QTextEdit::ExtraSelection> extraSelections;

  QTextEdit::ExtraSelection selection;
  selection.format.setBackground(QColor(0, 100, 100, 20));
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = ui->textEdit->textCursor();

  //  selection.cursor.clearSelection();

  extraSelections.append(selection);

  ui->textEdit->setExtraSelections(extraSelections);
}
