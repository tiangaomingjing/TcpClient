#include "pduitemdelegate.h"
#include "pduitemwidget.h"

PduItemDelegate::PduItemDelegate(QObject *parent) : QItemDelegate(parent)
{

}
QWidget *PduItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  PduItemWidget *item=new PduItemWidget(parent);
  return item;
}
void PduItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{

}
void PduItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}
