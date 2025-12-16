#include "Display.hpp"
#include <avr/pgmspace.h>

// Display driver for SH1106

// Pin configuration.
static constexpr uint8_t PIN_RESET = 14;
static constexpr uint8_t PIN_DC = 18;
static constexpr uint8_t PIN_CS = 10;
static constexpr uint8_t SPI_PIN_MOSI = 11; // connect to the DIN pin of OLED
static constexpr uint8_t SPI_PIN_SCK = 13; // connect to the CLK pin of OLED

Display::Display() :
  // первый параметр влияет на скорость передачи данных на дисплей
  // это заметно по тому как заполняются страницы
  Settings(/*Speed up to 16M Hz*/8000000, MSBFIRST, SPI_MODE0)
{}

void Display::init() const
{
  // Difference between SSD1306 and SH1106:
  // - The SH1106 controller has an internal RAM of 132x64 pixel.
  //   The SSD1306 controller only has 128x64 pixel.
  // - The SSD1306 has an expanded command set over the SH1106.
  //   The SSD1306 also has capability for automatic scrolling.The SH1106 hasn't.
  // - The SH1106 only supports page addressing mode.
  //   The SSD1306 supports special horizontal and vertical addressing modes.

  pinMode(PIN_RESET, OUTPUT);
  pinMode(PIN_DC, OUTPUT);
  pinMode(PIN_CS, OUTPUT);
  SPI.begin();

  // http://microsin.net/adminstuff/hardware/ssd1306-oled-controller.html

  // GDDRAM - Graphic Display Data RAM
  // COM - Common Drivers
  // SEG - Segment Drivers

  // D/C - Data/Command
  // DC говорит какая информация будет передаваться:
  // 0 - команда (non-graphics data)
  // 1 - данные, которые будут переданы в GDDRAM (The GDDRAM column address pointer will be increased by one automatically after each data write.)

  // CS(aka SS) говорит какому устройству информация будет передаваться:
  // 0 - устройство принимает данные
  // 1 - устройство игнорирует данные
  digitalWrite(PIN_CS, LOW);
  digitalWrite(PIN_RESET, HIGH);
  delay(10);
  digitalWrite(PIN_RESET, LOW);
  delay(10);
  digitalWrite(PIN_RESET, HIGH);


  // Разрещить передачу данных/команд на дисплей. Делаем это один раз в начале, потому что планируется,
  // что больше нет устройств работающих через протокол SPI,
  // иначе нужно завершать передачу после каждой отсылки данных/команд.
  SPI.beginTransaction(Settings);

  // set command flag for the following commands
  digitalWrite(PIN_DC, LOW);

  // Выключить экран
  command(0xAE);//--turn off oled panel

  // Установка адреса начальной страницы
  // 0xB0 + X[2:0]:
  // 0-7 адрес начальной страницы GDDRAM(PAGE0~PAGE7)
  // Примечание: эта команда используется только для Page Addressing Mode.
  //command(0xB0);

  // Устанавливает младший полубайт регистра начального адреса столбца для режима адресации страниц
  // 0x00 + X[3:0]:
  // 0-F (по умолчанию 0)
  // Примечание: эта команда используется только для Page Addressing Mode.
  //command(0x02);//---set low column address

  // Устанавливает старший полубайт регистра начального адреса столбца для режима адресации страниц.
  // 0x10 + X[3:0]:
  // 0-F (по умолчанию 0)
  // Примечание: эта команда используется только для Page Addressing Mode.
  //command(0x10);//---set high column address

  // X[5:0]: 0-63 - регистр начальной строки
  command(0x40);//--set start line address  Set Mapping GDDRAM Display Start Line (0x00~0x3F)

  // установка контраста экрана.
  // X[7:0]:
  // 0-255 - контраст, где 0 это наименьший. (127 по умолчанию)
  command(0x81, 100);//--set contrast control register

  // Отражение изображения по горизонтали.
  // 0xA0 + X[0]:
  // 1 - счёт колонок слева направо
  // 0 - счёт колонок справа налево
  command(0xA1);//--Set SEG/Column Mapping (0xA1, 0xA0)

  // Отражение изображения по вертикали.
  // 0xC8 - счёт рядов сверху вниз, сканирование от COM[N-1] до COM0, где N - MUX ratio.
  // 0xC0 - счёт рядов снизу вверх, сканирование от COM0 до COM[N-1]. (по умолчанию)
  command(0xC8);//Set COM/Row Scan Direction  (0xC8, 0xC0)

  // в режиме инверсии активные пиксели не будут светиться, а неактивные будут.
  // 0xA6 + X[0]:
  // 0 - нормальный (по умолчанию)
  // 1 - инвертированный
  command(0xA7);//--set display normal(0xA6)/inverse(0xA7)

  // количество рядов используемое на экране снизу вверх. всё что выше не будет отрисовано
  // 0x00-0x3F - количество рабочих рядов.
  // Установка коэффициента мультиплексирования (MUX ratio) для N+1 MUX.
  // X[5:0]:
  // 0-14 - недопустимы
  // 15-63 - 16MUX до 64MUX, где - 63 это 64MUX. (63 по умолчанию)
  command(0xA8, 63);//--set multiplex ratio(1 to 64) and 1/64 duty

  // магия
  command(0xAD, 0x8B); // Set Charge Pump

  command(0x32); /* set VPP 8V (0x30-0x33)*/

  //сдвиг картинки вверх по вертикали
  // X[5:0]:
  // 0-64 - сдвиг начала строк по одной строке вверх (0 по умолчанию)
  command(0xD3, 0);//-set display offset. Shift Mapping GDDRAM Counter (0x00~0x3F) not offset

  // Частота кадров.
  // X[3:0] F:
  // 0-F - коэфициент деления внутреннего генератора, где - 0 минимальная частота
  // X[7:4] D:
  // 0-F - коэффициент деления от 1 до 16, где - 0 это 1
  // Формула. Частота кадров = F / (D · 54 · N), где N устанавливается командой 0xA8
  command(0xD5, 0x80);//--set display clock divide ratio/oscillator frequency. Set divide ratio, Set Clock as 100 Frames/Sec

  // установка периода Phase 1 и Phase 2
  // X[3:0]:
  // 0 - недопустимо
  // 1-15 установка периода Phase 1 (2 по умолчанию)
  // X[7:4]:
  // 0 - недопустимо
  // 1-15 установка периода Phase 2 (2 по умолчанию)
  command(0xD9, 0xF2);//--set Pre-Charge / Discharge period

  // конфигурация выводов COM.
  // 0x02 + X[5:4]:
  // X[4]:
  // 0 - конфигурация последовательных выводов COM.
  // 1 - альтернативная конфигурация выводов COM. (по умолчанию)
  // X[5]:
  // 0 - Disable COM Left / Right remap.(по умолчанию)
  // 1 - Enable COM Left / Right remap.
  command(0xDA, 0x12);//--set com pins hardware configuration

  // Эта команда настраивает выход регулятора напряжения VCOMH.
  // X[6:4]:
  // 0x00 ~0.65 · VCC
  // 0x20 ~0.77 · VCC (по умолчанию)
  // 0x30 ~0.83 · VCC
  command(0xDB, 0x40);//--Set VCOMH Deselect Level

  // Memory Addressing Mode
  // 0 - Horizontal Addressing Mode
  // 1 - Vertical Addressing Mode
  // 2 - Page Addressing Mode (значение по умолчанию после сброса)
  // 3 - недопустимый режим
  // SH1106 поддерживает только Page Addressing Mode
  //command(0x20, 0x00);//-Set Page Addressing Mode

  // Устанавливает младший полубайт регистра начального адреса столбца для режима адресации страниц
  // 0x00 + X[3:0]:
  // 0-F (по умолчанию 0)
  // Примечание: эта команда используется только для Page Addressing Mode.
  // SH1106 имеет 132x64 RAM, и экран центрирован относительно RAM, потому первый пиксель имеет адрес (2,0)
  //command(0x02);//---set low column address

  // Устанавливает старший полубайт регистра начального адреса столбца для режима адресации страниц.
  // 0x10 + X[3:0]:
  // 0-F (по умолчанию 0)
  // Примечание: эта команда используется только для Page Addressing Mode.
  //command(0x10);//---set high column address

  // Настройка адреса начального и конечного столбца.
  // A[6:0]:
  // 0-127 - адрес начального столбца (по умолчанию 0).
  // B[6:0]:
  // 0-127 - адрес конечного столбца (по умолчанию 127).
  // Примечание: эта команда используется только для режимов горизонтальной или вертикальной адресации.
  // Не работает для SH1106
  //command(0x21, 0, 127);//---Set Column Address

  // Настройка адреса начальной и конечной страницы.
  // A[2:0]:
  // 0-7 - адрес начального столбца (по умолчанию 0).
  // B[2:0]:
  // 0-7 - адрес конечного столбца (по умолчанию 7).
  // Примечание: эта команда используется только для режимов горизонтальной или вертикальной адресации.
  // Не работает для SH1106
  //command(0x22, 0, 7);//---Set Page Address

  // активировать все пиксели на экране.
  // экран будет весь тупо светиться и перезапись данными не изменит этого состояния.
  // 0xA4 + X[0]:
  // 0 - нет (по умолчанию)
  // 1 - да
  command(0xA4);// Disable Entire Display On

  // Включить экран
  command(0xAF);//--turn on oled panel

  delay(100);
}

