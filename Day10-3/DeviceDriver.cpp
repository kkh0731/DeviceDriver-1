#include "DeviceDriver.h"
#include <windows.h>
#include <exception>

using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstReadTryValue = (int)(m_hardware->read(address));
	for(int tryCount = 2; tryCount <= TOTAL_READ_TRY_COUNT; tryCount++) {
        Sleep(200);
		int nextReadTryValue = (int)(m_hardware->read(address));
        if (firstReadTryValue == nextReadTryValue) continue;

		throw exception("ReadFailException");
	}
    return firstReadTryValue;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}