/*
 * BaseType.h
 *
 *  Created on: Jan 12, 2015
 *      Author: lwj
 */

#ifndef BASETYPE_H_
#define BASETYPE_H_

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <vector>
#include <map>
#include <set>
#include <errno.h>
#include <netinet/tcp.h>

using namespace std;

typedef unsigned char      uint8;
typedef char               int8;
typedef unsigned short     uint16;
typedef short              int16;
typedef unsigned int       uint32;
typedef int                int32;
typedef unsigned long long uint64;
typedef long long          int64;

#define THOUSAND (1000)
#define MILLION  (1000 * 1000)

enum eServerType
{
	eServerTypeWorld = 0,
	eServerTypeGame  = 1
};

#define SAFE_DEL(x) if((x) != NULL) {delete (x); (x) = NULL;}


#endif /* BASETYPE_H_ */
