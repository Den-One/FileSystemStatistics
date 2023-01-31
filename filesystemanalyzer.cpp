#include "filesystemanalyzer.h"

FileSystemAnalyzer::FileSystemAnalyzer(QObject *parent): QObject(parent) {
}

FileSystemAnalyzer::~FileSystemAnalyzer() {
    qDebug() << "thread finished";
}

void FileSystemAnalyzer::clear() {
    types_.clear();
    amount_.clear();
    totalSize_.clear();
    averageSize_.clear();
}

QList<QString> FileSystemAnalyzer::getTypes() const {
    return types_;
}

QList<QString> FileSystemAnalyzer::getAmount() const {
    return amount_;
}

QList<QString> FileSystemAnalyzer::getTotalSize() const {
    return totalSize_;
}

QList<QString> FileSystemAnalyzer::getAverageSize() const {
    return averageSize_;
}

void FileSystemAnalyzer::recursiveDataSearch(QDir dir, quint32& nSubdirectories) {
    foreach(QFileInfo info, dir.entryInfoList( QDir::Files
                                              |QDir::Dirs
                                              |QDir::NoDotAndDotDot, QDir::Type
                                              |QDir::DirsFirst))
    {
        if (info.isDir()) {
            ++nSubdirectories;
            recursiveDataSearch(info.filePath(), nSubdirectories);
        }
        else if (info.isFile()) {
            addFileTuple(info);
        }
    }
}

void FileSystemAnalyzer::addFileTuple(const QFileInfo& info) {
    auto id = types_.indexOf(info.suffix());
    if (id != -1) {
        amount_[id] = QString::number(amount_[id].toInt() + 1);
        totalSize_[id] = QString::number(totalSize_[id].toInt() + info.size());
        averageSize_[id] = QString::number(totalSize_[id].toInt() / amount_[id].toInt());
    }
    else {
        types_.emplaceBack(info.suffix());
        amount_.emplaceBack("1");
        totalSize_.emplaceBack(QString::number(info.size()));
        averageSize_.emplaceBack(QString::number(info.size()));
    }
}

void FileSystemAnalyzer::addDirectoryTuple(quint32 nSubdirectories) {
    types_.emplaceBack("Subdirectories");
    amount_.emplaceBack(QString::number(nSubdirectories));
    totalSize_.emplaceBack("-");
    averageSize_.emplaceBack("-");
}

void FileSystemAnalyzer::startAnalysis(QDir path) {
    auto dir = QDir(path);
    quint32 nSubdirectories = 0;
    recursiveDataSearch(dir, nSubdirectories);
    addDirectoryTuple(nSubdirectories);

    emit analysisFinished();
}
