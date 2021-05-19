#include "oper_window.h"
#include "ui_oper_window.h"

Oper_window::Oper_window(QWidget *parent, Database* database_) :
    QMainWindow(parent),
    ui(new Ui::Oper_window),
    database(database_),
    selected_table(""),
    field_should_change(false)
{
    ui->setupUi(this);
    ui->pushButton_TablesList->setModel(database->getTables());
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Oper_window::~Oper_window()
{
    delete ui;
}

void Oper_window::on_actionRelogin_triggered()
{
    this->close();
    emit mainWindow();
}

void Oper_window::on_actionExit_triggered()
{
    QApplication::quit();
}

void Oper_window::actionUpdate()
{
    field_should_change = false;
    ui->pushButton_FieldTable->clear();
    selected_table = ui->pushButton_TablesList->currentText();
    //qDebug() << selected_table;
    current_model = database->printTable(selected_table);
    ui->tableView->setModel(current_model);
}

void Oper_window::on_pushButton_ChooseTable_clicked(){
    this->actionUpdate();
}

void Oper_window::on_pushButton_Delete_clicked()
{
    if(selected_table.isEmpty()){
        QMessageBox::warning(this, "ATTENTION!", "Choose the table.");
        return;
    }
    int col = ui->tableView->currentIndex().column();
    QModelIndex ind = ui->tableView->currentIndex();
    if (col != 0){
        QMessageBox::warning(this, "ATTENTION!", "Choose one with an ID");
        return;
    }
    database->deleteLineFrom(selected_table, current_model->data(ind, Qt::DisplayRole).toInt());
    this->actionUpdate();
}

void Oper_window::on_pushButton_Add_clicked()
{
    if(selected_table.isEmpty()){
        QMessageBox::warning(this, "ATTENTION!", "Choose the table.");
        return;
    }
    database->insertLineInto(selected_table);
    this->actionUpdate();
}

void Oper_window::on_pushButton_ChangeTable_clicked()
{
    if(!field_should_change){
        QMessageBox::warning(this, "ATTENTION!", "Choose the table cell.");
        return;
    }
    int row = index_of_field.row();
    int col = index_of_field.column();
    int ID = database->getID(selected_table, row);
    database->updateField(selected_table, col, ID, ui->pushButton_FieldTable->text());
    this->actionUpdate();
}

void Oper_window::on_list_tableNames_clicked(const QModelIndex &index)
{
    index_of_field = index;
    field_should_change = true;
    ui->pushButton_FieldTable->setText(current_model->data(index, Qt::DisplayRole).toString());
}
