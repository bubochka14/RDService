#pragma once
#include <QObject>
#include <QString>
#include <QMultiHash>
#include <QMetaEnum>
class RDServer;
struct Session{
	Q_GADGET;
public:
	enum  State
	{
		INVALID=0,
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
	}; Q_ENUM(State);
private:
	Q_PROPERTY(ulong id	MEMBER id );
	Q_PROPERTY(QString hostname MEMBER hostname )
	Q_PROPERTY(QString station MEMBER station);
	Q_PROPERTY(QString user MEMBER user);
	Q_PROPERTY(State state MEMBER state);
public:
	State  state;
	ulong   id;
	QString station;
	QString user;
	QString hostname;
//public:
//	State state() const;
//	QString station()	 const;
//	QString user()		 const;
//	QString server()     const;
//	ulong id()			 const;
//
	/*void setState(State state);
	void setStation(const QString& station);
	void setUser(const QString& user);*/
	Session(ulong id, const QString& server, State state = INVALID);

	inline bool isValid() const { return state != INVALID; }
	};

struct RDServer 
{
	Q_GADGET
public:
	enum ServerState
	{
		UNOPENED,
		NOT_AVAILABLE,
		ACTIVE
	}; Q_ENUM(ServerState);
private:
	Q_PROPERTY(QString name MEMBER name)
	Q_PROPERTY(ServerState state MEMBER state)

public:
	QString name;
	ServerState state;
	explicit RDServer(const QString& name, ServerState state = UNOPENED);
//	QString name() const;
//	ServerState state() const;
//signals:
//	void stateChanged();
};
using SessionList = QList<Session>;