#include "tablestatisticsmodel.h"

TableStatisticsModel::TableStatisticsModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

void TableStatisticsModel::populate(const FileSystemAnalyzer& analyzer) {
    clear();

    types_ = analyzer.getTypes();
    amount_ = analyzer.getAmount();
    totalSize_ = analyzer.getTotalSize();
    averageSize_ = analyzer.getAverageSize();
}

void TableStatisticsModel::clear() {
    types_.clear();
    amount_.clear();
    totalSize_.clear();
    averageSize_.clear();
}

int TableStatisticsModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return types_.length();
}

int TableStatisticsModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 4;
}

QVariant TableStatisticsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    if (index.column() == 0)
        return types_[index.row()];
    else if (index.column() == 1)
        return amount_[index.row()];
    else if (index.column() == 2)
        return totalSize_[index.row()];
    else if (index.column() == 3)
        return averageSize_[index.row()];

    return QVariant();
}

QVariant TableStatisticsModel::headerData(int section,
                                          Qt::Orientation orientation,
                                          int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0)
            return QString("Type");
        else if (section == 1)
            return QString("Amount");
        else if (section == 2)
            return QString("Total size");
        else if (section == 3)
            return QString("Average size");
    }

    return QVariant();
}
