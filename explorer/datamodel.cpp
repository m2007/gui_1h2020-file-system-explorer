#include "datamodel.h"
DataModel::DataModel(QObject *parent) : QAbstractItemModel(parent)
{
    m_data = new QStringList();
}

int DataModel::columnCount(const QModelIndex &) const
{
    return 1;
}

int DataModel::rowCount(const QModelIndex &) const
{
    return 6;
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if( role == Qt::DisplayRole && m_data->size() == 6)
        {
            return m_data->at(index.row());
        }
        return QVariant();
}

QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Vertical) {
        switch (section) {
            case 0:
                return "Название";
            case 1:
                return "Расширение";
            case 2:
                return "Путь";
            case 3:
                return "Дата создания";
            case 4:
                return "Дата изменения";
            case 5:
                return "Размер файла (байт)";
        }
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return "Параметр";
        }
    }
}

QModelIndex DataModel::index(int row, int column, const QModelIndex &) const
{
    return createIndex(row, column, (void*)&m_data[row]);
}

QModelIndex DataModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

void DataModel::updateFile(QFileInfo fileInfo)
{
    while (m_data->size() > 0) {
        m_data->pop_back();
    }

    m_data->append(fileInfo.baseName());
    m_data->append(fileInfo.completeSuffix());
    m_data->append(fileInfo.absoluteFilePath());
    QDateTime dateC = fileInfo.created();
    m_data->append(dateC.toString("yyyy-MM-dd") + " в " + dateC.toString("hh:ss:mm"));
    QDateTime dateM = fileInfo.lastModified();
    m_data->append(dateM.toString("yyyy-MM-dd") + " в " + dateM.toString("hh:ss:mm"));
    m_data->append(fileInfo.isFile() ? QString::number(fileInfo.size()) : "");
    emit layoutChanged();
}

void DataModel::clear()
{
    while (m_data->size() > 0) {
        m_data->pop_back();
    }
    emit layoutChanged();
}
