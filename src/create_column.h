#pragma once
#ifndef CREATE_COLUMN_H
#define CREATE_COLUMN_H

#include "database.h"
#include <QDialog>

namespace Ui {
class Create_column;
}

///@brief Окно создания колонки
class Create_column : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit Create_column(QWidget *parent = nullptr, Database* database_=nullptr);
    ~Create_column();

    ///@brief Получить название колонки.
    QString getName() const { return name; }

    ///@brief Получить тип данных колонки.
    QString getType() const { return type; }

    ///@brief Установить название таблицы.
    void setTableName(QString value) { table_name = value; }

signals:
    /**
     * @brief Сигнал ввода названия и типа данных колонки.
     * @param table_name_ Имя таблицы.
     * @param new_name Имя колонки.
     * @param new_type Тип данных таблицы.
     */
    void nameIsEntered(QString table_name_, QString new_name, QString new_type);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);

private slots:

    ///@brief Нажатие на кнопку создания
    void on_pushButton_create_clicked();

private:
    Ui::Create_column *ui;
    Database* database;
    Create_column* create;
    QString table_name;
    QString name;
    QString type;

};

#endif // CREATE_COLUMN_H
