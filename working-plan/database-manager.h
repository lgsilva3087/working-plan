/**
  @author MSc. Luis Guillermo Silva Rojas
  @date   15/11/17
*/

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager* instance();

public:
    explicit DatabaseManager(QObject *parent = nullptr);

private:
    static DatabaseManager* m_instance;

    bool createDatabaseConnection(QString filename);
    void createStructure();
    void logError(const QSqlQuery &query) const;
};

#endif // DATABASEMANAGER_H
