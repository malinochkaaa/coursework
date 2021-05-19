#pragma once
#ifndef FK_CREATE_H
#define FK_CREATE_H

#include "database.h"
#include <QDialog>

namespace Ui {
class FK_create;
}

///@brief Окно создания внешнего ключа.
class FK_create : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор.
     * @param parent Указатель на экземпляр родительского класса.
     * @param db_manager_ Указатель на класс обработки БД.
     */
    explicit FK_create(QWidget *parent = nullptr, Database* database_=nullptr);
    ~FK_create();

    ///@brief Установить название таблицы, где создается внешний ключ.
    void setFKTable(QString value) { FK_table = value; }

signals:

    /**
     * @brief Сигнал выбора таблицы.
     * @param FK_table_name Название таблицы, где будет создаваться внешний ключ.
     * @param PK_table_name Название таблицы, куда внешний ключ будет относиться.
     */
    void tableWasChosen(QString FK_table_name, QString PK_table_name);

    /**
     * @brief Сигнал закрытия окна.
     * @param should_show_columns true, если нужно показывать колонки в списке.
     */
    void isClosed(bool should_show_columns);

private slots:

   ///@brief Нажатие на таблицу в списке.
   void on_listView_clicked(const QModelIndex &index);

   ///@brief Нажатие на кнопку выбора.
   void on_pushButton_choose_clicked();

private:
    Ui::FK_create *ui;
    Database* database;
    QString FK_table;
    QString chosenTable;
};

#endif // FK_CREATE_H
