#include "UTF8Print.h"
#include <iostream>
#include <vector>

UTF8Print::UTF8Print() {

}

/**
 * @brief 初始化显示屏和设置相关参数。
 * @param gfx Adafruit_GFX 类型的显示屏对象，传入用以控制显示的屏幕。
 * @param chinese_unicode 包含 Unicode 代码点的数组，表示中文字符的 Unicode 代码点。
 * @param array_size 数组的大小，表示 Unicode 代码点数组的元素个数。
 */
void UTF8Print::begin(Adafruit_GFX &gfx, const uint16_t* chinese_unicode, size_t array_size) {
    _gfx = &gfx;  // 设置显示屏对象指针
    _chinese_unicode = chinese_unicode;  // 保存 Unicode 代码点数组
    _array_size = array_size;  // 保存数组大小
}

/**
 * @brief 打印中文字符串并显示对应的 Unicode 索引。
 * @param chineseStr 需要打印的中文字符串。
 * 
 * @note 该方法会遍历输入的字符串，解码每个字符的 Unicode 代码点，并查找该代码点在 Unicode 数组中的索引。
 */
void UTF8Print::printString(const std::string& chineseStr) {
    if (_gfx == nullptr || _chinese_unicode == nullptr) {
        std::cerr << "Error: gfx or chinese_unicode not initialized!" << std::endl;
        return;  // 如果没有初始化 gfx 或 chinese_unicode，则返回
    }

    // 将中文字符串转换为 UTF-8 字节流
    std::vector<uint8_t> utf8Bytes(chineseStr.begin(), chineseStr.end());

    // 遍历字符串中的每个字符，解码并查找索引
    for (size_t i = 0; i < utf8Bytes.size(); ++i) {
        uint16_t unicodeCodePoint = decodeUTF8(utf8Bytes[i]);

        // 如果解码成功并且有有效的 Unicode 代码点
        if (unicodeCodePoint != 0) {
            // 查找该 Unicode 代码点在数组中的索引
            int index = findUnicodeIndex(unicodeCodePoint, _chinese_unicode, _array_size);

            if (index != -1) {
                // 打印索引到显示屏
                _gfx->write(index); 
            } else {
                _gfx->print("Not found\n");
            }
        }
    }
}

/**
 * @brief 解码单个 UTF-8 字节为 Unicode 代码点。
 * @param c 输入的 UTF-8 字节。
 * @return 返回解码后的 Unicode 代码点，若解码失败，则返回 0。
 */
uint16_t UTF8Print::decodeUTF8(uint8_t c) {
    if ((c & 0x80) == 0x00) {
        decoderState = 0;
        return (uint16_t)c;
    }

    if (decoderState == 0) {
        if ((c & 0xE0) == 0xC0) {
            decoderBuffer = ((c & 0x1F) << 6);
            decoderState = 1;
            return 0;
        }
        if ((c & 0xF0) == 0xE0) {
            decoderBuffer = ((c & 0x0F) << 12);
            decoderState = 2;
            return 0;
        }
        if ((c & 0xF8) == 0xF0) {
            decoderBuffer = ((c & 0x07) << 18);
            decoderState = 3;
            return 0;
        }
    } else {
        if (decoderState == 3) {
            decoderBuffer |= ((c & 0x3F) << 12);
            decoderState--;
            return 0;
        }
        if (decoderState == 2) {
            decoderBuffer |= ((c & 0x3F) << 6);
            decoderState--;
            return 0;
        }
        if (decoderState == 1) {
            decoderBuffer |= (c & 0x3F);
            decoderState = 0;
            return decoderBuffer;
        }
    }

    decoderState = 0;
    return (uint16_t)c;  // 解码失败，返回原始字节
}

/**
 * @brief 查找 Unicode 代码点在指定数组中的索引。
 * @param code 要查找的 Unicode 代码点。
 * @param array 存储 Unicode 代码点的数组。
 * @param array_size 数组的大小。
 * @return 若找到则返回该代码点在数组中的索引，若未找到则返回 -1。
 */
int UTF8Print::findUnicodeIndex(uint16_t code, const uint16_t* array, size_t array_size) {
    for (size_t i = 0; i < array_size; ++i) {
        if (array[i] == code) {
            return i;  // 返回索引
        }
    }
    return -1;  // 如果没有找到，返回 -1
}
