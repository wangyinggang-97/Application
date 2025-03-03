/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/
static void Palette_Init(void);                               //调色板初始化
static void Palette_DrawPoint(uint16_t,uint16_t,LCD_Color_t); //绘图区域画点
static uint8_t Touch_Read_ADC_XY(uint16_t *, uint16_t *);     //读触摸IC的XY坐标值
static uint8_t Touch_Calibrate(void);                         //触摸屏校准
static uint8_t Touch_Scan(void);                              //触摸屏扫描

/* Public variables-----------------------------------------------------------*/
Touch_Calibrate_Para_t Touch_Calibrate_Para;

Touch_t Touch =
{
        FALSE,
        FALSE,
        0,
        0,
        0,
        0,
        Color_RED,

        Palette_Init,
        Palette_DrawPoint,
        Touch_Read_ADC_XY,
        Touch_Calibrate,
        Touch_Scan
};
/* Private function prototypes------------------------------------------------*/
static uint8_t  SPI_Touch_ReadByte(void);        //从Flash读1个字节
static void     SPI_Touch_WriteByte(uint8_t);    //给Flash写1个字节
static uint16_t Touch_Read_ADC(uint8_t);         //读取触摸屏的ADC值

static void     LCD_DrawCross(uint16_t,uint16_t);//校正触摸时画十字专用

/*
	* @name   SPI_Touch_ReadByte
	* @brief  从触摸IC读1个字节
	* @param  None
	* @retval 读取到的数据
*/
static uint8_t SPI_Touch_ReadByte()
{
    uint8_t ReceiveByte;
    //等待模式读出1个字节
    if(HAL_SPI_Receive(&hspi2,&ReceiveByte,1,0x0A) != HAL_OK)
        ReceiveByte = Dummy_Byte;
    //返回字节
    return ReceiveByte;
}

/*
	* @name   SPI_Touch_ReadByte
	* @brief  给触摸IC写1个字节
	* @param  Byte -> 待写入的字节
	* @retval 读取到的数据
*/
static void SPI_Touch_WriteByte(uint8_t Byte)
{
    uint8_t SendByte = Byte;
    //等待模式写入1个字节
    HAL_SPI_Transmit(&hspi2,&SendByte,1,0x0A);
}

/*
	* @name   Palette_Init
	* @brief  调色板初始化
	* @param  None
	* @retval None
*/
static void Palette_Init()
{
    //屏幕填充灰色
    TFT_LCD.FillColor(0,0,LCD_WIDTH,LCD_HEIGTH,Color_GRAY);

    //绘图区域填充白色
    TFT_LCD.FillColor(0,0,240,LCD_HEIGTH-48,Color_WHITE);

    //显示调色板
    TFT_LCD.FillColor(0,  LCD_HEIGTH-48,24,24,Color_RED);
    TFT_LCD.FillColor(24, LCD_HEIGTH-48,24,24,Color_GREEN);
    TFT_LCD.FillColor(48, LCD_HEIGTH-48,24,24,Color_BLUE);
    TFT_LCD.FillColor(72, LCD_HEIGTH-48,24,24,Color_YELLOW);
    TFT_LCD.FillColor(96, LCD_HEIGTH-48,24,24,Color_MAGENTA);
    TFT_LCD.FillColor(120,LCD_HEIGTH-48,24,24,Color_CYAN);
    TFT_LCD.FillColor(144,LCD_HEIGTH-48,24,24,Color_BROWN);
    TFT_LCD.FillColor(168,LCD_HEIGTH-48,24,24,Color_LIGHTBLUE);
    TFT_LCD.FillColor(192,LCD_HEIGTH-48,24,24,Color_GRAY);
    TFT_LCD.FillColor(216,LCD_HEIGTH-48,24,24,Color_BLACK);

    //显示坐标信息
    TFT_LCD.LCD_ShowString(0,  LCD_HEIGTH-24,"X:",  Color_GRAY,Color_RED,ASCII_font_24);
    TFT_LCD.LCD_ShowString(24, LCD_HEIGTH-24,"----",Color_GRAY,Color_RED,ASCII_font_24);
    TFT_LCD.LCD_ShowString(96, LCD_HEIGTH-24,"Y:",  Color_GRAY,Color_RED,ASCII_font_24);
    TFT_LCD.LCD_ShowString(120,LCD_HEIGTH-24,"----",Color_GRAY,Color_RED,ASCII_font_24);

    //显示画笔色彩
    TFT_LCD.FillColor(LCD_WIDTH-48, LCD_HEIGTH-24,24,24,Touch.Color_PEN);

    //显示清除画板信息
    TFT_LCD.FillColor(LCD_WIDTH-24,LCD_HEIGTH-24,24,24,Color_WHITE);
    TFT_LCD.LCD_ShowString(LCD_WIDTH-20,LCD_HEIGTH-20,"CL",Color_WHITE,Color_RED,ASCII_font_16);
}

