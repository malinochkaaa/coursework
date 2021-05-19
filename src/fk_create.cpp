#include "fk_create.h"
#include "ui_fk_create.h"

FK_create::FK_create(QWidget *parent, Database* database_) :
    QDialog(parent),
    ui(new Ui::FK_create),
    database(database_),
    chosenTable("")
{
    ui->setupUi(this);
    ui->listView->setModel(database->getTables());
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

FK_create::~FK_create()
{
    delete ui;
}

void FK_create::on_listView_clicked(const QModelIndex &index)
{
    chosenTable = ui->listView->model()->data(index).toString();
}

void FK_create::on_pushButton_choose_clicked()
{
    if(chosenTable == "")
        return;
    emit tableWasChosen(FK_table, chosenTable);
    emit isClosed(true);
    this->close();
}
