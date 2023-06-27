#include <QtPlugin>
#include <QString>
#include <QVector>
#include "rdserver.h"
#include <rdsession.h>
class RDSessionInterface
{
public:
	virtual int disconnectSession(RDSession*) = 0;
	virtual int sendMessage(RDSession*, const QString&) = 0;
	virtual int startShadowing(RDSession*) = 0;
	virtual int stopShadowing(RDSession*) = 0;
	virtual ~RDSessionInterface() = default;
};
#ifndef RDSessionInterface_iid
	#define RDSessionInterface_iid "RDSessionViewer.RDSessionInterfaceV0.1"
	Q_DECLARE_INTERFACE(RDSessionInterface RDSessionInterface_iid)
#endif 

class RDServerInterface
{
public:
	virtual int disconnectServer() = 0;
	virtual QVector<RDSession> getSessions() = 0;
	virtual ~RDServerInterface = default;
};
#ifndef RDServerInterface_iid
#define RDServerInterface_iid "RDSessionViewer.RDServerInterfaceV0.1"
	Q_DECLARE_INTERFACE(RDSessionInterface RDServerInterface_iid)
#endif 
class RDServerRepInterface
{
public:
	virtual QVector<RDServer> getServers(const QString& methodName) = 0;
	virtual QStringList getMethodNames() = 0;


};
#ifndef RDServerRepInterface_iid
#define RDServerRepInterface_iid "RDSessionViewer.RDServerRepInterfaceV0.1"
	Q_DECLARE_INTERFACE(RDSessionInterface RDServerRepInterface_iid)
#endif 