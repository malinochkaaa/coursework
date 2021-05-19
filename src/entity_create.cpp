#include "entity_create.h"
#include "ui_entity_create.h"
#include <QMessageBox>
#include <QDebug>

Entity_create::Entity_create(QWidget *parent, Database* database_) :
    QDialog(parent),
    ui(new Ui::Entity_create),
    database(database_)
{
    this->setEnabled(true);
    ui->setupUi(this);
}

Entity_create::~Entity_create()
{
    emit isClosed(false);
    delete ui;
}

void Entity_create::on_pushButton_create_clicked()
{
    QString table_name = ui->lineEdit->text();
    //qDebug() << table_name;
    QSqlQuery query(*database->getDatabase());
    bool res = query.prepare("CREATE TABLE " + table_name + "('ID' integer PRIMARY KEY AUTOINCREMENT NOT NULL);");
    for(const auto& x : table_name){
        if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
            res = false;
        }
    }
    if(!res){
        QMessageBox::warning(this, "ERROR!", "Data is incorrect.");
        return;
    }
    name = table_name;
    emit nameIsEntered(table_name);
    emit isClosed(false);
    this->close();
}
