#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filesystemanalyzer.h"
#include "qabstractitemmodel.h"

#include <QMainWindow>

class QFileSystemModel;

class FileSystemAnalyzer;
class TableStatisticsModel;


QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalToAnalyzer(QDir dir);

private slots:
    void onFileSystemListViewDoubleClicked(const QModelIndex &index);
    void showAnalysisResults();

    void onStatisticsButtonClicked();

private:
    Ui::MainWindow* ui_;
    QFileSystemModel* fileSystemModel_;
    TableStatisticsModel* tableStatisticsModel_;
    QThread* statisticsThread_;
    FileSystemAnalyzer* fileSystemAnalyzer_;
    QModelIndex index_;
};

#endif // MAINWINDOW_H
