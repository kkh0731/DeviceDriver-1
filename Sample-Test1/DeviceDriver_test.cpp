#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Day10-3/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(DeviceDriver, TestFiveRead) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read)
		.Times(5);

	DeviceDriver devicedriver(&flash_mock);
	devicedriver.read(0xA);
}

TEST(DeviceDriver, ExceptionRead) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&flash_mock);
	EXPECT_THROW(driver.read(0x2), exception);
}

TEST(DeviceDriver, TestWrite) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(_))
		.Times(1)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, write(_, _))
		.Times(1);

	DeviceDriver devicedriver(&flash_mock);
	devicedriver.write(0xA, 0x3D);
}

TEST(DeviceDriver, ExceptionWrite) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(0x2))
		.WillRepeatedly(Return(0x88));

	DeviceDriver driver(&flash_mock);
	EXPECT_THROW(driver.write(0x2, 0x37), exception);
}