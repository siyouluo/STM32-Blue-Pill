/**
  ***************************************************************
  * @file    usart3.c
  * @author  Siyou luo
  * @contact siyouluo11@gmail.com
  * @version V1.0
  * @date    10-Sept-2019
  * @brief   USART3 串口3驱动程序,串口3用于和指纹模块通信
  ******************************************************************************
  * @resources
  * USART3
  * 	TX (GPIOB_Pin_10)
  *		RX (GPIOB_Pin_11)
  ******************************************************************************
  */
#include "usart3.h"
#include "usart1.h"
uint8_t USART3_RECEIEVE_QUEUE_BUF[USART3_MAX_QUEUE_BUF_SIZE];//USART3串口缓冲区
uint8_t USART3_QUEUE_PTR=0;//串口缓冲区队列尾，入队位置

//int fputc(int ch, FILE *p)
//{
//	USART_SendData(USART3,(u8)ch);
//	while(USART_GetFlagStatus(USART3,USART_FLAG_TC) != SET);
//	return ch;
//}


/**
  * @brief :判断USART3串口缓冲区是否满
  * @param :void
  * @retval :返回1:满 返回0:非满
  * @usage:if(USART3_QUEUE_FULL()==1)...	if(USART3_QUEUE_FULL()==0)...
  */
uint8_t  USART3_QUEUE_FULL(void)
{
    return (uint8_t)(USART3_QUEUE_PTR==USART3_MAX_QUEUE_BUF_SIZE);
}


/**
  * @brief	:判断USART3串口缓冲区是否空
  * @param	:void
  * @retval	:返回1:空 返回0:非空
  * @usage	:if(USART3_QUEUE_EMPTY()==1)...	if(USART3_QUEUE_EMPTY()==0)...
  */
uint8_t USART3_QUEUE_EMPTY(void)
{
    return (uint8_t)(USART3_QUEUE_PTR==0);
}

/**
  * @brief	:往USART3串口缓冲区内存入一个字节数据
  * @param	ch: uint8_t类型，写入ch
  * @retval	:1,队列满，写入失败；0，写入成功
  * @usage	:USART3_PUSH_QUEUE(0x3f)
  */
uint8_t USART3_PUSH_QUEUE(uint8_t ch)
{
    if(USART3_QUEUE_FULL())
    {
        printf("err: queue full!\n");
        return 1;
    }
    USART3_RECEIEVE_QUEUE_BUF[USART3_QUEUE_PTR]=ch;
    USART3_QUEUE_PTR++;
	return 0;
}
/**
  * @brief	:清空串口缓冲区
  * @param	:void
  * @retval	:void
  * @usage	:
  */
void USART3_CLEAR_QUEUE()
{
	USART3_QUEUE_PTR=0;
}

/**
  * @brief	:获取串口缓冲区内有效字节数
  * @param	:void
  * @retval	:uint8_t
  * @usage	:
  */
uint8_t USART3_GET_NUM_QUEUE()
{
	return USART3_QUEUE_PTR;
}
/**
  * @brief	:等待USART3接收到n个字节
  * @param	:uint8_t n
  * @retval	:0
  * @usage	:
  */
uint8_t USART3_RECIEVE_BYTES(uint8_t n)
{
	while(USART3_GET_NUM_QUEUE()<n);
	return 0;
}



/**
  * @brief	:串口USART3写一个字节数据
  * @param	ch: uint8_t 类型，从TX管脚写出
  * @retval	:void
  * @usage	:USART3_WriteByte(0x3f)
  */
void USART3_WriteByte(uint8_t ch)
{
    USART_SendData(USART3,(u8)ch);
    while(USART_GetFlagStatus(USART3,USART_FLAG_TC) != SET);
}
/**
  * @brief	:串口USART3写n个连续存储的字节数据
  * @param	n: uint8_t类型，写出的字节个数
  * @param	*p: uint8_t类型，待写出的字节数据首地址
  * @retval	:void
  * @usage	:uint8_t temp_array[n]={0x01,0x02,0x03,...};
  * @usage	:USART3_WriteBytes(n, temp_array);
  */
void USART3_WriteBytes(uint8_t n, uint8_t *p)
{
    uint8_t i;
    for(i=0; i<n; i++)
    {
        USART3_WriteByte(p[i]);
    }
}

void USART3_Init(u32 baud)
{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);


    /*  配置GPIO的模式和IO口 */
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //串口输出PB10
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
    GPIO_Init(GPIOB,&GPIO_InitStructure);  /* 初始化串口输入IO */
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //串口输入PB11
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
    GPIO_Init(GPIOB,&GPIO_InitStructure); /* 初始化GPIO */


    //USART3 初始化设置
    USART_InitStructure.USART_BaudRate = baud;//波特率设置
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART3, &USART_InitStructure); //初始化串口3

    USART_Cmd(USART3, ENABLE);  //使能串口3

    USART_ClearFlag(USART3, USART_FLAG_TC);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启相关中断

    //Usart3 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//串口3中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能

    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、


}

/*******************************************************************************
* 函 数 名         : USART3_IRQHandler
* 函数功能		   : USART3中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void USART3_IRQHandler(void)                	//串口1中断服务程序
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
    {
		USART3_PUSH_QUEUE(USART_ReceiveData(USART3));
    }
    USART_ClearFlag(USART3,USART_FLAG_TC);
}
