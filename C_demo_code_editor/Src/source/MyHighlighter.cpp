#include "Src/include/MyHighlighter.h"

MyHighlighter::MyHighlighter(QTextDocument *parent, QString fontFamily,
                             int fontSize)
    : QSyntaxHighlighter{parent} {
  mFontSize = fontSize;
  mFontFamily = fontFamily;
  this->setFormats();
}

void MyHighlighter::setFormats() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->addNormalTextFormat();
  this->addNumberFormat();
  this->addStringFormat();
  this->addCommentFormat();
  this->addKeywordsFormat();
  this->addClassNameFormat();
  this->addFunctionFormat();
}

void MyHighlighter::setFont(QFont font) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  mFontFamily = font.family();
  mFontSize = font.pointSize();
}

void MyHighlighter::highlightBlock(const QString &text) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  foreach (const HighlightRule &rule, highlightRules) {
    QRegExp regExp(rule.pattern);
    int idx = regExp.indexIn(text);
    while (idx >= 0) {
      int length = regExp.matchedLength();
      setFormat(idx, length, rule.format);
      idx = regExp.indexIn(text, idx + length);
    }
  }

  this->addMultiLineCommentFormat(text);
}

void MyHighlighter::addNormalTextFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;
  rule.pattern = QRegExp("[a-z0-9A-Z]+");

  QTextCharFormat normalTextFormat;
  normalTextFormat.setFont(QFont(mFontFamily, mFontSize));
  normalTextFormat.setForeground(QColor(0, 0, 0));
  rule.format = normalTextFormat;

  highlightRules.append(rule);
}

void MyHighlighter::addNumberFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;
  rule.pattern = QRegExp("\\b\\d+|\\d+\\.+\\d+\\b");

  QTextCharFormat numberFormat;
  numberFormat.setFont(QFont(mFontFamily, mFontSize));
  numberFormat.setForeground(QColor(250, 80, 50));
  rule.format = numberFormat;

  highlightRules.append(rule);
}

void MyHighlighter::addStringFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;

  QTextCharFormat stringFormat;
  stringFormat.setFont(QFont(mFontFamily, mFontSize));
  stringFormat.setForeground(QColor(0, 180, 180));

  rule.format = stringFormat;

  // ''
  rule.pattern = QRegExp("'[^']*'");
  highlightRules.append(rule);

  // ""
  rule.pattern = QRegExp("\"[^\"]*\"");
  highlightRules.append(rule);

  // ``
  rule.pattern = QRegExp("`[^`]*`");
  highlightRules.append(rule);
}

void MyHighlighter::addCommentFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;

  QTextCharFormat commentFormat;
  commentFormat.setFont(QFont(mFontFamily, mFontSize));
  commentFormat.setForeground(Qt::darkGreen);
  commentFormat.setFontItalic(true);

  rule.format = commentFormat;

  // //data
  rule.pattern = QRegExp("\\/\\/.*$");
  highlightRules.append(rule);

  //  // /*data*/ ... /*data*/
  //  rule.pattern = QRegExp("\\/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*\\/");
  //  highlightRules.append(rule);
}

void MyHighlighter::addKeywordsFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QFile file(":/config/keywords.txt");
  QTextStream keywordsStream(&file);

  HighlightRule rule;
  QTextCharFormat keywordsFormat;
  keywordsFormat.setFont(QFont(mFontFamily, mFontSize));
  keywordsFormat.setForeground(Qt::darkMagenta);
  rule.format = keywordsFormat;

  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(nullptr, "警告",
                         "无法打开此文件" + file.errorString());
    return;
  }

  keywordsStream.seek(0);
  QString line;
  while (!keywordsStream.atEnd()) {
    line = keywordsStream.readLine();
    if (line != "") {
      rule.pattern = QRegExp("\\b" + line + "\\b");
      highlightRules.append(rule);
    }
  }

  file.close();
}

void MyHighlighter::addClassNameFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;

  QTextCharFormat classFormat;
  classFormat.setFont(QFont(mFontFamily, mFontSize));
  classFormat.setForeground(QColor(150, 20, 100));
  classFormat.setFontWeight(99);

  rule.format = classFormat;

  rule.pattern = QRegExp("\\b[A-Z]+\\w*");
  highlightRules.append(rule);
}

void MyHighlighter::addFunctionFormat() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  HighlightRule rule;

  QTextCharFormat functionFormat;
  functionFormat.setFont(QFont(mFontFamily, mFontSize));
  functionFormat.setForeground(QColor(250, 0, 150));

  rule.format = functionFormat;

  rule.pattern = QRegExp("\\w+\\(");
  highlightRules.append(rule);

  rule.pattern = QRegExp("\\)");
  highlightRules.append(rule);
}

void MyHighlighter::addMultiLineCommentFormat(const QString &text) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->setCurrentBlockState(0);

  // /*
  QRegExp commentStartRegExp("\\/\\*");

  // */
  QRegExp commentEndRegExp("\\*\\/");

  // 高亮格式
  QTextCharFormat multiLineCommentFormat;
  multiLineCommentFormat.setFont(QFont(mFontFamily, mFontSize));
  multiLineCommentFormat.setForeground(Qt::darkGreen);
  multiLineCommentFormat.setFontItalic(true);

  int startindex = 0;
  if (this->previousBlockState() != 1) {
    startindex = commentStartRegExp.indexIn(text);
  }

  while (startindex >= 0) {
    int endindex = commentEndRegExp.indexIn(text, startindex);
    int commentLength = 0;
    if (endindex == -1) {  // 没有结束位置
      setCurrentBlockState(1);
      commentLength = text.length() - startindex;
    } else {  // 有结束位置需要设置格式
      commentLength = endindex - startindex + commentEndRegExp.matchedLength();
    }
    setFormat(startindex, commentLength, multiLineCommentFormat);
    startindex = commentStartRegExp.indexIn(text, commentLength + startindex);
  }
}