void Display::update() const
{
  uint8_t page = 0;
  const uint8_t* buf = buffer;
  const uint8_t* end = buffer + WIDTH * NUM_PAGE;
  while (buf != end)
  {
    fillPage(page++, buf);
    buf += WIDTH;
  }
}

Buffer Display::getBuffer() const
{
  return { const_cast<uint8_t*>(buffer), WIDTH, HEIGHT };
}

// This function is an improved version of `SPIClass::transfer` function.
// See all details in it. This version doesn't erase the data. of the given buffer.
void Display::transfer(const uint8_t* buf, size_t count) const {
  while (count--) {
    SPDR = *(buf++);
    while (!(SPSR & _BV(SPIF)));
  }
}

// This function is an improved version of `SPIClass::transfer` function.
// See all details in it. This version returns `void`.
// NOTE: This function is designed to be invoked from `init` function only.
// To use it from other places you should set command flag explicitly: digitalWrite(PIN_DC, LOW);
void Display::command(uint8_t cmd) const {
  SPDR = cmd;
  asm volatile("nop");
  while (!(SPSR & _BV(SPIF)));
}

// See function above.
void Display::command(uint8_t cmd, uint8_t data) const {
  command(cmd);
  command(data);
}

void Display::fillPage(uint8_t pageNum, const uint8_t* buf) const
{
  digitalWrite(PIN_DC, LOW);  // set command flag
  command(0xB0 + pageNum);    // set page address
  command(0x02, 0x10);        // set LOW and HIGH column address
  digitalWrite(PIN_DC, HIGH); // set data flag
  transfer(buf, WIDTH);
}
