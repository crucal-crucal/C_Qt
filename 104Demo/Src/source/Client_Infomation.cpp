#include "Src/include/Client_Infomation.h"

#include "ui_Client_Infomation.h"

Client_Infomation* Client_Infomation::self = nullptr;

Client_Infomation::Client_Infomation(QDialog* parent)
    : QDialog(parent), ui(new Ui::Client_Infomation) {
  ui->setupUi(this);
  // 消除右上角问号
  this->setWindowFlags(Qt::WindowCloseButtonHint);

  connect(ui->btn_ok, &QPushButton::clicked, this, &Client_Infomation::btnOk);
  connect(ui->btn_cancel, &QPushButton::clicked, this,
          &Client_Infomation::close);
}

Client_Infomation::~Client_Infomation() { delete ui; }

void Client_Infomation::infoMation(tmap t, clientType type) {
  std::unordered_map<clientType, QString> mp = {
      {telemetry, "客户端信息"},
      {telesigna, "客户端信息"},
      {cleint_telemetryID, "遥测地址"},
      {client_telesignaID, "遥信地址"},
  };

  ui->tableView->clearSelection();
  QString headerName = mp[type];
  model = new QStandardItemModel(this);
  model->setHorizontalHeaderItem(0, new QStandardItem(headerName));
  model->setHorizontalHeaderItem(1, new QStandardItem("描述"));

  int cnt = 0;
  for (const auto& [key, value] : t) {
    QString str = type == telemetry || type == telesigna
                      ? key.first
                      : QString::number(key.second);
    QStandardItem* item1 = new QStandardItem(str);
    QStandardItem* item2 = new QStandardItem(value);

    model->setItem(cnt, 0, item1);
    model->setItem(cnt, 1, item2);
    cnt++;
  }

  ui->tableView->setFocusPolicy(Qt::NoFocus);  // 禁用焦点框
  ui->tableView->verticalHeader()->hide();     // 隐藏行号
  ui->tableView->viewport()->update();
  ui->tableView->horizontalHeader()->setStretchLastSection(
      true);  // 最后一列填充剩余空间
  ui->tableView->horizontalHeader()->setSectionsClickable(
      false);  // 表头不可点击
  ui->tableView->horizontalHeader()->setDefaultAlignment(
      Qt::AlignLeft);  // 表头默认靠左对其
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);  // 选中行
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);  // 单选
  ui->tableView->setEditTriggers(
      QAbstractItemView::NoEditTriggers);  // 不可编辑
  ui->tableView->setModel(model);
  // 需要放在将所有数据填充完成之后也即是 setModel 之后，否则不会起作用
  ui->tableView->setColumnWidth(0, 250);  // 第一列宽度设置

  local_type = type;
  local = t;
}

tvalue Client_Infomation::getValue() {
  auto selectionModel = ui->tableView->selectionModel();
  auto selectedIndexs = selectionModel->selectedIndexes();

  if (!selectedIndexs.isEmpty()) {
    QModelIndex first = selectedIndexs.first();
    bool isClient = local_type == telemetry || local_type == telesigna;
    QString data1 = first.data().toString();
    QString data2 =
        QString("%1（%2）").arg(data1, selectedIndexs.last().data().toString());
    QString data = isClient ? data1 : data2;
    for (const auto& [key, value] : local) {
      if (key.first == data) {
        return key;
      }
    }
  }
  return std::make_pair(QString(""), std::numeric_limits<unsigned int>::max());
}

void Client_Infomation::btnOk() {
  tvalue value = this->getValue();
  if (value ==
      std::make_pair(QString(""), std::numeric_limits<unsigned int>::max())) {
    QMessageBox::information(nullptr, "警告", "还未选择值，不能确定");
    return;
  }
  switch (local_type) {
    case telemetry: {
      emit teleMetry(value);
      break;
    }
    case telesigna: {
      emit teleSigna(value);
      break;
    }
    case cleint_telemetryID: {
      emit clientTelemetryValue(value);
      break;
    }
    case client_telesignaID: {
      emit clientTelesignaValue(value);
      break;
    }
    default:
      break;
  }

  this->close();
}
