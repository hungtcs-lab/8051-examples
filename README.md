51单片机示例
====

[![](./bilibili.svg)](https://space.bilibili.com/25043249)
[![](./youtube.svg)](https://www.youtube.com/channel/UCmGaZOmnP5qx8bbdsPrBPtg)

### 目录
<details>
  <summary>基础</summary>
  <p>

  - [Blink](./Basic/Blink) _LED闪烁_
  - [Timer](./Basic/Timer) _使用定时器实现LED闪烁_
  </p>
</details>
<details>
  <summary>通讯总线</summary>
  <p>

  - [SPI](./Bus/SPI) _SPI总线协议_
  - [IIC](./Bus/IIC) _IIC总线协议_
  </p>
</details>
<details>
  <summary>常用模块</summary>
  <p>

  - [AT24C](./Modules/AT24C) _AT24Cxx是串行CMOS E2PROM_
  - [DHT22](./Modules/DHT22) _温湿度传感器_
  - [DS1302](./Modules/DS1302) _DS1302是由美国DALLAS公司推出的具有涓细电流充电能力的低功耗实时时钟芯片_
  - [HC-SR04](./Modules/HC-SR04) _HC-SR04是一款超声测距模块_
  - [IR-NEC](./Modules/IR-NEC) _解析NEC红外遥控协议_
  - [DS18B20](./Modules/DS18B20) _DS18B20是常用的数字温度传感器_
  - [NRF24L01](./Modules/NRF24L01) _nRF24L01是由NORDIC生产的工作在2.4GHz~2.5GHz的ISM 频段的单片无线收发器芯片_
  - [OLED](./Modules/OLED) _0.96寸OLED模块，主控是SSD1306_
  - [PCF8563](./Modules/PCF8563) _PCF8563是PHILIPS公司推出的一款工业级内含I2C总线接口功能的具有极低功耗的多功能时钟/日历芯片_
  - [SG90](./Modules/SG90) _SG90舵机_
  - [TCS34725](./Modules/TCS34725) _TCS34725顏色傳感器_
  - [TM1637-4-Digit-Tube-Display](./Modules/TM1637-4-Digit-Tube-Display) _4位数码管显示模块_
  </p>
</details>
<details>
  <summary>其他</summary>
  <p>

  _暂未整理_
  </p>
</details>

### 推荐工具链
- [`sdcc`](http://sdcc.sourceforge.net/) _small device C compiler_
- [`cutecom`](http://cutecom.sourceforge.net/) _GUI串口调试器_
- [`stcflash`](https://github.com/laborer/stcflash) _A command line programmer for STC 8051 microcontroller_
- [`Visual Studio Code`](https://code.visualstudio.com/)编辑器，推荐安装以下插件
    - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) _language support for C/C++ to Visual Studio Code_
    - [Doxygen Documentation Generator](https://marketplace.visualstudio.com/items?itemName=cschlosser.doxdocgen) _Doxygen Documentation generation on the fly by starting a Doxygen comment block and pressing enter_
    - [EditorConfig for VS Code](https://marketplace.visualstudio.com/items?itemName=EditorConfig.EditorConfig)

### Tips
- 如果你使用VSCode 和 `C/C++`插件，那么需要修改`.vscode/c_cpp_properties.json`文件中的`includePath`和`compilerPath`。
- 如果你使用的sdcc版本大于3.6，那么需要修改`putchar`方法的定义。
  > Mar 1st, 2018: SDCC 3.7.0 released.

  > Changed putchar() prototype from void putchar(char) to int putchar(int) to improve standard-compliance and allow error reporting.