/*
	* @name   Palette_DrawPoint
	* @brief  绘图区域画点
	* @param  x：x坐标
  *         y：y坐标
  *         Color：点的颜色
	* @retval None
*/
static void Palette_DrawPoint(uint16_t x, uint16_t y,LCD_Color_t Color)
{
    TFT_LCD.LCD_SetPointPiexl ( x-1, y-1, Color);
    TFT_LCD.LCD_SetPointPiexl (   x, y-1, Color);
    TFT_LCD.LCD_SetPointPiexl ( x+1, y-1, Color);
    TFT_LCD.LCD_SetPointPiexl ( x-1,   y, Color);
    TFT_LCD.LCD_SetPointPiexl (   x,   y, Color);
    TFT_LCD.LCD_SetPointPiexl ( x+1,   y, Color);
    //调色板边界处理
    if((y+1) < LCD_HEIGTH-48)
    {
        TFT_LCD.LCD_SetPointPiexl ( x-1, y+1, Color);
        TFT_LCD.LCD_SetPointPiexl (   x, y+1, Color);
        TFT_LCD.LCD_SetPointPiexl ( x+1, y+1, Color);
    }
}
/*
	* @name   Touch_Read_ADC
	* @brief  读取触摸屏的ADC值
	* @param  XT2046_CMD：触摸IC命令
  * @retval ADC值
*/
static uint16_t Touch_Read_ADC(uint8_t XT2046_CMD)
{
    uint8_t  i,j;
    uint16_t Value_Buf[Touch_READ_TIMES],usTemp;
    uint32_t SumValue = 0;

    //通过SPI接口循环读取Touch_READ_TIMES次数
    for(i=0; i<Touch_READ_TIMES; i++)
    {
        //选择触摸芯片: CS输出低电平
        CLR_SPI_Touch_CS;

        /* 在差分模式下，XPT2046转换需要24个时钟，8个时钟输入命令，延时一会，
       之后1个时钟去除忙信号，接着输出12位转换结果，剩下3个时钟是忽略位*/

        //发送控制命令
        SPI_Touch_WriteByte(XT2046_CMD);
        //延时一会，等待ADC转换
        for(j=0; j<100; j++);
        //读取数据
        Value_Buf[i] = SPI_Touch_ReadByte(); //获取前面7个字节，其中最高位无效
        Value_Buf[i] &= (~BIT7);             //最高位无效
        Value_Buf[i] <<= 8;                  //左移至高字节
        Value_Buf[i] += SPI_Touch_ReadByte();//获取后面5字节，其中低3位无效
        Value_Buf[i] >>= 3;	                 //右移3位，得到12位有效数据
        //禁用触摸芯片: CS输出高电平
        SET_SPI_Touch_CS;
    }

    //采样值从大到小排序排序
    for(i=0; i<(Touch_READ_TIMES-1); i++)
    {
        for(j=i+1; j<Touch_READ_TIMES; j++)
        {
            if(Value_Buf[i] < Value_Buf[j])
            {
                usTemp        = Value_Buf[i];
                Value_Buf[i]  = Value_Buf[j];
                Value_Buf[j]  = usTemp;
            }
        }
    }

    //去掉最大与最小值，求和
    for(i=1; i<Touch_READ_TIMES-1; i++)
    {
        SumValue += Value_Buf[i];
    }

    //返回平均值
    return  SumValue/(Touch_READ_TIMES-2);
}

