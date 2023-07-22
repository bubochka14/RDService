#include <QSqlDatabase>
#include <QObject>
#include <gtest/gtest.h>
#include "sessionsqlmodel.h"
#include <QCoreApplication>
#include <QSQlQuery>

#ifndef EMPTY_BD_CONNECTION
	#define EMPTY_BD_CONNECTION  QStringLiteral("EMPTY_SQLITE")
#endif 
#ifndef FILLED_BD_CONNECTION
	#define FILLED_BD_CONNECTION QStringLiteral("FILLED_SQLITE")
#endif 

class SessionSqlModelTest : public ::testing::Test
{
protected:

	QSqlDatabase emptyDB;;
	QSqlDatabase filledDB;
	explicit SessionSqlModelTest()
	{
		emptyDB = QSqlDatabase::addDatabase("QSQLITE", EMPTY_BD_CONNECTION);
		emptyDB.setHostName("TEST_DATABASE");
		emptyDB.setDatabaseName(":memory:");
		emptyDB.open();
		


		filledDB = QSqlDatabase::addDatabase("QSQLITE", FILLED_BD_CONNECTION);
		filledDB.setHostName("TEST_DATABASE");
		filledDB.setDatabaseName(":memory:");
		filledDB.open();
	}
	void SetUp() override
	{
		for (auto& table : emptyDB.tables())
		{
			QSqlQuery query(emptyDB);
			query.exec(QString("DROP TABLE %1").arg(table));
		}
		QSqlQuery query(filledDB);
		for (auto& table : filledDB.tables())
		{
			query.exec(QString("DROP TABLE %1").arg(table));
		}
		query.exec(QString(
			"CREATE TABLE %1 ("
			"%2 int, "
			"%3 int,"
			"%4 varchar(255),"
			"%5 varchar(255),"
			"%6 varchar(255) "
			");"
		).arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID)
			.arg(DB_SESSION_HOSTNAME).arg(DB_SESSION_STATE)
			.arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION));
		if (!query.exec(QString(
			"INSERT INTO %1 (%2,%3,%4,%5,%6)"
			"VALUES(1,'test_hostname','test_state','test_username','test_station')")
			.arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID).arg(DB_SESSION_HOSTNAME)
			.arg(DB_SESSION_STATE).arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION)))
			qDebug() << query.lastError();
		if (!query.exec(QString(
			"INSERT INTO %1 (%2,%3,%4,%5,%6)"
			"VALUES(2,'test_hostname','test_state','test_username','test_station')")
			.arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID).arg(DB_SESSION_HOSTNAME)
			.arg(DB_SESSION_STATE).arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION)))
			qDebug() << query.lastError();

	}
	void TearDown() override
	{

	}
	void init()
	{
	/*	QSqlDatabase empty = QSqlDatabase::database(EMPTY_TEST_BD);
		for (auto& table : empty.tables())
		{
			QSqlQuery query(empty);
			query.exec(QString("DROP TABLE %1").arg(table));
		}
		QSqlDatabase filled = QSqlDatabase::database(FILLED_TEST_BD);
		QSqlQuery query(filled);
		for (auto& table : filled.tables())
		{
			query.exec(QString("DROP TABLE %1").arg(table));
		}
		query.exec(QString("CREATE TABLE %1 ("
			"%2 int, "
			"%3 varchar(255),"
			"%4 varchar(255),"
			"%5 varchar(255),"
			"%6 varchar(255)); "
			"primary key(%2, %3)"
		).arg(DB_SESSIONS_TABLE).arg(DB_SESSION_ID)
			.arg(DB_SESSION_HOSTNAME).arg(DB_SESSION_STATE)
			.arg(DB_SESSION_USERNAME).arg(DB_SESSION_STATION));
		query.exec(QString(
			"INSERT INTO %1"
			"VALUES ('1','test_hostname','test_state','test_username','test_station');").arg(DB_SESSIONS_TABLE));
		query.exec(QString(
			"INSERT INTO %1"
			"VALUES ('2','test_hostname','test_state','test_username','test_station');").arg(DB_SESSIONS_TABLE));*/
	}
	void findRowTest_data()
	{
		//QTest::addColumn<QString>("database");
		//QTest::addColumn<ulong>("id");
		//QTest::addColumn<QString>("hostname");
		//QTest::addColumn<int>("result");

		//QTest::newRow("empty_bd_test") << EMPTY_TEST_BD << 123 << "" << "" << -1;
		//QTest::newRow("first_session_test") << FILLED_TEST_BD << 2 << "test_hostname" << 1;
		//QTest::newRow("second_session_test") << FILLED_TEST_BD << 1 << "test_hostname" << 0;
		//QTest::newRow("non-existent_session_test") << FILLED_TEST_BD << 2 << "wrong_hostname";
	}
	void findRowTest()
	{
		//QFETCH(QString, database);
		//QFETCH(ulong, id);
		//QFETCH(QString, hostname);
		//QFETCH(int, result);
		//QSqlDatabase db = QSqlDatabase::database(database);
		//SessionSqlModel model(db);
		//QCOMPARE(model.findRow(hostname, id), result);
	}
	~SessionSqlModelTest() override
	{
		QSqlDatabase::removeDatabase(EMPTY_BD_CONNECTION);
		QSqlDatabase::removeDatabase(FILLED_BD_CONNECTION);
	}
};
TEST_F(SessionSqlModelTest, EmptyDBinitialization)
{
	SessionSqlModel model(emptyDB);
	ASSERT_EQ(model.rowCount(), 0) << "Model with empty database has more than one row";
	EXPECT_EQ(model.findRow("test_hostname", 1),-1);

}
TEST_F(SessionSqlModelTest, FilledDBinitialization)
{
	SessionSqlModel model(filledDB);
	ASSERT_EQ(model.rowCount(), 2) ;
	EXPECT_EQ(model.findRow("wrong_hostname", 1), -1);
	EXPECT_EQ(model.findRow("test_hostname", 1),0);

	EXPECT_STREQ(model.data(model.index(model.findRow("test_hostname", 1), 
		model.fieldIndex(DB_SESSION_STATE))).toString().toStdString().c_str(), "test_state");

}
TEST_F(SessionSqlModelTest, setSessionsTest)
{
	SessionSqlModel model(filledDB);
	SessionList testList;
	testList.push_back(Session(0, "another_hostname"));
	testList.push_back(Session(1, "another_hostname"));
	testList.push_back(Session(2, "another_hostname"));
	testList.push_back(Session(3, "another_hostname",Session::SHADOW));
	EXPECT_NE(model.setSessionsOnServer("another_hostname", testList),0);
	EXPECT_EQ(model.rowCount(), 6);
	EXPECT_NE(model.findRow("another_hostname", 1), -1);
	EXPECT_EQ(model.data(model.index(model.findRow("another_hostname", 3),
		model.fieldIndex(DB_SESSION_STATE))).value<int>(), Session::SHADOW);



}