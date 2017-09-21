#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>

namespace Ui {
class MainWindow;
}
class QTcpSocket;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void onBtnSingleSendClicked();
  void onCheckBoxAllClicked(bool checked);
  void onBtnAddClicked(void);
  void onBtnRemoveClicked(void);
  void onBtnConnectClicked(void);
  void onBtnDisconnectClicked(void);
  void onBtnSendAllClicked();
  void onSocketConnected();
  void onSocketDisconnected();
  void onSocketError(QAbstractSocket::SocketError error);
  void onSocketReadyRead();

private:
  void listWidgetAddItemWidget();
private:
  Ui::MainWindow *ui;
  QTcpSocket *m_clientSocket;
  bool m_isConnected;
};

#endif // MAINWINDOW_H
