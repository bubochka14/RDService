#include "rdserver.h"
Session::Session(ulong id, const QString& server, State state)
	:id(id)
	,hostname(server)
	,state(state)
{
}
RDServer::RDServer(const QString& name_, ServerState state_)
	:name(name_)
	,state(state_)
{

}
