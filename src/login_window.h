#pragma once
#ifndef LOGIN_WINDOW_H
#define LOGIN_WINDOW_H

#include "admin_window.h"
#include "oper_window.h"
#include "database.h"

#include <QFileDialog>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Login_window; }
QT_END_NAMESPACE

///@brief Окно авторизации.
class Login_window : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit Login_window(QWidget *parent = nullptr, Database* database_ = nullptr);
    ~Login_window();

private slots:

    ///@brief Нажатие на кнопку выбора пути.
    void on_btnPath_clicked();

    ///@brief Нажатие на кнопку открытия БД.
    void on_pushButton_open_clicked();

    ///@brief Нажатие на кнопку создания новой БД.
    void on_pushButton_create_clicked();

    ///@brief Спрятать поля авторизации.
    void hide_login();

    ///@brief Показать поля авторизации.
    void show_login();

    ///@brief Нажатие на кнопку выбора роли администратора.
    void on_radioButton_Admin_clicked();

     ///@brief Нажатие на кнопку выбора роли оператора.
    void on_radioButton_Operator_clicked();

     ///@brief Нажатие на кнопку входа.
    void on_pushButton_login_clicked();

private:
    Ui::Login_window *ui;
    Admin_window *adm_win;
    Oper_window *oper_win;
    Database* database;
    bool path_was_chosen;
    bool admin_chosen;
};

#endif // Login_window_H
