#ifndef _BANK_H
#define _BANK_H
#define TYPE_OPEN 8001          //开户
#define TYPE_CLOSE 8002         //清户
#define TYPE_SAVE 8003          //存款
#define TYPE_WITHDRAW 8004      //取款
#define TYPE_QUERY 8005         //查询
#define TYPE_TRANSFER 8006      //转账
//账户结构
typedef struct tag_Account{
    int id;             //账号
    char name[256];     //户名
    char passwd[9];     //密码
    double balance;     //余额
} ACCOUNT;
//开户请求
typedef struct tag_OpenRequest{
    char name[256];     //户名
    char passwd[9];     //密码
    double balance;     //初始余额 

} OPEN_REQUEST;
//开户响应
typedef struct tag_OpenRespond{
    char error[512];    //错误消息
    int id;             //账号
} OPEN_RESPOND;
//清户请求
typedef struct tag_CloseRequest{
    int id;             //账号
    char name[256];     //户名
    char passwd[9];     //密码
} CLOSE_REQUEST;
//清户响应
typedef struct tag_CloseRespond{
    char error[512];    //错误消息
    double balance;     //余额
} CLOSE_RESPOND;
//存款请求
typedef struct tag_SaveRequest{
    int id;             //账号
    char name[256];     //户名
    double money;       //存款金额
} SAVE_REQUEST;
//存款响应
typedef struct tag_SaveRespond{
    char error[512];    //错误消息
    double balance;     //余额
} SAVE_RESPOND;
//取款请求
typedef struct tag_WithdrawRequest{
    int id;             //账号
    char name[256];     //户名
    char passwd[9];     //密码
    double money;       //取款金额
} WITHDRAW_REQUEST;
//取款响应
typedef struct tag_WithdrawRespond{
    char error[512];    //错误消息
    double balance;     //余额
} WITHDRAW_RESPOND;
//查询请求
typedef struct tag_QueryRequest{
    int id;             //账号
    char name[256];     //户名
    char passwd[9];     //密码
} QUERY_REQUEST;
//查询响应
typedef struct tag_QUERYRespond{
    char error[512];    //错误消息
    double balance;     //余额
} QUERY_RESPOND;
//转账请求
typedef struct tag_TransferRequest{
    int id[2];          //账号
    char name[2][256];  //户名
    char passwd[9];     //密码
    double money;       //转账金额
} TRANSFER_REQUEST;
//转账响应
typedef struct tag_TransferRespond{
    char error[512];    //错误消息
    double balance;     //余额
} Transfer_RESPOND;
#endif //_BANK_H