/*
 * ByteBuffer.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: lwj
 */
#include "ByteBuffer.h"

ByteBuffer::ByteBuffer()
{
	mBuff = NULL;
	mPos  = NULL;
	mSize = 0;
}

ByteBuffer::~ByteBuffer()
{
	if(mBuff != NULL)
	{
		free(mBuff);
		mBuff = NULL;
	}
}

bool ByteBuffer::init(uint32 size)
{
	mBuff = (char*)malloc(sizeof(char) * size);
	if(mBuff == NULL)
	{
		cout << "Err ByteBuffer malloc fail, size = " << size << endl;
		return false;
	}
	mPos = mBuff;

	return true;
}

void ByteBuffer::writeUint8(uint8 i)
{
	memcpy(mPos, &i, sizeof(i));
	mPos += sizeof(i);
	mSize += sizeof(i);
}

void ByteBuffer::writeUint16(uint16 i)
{
	memcpy(mPos, &i, sizeof(i));
	mPos += sizeof(i);
	mSize += sizeof(i);
}

void ByteBuffer::writeUint32(uint32 i)
{
	memcpy(mPos, &i, sizeof(i));
	mPos += sizeof(i);
	mSize += sizeof(i);
}

uint8 ByteBuffer::readUint8()
{
	uint8 i = 0;
	memcpy(&i, mPos, sizeof(i));
	mPos += sizeof(i);
	return i;
}

uint16 ByteBuffer::readUint16()
{
	uint16 i = 0;
	memcpy(&i, mPos, sizeof(i));
	mPos += sizeof(i);
	return i;
}

uint32 ByteBuffer::readUint32()
{
	uint32 i = 0;
	memcpy(&i, mPos, sizeof(i));
	mPos += sizeof(i);
	return i;
}

void ByteBuffer::writeMsg(ProtoBuff& proBuff)
{
	proBuff.encode(mPos);
	mSize += proBuff.getLen();
}

void ByteBuffer::cleanUp()
{
	mPos = mBuff;
	memset(mBuff, 0, mSize);
	mSize = 0;
}
