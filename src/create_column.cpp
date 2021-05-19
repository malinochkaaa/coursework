#include "create_column.h"
#include "ui_create_column.h"

Create_column::Create_column(QWidget *parent, Database* database_) :
    QDialog(parent),
    ui(new Ui::Create_column),
    database(database_),
    table_name("")
{
    ui->setupUi(this);
}

Create_column::~Create_column()
{
    emit isClosed(true);
    delete ui;
}

void Create_column::on_pushButton_create_clicked()
{
    QString line_text = ui->lineEdit->text();
    QString column_name, column_type;
    QTextStream ss(&line_text);
    ss >> column_name >> column_type;
    if(!ss.atEnd()){
        QMessageBox::warning(this, "ERROR!", "Data is incorrect, use less words.");
        return;
    }
    bool res = true;
    QSqlQuery query(*database->getDatabase());
    res = query.prepare("ALTER TABLE " + table_name + " ADD COLUMN " +
                        column_name + " " + column_type + ";");
    if(res){
        for(const auto& x : column_name){
            if(!((x >= '0' && x <= '9') || (x >='A' && x <= 'Z') || (x >= 'a' && x <= 'z') || x == '_')){
                res = false;
            }
        }
    }
    if(!res){
        QMessageBox::warning(this, "ERROR!", "Data is incorrect.");
        return;
    }
    name = column_name;
    type = column_type;
    emit nameIsEntered(table_name, name, type);
    emit isClosed(true);
    this->close();
}
