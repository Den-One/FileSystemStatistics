#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tablestatisticsmodel.h"

#include <QFileSystemModel>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui_(new Ui::MainWindow)
    , fileSystemModel_(new QFileSystemModel(this))
    , tableStatisticsModel_(new TableStatisticsModel())
    , statisticsThread_(new QThread(this))
    , fileSystemAnalyzer_(new FileSystemAnalyzer())
{
    ui_->setupUi(this);
    setWindowTitle("File System Statistics");

    fileSystemModel_->setFilter(QDir::QDir::AllEntries);
    fileSystemModel_->setRootPath("");
    ui_->fileSystemListView->setModel(fileSystemModel_);

    fileSystemAnalyzer_->moveToThread(statisticsThread_);
    statisticsThread_->start();

    connect(fileSystemAnalyzer_, &FileSystemAnalyzer::analysisFinished,
            this, &MainWindow::showAnalysisResults);

    connect(ui_->fileSystemListView, &QListView::doubleClicked,
            this, &MainWindow::onFileSystemListViewDoubleClicked);

    connect(statisticsThread_, &QThread::finished,
            fileSystemAnalyzer_, &FileSystemAnalyzer::deleteLater);

    connect(this, &MainWindow::signalToAnalyzer,
            fileSystemAnalyzer_, &FileSystemAnalyzer::startAnalysis);

    connect(ui_->statisticsButton, &QPushButton::clicked,
            this, &MainWindow::onStatisticsButtonClicked);

}

MainWindow::~MainWindow() {
    delete ui_;
    delete fileSystemModel_;
    delete tableStatisticsModel_;
    delete fileSystemAnalyzer_;
    delete statisticsThread_;
}

void MainWindow::onFileSystemListViewDoubleClicked(const QModelIndex &index) {
    index_ = index;
    auto* listView = qobject_cast<QListView*>(sender());
    auto fileInfo = fileSystemModel_->fileInfo(index);

    if (fileInfo.fileName() == ".."){
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(fileSystemModel_->index(dir.absolutePath()));
    }
    else if (fileInfo.fileName() == "."){
        listView->setRootIndex(fileSystemModel_->index(""));
    }
    else if (fileInfo.isDir()){
        listView->setRootIndex(index);
    }
}

void MainWindow::showAnalysisResults() {
    tableStatisticsModel_->populate(*fileSystemAnalyzer_);
    ui_->tableView->setModel(tableStatisticsModel_);
    ui_->tableView->horizontalHeader()->setStretchLastSection(true);
    ui_->tableView->horizontalHeader()->setVisible(true);
    ui_->tableView->show();

    ui_->statisticsButton->setEnabled(true);
}


void MainWindow::onStatisticsButtonClicked() {
    fileSystemAnalyzer_->clear();
    tableStatisticsModel_->clear();
    ui_->tableView->setVisible(false);

    ui_->statisticsButton->setEnabled(false);
    auto fileInfo = fileSystemModel_->fileInfo(index_);
    qDebug() << fileInfo.absoluteFilePath();

    emit signalToAnalyzer(fileInfo.absoluteFilePath());
}

