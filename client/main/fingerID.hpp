#ifndef __FINGERID_HPP__
#define __FINGERID_HPP__
#pragma once

//#define TEST

#include <stdint.h>
#include "UARTtrans.hpp"

#include <string.h>
#include <stdio.h>

#define PACKHEAD ((uint16_t)0xEF01)                                                                     //通信包头
#define COMMANDSIGN ((uint8_t)0x01)                                                                     //命令包标识
#define CharBuffer1 0x01
#define CharBuffer2 0x02


class IDENTIFIER_class
{
    private:

    uint32_t IDaddr = 0XFFFFFFFF;
    uint32_t IDpwd = 0x00000000;                                                                        //口令验证
    typedef struct  
    {
        uint16_t pageID;                                                                                //指纹ID
        uint16_t mathscore;                                                                             //匹配得分
    }SearchResult;

    typedef struct
    {
        uint16_t PS_max;                                                                                //指纹最大容量
        uint8_t  PS_level;                                                                              //安全等级
        uint32_t PS_addr;
        uint8_t  PS_size;                                                                               //通讯数据包大小
        uint8_t  PS_N;                                                                                  //波特率基数N
    }SysPara;

    void SendHead(void);
    void SendAddr(void);
    void SendFlag(uint8_t flag);
    void SendLength(uint16_t length);
    void Sendcmd(uint8_t cmd);
    void SendCheck(uint16_t check);
    uint8_t *JudgeStr();                                                                                //判断中断接收的数组有没有应答包
    bool AS608_Check(void);                                                                             //连接检查
    uint8_t PS_GetImage(void);                                                                          //录入图像 
    uint8_t PS_GenChar(uint8_t BufferID);                                                               //生成特征 
    uint8_t PS_Match(void);                                                                             //精确比对两枚指纹特征 
    uint8_t PS_Search(uint8_t BufferID,uint16_t StartPage,uint16_t PageNum,SearchResult *p);            //搜索指纹 
    uint8_t PS_RegModel(void);                                                                          //合并特征（生成模板） 
    uint8_t PS_StoreChar(uint8_t BufferID,uint16_t PageID);                                             //储存模板 
    uint8_t PS_DeletChar(uint16_t PageID,uint16_t N);                                                   //删除模板 
    uint8_t PS_Empty(void);                                                                             //清空指纹库 
    uint8_t PS_WriteReg(uint8_t RegNum,uint8_t DATA);                                                   //写系统寄存器 
    uint8_t PS_ReadSysPara(SysPara *p);                                                                 //读系统基本参数 
    uint8_t PS_SetAddr(uint32_t addr);                                                                  //设置模块地址 
    uint8_t PS_WriteNotepad(uint8_t NotePageNum,uint8_t *content);                                      //写记事本 
    uint8_t PS_ReadNotepad(uint8_t NotePageNum,uint8_t *note);                                          //读记事 
    uint8_t PS_HighSpeedSearch(uint8_t BufferID,uint16_t StartPage,uint16_t PageNum,SearchResult *p);   //高速搜索 
    uint8_t PS_ValidTempleteNum(uint16_t *ValidN);                                                      //读有效模板个数 
    uint8_t PS_HandShake(uint32_t *PS_Addr);                                                            //与AS608模块握手
    uint32_t PS_GetRandomCode();                                                                        //让模块发送一个随机数
    const char *EnsureMessage(uint8_t ensure);                                                          //确认码错误信息解析
    void ShowErrMessage(uint8_t ensure);



    public:

    IDENTIFIER_class();
    ~IDENTIFIER_class();

    void Add_FR(void);
    bool press_FR(void);
    void Del_FR(void);
    void Del_FR_Lib(void);

};

#endif