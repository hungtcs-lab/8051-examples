NEC红外遥控协议解析
====

解析NEC红外遥控协议，
需要占用外部中断0和定时器0

### 使用步骤

1. 初始化
    ```c
    ir_nec_init();
    ```

2. 判断是否已经接收到数据
    ```c
    ir_nec_available();
    ```

3. 读取已经接收的数据
    ```c
    ir_nec_get_code();
    ```

### 完整实例
部分代码已省略，完整代码参考[main.c](./src/main.c)
```c
#include <stdint.h>
#include <mcs51/8051.h>
#include "ir-nec.h"

void main()
{
  ir_nec_init();

  while(1)
  {
    if(ir_nec_available())
    {
      printf("data is 0x%08lX\n", ir_nec_get_code());
    }
  }
}
```
