#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Day10-3/DeviceDriver.cpp"
#include "../Day10-3/App.cpp"

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

TEST(DeviceDriver, Exception) {
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

TEST(Application, TestReadAndPrint) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(_))
		.Times(25)
		.WillRepeatedly(Return(42));

	DeviceDriver driver(&flash_mock);

	Application app(&driver);
	app.ReadAndPrint(0x0, 0x4);
}

TEST(Application, TestWriteAll) {
	FlashMock flash_mock;
	EXPECT_CALL(flash_mock, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(flash_mock, write(_, _))
		.Times(5);

	DeviceDriver driver(&flash_mock);

	Application app(&driver);
	app.WriteAll(58);
}