#include "Src/include/mainwindow.h"

#include "ui_mainwindow.h"

std::unique_ptr<QSettings> m_Settings;

// 获取历史记录
QList<QString> getHistory();
// 保存打开历史记录
void saveHistory(QString path);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->init();
  m_Settings =
      std::make_unique<QSettings>("settings.ini", QSettings::IniFormat);
#if !QT_CONFIG(printer)
  ui->action_print->setEnabled(false);
#endif
  this->initMenu();
}

MainWindow::~MainWindow() { delete ui; }

QList<QString> getHistory() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 打开开始读入
  int size = m_Settings.get()->beginReadArray("history");

  QList<QString> list;
  for (int i = 0; i < size; i++) {
    m_Settings.get()->setArrayIndex(i);
    list.append(m_Settings.get()->value("path").toString());
  }

  // 关闭读入
  m_Settings.get()->endArray();

  return list;
}

void saveHistory(QString path) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取历史
  QList<QString> list = getHistory();
  list.append(path);
  QSet<QString> set(list.begin(), list.end());
  QList<QString> uniqueList(set.begin(), set.end());
  // 打开开始写入
  m_Settings.get()->beginWriteArray("history");
  for (int i = 0; i < uniqueList.size(); i++) {
    m_Settings.get()->setArrayIndex(i);
    // 保存字符串
    m_Settings.get()->setValue("path", uniqueList[i]);
  }
  // 关闭开始写入
  m_Settings.get()->endArray();
}

void MainWindow::init() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  this->setWindowTitle("Demo_Notepad");
  this->setWindowIcon(QIcon(":/images/pencil.png"));
  this->setCentralWidget(ui->textEdit);

  {
    connect(ui->action_about, &QAction::triggered, this, &MainWindow::about,
            Qt::UniqueConnection);
    connect(ui->action_print, &QAction::triggered, this, &MainWindow::print,
            Qt::UniqueConnection);
    connect(ui->action_bold, &QAction::triggered, this, &MainWindow::bold,
            Qt::UniqueConnection);
    connect(ui->action_copy, &QAction::triggered, this, &MainWindow::copy,
            Qt::UniqueConnection);
    connect(ui->action_cut, &QAction::triggered, this, &MainWindow::cut,
            Qt::UniqueConnection);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::exit,
            Qt::UniqueConnection);
    connect(ui->action_font, &QAction::triggered, this, &MainWindow::font,
            Qt::UniqueConnection);
    connect(ui->action_italic, &QAction::triggered, this, &MainWindow::italic,
            Qt::UniqueConnection);
    connect(ui->action_new, &QAction::triggered, this, &MainWindow::newFile,
            Qt::UniqueConnection);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::openFile,
            Qt::UniqueConnection);
    connect(ui->action_paste, &QAction::triggered, this, &MainWindow::paste,
            Qt::UniqueConnection);
    connect(ui->action_undo, &QAction::triggered, this, &MainWindow::undo,
            Qt::UniqueConnection);
    connect(ui->action_underline, &QAction::triggered, this,
            &MainWindow::underline, Qt::UniqueConnection);
    connect(ui->action_save_as, &QAction::triggered, this,
            &MainWindow::saveAsFile, Qt::UniqueConnection);
    connect(ui->action_redo, &QAction::triggered, this, &MainWindow::redo,
            Qt::UniqueConnection);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::saveFile,
            Qt::UniqueConnection);
  }
}

void MainWindow::newFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  currentFile.clear();
  ui->textEdit->clear();
}

void MainWindow::openFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName = QFileDialog::getOpenFileName(this, "打开文件");
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法打开此文件:" + file.errorString());
    return;
  }
  currentFile = fileName;
  setWindowTitle(currentFile);

  QTextStream in(&file);
  QString text = in.readAll();
  ui->textEdit->setText(text);
  file.close();

  saveHistory(currentFile);
  this->initMenu();
}

void MainWindow::openRecentFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  // 获取发送者
  QAction *action = static_cast<QAction *>(sender());
  QString fileName = action->text();
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法打开此文件:" + file.errorString());
    return;
  }
  currentFile = fileName;
  setWindowTitle(currentFile);

  QTextStream in(&file);
  QString text = in.readAll();
  ui->textEdit->setText(text);
  file.close();

  saveHistory(currentFile);
  this->initMenu();
}

void MainWindow::saveFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName;
  if (currentFile.isEmpty()) {
    fileName = QFileDialog::getSaveFileName(this, "保存文件");
    currentFile = fileName;
  } else {
    fileName = currentFile;
  }

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
    return;
  }
  setWindowTitle(fileName);

  QTextStream out(&file);
  QString text = ui->textEdit->toHtml();
  out << text;

  file.close();
  saveHistory(currentFile);
  this->initMenu();
}

void MainWindow::saveAsFile() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QString fileName;
  fileName = QFileDialog::getSaveFileName(this, "另存文件");

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, "警告", "无法保存文件:" + file.errorString());
    return;
  }
  currentFile = fileName;
  setWindowTitle(fileName);

  QTextStream out(&file);
  QString text = ui->textEdit->toHtml();
  out << text;

  file.close();
  saveHistory(currentFile);
  this->initMenu();
}

void MainWindow::print() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif

#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
  QPrinter printDev;
#if QT_CONFIG(printdialog)
  QPrintDialog dialog(&printDev, this);
  // 如果用户在打印对话框中点击了 Cancel
  if (dialog.exec() == QDialog::Rejected) {
    return;
  }
#endif
  ui->textEdit->print(&printDev);
#endif
}

void MainWindow::bold(bool bold) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->setFontWeight(bold ? QFont::Bold : QFont::Normal);
}

void MainWindow::italic(bool italic) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->setFontItalic(italic);
}

void MainWindow::underline(bool onderline) {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->setFontUnderline(onderline);
}

void MainWindow::font() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  bool fontSelected;
  QFont font = QFontDialog::getFont(&fontSelected, this);
  if (fontSelected) {
    ui->textEdit->setFont(font);
  }
}

void MainWindow::copy() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->copy();
}

void MainWindow::paste() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->paste();
}

void MainWindow::cut() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->cut();
}

void MainWindow::undo() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->undo();
}

void MainWindow::redo() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  ui->textEdit->redo();
}

void MainWindow::exit() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QCoreApplication::exit();
}

void MainWindow::about() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QMessageBox::about(this, "这是我的 Notepad...",
                     "这是我的 Notepad，欢迎使用...");
}

void MainWindow::clearHistory() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  m_Settings.get()->remove("history");
  this->initMenu();
}

void MainWindow::initMenu() {
#ifdef NDEBUG
  qDebug() << __func__;
#endif
  QMenu *recent = this->findChild<QMenu *>("recent");
  qDebug() << recent->title();
  auto arr = recent->children().toVector();
  QSet<QObject *> set(arr.begin(), arr.end());
  foreach (QObject *ch, set) {
    QAction *action = static_cast<QAction *>(ch);
    recent->removeAction(action);
  }

  QList<QString> list = getHistory();

  for (int i = list.size() - 1; i >= 0; i--) {
    recent->addAction(list[i], this, &MainWindow::openRecentFile);
  }
  if (list.size()) {
    recent->addAction("清除历史记录", this, &MainWindow::clearHistory,
                      QKeySequence("Ctrl+Alt+Shift+C"));
  }
}
