#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");
    ui->lvBackup->setModel(model);
    ui->lvSource->setModel(model);
    ui->lvBackup->setSelectionMode(QAbstractItemView::ExtendedSelection);

    model_b = new DataModel(this);
    model_s = new DataModel(this);
    ui->tvInfoB->setModel(model_b);
    ui->tvInfoS->setModel(model_s);
    connect(ui->lvSource, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(on_lvBackup_doubleClicked(QModelIndex)));

    reserve = new QFileInfoList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lvBackup_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..") {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    } else if (fileInfo.fileName() == ".") {
        listView->setRootIndex(model->index(""));
    } else if (fileInfo.isDir()) {
        listView->setRootIndex(index);
    }
}

void MainWindow::on_btnCopy_clicked()
{
    QDir bdir = QDir(model->filePath(ui->lvBackup->rootIndex()));
    QDir sdir = QDir(model->filePath(ui->lvSource->rootIndex()));
    if (bdir.absolutePath() == sdir.absolutePath()) {
        QMessageBox::warning(this, "Внимание","Были выбранные одинаковые папки для копирования/перемещения.");
        return;
    }
    foreach(const QModelIndex &index, ui->lvBackup->selectionModel()->selectedIndexes()) {
        bool alrdyFlag = false;
        QFileInfo file = model->fileInfo(index);
        foreach (QFileInfo info, sdir.entryInfoList(QDir::Files)) {
            if (file.baseName() == info.baseName() && file.completeSuffix() == info.completeSuffix()) {
                 QMessageBox::warning(this, "Внимание","Файл " + file.baseName() + "." + file.completeSuffix() + " уже есть в " + sdir.absolutePath() + " он был пропущен.");
                 reserve->push_back(file);
                 alrdyFlag = true;
                 break;
            }
        }
        if (alrdyFlag) continue;
        QFile::copy(file.absoluteFilePath(), sdir.absolutePath()+'/'+file.fileName());
    }
}

void MainWindow::on_lvBackup_clicked(const QModelIndex &index)
{
    if (ui->lvBackup->selectionModel()->selectedIndexes().length() == 1) {
        QFileInfo fileInfo = model->fileInfo(ui->lvBackup->selectionModel()->selectedIndexes()[0]);
        if (fileInfo.isFile()) model_b->updateFile(fileInfo);
        else model_b->clear();
    } else model_b->clear();
}

void MainWindow::on_lvSource_clicked(const QModelIndex &index)
{
    if (ui->lvSource->selectionModel()->selectedIndexes().length() == 1) {
        QFileInfo fileInfo = model->fileInfo(ui->lvSource->selectionModel()->selectedIndexes()[0]);
        if (fileInfo.isFile()) model_s->updateFile(fileInfo);
        else model_s->clear();
    } else model_s->clear();
}

void MainWindow::on_btnDelete_clicked()
{
    foreach(const QModelIndex &index, ui->lvBackup->selectionModel()->selectedIndexes()) {
        if (!reserve->contains(model->fileInfo(index))) QFile::remove(model->fileInfo(index).absoluteFilePath());
    }
    reserve->clear();
}

void MainWindow::on_btnMove_clicked()
{
    QDir bdir = QDir(model->filePath(ui->lvBackup->rootIndex()));
    QDir sdir = QDir(model->filePath(ui->lvSource->rootIndex()));
    if (bdir.absolutePath() == sdir.absolutePath()) {
        QMessageBox::warning(this, "Внимание","Были выбранные одинаковые папки для копирования/перемещения");
        return;
    }
    on_btnCopy_clicked();
    on_btnDelete_clicked();
}