/*
	* @name   Touch_Read_ADC_XY
	* @brief  读触摸IC的XY坐标值
	* @param  *xValue：保存读取到X轴ADC值的地址
  *         *yValue：保存读取到Y轴ADC值的地址
  * @retval TRUE:读取成功，FALSE:读取失败
*/
static uint8_t Touch_Read_ADC_XY(uint16_t *xValue, uint16_t *yValue)
{
    uint16_t xValue_Buf[2],yValue_Buf[2];
    uint16_t xValue_Error,yValue_Error;

    //读取坐标X，Y的值，各2次
    xValue_Buf[0] = Touch_Read_ADC(Touch_X_CMD);
    yValue_Buf[0] = Touch_Read_ADC(Touch_Y_CMD);
    xValue_Buf[1] = Touch_Read_ADC(Touch_X_CMD);
    yValue_Buf[1] = Touch_Read_ADC(Touch_Y_CMD);

    //计算2次采样的差值
    if(xValue_Buf[0] >= xValue_Buf[1])
        xValue_Error = xValue_Buf[0] - xValue_Buf[1];
    else
        xValue_Error = xValue_Buf[1] - xValue_Buf[0];

    if(yValue_Buf[0] >= yValue_Buf[1])
        yValue_Error = yValue_Buf[0] - yValue_Buf[1];
    else
        yValue_Error = yValue_Buf[1] - yValue_Buf[0];

    //两次采样差值超过误差，丢弃
    if((xValue_Error > Touch_Error) || (yValue_Error > Touch_Error))
    {
        return  FALSE;
    }

    //求平均
    *xValue = (xValue_Buf[0] + xValue_Buf[1]) / 2;
    *yValue = (yValue_Buf[0] + yValue_Buf[1]) / 2;

    //判断值是否有效
    if((*xValue > Touch_X_MAX) || (*xValue < Touch_X_MIN))
        return  FALSE;
    if((*yValue > Touch_Y_MAX) || (*yValue < Touch_Y_MIN))
        return  FALSE;

    //打印坐标值
    //printf("触摸屏坐标值(ADC)：X=%u,Y=%u\r\n",*xValue,*yValue);

    //返回
    return TRUE;
}

/*
	* @name   LCD_DrawCross
	* @brief  校正触摸时画十字专用
	* @param  x：十字中点x轴
  *         y：十字中点y轴
  * @retval None
*/
static void LCD_DrawCross(uint16_t x,uint16_t y)
{
    TFT_LCD.LCD_DrawLine(x-10,y,x+10,y,Color_RED);
    TFT_LCD.LCD_DrawLine(x,y-10,x,y+10,Color_RED);
}

/*
	* @name   Touch_ReadCalibrateValue
	* @brief  读取校准点坐标值
	* @param  x：x轴
  *         y：y轴
	*         *xValue：x轴坐标值
	*         *xValue：y轴坐标值
  * @retval None
*/
static uint8_t Touch_ReadCalibrateValue(uint16_t x, uint16_t y, uint16_t *xValue, uint16_t *yValue)
{
    uint8_t Cnt = 0;

    //显示校准位置
    LCD_DrawCross(x,y);
    while(1)
    {
        if(Touch_Read_ADC_XY(xValue,yValue))
        {
            //取第十次读到的值，数据更稳定
            if(Cnt++ > 10)
            {
                TFT_LCD.FillColor(0,0,240,320,Color_BLACK);
                return TRUE;
            }
        }
    }
}


/*
	* @name   Touch_Calibrate
	* @brief  触摸屏幕校准
	* @param  None
  * @retval TRUE:校准成功，FALSE:校准失败
*/

