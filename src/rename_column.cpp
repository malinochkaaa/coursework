#include "rename_column.h"
#include "ui_rename_column.h"

Rename_column::Rename_column(QWidget *parent, Database* database_) :
    QDialog(parent),
    ui(new Ui::Rename_column),
    database(database_)
{
    ui->setupUi(this);
}

Rename_column::~Rename_column()
{
    emit isClosed(true);
    delete ui;
}

void Rename_column::on_pushButton_rename_clicked()
{
    QString col_name = ui->lineEdit->text();
    QSqlQuery query(*database->getDatabase());
    bool res = query.prepare("ALTER TABLE " + table_name + " RENAME COLUMN " +
                        old_name + " TO " + col_name + ";");
    if(res){
        for(const auto& x : col_name){
            if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
                res = false;
            }
        }
    }
    if(!res){
        QMessageBox::warning(this, "ERROR!", "Data is incorrect.");
        return;
    }
    new_name = col_name;
    emit nameIsEntered(table_name, old_name, new_name);
    emit isClosed(true);
    emit changeChosenColumn(new_name);
    this->close();
}
