#include "Src/include/MyCodeEditor.h"

MyCodeEditor::MyCodeEditor(QWidget *parent, QFont font)
    : QPlainTextEdit{parent} {
  lineNumberWidget = new LineNumberWidget(this);
  this->initConnection();
  this->initHighlighter();
  this->setAllFont(font);
  this->highlightCurrentLine();
  this->updateLineNumberWidgetWidth();

  this->setLineWrapMode(QPlainTextEdit::NoWrap);
}

MyCodeEditor::~MyCodeEditor() { delete lineNumberWidget; }

void MyCodeEditor::lineNumberWidgetPaintEvent(QPaintEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QPainter painter(lineNumberWidget);
  // 绘制行号区域
  painter.fillRect(event->rect(), QColor(100, 100, 100, 20));

  // 拿到 block
  QTextBlock block = this->firstVisibleBlock();
  // 拿到行号
  int blockNumber = block.blockNumber();
  // 拿到当前的 block 的 top
  int cursorTop = this->blockBoundingGeometry(this->textCursor().block())
                      .translated(this->contentOffset())
                      .top();
  // 拿到 block 的 top
  int top = this->blockBoundingGeometry(block)
                .translated(this->contentOffset())
                .top();

  int bottom = top + this->blockBoundingRect(block).height();

  while (block.isValid() && top <= event->rect().bottom()) {
    // 绘制画笔颜色
    painter.setPen(cursorTop == top ? Qt::black : Qt::gray);
    // 绘制文字
    painter.drawText(0, top, this->getLineNumberWidgetWidth() - 3, bottom - top,
                     Qt::AlignRight, QString::number(blockNumber + 1));

    // 拿到下一个 block
    block = block.next();
    top = bottom;
    bottom = top + this->blockBoundingRect(block).height();
    blockNumber++;
  }
}

void MyCodeEditor::lineNumberWidgetMousePressEvent(QMouseEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__;
  qDebug() << "y:\t" << event->y();
#endif
  QTextBlock block = this->document()->findBlockByLineNumber(
      event->y() / this->fontMetrics().height() +
      this->verticalScrollBar()->value());
  this->setTextCursor(QTextCursor(block));
}

void MyCodeEditor::lineNumberWidgetwheelEventEvent(QWheelEvent *event) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  if (event->angleDelta().y() == Qt::Horizontal) {
    this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value() -
                                          event->angleDelta().x());
  } else {
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() -
                                        event->angleDelta().y());
  }

  event->accept();
}

bool MyCodeEditor::saveFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName;
  if (mFileName.isEmpty()) {
    fileName = QFileDialog::getSaveFileName(this, "保存文件");
    mFileName = fileName;
  } else {
    fileName = mFileName;
  }

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
    return false;
  }

  QTextStream out(&file);
  out << this->toPlainText();
  file.close();
  isSaved = true;

  return true;
}

bool MyCodeEditor::saveAsFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName = QFileDialog::getSaveFileName(this, "保存文件");
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
    return false;
  }
  mFileName = fileName;

  QTextStream out(&file);
  out << this->toPlainText();
  file.close();
  isSaved = true;

  return true;
}

void MyCodeEditor::setFileName(QString fileName) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mFileName = fileName;
}

QString MyCodeEditor::getFileName() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  return mFileName;
}

void MyCodeEditor::setAllFont(QFont font) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->setFont(font);
  if (mHighlighter) {
    mHighlighter->setFont(font);
  }
  this->updateLineNumberWidgetWidth();
}

bool MyCodeEditor::checkSaved() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  return isSaved;
}

void MyCodeEditor::highlightCurrentLine() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QList<QTextEdit::ExtraSelection> extraSelections;

  QTextEdit::ExtraSelection selection;
  selection.format.setBackground(QColor(0, 100, 100, 20));
  selection.format.setProperty(QTextFormat::FullWidthSelection, true);
  selection.cursor = this->textCursor();

  extraSelections.append(selection);

  this->setExtraSelections(extraSelections);
}

void MyCodeEditor::updateLineNumberWidget(const QRect &rect, int dy) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  if (dy) {
    lineNumberWidget->scroll(0, dy);
  } else {
    lineNumberWidget->update(0, rect.y(), this->getLineNumberWidgetWidth(),
                             rect.height());
  }
}

void MyCodeEditor::updateLineNumberWidgetWidth() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 设置边距
  this->setViewportMargins(this->getLineNumberWidgetWidth(), 0, 0, 0);
}

void MyCodeEditor::updateSaveState() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  isSaved = false;
}

void MyCodeEditor::initConnection() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // cursor
  connect(this, &QPlainTextEdit::cursorPositionChanged, this,
          &MyCodeEditor::highlightCurrentLine, Qt::UniqueConnection);
  // updateisSave
  connect(this, &QPlainTextEdit::textChanged, this,
          &MyCodeEditor::updateSaveState, Qt::UniqueConnection);
  // blockCount
  connect(this, &QPlainTextEdit::blockCountChanged, this,
          &MyCodeEditor::updateLineNumberWidgetWidth, Qt::UniqueConnection);
  // updateRequest
  connect(this, &QPlainTextEdit::updateRequest, this,
          &MyCodeEditor::updateLineNumberWidget, Qt::UniqueConnection);
}

void MyCodeEditor::initHighlighter() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mHighlighter = new MyHighlighter(this->document());
}

int MyCodeEditor::getLineNumberWidgetWidth() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取宽度
  int t = this->fontMetrics().horizontalAdvance(QChar('0'));
  return 8 + QString::number(this->blockCount() + 1).size() * t;
}

void MyCodeEditor::resizeEvent(QResizeEvent *event) {
  QPlainTextEdit::resizeEvent(event);
  lineNumberWidget->setGeometry(0, 0, this->getLineNumberWidgetWidth(),
                                this->contentsRect().height());
}
