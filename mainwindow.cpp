#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pduitemwidget.h"
#include <QStringListModel>
#include <QHeaderView>
#include <QListWidgetItem>
#include <QListView>
#include <QStandardItemModel>
#include <QTcpSocket>
#include <QHostAddress>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_isConnected(false)
{
  ui->setupUi(this);
//  PduItemWidget *item=new PduItemWidget;
//  item->show();

  for(int i=0;i<10;i++)
  {
    listWidgetAddItemWidget();
  }
  ui->listWidget->setResizeMode(QListView::Adjust);
  m_clientSocket=new QTcpSocket(this);
  ui->radioButton->setEnabled(false);

  connect(ui->checkBox,SIGNAL(clicked(bool)),this,SLOT(onCheckBoxAllClicked(bool)));
  connect(ui->btnAdd,SIGNAL(clicked(bool)),this,SLOT(onBtnAddClicked()));
  connect(ui->btnRemove,SIGNAL(clicked(bool)),this,SLOT(onBtnRemoveClicked()));
  connect(ui->btnConnect,SIGNAL(clicked(bool)),this,SLOT(onBtnConnectClicked()));
  connect(ui->btnDisconnect,SIGNAL(clicked(bool)),this,SLOT(onBtnDisconnectClicked()));
  connect(ui->btnSendAll,SIGNAL(clicked(bool)),this,SLOT(onBtnSendAllClicked()));
  connect(m_clientSocket,SIGNAL(connected()),this,SLOT(onSocketConnected()));
  connect(m_clientSocket,SIGNAL(disconnected()),this,SLOT(onSocketDisconnected()));
  connect(m_clientSocket,SIGNAL(readyRead()),this,SLOT(onSocketReadyRead()));
  connect(m_clientSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));
}

MainWindow::~MainWindow()
{
  delete ui;
}
void MainWindow::listWidgetAddItemWidget()
{
  QListWidgetItem *item;
  PduItemWidget *itemBuddy;
  item=new QListWidgetItem(ui->listWidget);
  itemBuddy=new PduItemWidget(ui->listWidget);
  connect(itemBuddy,SIGNAL(sendClicked()),this,SLOT(onBtnSingleSendClicked()));

  item->setSizeHint(QSize(200,80));

  ui->listWidget->addItem(item);
  ui->listWidget->setItemWidget(item,itemBuddy);
}

void MainWindow::onBtnSingleSendClicked()
{
  if(m_clientSocket->isOpen())
  {
    PduItemWidget *item=qobject_cast<PduItemWidget*>(sender());
    QByteArray array=item->toByteArray();
    m_clientSocket->write(array);
  }
}
void MainWindow::onCheckBoxAllClicked(bool checked)
{
  int count=ui->listWidget->count();
  PduItemWidget *item;
  for(int i=0;i<count;i++)
  {
    item=qobject_cast<PduItemWidget *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
    item->setChecked(checked);
  }
}
void MainWindow::onBtnAddClicked(void)
{
  listWidgetAddItemWidget();
}

void MainWindow::onBtnRemoveClicked(void)
{
  QListWidgetItem *item=NULL;
  item=ui->listWidget->currentItem();
  if(item!=NULL)
  {
    ui->listWidget->removeItemWidget(item);
    delete item;
  }
}
void MainWindow::onBtnConnectClicked(void)
{
  if(m_clientSocket->isOpen())
    return;
  QString ipaddr;
  quint16 port;
  ipaddr=ui->lineEditIpAddr->text();
  port=ui->lineEditIpPort->text().toUShort();
  if(ipaddr=="127.0.0.1")
  {
    m_clientSocket->connectToHost(QHostAddress::LocalHost,port);
  }
  else
  {
    m_clientSocket->connectToHost(ipaddr,port);
  }
}

void MainWindow::onBtnDisconnectClicked(void)
{
  if(m_clientSocket->isOpen())
  {
    m_clientSocket->close();
    qDebug()<<"disconnect socket";
  }
}
void MainWindow::onSocketConnected()
{
  m_isConnected=true;
  ui->radioButton->setChecked(true);
  qDebug()<<"connect......";
}
void MainWindow::onSocketDisconnected()
{
  ui->radioButton->setChecked(false);
  m_isConnected=false;
}

void MainWindow::onSocketError(QAbstractSocket::SocketError error)
{
  qDebug()<<error;
}

void MainWindow::onSocketReadyRead()
{
  qDebug()<<m_clientSocket->readAll();
}

void MainWindow::onBtnSendAllClicked()
{
  if(m_clientSocket->isOpen())
  {
    int count=ui->listWidget->count();
    PduItemWidget *item;
    for(int i=0;i<count;i++)
    {
      item=qobject_cast<PduItemWidget *>(ui->listWidget->itemWidget(ui->listWidget->item(i)));
      if(item->isChecked())
      {
        QByteArray array=item->toByteArray();
        m_clientSocket->write(array);
      }
    }
  }
}
