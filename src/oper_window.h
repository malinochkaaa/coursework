#pragma once
#ifndef OPER_WINDOW_H
#define OPER_WINDOW_H

#include "database.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Oper_window; }
QT_END_NAMESPACE

///@brief Окно оперирования БД.
class Oper_window : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    Oper_window(QWidget *parent = nullptr, Database* database_ = nullptr);
    ~Oper_window();

signals:

    ///@brief Сигнал возврата к окну авторизации.
    void mainWindow();

private slots:

    ///@brief Возврат к окну авторизации.
    void on_actionRelogin_triggered();

    ///@brief Выход из программы.
    void on_actionExit_triggered();

    ///@brief Обновление страницы окна.
    void actionUpdate();

    ///@brief Нажатие на кнопку выбора таблицы.
    void on_pushButton_ChooseTable_clicked();

    ///@brief Нажатие на кнопку добавления строки.
    void on_pushButton_Add_clicked();

    ///@brief Нажатие на кнопку удаления строки.
    void on_pushButton_Delete_clicked();

    ///@brief Нажатие на кнопку изменения значения в ячейке.
    void on_pushButton_ChangeTable_clicked();

    ///@brief Выбор таблицы.
    void on_list_tableNames_clicked(const QModelIndex &index);

private:
    Ui::Oper_window *ui;
    Database* database;
    QString selected_table;
    QSqlRelationalTableModel* current_model;
    bool field_should_change;
    QModelIndex index_of_field;
};
#endif // OPER_WINDOW_H
