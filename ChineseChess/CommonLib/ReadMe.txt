协议库

1，通用协议格式
STX(0X02)——Command——Data——ETX(0X03)

说明：STX-----------消息开始符，特殊字符0x02
      ETX-----------消息结束符，特殊字符0x03
	  Command-------命令，使用数字表示
	  Data----------命令数据集，每一条命令都用对应的数据



2，命令详细说明
2.1 命令
Command				shorthand	code				direction                           description
Login     Command-->   L--->  1001					C->S                                登录
Login Rec Command-->   LC-->  1002					S->C								登录回应
Move      Command-->   M--->  2001					C->S								移动（走棋命令）
Move  Rec Command-->   MR-->  2002					S->C								移动回复
Select Room Command--> SR--> 3001					C->S								选择房间
Select Room Rec Command--> SRR--> 3002				S->C								选择房间回复
Select Desk Command--> SD--> 4001					C->S								选择房间桌子
Select Desk Rec Command SDR--> 4002					S->C								选择房间桌子回复
Start Chess Command---> SC--> 5001					S->C								开始走棋
Start Chess Rec Command--> SCR-->  5002				C->S								开始走棋回复
Authorize Error Command--> AE--> 60001				S->C								验证失败
Go To War Command--> GTW-->      70001              C->S								参战
Go To War Rec Command--> GTWR--> 70002              S->C								参战回复


2.2 数据说明
Login Data-->userName,password,token
Login Rec Data-->userName,token,1/0

Select Room Data-->userName,token,room
Select Room Rec Data-->userName,1/0

Select Desk Data-->userName,token,room,desk
Select Desk Rec Data-->userName,1/0

Start Data-->userName,sdPlayer
Start Rec Data-->userName,1/0

Go To War Data-->userName,token,room,desk
Go To War Rec Data-->userName,1/0

Move Data-->userName,token,room,desk,sdPlayer,srcX,srcY,destX,destY
Move Rec Data-->userName,1/0

Authorize Error Data-->userName

数据项说明：userName-----------------用户名称
            token--------------------用户令牌，当用户登录后，由服务站随机产生，客户端每次请求必须带token，否者试为非法用户；
			password-----------------用户密码
			1/0----------------------表示请求结果，1为成功；0为失败。
			room---------------------房间号
			desk---------------------桌号
			sdPlayer-----------------用户持棋子的颜色
			srcX---------------------发送端的始点横方向上的格子数
			srcY---------------------发送端的始点纵方向上的格子数
			destX--------------------发送端的终点横方向上的格子数
			destY--------------------发送端的终点纵方向上的格子数


3 协议消息例子
eg:
L   -----------> 0x021001,100001,ssddyy,0x03
LC  -----------> 0x021002,100001,AB0EFGG11232323SSSS0x03
M   -----------> 0x022001,100001,AB0EFGG11232323SSSS,r100,rd01,1,0,0,0,1
MR  -----------> 0x022002,100001,AB0EFGG11232323SSSS,1