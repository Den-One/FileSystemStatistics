#ifndef TABLESTATISTICSMODEL_H
#define TABLESTATISTICSMODEL_H

#include "filesystemanalyzer.h"

#include <QAbstractTableModel>

class TableStatisticsModel: public QAbstractTableModel {
    Q_OBJECT

public:
    explicit TableStatisticsModel(QObject* parent = nullptr);

    void populate(const FileSystemAnalyzer& analyzer);
    void clear();

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

private:
    QList<QString> types_;
    QList<QString> amount_;
    QList<QString> totalSize_;
    QList<QString> averageSize_;
};

#endif // TABLESTATISTICSMODEL_H
