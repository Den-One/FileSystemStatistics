#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*
 * Статистика для каждой группы файлов:
 * 1. количество файлов;
 * 2. общий размер файлов;
 * 3. средний размер файла;
 *
 * Отдельно:
 * 1. Количество подкаталогов (для выбранной папки)
 *
 * Статусы чего отобразить:
 * 1. Построение дерева каталогов;
 * 2. Подсчет статистики;
 *
 * Статусы операций:
 * 1. не начата;
 * 2. В процессе;
 * 3. Завершена;
*/
