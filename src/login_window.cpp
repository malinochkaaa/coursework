#include "login_window.h"
#include "ui_login_window.h"

Login_window::Login_window(QWidget *parent, Database* database_) :
    QWidget(parent),
    ui(new Ui::Login_window),
    database(database_),
    path_was_chosen(false),
    admin_chosen(true)
{
    ui->setupUi(this);
    ui->pathBD->setReadOnly(true);
    ui->radioButton_Admin->click();
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    //this->hide_login();
   // ui->verticalLayout_Role->hide();
}

Login_window::~Login_window()
{
    delete ui;
}



void Login_window::on_btnPath_clicked()
{
    QString file_path = QFileDialog::getOpenFileName(this, "Choose a database.", "", "Databases (*.db)");
    ui->pathBD->setText(file_path);
    path_was_chosen = true;
}

void Login_window::on_pushButton_open_clicked()
{
    if(!path_was_chosen){
        QMessageBox::warning(this, "WARNING!", "Path is not chosen.");
        return;
    }
    if(!database->connectToDataBase(ui->pathBD->text())){
        QMessageBox::warning(this, "ERROR!", "Database is not available.");
        return;
    }
    this->show_login();
    ui->pathBD->clear();
    path_was_chosen = false;

}

void Login_window::on_pushButton_create_clicked()
{
    QString file_path = QFileDialog::getSaveFileName(this, "Choose a database.", "", "Databases (*.db)");
    ui->pathBD->setText(file_path);
    if(!file_path.isEmpty())
        path_was_chosen = true;
}

void Login_window::hide_login()
{
    ui->lineEdit_username->hide();
    ui->lineEdit_password->hide();
    ui->radioButton_Admin->hide();
    ui->radioButton_Operator->hide();
    ui->pushButton_login->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
      //ui->SignIn->hide();
}

void Login_window::show_login()
{
    ui->lineEdit_username->show();
    ui->lineEdit_password->show();
    ui->radioButton_Admin->show();
    ui->radioButton_Operator->show();
    ui->pushButton_login->show();
    ui->label->show();
    ui->label_2->show();
    ui->label_3->show();
    ui->label_4->show();
}



void Login_window::on_radioButton_Admin_clicked()
{
    admin_chosen = true;
}

void Login_window::on_radioButton_Operator_clicked()
{
    admin_chosen = false;
}

void Login_window::on_pushButton_login_clicked()
{
    QString login = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
   // QString role;
    QString res = database->checkPassword(admin_chosen, login, password);
    if(!res.isEmpty()){
        QMessageBox::warning(this, "ERROR!", res);
        return;
    }

    if(admin_chosen){
        this->close();
        adm_win = new Admin_window(this, database);
        adm_win->setAttribute(Qt::WA_DeleteOnClose);
        connect(adm_win, &Admin_window::mainWindow, this, &Login_window::show);
        connect(adm_win, &Admin_window::mainWindow, this, &Login_window::hide_login);
        adm_win->show();
    }else{
        this->close();
        oper_win = new Oper_window(this, database);
        oper_win->setAttribute(Qt::WA_DeleteOnClose);
        connect(oper_win, &Oper_window::mainWindow, this, &Login_window::show);
        connect(oper_win, &Oper_window::mainWindow, this, &Login_window::hide_login);
        oper_win->show();
    }
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
}
