#ifndef UTF8PRINT_H
#define UTF8PRINT_H

#include <stdint.h>
#include <string>
#include <Adafruit_GFX.h>  // 引入 Adafruit_GFX 库

/**
 * @class UTF8Print
 * @brief 该类用于处理 UTF-8 字符串的解码和打印，并在显示屏上显示对应的 Unicode 索引。
 * 主要功能包括：初始化显示屏、打印中文字符串及其在 Unicode 数组中的索引。
 */
class UTF8Print {
public:
  /**
     * @brief 构造函数，初始化 UTF8Print 对象。
     */
  UTF8Print();

  /**
     * @brief 初始化显示屏和设置相关参数。
     * @param gfx Adafruit_GFX 类型的显示屏对象，传入用以控制显示的屏幕。
     * @param chinese_unicode 包含 Unicode 代码点的数组，表示中文字符的 Unicode 代码点。
     * @param array_size 数组的大小，表示 Unicode 代码点数组的元素个数。
     * 
     * @note 此方法用于初始化显示屏参数并保存 Unicode 数组，必须在调用 `print` 前调用。
     */
  void begin(Adafruit_GFX& gfx, const uint16_t* chinese_unicode, size_t array_size);

  /**
     * @brief 打印中文字符串并显示对应的 Unicode 索引。
     * @param chineseStr 需要打印的中文字符串。
     * 
     * @note 此方法会遍历输入的字符串，解码每个字符的 Unicode 代码点，并查找该代码点在 Unicode 数组中的索引。
     */
  void printString(const std::string& chineseStr);

private:
  Adafruit_GFX* _gfx;      ///< 指向 Adafruit_GFX 对象的指针
  int decoderState;        ///< 解码状态，表示当前正在解码哪个字节
  uint16_t decoderBuffer;  ///< 缓冲区，用于保存正在解码的 Unicode 代码点

  int cursorX, cursorY;  ///< 光标位置，用于确定打印文本的位置
  uint16_t textColor;    ///< 文本颜色
  uint8_t textSize;      ///< 文本大小

  const uint16_t* _chinese_unicode;  ///< 存储 Unicode 代码点数组
  size_t _array_size;                ///< 存储 Unicode 代码点数组的大小

  /**
     * @brief 解码单个 UTF-8 字节为 Unicode 代码点。
     * @param c 输入的 UTF-8 字节。
     * @return 返回解码后的 Unicode 代码点，若解码失败，则返回 0。
     */
  uint16_t decodeUTF8(uint8_t c);
  
  /**
     * @brief 查找 Unicode 代码点在指定数组中的索引。
     * @param code 要查找的 Unicode 代码点。
     * @param array 存储 Unicode 代码点的数组。
     * @param array_size 数组的大小。
     * @return 若找到则返回该代码点在数组中的索引，若未找到则返回 -1。
     */
  int findUnicodeIndex(uint16_t code, const uint16_t* array, size_t array_size);
};

#endif  // UTF8PRINT_H
