/*
 * ProtoBuff.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: root
 */
#include "ProtoBuff.h"

using namespace Proto;

ProtoBuff::ProtoBuff()
{

}

ProtoBuff::~ProtoBuff()
{

}

void ProtoBuff::writeUint8(char* buff, uint8 i)
{
	memcpy(buff, &i, sizeof(i));
	buff += sizeof(i);
}

void ProtoBuff::writeUint16(char* buff, uint16 i)
{
	memcpy(buff, &i, sizeof(i));
	buff += sizeof(i);
}

void ProtoBuff::writeUint32(char* buff, uint32 i)
{
	memcpy(buff, &i, sizeof(i));
	buff += sizeof(i);
}

uint8 ProtoBuff::readUint8(char* buff)
{
	uint8 i = 0;
	memcpy(&i, buff, sizeof(i));
	buff += sizeof(i);
	return i;
}

uint16 ProtoBuff::readUint16(char* buff)
{
	uint16 i = 0;
	memcpy(&i, buff, sizeof(i));
	buff += sizeof(i);
	return i;
}

uint32 ProtoBuff::readUint32(char* buff)
{
	uint32 i = 0;
	memcpy(&i, buff, sizeof(i));
	buff += sizeof(i);
	return i;
}
