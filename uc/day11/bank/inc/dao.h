#ifndef  _DAO_H
#define  _DAO_H
#include "../inc/bank.h"
//生成唯一的账号
int genid(void); 
//保存账号信息
int save(const ACCOUNT* acc);
//获取账户信息
int get(int id,ACCOUNT* acc);
//更新账号信息
int update(const ACCOUNT* acc);
//删除账户信息
int delete(int id);
#endif // _DAO_H