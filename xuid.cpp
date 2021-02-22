#include "hdd_serial_number.h"
#include <string.h>

/*
stolen from sample code && AlterIw/fourdeltaone uses this too
*/

static unsigned int xuid = 0;

inline unsigned int jenkins_one_at_a_time_hash(char *key, size_t len)
{
	unsigned int hash, i;
	for (hash = i = 0; i < len; ++i)
	{
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}

unsigned int getxuid()
{
	if (xuid)
		return xuid;


	MasterHardDiskSerial diskSerial;
	char *serial = diskSerial.GetSerialNo();
	xuid = jenkins_one_at_a_time_hash(serial, strlen(serial));
	return xuid;
}