static uint8_t Touch_Calibrate()
{
    //5个校准位置，中间的校验用
    uint16_t Calibrate_xyLCD[5][2] ={
            {20,20},
            {20,LCD_HEIGTH-20},
            {LCD_WIDTH-20,LCD_HEIGTH-20},
            {LCD_WIDTH-20,20},
            {LCD_WIDTH/2,LCD_HEIGTH/2}    //屏幕中央，校验用
    };
    uint16_t xValue[5],yValue[5];         //5个校准位置对应的坐标值
    uint16_t xOpposite[2],yOpposite[2];   //计算得到对角的坐标
    uint16_t Avr_xOpposite,Avr_yOpposite; //对角坐标的平均值，用于与屏幕中央的坐标值比较
    uint8_t  i;

    //读取5个校准点的坐标值
    TFT_LCD.FillColor(0,0,240,320,Color_BLACK);
    for(i=0;i<5;i++)
    {
        Touch_ReadCalibrateValue(Calibrate_xyLCD[i][0],Calibrate_xyLCD[i][1],&xValue[i],&yValue[i]);
        //适当延时，读取下一个校准点
        HAL_Delay(800);
    }

    //将正方形的4个校准点整合成对角两点，减小触摸误差
    xOpposite[0] = (xValue[0] + xValue[1]) / 2;
    yOpposite[0] = (yValue[0] + yValue[3]) / 2;
    xOpposite[1] = (xValue[2] + xValue[3]) / 2;
    yOpposite[1] = (yValue[1] + yValue[2]) / 2;
    //计算对角两点的平均值
    Avr_xOpposite = (xOpposite[0]+xOpposite[1])/2;
    Avr_yOpposite = (yOpposite[0]+yOpposite[1])/2;

   // printf("触摸屏坐标值(ADC)：xAvr=%u,yAvr=%u\r\n",Avr_xOpposite,Avr_yOpposite);
   // printf("触摸屏坐标值(ADC)：xMid=%u,yMid=%u\r\n",xValue[4],yValue[4]);

    //对校准点进行校验
    if(Avr_xOpposite >= xValue[4])
    {
        if((Avr_xOpposite - xValue[4]) > 100)
        {
            printf("校准失败\r\n");
            TFT_LCD.LCD_ShowString(24,160,"Calibrate Fail",Color_BLACK,Color_RED,ASCII_font_24);
            HAL_Delay(1000);
            return FALSE;
        }
    }
    else
    {
        if((xValue[4] - Avr_xOpposite) > 100)
        {
            printf("校准失败\r\n");
            TFT_LCD.LCD_ShowString(24,160,"Calibrate Fail",Color_BLACK,Color_RED,ASCII_font_24);
            HAL_Delay(1000);
            return FALSE;
        }
    }

    if(Avr_yOpposite >= yValue[4])
    {
        if((Avr_yOpposite - yValue[4]) > 100)
        {
            printf("校准失败\r\n");
            TFT_LCD.LCD_ShowString(24,160,"Calibrate Fail",Color_BLACK,Color_RED,ASCII_font_24);
            HAL_Delay(1000);
            return FALSE;
        }
    }
    else
    {
        if((yValue[4] - Avr_yOpposite) > 100)
        {
            printf("校准失败\r\n");
            TFT_LCD.LCD_ShowString(24,160,"Calibrate Fail",Color_BLACK,Color_GREEN,ASCII_font_24);
            HAL_Delay(1000);
            return FALSE;
        }
    }

    //计算比例因素
    Touch_Calibrate_Para.xFactor = (float)(LCD_WIDTH - 40)  / (xOpposite[1] - xOpposite[0]);
    Touch_Calibrate_Para.yFactor = (float)(LCD_HEIGTH - 40) / (yOpposite[1] - yOpposite[0]);

    //计算偏移量
    Touch_Calibrate_Para.xOffset = (uint8_t)(Touch_Calibrate_Para.xFactor*Avr_xOpposite - LCD_WIDTH/2);
    Touch_Calibrate_Para.yOffset = (uint8_t)(Touch_Calibrate_Para.yFactor*Avr_yOpposite - LCD_HEIGTH/2);

    //设置校准标志位
    Touch_Calibrate_Para.Calibrate_Flag = Touch_Calibrate_OK;

    printf("校准成功\r\n");
    //printf("校准因素xFactor：%.2f\r\n",Touch_Calibrate_Para.xFactor);
    //printf("校准因素yFactor：%.2f\r\n",Touch_Calibrate_Para.yFactor);
   // printf("偏移量xOffset：  %u\r\n",Touch_Calibrate_Para.xOffset);
   // printf("偏移量yOffset：  %u\r\n",Touch_Calibrate_Para.yOffset);
    TFT_LCD.LCD_ShowString(12,160,"Calibrate Success",Color_BLACK,Color_GREEN,ASCII_font_24);
    HAL_Delay(1000);

    ////保存参数
    //扇区擦除
    SPI_Flash.EraseSector(Touch_Calibrate_Para_Addr);
    SPI_Flash.WriteUnfixed(&Touch_Calibrate_Para.Calibrate_Flag,Touch_Calibrate_Para_Addr,sizeof(Touch_Calibrate_Para));

    return TRUE;
}

