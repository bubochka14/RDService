#pragma once
#include <QObject>
#include <QString>
#include <QMetaEnum>
class AbstractRDServer;
struct RDSession {
private:
	Q_GADGET
public:
	enum  State
	{
		ACTIVE,
		CONNECTED,
		CONNECTQUERY,
		SHADOW,
		DISCONNECTED,
		IDLE,
		LISTEN,
		RESET,
		DOWN,
		INIT
	};
	Q_ENUM(State);
	State state;
	ulong   id;
	QString station;
	QString user;
	AbstractRDServer* server;
};
class AbstractRDServer : public QObject
{
	Q_OBJECT;
protected:
	QString _hostname;
	//QList<RDsession*> _sessions;
	//HANDLE hServer;
	AbstractRDServer(const QString& hostname, QObject* parent = nullptr);
public:
	virtual QVector<RDSession> recvSessions()=0;
	virtual QString hostname() const;
	virtual ~AbstractRDServer();
};