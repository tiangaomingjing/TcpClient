#ifndef PDUITEMDELEGATE_H
#define PDUITEMDELEGATE_H

#include <QObject>
#include <QItemDelegate>

class PduItemDelegate : public QItemDelegate
{
  Q_OBJECT
public:
  explicit PduItemDelegate(QObject *parent = 0);
  QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
  void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
  void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:

public slots:
};

#endif // PDUITEMDELEGATE_H
