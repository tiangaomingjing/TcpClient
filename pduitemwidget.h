#ifndef PDUITEMWIDGET_H
#define PDUITEMWIDGET_H

#include <QWidget>

namespace Ui {
class PduItemWidget;
}

class PduItemWidget : public QWidget
{
  Q_OBJECT

public:
  explicit PduItemWidget(QWidget *parent = 0);
  ~PduItemWidget();
  QByteArray toByteArray(void);
  bool isChecked(void);
  void setHeaderVisible(bool visible);
  void setChecked(bool checked);
signals:
  void sendClicked();
private slots:
  void onBtnAddClicked();
  void onBtnSendClicked();
  void onBtnRemoveClicked();
private:
  Ui::PduItemWidget *ui;
};

#endif // PDUITEMWIDGET_H
