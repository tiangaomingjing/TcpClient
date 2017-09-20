#include "mainwindow.h"
#include <QApplication>
#include "pduitemwidget.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
//  PduItemWidget *item=new PduItemWidget;
//  item->show();
  return a.exec();
}
