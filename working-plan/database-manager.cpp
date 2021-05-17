/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#include "database-manager.h"

#include <QApplication>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    createDatabaseConnection("");

    createStructure();
}

DatabaseManager* DatabaseManager::instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new DatabaseManager;
    }

    return m_instance;
}

bool DatabaseManager::createDatabaseConnection(QString filename)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbfileName = QApplication::applicationDirPath() + "/database.sqlite";

    if(!filename.isEmpty())
        dbfileName = filename;

    db.setDatabaseName(dbfileName);

    if(!db.open())
    {
        QMessageBox::critical(0, tr("No se pudo abrir la Base de Datos"),
                              tr("No se pudo conectar con la Base de Datos.\n"
                                 "Esta aplicación requiere de SQLite.\n\n"
                                 "Clic en Cancelar para salir."), QMessageBox::Cancel);

        qDebug("No se pudo abrir la Base de Datos");
        return false;
    }

    QSqlQuery query;

    //******************************Tuning the database properties**********************************
    query.exec("PRAGMA locking_mode = NORMAL");                 //NORMAL: Releases the database after each operation

    query.exec("PRAGMA page_size = 4096;");                     //The default is 1024
    query.exec("PRAGMA cache_size = 16384;");                    //The default is 2000

    query.exec("PRAGMA synchronous = NORMAL");

    if(query.exec("VACUUM"))                                    //Mandatory after changing cache_size or page_size
        qDebug("vacuum works");

    //printDatabasePragma("synchronous");
    //printDatabasePragma("journal_mode");

    //ONLY FOR EXTREME PERFORMANCE
    //query.exec("PRAGMA synchronous = OFF");
    //query.exec("PRAGMA journal_mode = MEMORY");

    return true;
}

void DatabaseManager::createStructure()
{
    QSqlQuery query;

    query.exec("CREATE TABLE task (id int primary key, name varchar(30), startDate int, endDate int,"
               "startTime varchar(10), endTime varchar(10), periodicity int, status int,"
               "color varchar(10), principal boolean, remove varchar(1))");
    logError(query);

    query.exec("CREATE TABLE personal (id int primary key, name varchar(30), startDate int, endDate int,"
               "startTime varchar(10), endTime varchar(10), periodicity int, status int,"
               "color varchar(10), principal boolean, remove varchar(1))");
    logError(query);

    query.exec("INSERT INTO task VALUES (1, 'Prueba', 20170214,"
               "1400, 1700, 14, 1, 'blue', 'TRUE', '1')");
    logError(query);

    query.exec("CREATE TABLE core_settings (id int primary key, name varchar(30), value varchar(30))");

    query.exec("CREATE TABLE holliday (id int primary key, dateStamp varchar(30), remove varchar(1))");

    query.exec("INSERT INTO holliday VALUES (1, 20170101, NULL)");
    query.exec("INSERT INTO holliday VALUES (2, 20170726, NULL)");
    query.exec("INSERT INTO holliday VALUES (3, 20171010, NULL)");
    logError(query);
}

void DatabaseManager::logError(const QSqlQuery &query) const
{
    if(!query.lastError().text().isEmpty())
        qDebug(qPrintable(query.lastError().text()));
}
