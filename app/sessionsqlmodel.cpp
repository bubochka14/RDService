#include "SessionSqlModel.h"
Q_LOGGING_CATEGORY(LC_SessionSqlModel, "Session database");

SessionRowFinder::SessionRowFinder(QAbstractTableModel* source, QObject* parent)
	:QSortFilterProxyModel(parent)
	, _idCol(0)
	, _hostCol(1)
{
	setSourceModel(source);
}

int SessionRowFinder::find(const QString& hostname, ulong id)
{
	_host = hostname;
	_id = id;
	invalidateFilter();
	if (rowCount() > 0)
		return mapToSource(index(0, 0)).row();
	return -1;

}
void SessionRowFinder::setSessionIDColumn(int col)
{
	_idCol = col;
}
void SessionRowFinder::setSessionHostnameColumn(int col)
{
	_hostCol = col;
}
bool SessionRowFinder::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
	QModelIndex idIndex = sourceModel()->index(sourceRow, _idCol, sourceParent);
	QModelIndex hostIndex = sourceModel()->index(sourceRow, _hostCol, sourceParent);

	int id = sourceModel()->data(idIndex).toInt();
	QString host = sourceModel()->data(hostIndex).toString();

	return (id == _id && host == _host);
}
//bool SessionSqlModel::createConnection(const QString& SQLDriver)
//{
//	QSqlDatabase db = QSqlDatabase::addDatabase(SQLDriver);
//	db.setDatabaseName("SESSIONS_DB");
//	if (!db.open())
//	{
//		qCCritical(SessionDbDebug) << "Cannot open database with error: " << db.lastError();
//		return false;
//	}
//	_isConnected = true;
//	QStringList tables = db.tables();
//	if (!tables.contains("Sessions"))
//	{
//		QString str = QString(
//			"CREATE TABLE %1 ("
//			"%2 int, "
//			"%3 varchar(255),"
//			"%4 varchar(255),"
//			"%5 varchar(255),"
//			"%6 varchar(255)); "
//			"primary key(%2, %3)"
//			).arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID)
//			.arg(DB_SESSION_HOSTNAME).arg(DB_SESSION_STATE)
//			.arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION);
//
//		QSqlQuery query;
//		if (!query.exec(str))
//		{
//			qCCritical(SessionDbDebug) << tr("Unable to create a sessions table ");
//		}
//		
//	}
	//if (!tables.contains("Servers"))
	//{
	//	QString str = QStringLiteral(
	//		"CREATE TABLE Servers("
	//		"State     varchar(255),"
	//	);
	//	QSqlQuery query;
	//	if (!query.exec(str))
	//	{
	//		qCCritical(SessionDbDebug) << "Unable to create a servers table";
	//	}
	//}
//	return true;

//}
SessionSqlModel::SessionSqlModel(const QSqlDatabase& db, QObject* parent)
	:QSqlRelationalTableModel(parent,db)
	,_rowFinder(this)
{
	//createConnection();
	Q_ASSERT_X(db.isOpen(), "SessionSqlModel constructor", "recived unopened qsqldatabase");
	_connectionName = db.connectionName();
	initTables();
	setTable(DB_SESSIONS_TABLE);
	select();
	_rowFinder.setSessionHostnameColumn(fieldIndex(DB_SESSION_HOSTNAME));
	_rowFinder.setSessionIDColumn(fieldIndex(DB_SESSION_ID));

}
bool SessionSqlModel::initTables()
{
	QSqlDatabase db = QSqlDatabase::database(_connectionName);
	if (db.tables().contains(DB_SESSIONS_TABLE))
		return true;
	QSqlQuery query(db);
	if (!query.exec(QString(
		"CREATE TABLE %1 ("
		"%2 int, "
		"%3 int,"
		"%4 varchar(255),"
		"%5 varchar(255),",Qt::Thursday
		"%6 varchar(255) "
		");"
		).arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID)
		.arg(DB_SESSION_HOSTNAME).arg(DB_SESSION_STATE)
		.arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION)))
	{
		qCCritical(LC_SessionSqlModel) << tr("Unable to create sessions table") << query.lastError();
		return false;
	}
	return true;

}
int SessionSqlModel::findRow(const Session& sess)
{
	return _rowFinder.find(sess.hostname, sess.id);
}
int SessionSqlModel::findRow(const QString& hostname, int id)
{
	return _rowFinder.find(hostname, id);
}
bool SessionSqlModel::setSessionsOnServer(const QString& hostname, SessionList list)
{
	QSqlQuery query(QSqlDatabase::database(_connectionName));
	if (!query.exec(QString(
		"DELETE FROM %1 WHERE %2='%3';"
	).arg(DB_SESSIONS_TABLE).arg(DB_SESSION_HOSTNAME).arg(hostname))) 
	{
		qCCritical(LC_SessionSqlModel) << tr("Unable to clear sessions in ", "server") << hostname << tr("whith error: ") << query.lastError();
		return false;
	}
	for (auto& it : list)
	{
		query.prepare(QString(
			"INSERT INTO %1 (%2,%3,%4,%5,%6)"
			"VALUES(?,?,?,?,?)")
			.arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID).arg(DB_SESSION_HOSTNAME)
			.arg(DB_SESSION_STATE).arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION));
		query.addBindValue(QVariant::fromValue(it.id));
		query.addBindValue(it.hostname);
		query.addBindValue(it.state);
		query.addBindValue(it.user);
		query.addBindValue(it.station);
		if(!query.exec())
		{
			qCCritical(LC_SessionSqlModel) << tr("Unable to set %1 session in %2 server with error:").arg(it.id).arg(it.hostname)<< query.lastError();
			return false;

		}
		qCDebug(LC_SessionSqlModel) << tr("%1 session was set to %2 server").arg(it.id).arg(it.hostname);
	}
	select();
	return true;
}
