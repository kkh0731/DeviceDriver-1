#include "App.h"
#include <iostream>

using namespace std;

Application::Application(DeviceDriver* devicedriver) : m_devicedriver(devicedriver)
{}

void Application::ReadAndPrint(long startAddr, long endAddr) {
	for (long curAddr = startAddr; curAddr <= endAddr; curAddr++) {
		cout << m_devicedriver->read(curAddr);
	}
	cout << endl;
}

void Application::WriteAll(int value) {
	for (long curAddr = 0x0; curAddr <= 0x4; curAddr++) {
		m_devicedriver->write(curAddr, value);
	}
}