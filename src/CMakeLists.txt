set(TS_FILES Sqlite3QT_ru_RU.ts)

set(PROJECT_SOURCES
        admin_window.h
        admin_window.cpp
        admin_window.ui
        create_column.h
        create_column.cpp
        create_column.ui
        database.h
        database.cpp
        entity_create.ui
        entity_create.cpp
        entity_create.h
        fk_create.h
        fk_create.cpp
        fk_create.ui
        oper_window.h
        oper_window.cpp
        oper_window.ui
        rename_column.h
        rename_column.cpp
        rename_column.ui
        main.cpp
        login_window.cpp
        login_window.h
        login_window.ui
        ${TS_FILES}
)

add_executable(Sqlite3QT ${PROJECT_SOURCES})

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(Sqlite3QT PRIVATE
    Qt5::Widgets
    Qt5::Sql)
