# Adafruit GFX UTF8 TFT Print


#### 介绍
Adafruit_GFX 中文显示 详细教程 中文字体库程序包

#### 软件架构
软件架构说明
1.  fontconverter.exe 从以下位置获取[https://github.com/Bodmer/GFX_Font_Converter](https://github.com/Bodmer/GFX_Font_Converter)
2.  GFXFontConverte.exe 是手搓的就是在 fontconverter.exe 基础上套壳

#### 安装教程

1.  使用 GFXFontConverte.exe 或 fontconvert.exe 字体转换需要的中文
2.  项目中引用转换后的字体.h文件
3.  Arduino ino 中调用

#### 使用说明            
1.  项目中引用生成的字体文件
    ```
        #include "./font/ch2.h"  // 生成的字体文件
        #include "./UTF8Print.h" // 中文打印主程序代码
    ```
2.  创建对象
    ```
      UTF8Print utf8_print;
    ```
3.  调用打印中文
    ```
      tft.setTextSize(1);  // Adafruit_GFX 的一些设置
      tft.setTextColor(ST77XX_WHITE);
      tft.setFont(&songti20pt8b);  // 设置字体为我们生成的字体 font
      size_t array_size = sizeof(songti20pt8bUnicode) / sizeof(songti20pt8bUnicode[0]); // 中文字体对应的Unicode序列
      utf8_print.begin(tft, songti20pt8bUnicode, array_size); // 准备一个 utf8_print 对象
      utf8_print.printString("我的中国心abc"); // 打印
    ```

#### 特技

1.  对于大量汉字应用，可使用 U8g2_for_Adafruit_GFX 中包含大量字体，u8g2_font_wqy14_t_gb2312 字体库包含 全部中文字体，对于ESP8266小内容MUC出现内存不足错误：
    ```
    section \`.bss' is not within region \`dram0_0_seg'
    ```
    可以通过修改两处代码解决<br>
    U8g2_for_Adafruit_GFX.cpp
    ```
    #include "u8g2_fonts.h"
    #if defined(ESP8266)
    uint8_t u8x8_pgm_read_esp(const uint8_t * addr)
    {
    uint32_t bytes;
    bytes = *(uint32_t*)((uint32_t)addr & ~3);
    return ((uint8_t*)&bytes)[(uint32_t)addr & 3];
    }
    #endif
    ```
    u8g2_fonts.h
    ```
    #if defined(ESP8266)
    uint8_t u8x8_pgm_read_esp(const uint8_t * addr);   /* u8x8_8x8.c */
    #  define U8X8_FONT_SECTION(name) __attribute__((section(".text." name)))
    #  define u8x8_pgm_read(adr) u8x8_pgm_read_esp(adr)
    #  define U8X8_PROGMEM
    #endif
    ```
    
2.  对于少量汉字应用，可使用PCtoLCD2002软件取字模，使用Adafruit_GFX中的  drawChar 方法绘制出汉字
     ```
    const unsigned char  ni[] = { 0x08, 0x80, 0x08, 0x80, 0x08, 0x80, 0x11, 0xFE, 0x11, 0x02, 0x32, 0x04, 0x34, 0x20, 0x50, 0x20, 0x91, 0x28, 0x11, 0x24, 0x12, 0x24, 0x12, 0x22, 0x14, 0x22, 0x10, 0x20, 0x10, 0xA0, 0x10, 0x40 }; /*"你",0*/
    const unsigned char  de[] = { 0x10, 0x40, 0x10, 0x40, 0x20, 0x40, 0x7E, 0x7C, 0x42, 0x84, 0x42, 0x84, 0x43, 0x04, 0x42, 0x44, 0x7E, 0x24, 0x42, 0x24, 0x42, 0x04, 0x42, 0x04, 0x42, 0x04, 0x7E, 0x04, 0x42, 0x28, 0x00, 0x10 }; /*"的",1*/
    const unsigned char  ming[] = { 0x02, 0x00, 0x02, 0x00, 0x07, 0xF0, 0x08, 0x10, 0x14, 0x20, 0x62, 0x40, 0x02, 0x80, 0x01, 0x00, 0x06, 0x00, 0x1F, 0xF8, 0xE8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0F, 0xF8, 0x08, 0x08 }; /*"名",2*/
    const unsigned char  zi[] = { 0x02, 0x00, 0x01, 0x00, 0x7F, 0xFE, 0x40, 0x02, 0x80, 0x04, 0x1F, 0xE0, 0x00, 0x40, 0x00, 0x80, 0x01, 0x00, 0xFF, 0xFE, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x05, 0x00, 0x02, 0x00 }; /*"字",3*/
    
    tft.drawBitmap(10, 10, ni, 16, 16, 0xFFFF);  // 绘制 "你"
     ```

#### 参与贡献
1.  [https://github.com/kaldoran/Adafruit-Weather-Icon](https://github.com/kaldoran/Adafruit-Weather-Icon)
2.  [https://github.com/ZinggJM/GFX_FontExtension_for_Adafruit_GFX](https://github.com/ZinggJM/GFX_FontExtension_for_Adafruit_GFX)
3.  [Adafruit_GFX显示中文详细教程](https://blog.csdn.net/weixin_44807826/article/details/131404098)
4.  [Adafruit-GFX显示中文详细教程-字体库程序包](https://gitcode.com/open-source-toolkit/fed79)
5.  [[ESP8266]ESP8266-12F使用U8g2_for_Adafruit_GFX库展示汉语](https://segmentfault.com/a/1190000044538471)
6.  [https://github.com/will127534/AdafruitGFX-ChineseFont-Addon](https://github.com/will127534/AdafruitGFX-ChineseFont-Addon)

