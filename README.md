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


#### 参与贡献


1.  [https://github.com/kaldoran/Adafruit-Weather-Icon](https://github.com/kaldoran/Adafruit-Weather-Icon)
2.  [https://github.com/ZinggJM/GFX_FontExtension_for_Adafruit_GFX](https://github.com/ZinggJM/GFX_FontExtension_for_Adafruit_GFX)
3.  [Adafruit_GFX显示中文详细教程](https://blog.csdn.net/weixin_44807826/article/details/131404098)
4.  [Adafruit-GFX显示中文详细教程-字体库程序包](https://gitcode.com/open-source-toolkit/fed79)
5.  [https://github.com/will127534/AdafruitGFX-ChineseFont-Addon](https://github.com/will127534/AdafruitGFX-ChineseFont-Addon)
