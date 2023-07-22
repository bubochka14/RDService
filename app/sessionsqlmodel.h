#pragma once
#include <QAbstractListModel>
#include "rdserver.h"
#include <QObject>
#include <qvector.h>
#include <QSqlError>
#include "interfaces.h"
#include <QSortFilterProxyModel>
#include <qsqlquery.h>
#include <QSqlRelationalTableModel>
#include <QLoggingCategory>
Q_DECLARE_LOGGING_CATEGORY(LC_SessionSqlModel);

#define DB_SESSIONS_TABLE   QStringLiteral("Sessions")
#define DB_SESSION_HOSTNAME QStringLiteral("Hostname")
#define DB_SESSION_USERNAME QStringLiteral("Username")
#define DB_SESSION_STATE    QStringLiteral("State")
#define DB_SESSION_STATION  QStringLiteral("Station")
#define DB_SESSION_ID       QStringLiteral("ID")
class SessionRowFinder : protected QSortFilterProxyModel
{
	Q_OBJECT;
	int _idCol;
	int _hostCol;

	int _id;
	QString _host;
public:
	explicit SessionRowFinder(QAbstractTableModel* source, QObject* parent = nullptr);
	virtual int find(const QString& hostname, ulong id);
	void setSessionIDColumn(int);
	void setSessionHostnameColumn(int);
protected:
	bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
};
class SessionSqlModel : public QSqlRelationalTableModel
{
	Q_OBJECT;
	//static bool _isConnected;
	SessionRowFinder _rowFinder;
	QString _connectionName;
	///	Q_PROPERTY(int count READ rowCount NOTIFY rowChanged);
protected:
	virtual bool initTables();
	//static bool createConnection(const QString& SQLDriver = "QSQLITE");
public:
	explicit SessionSqlModel(const QSqlDatabase& db, QObject* parent = nullptr);
	int findRow(const Session&);
	int findRow(const QString& hostname, int id);
	bool setSessionsOnServer(const QString& hostname, SessionList list);

};