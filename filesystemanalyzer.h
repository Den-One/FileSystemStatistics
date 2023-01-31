#ifndef FILESYSTEMANALYZER_H
#define FILESYSTEMANALYZER_H

#include <QObject>
#include <QDir>
#include <QFileInfo>

class FileSystemAnalyzer : public QObject {
    Q_OBJECT

public:
    explicit FileSystemAnalyzer(QObject* parent = nullptr);
    ~FileSystemAnalyzer();

    void clear();

    QList<QString> getTypes() const;
    QList<QString> getAmount() const;
    QList<QString> getTotalSize() const;
    QList<QString> getAverageSize() const;

    void recursiveDataSearch(QDir dir, quint32& nSubdirectories);

    void addFileTuple(const QFileInfo& info);
    void addDirectoryTuple(quint32 nSubdirectories);

signals:
    void analysisFinished();

public slots:
    void startAnalysis(QDir path);

private:
    QList<QString> types_;
    QList<QString> amount_;
    QList<QString> totalSize_;
    QList<QString> averageSize_;
};

#endif // FILESYSTEMANALYZER_H
