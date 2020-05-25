#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QFileInfo>
#include <QDateTime>
class DataModel : public QAbstractItemModel
{
    Q_OBJECT

    QStringList* m_data;
public:
    DataModel(QObject *parent);

    virtual int columnCount(const QModelIndex &parent) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent) const;
    virtual QModelIndex parent(const QModelIndex &index) const;

public slots:
    void updateFile(QFileInfo fileInfo);
    void clear();
};

#endif // DATAMODEL_H
