#include "admin_window.h"
#include "ui_admin_window.h"
#include <QDebug>

Admin_window::Admin_window(QWidget *parent, Database* database_) :
    QMainWindow(parent),
    ui(new Ui::Admin_window),
    database(database_),
    empty_model(new QStringListModel())
{
    chosenTable_double_clicked = "";
    ui->setupUi(this);

    ui->list_tableNames->setModel(database->getTables());
    ui->list_tableNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list_columnNames->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Admin_window::~Admin_window()
{
    delete ui;
    ui=nullptr;
}

void Admin_window::on_actionRelogin_triggered()
{
    this->close();
    emit mainWindow();
}

void Admin_window::on_actionExit_triggered()
{
    QApplication::quit();
}

void Admin_window::on_actionUpdate_triggered()
{
    this->actionUpdate(false);
}

void Admin_window::actionUpdate(bool should_show_columns)
{
    if(ui == nullptr)
        return;
    ui->list_tableNames->setModel(database->getTables());
    if(!should_show_columns){
        ui->list_columnNames->setModel(empty_model);
    } else{
        ui->list_columnNames->setModel(database->getColumns(chosenTable_double_clicked));
    }
}

void Admin_window::on_list_tableNames_doubleClicked(const QModelIndex &index)
{
    chosenTable_double_clicked = ui->list_tableNames->model()->data(index).toString();
    ui->list_columnNames->setModel(database->getColumns(chosenTable_double_clicked));
}

void Admin_window::on_list_tableNames_clicked(const QModelIndex &index)
{
    chosenTable = ui->list_tableNames->model()->data(index).toString();
}

void Admin_window::on_list_columnNames_clicked(const QModelIndex &index)
{
    QString chosenColumn_ = ui->list_columnNames->model()->data(index).toString();
    QTextStream ss(&chosenColumn_);
    ss >> chosenColumn;
}

void Admin_window::on_pushButton_AddTable_clicked()
{
    table_creator = new Entity_create(this, database);
    table_creator->setAttribute(Qt::WA_DeleteOnClose);
    connect(table_creator, &Entity_create::nameIsEntered, database, &Database::addTable);
    connect(table_creator, &Entity_create::isClosed, this, &Admin_window::actionUpdate);
    table_creator->exec();
}

void Admin_window::on_pushButton_DeleteTable_clicked()
{
    if(chosenTable == "sqlite_sequence" || chosenTable == "TestTable"){
        QMessageBox::warning(this, "ERROR!", "Table can not be deleted.");
        return;
    }
    database->deleteTable(chosenTable);
    chosenTable = "";
    this->actionUpdate(false);
}



void Admin_window::on_pushButton_AddCol_clicked()
{
    column_creator = new Create_column(this, database);
    column_creator->setAttribute(Qt::WA_DeleteOnClose);
    if(chosenTable_double_clicked == ""){
        return;
    }
    column_creator->setTableName(chosenTable_double_clicked);
    connect(column_creator, &Create_column::nameIsEntered, database, &Database::addColumn);
    connect(column_creator, &Create_column::isClosed, this, &Admin_window::actionUpdate);
    column_creator->exec();
}


void Admin_window::on_pushButton_DeleteCol_clicked()
{
    //qDebug() << chosenColumn << " " << chosenTable_double_clicked;
    if(chosenColumn == "" || chosenTable_double_clicked == "sqlite_sequence"){
        return;
    }
    if(chosenColumn == "ID"){
        QMessageBox::warning(this, "ERROR!", "ID can not be deleted.");
        return;
    }
    database->deleteColumn(chosenTable_double_clicked, chosenColumn);
    chosenColumn = "";
    this->actionUpdate(true);
}

void Admin_window::changeChosenColumn(QString new_name)
{
    chosenColumn = new_name;
}

void Admin_window::on_pushButton_RenameCol_clicked()
{
    column_renamer = new Rename_column(this, database);
    column_renamer->setAttribute(Qt::WA_DeleteOnClose);
    if(chosenColumn == "" || chosenTable_double_clicked == "sqlite_sequence"){
        return;
    }
    if(chosenColumn == "ID"){
        QMessageBox::warning(this, "ERROR!", "ID can not be renamed!");
        return;
    }
    column_renamer->setTableName(chosenTable_double_clicked);
    column_renamer->setOldName(chosenColumn);
    connect(column_renamer, &Rename_column::nameIsEntered, database, &Database::renameColumn);
    connect(column_renamer, &Rename_column::changeChosenColumn, this, &Admin_window::changeChosenColumn);
    connect(column_renamer, &Rename_column::isClosed, this, &Admin_window::actionUpdate);
    column_renamer->exec();
}

void Admin_window::on_pushButton_makeFK_clicked()
{
    fk_create = new FK_create(this, database);
    fk_create->setAttribute(Qt::WA_DeleteOnClose);
    fk_create->setFKTable(chosenTable_double_clicked);
    connect(fk_create, &FK_create::tableWasChosen, database, &Database::makeForeignKey);
    connect(fk_create, &FK_create::isClosed, this, &Admin_window::actionUpdate);
    fk_create->exec();
}


