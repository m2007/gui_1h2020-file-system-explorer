#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDir>

#include "datamodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lvBackup_doubleClicked(const QModelIndex &index);

    void on_btnCopy_clicked();

    void on_lvBackup_clicked(const QModelIndex &index);

    void on_lvSource_clicked(const QModelIndex &index);

    void on_btnDelete_clicked();

    void on_btnMove_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;

    DataModel   *model_b;
    DataModel   *model_s;

    QFileInfoList *reserve;
};

#endif // MAINWINDOW_H
