/*
 * ByteBuffer.h
 *
 *  Created on: Jan 12, 2015
 *      Author: lwj
 */

#ifndef BYTEBUFFER_H_
#define BYTEBUFFER_H_

#include "BaseType.h"
#include "ProtoBuff.h"

#define MAX_PACKAGE      (65535)
#define INPUT_BUFF_SIZE  (65535)
#define OUTPUT_BUFF_SIZE (128*1024)

class ByteBuffer
{
public:
	ByteBuffer();
	~ByteBuffer();

	bool init(uint32 size);
	void writeUint8(uint8 i);
	void writeUint16(uint16 i);
	void writeUint32(uint32 i);
	void writeMsg(ProtoBuff& proBuff);
	void cleanUp();

	uint8  readUint8();
	uint16 readUint16();
	uint32 readUint32();

public:
	char*  mPos;
	char*  mBuff;
	uint32 mSize;
};


#endif /* BYTEBUFFER_H_ */
