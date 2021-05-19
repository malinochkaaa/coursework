#pragma once
#ifndef ENTITY_CREATE_H
#define ENTITY_CREATE_H

#include "database.h"
#include <QDialog>

namespace Ui {
class Entity_create;
}

///@brief Окно создания таблицы.
class Entity_create : public QDialog
{
    Q_OBJECT

public:

    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit Entity_create(QWidget *parent = nullptr, Database* database_ = nullptr);
    ~Entity_create();

     ///@brief Получить название таблиц
    QString getName() const { return name; }

signals:

    /**
     * @brief Сигнал ввода названия таблицы.
     * @param new_name Название таблицы.
     */
    void nameIsEntered(QString new_name);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);

private slots:

    ///@brief Нажатие на кнопку создания.
    void on_pushButton_create_clicked();

private:
    Ui::Entity_create *ui;
    Database* database;
    QString name;
};

#endif // ENTITY_CREATE_H
