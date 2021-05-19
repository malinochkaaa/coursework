#pragma once
#ifndef ADMIN_WINDOW_H
#define ADMIN_WINDOW_H

#include <QMainWindow>

#include "create_column.h"
#include "database.h"
#include "fk_create.h"
#include "entity_create.h"
#include "rename_column.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Admin_window;}
QT_END_NAMESPACE

///@brief Окно администрирования БД.
class Admin_window : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit Admin_window(QWidget *parent = nullptr, Database* database_=nullptr);
    ~Admin_window();

signals:
     ///@brief Сигнал возврата к окну авторизации.
    void mainWindow();

private slots:
    ///@brief Возврат к окну авторизации.
    void on_actionRelogin_triggered();

    ///@brief Выход из программы.
    void on_actionExit_triggered();

     ///@brief Обновление страницы окна по нажатию кнопки
    void on_actionUpdate_triggered();

    ///@brief Обновление страницы окна.
    void actionUpdate(bool should_show_columns);

    ///@brief Одно нажатие по колонке в списке.
    void on_list_columnNames_clicked(const QModelIndex &index);

    ///@brief Одно нажатие по таблице в списке
    void on_list_tableNames_clicked(const QModelIndex &index);

    ///@brief Двойное нажатие по таблице в списке.
    void on_list_tableNames_doubleClicked(const QModelIndex &index);

    ///@brief Добавление новой таблицы.
    void on_pushButton_AddTable_clicked();

    ///@brief Удаление таблицы.
    void on_pushButton_DeleteTable_clicked();

    ///@brief Добавление новой колонки в таблице.
    void on_pushButton_AddCol_clicked();

    ///@brief Удаление колонки в таблице
    void on_pushButton_DeleteCol_clicked();

    ///@brief Изменить выбранную коллонку.
    void changeChosenColumn(QString new_name);

    ///@brief Переименование колонки.
    void on_pushButton_RenameCol_clicked();

    ///@brief Добавить внешний ключ.
    void on_pushButton_makeFK_clicked();

private:
    Ui::Admin_window *ui;
    Database *database;
    Entity_create* table_creator;
    Create_column* column_creator;
    Rename_column* column_renamer;
    FK_create* fk_create;
    QString chosenTable;
    QString chosenTable_double_clicked;
    QString chosenColumn;
    QStringListModel* empty_model;
};

#endif // ADMIN_WINDOW_H

