#include "pduitemwidget.h"
#include "ui_pduitemwidget.h"
#include <QDebug>
#define MIN_COLUMN_SIZE 4
enum columnIndex{
  COL_LENGTH,
  COL_ID,
  COL_TYPE,
  COL_CMD};

PduItemWidget::PduItemWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PduItemWidget)
{
  ui->setupUi(this);

  for(int i=0;i<ui->tableWidget->columnCount();i++)
  {
    QTableWidgetItem *item=new QTableWidgetItem;
    item->setText("0");
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(0,i,item);
  }
  int count=ui->tableWidget->columnCount();
  ui->tableWidget->item(0,0)->setText(QString::number(count-1,16).toUpper());
  QStringList list;
  list<<tr("len(2)")<<tr("id(1)")<<tr("type(1)")<<tr("cmd(1)")<<tr("prm_0");
  ui->tableWidget->setHorizontalHeaderLabels(list);
  ui->tableWidget->resizeColumnsToContents();

  connect(ui->btnAdd,SIGNAL(clicked(bool)),this,SLOT(onBtnAddClicked()));
//  connect(ui->btnSend,SIGNAL(clicked(bool)),this,SLOT(onBtnSendClicked()));
  connect(ui->btnSend,SIGNAL(clicked(bool)),this,SIGNAL(sendClicked()));
  connect(ui->btnRemove,SIGNAL(clicked(bool)),this,SLOT(onBtnRemoveClicked()));
}

PduItemWidget::~PduItemWidget()
{
  delete ui;
  qDebug()<<"PduItemWidget release ---->";
}

void PduItemWidget::onBtnAddClicked()
{
  int count=ui->tableWidget->columnCount();
//  ui->tableWidget->setColumnCount(count+1);
  ui->tableWidget->insertColumn(count);
  QTableWidgetItem *item=new QTableWidgetItem;
  item->setText("0");
  item->setTextAlignment(Qt::AlignCenter);
  ui->tableWidget->setItem(0,count,item);
  ui->tableWidget->item(0,0)->setText(QString::number(count,16).toUpper());
  ui->tableWidget->setHorizontalHeaderItem(count,new QTableWidgetItem(tr("prm_%1(1)").arg(count-4)));
  ui->tableWidget->resizeColumnToContents(count);
}
void PduItemWidget::onBtnSendClicked()
{
  toByteArray();
}
void PduItemWidget::onBtnRemoveClicked()
{
  int count=ui->tableWidget->columnCount();
  if(count>MIN_COLUMN_SIZE)
  {
    ui->tableWidget->removeColumn(count-1);
    ui->tableWidget->item(0,0)->setText(QString::number(count-2,16).toUpper());
  }
}

QByteArray PduItemWidget::toByteArray()
{
  QByteArray array;
  bool ok;
  quint16 len=ui->tableWidget->item(0,0)->text().toUInt(&ok,16);
  quint8 byte=len&0xff;
  array.append(byte);
  quint8 byte2=(len>>8)&0xff;
  array.append(byte2);

  for(int i=1;i<ui->tableWidget->columnCount();i++)
  {
    quint8 byte=ui->tableWidget->item(0,i)->text().toUInt(&ok,16);
    if(ok)
      array.append(byte);
  }
  for(int i=0;i<array.size();i++)
    qDebug()<<"byte "<<i<<":"<<QString::number((quint8)array.at(i),16);
  return array;
}
bool PduItemWidget::isChecked()
{
  return ui->checkBox->isChecked();
}
void PduItemWidget::setHeaderVisible(bool visible)
{
  ui->tableWidget->horizontalHeader()->setVisible(visible);
}
void PduItemWidget::setChecked(bool checked)
{
  ui->checkBox->setChecked(checked);
}