/*
	* @name   Touch_Scan
	* @brief  触摸屏扫描
	* @param  None
  * @retval TRUE:有触摸，获取到坐标值，FALSE:无触摸
   说明：降低干扰，每次获取两次LCD屏幕坐标值，计算误差，求平均。
*/
static uint8_t Touch_Scan()
{
    uint16_t LCD_X1,LCD_Y1,LCD_X2,LCD_Y2;

    //if(HAL_GPIO_ReadPin(TP_NIRQ_GPIO_Port,TP_NIRQ_Pin) == GPIO_PIN_RESET)
    //{
    //第一次读取触摸屏的坐标值
    if(Touch.Read_ADC_XY(&Touch.ADC_X,&Touch.ADC_Y) == FALSE)
    {
        return FALSE;
    }

    //第二次计算LCD屏幕坐标值
    LCD_X1 = (uint16_t)(Touch.ADC_X*Touch_Calibrate_Para.xFactor) - Touch_Calibrate_Para.xOffset;
    LCD_Y1 = (uint16_t)(Touch.ADC_Y*Touch_Calibrate_Para.yFactor) - Touch_Calibrate_Para.yOffset;

    if(Touch.Read_ADC_XY(&Touch.ADC_X,&Touch.ADC_Y) == FALSE)
    {
        return FALSE;
    }

    //第二次计算LCD屏幕坐标值
    LCD_X2 = (uint16_t)(Touch.ADC_X*Touch_Calibrate_Para.xFactor) - Touch_Calibrate_Para.xOffset;
    LCD_Y2 = (uint16_t)(Touch.ADC_Y*Touch_Calibrate_Para.yFactor) - Touch_Calibrate_Para.yOffset;

    //误差检查
    if(LCD_X1 >= LCD_X2)
    {
        if((LCD_X1 - LCD_X2) > 2)
            return FALSE;
    }
    else
    {
        if((LCD_X2 - LCD_X1) > 2)
            return FALSE;
    }

    if(LCD_Y1 >= LCD_Y2)
    {
        if((LCD_Y1 - LCD_Y2) > 2)
            return FALSE;
    }
    else
    {
        if((LCD_Y2 - LCD_Y1) > 2)
            return FALSE;
    }

    //计算两次的平均值，得到LCD屏幕坐标值
    Touch.LCD_X = (LCD_X1 + LCD_X2)/2;
    Touch.LCD_Y = (LCD_Y1 + LCD_Y2)/2;

    if(Touch.LCD_X > (LCD_WIDTH - 1))
    {
        Touch.LCD_X = LCD_WIDTH - 1;
    }

    if(Touch.LCD_Y > (LCD_HEIGTH - 1))
    {
        Touch.LCD_X = LCD_WIDTH - 1;
    }


    //LCD屏幕上显示触摸屏的坐标值
//    TFT_LCD.LCD_ShowChar(24, LCD_HEIGTH-24,Touch.ADC_X/1000+'0',    Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(36, LCD_HEIGTH-24,Touch.ADC_X%1000/100+'0',Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(48, LCD_HEIGTH-24,Touch.ADC_X%100/10+'0',  Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(60, LCD_HEIGTH-24,Touch.ADC_X%10+'0',      Color_GRAY,Color_RED,ASCII_font_24);

//    TFT_LCD.LCD_ShowChar(120, LCD_HEIGTH-24,Touch.ADC_Y/1000+'0',    Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(132, LCD_HEIGTH-24,Touch.ADC_Y%1000/100+'0',Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(144, LCD_HEIGTH-24,Touch.ADC_Y%100/10+'0',  Color_GRAY,Color_RED,ASCII_font_24);
//    TFT_LCD.LCD_ShowChar(156, LCD_HEIGTH-24,Touch.ADC_Y%10+'0',      Color_GRAY,Color_RED,ASCII_font_24);

    return TRUE;

    //}
    //else
    //{
    //return FALSE;
    //}
}
/********************************************************
  End Of File
********************************************************/
