/*
 * ProtoBuff.h
 *
 *  Created on: Nov 2, 2014
 *      Author: root
 */

#ifndef PROTOBUFF_H_
#define PROTOBUFF_H_

#include "BaseType.h"

//#define MAX_PROTO_BUFFER (128 * 1024)

//enum ProtoType
//{
//	eInt    = 0,
//	eString = 1,
//	eFloat  = 2,
//};

class ProtoBuff
{
public:
	ProtoBuff();
	virtual ~ProtoBuff();

	void writeUint8(char* buff, uint8 i);
	void writeUint16(char* buff, uint16 i);
	void writeUint32(char* buff, uint32 i);

	uint8  readUint8(char* buff);
	uint16 readUint16(char* buff);
	uint32 readUint32(char* buff);

	virtual void encode(char* buff) = 0;
	virtual void decode(char* buff) = 0;
	virtual uint32 getLen() = 0;
};

namespace Opcodes
{
	const uint32 OCGateRegister = 100;
};

namespace Proto
{

struct ProGateRegister : public ProtoBuff
{
	uint32 serverType;

	uint32 getLen()
	{
		return sizeof(serverType);
	}

	void encode(char* buff)
	{
		writeUint32(buff, serverType);
	}

	void decode(char* buff)
	{
		serverType = readUint32(buff);
	}
};

}
#endif /* PROTOBUFF_H_ */
