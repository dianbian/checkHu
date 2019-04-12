#ifndef _BASEDEFINE_H_
#define _BASEDEFINE_H_

//1 3 5 7表示风牌东南西北(16)
//11 13 15表示箭牌中发白(12)
//21-29表示万字牌(36)
//31-39表示饼子牌(36)
//41-49表示条子牌(36)
//51-58表示花牌春夏秋冬梅兰竹菊(8)

enum //定义牌的类型
{
	CARD_TYPE_FENG = 0,		//东南西北风
	CARD_TYPE_ZI,			//白发中字
	CARD_TYPE_WAN,			//万
	CARD_TYPE_TIAO,			//条
	CARD_TYPE_TONG,			//筒
	CARD_TYPE_HUA,			//花
};

enum //定义搭子的类型
{
	SPECIAL_TYPE_NONE 	= 0x00,		//空
	SPECIAL_TYPE_PENG	= 0x01,		//碰
	SPECIAL_TYPE_SHUN = 0x02,		//顺子
	SPECIAL_TYPE_MINGGANG = 0x04,	//明杠
	SPECIAL_TYPE_ANGANG = 0x08,		//暗杠
	SPECIAL_TYPE_PENGGANG = 0x10,   //碰杠，面下杠
};


enum//胡牌的计分类型
{
	HU_NO = 0x0000,
	HUTYPE_1_DSX = 0x00000001,		//大四喜
	HUTYPE_1_DSY = 0x00000002,		//大三元
	HUTYPE_1_LYS = 0x00000004,		//绿一色
	HUTYPE_1_JLBD = 0x00000008,		//九莲宝灯
	HUTYPE_1_4G = 0x00000010,			//四杠
	HUTYPE_1_L7D = 0x00000020,		//连七对
	HUTYPE_1_13Y = 0x00000040,		//十三幺
	HUTYPE_1_QYJ = 0x00000080,		//清幺久
	HUTYPE_1_XSX = 0x00000100,		//小四喜
	HUTYPE_1_XSY = 0x00000200,		//小三元
	HUTYPE_1_ZYS = 0x00000400,		//字一色
	HUTYPE_1_4AK = 0x00000800,		//四暗刻
	HUTYPE_1_1SSLH = 0x00001000,		//一色双龙会
	HUTYPE_1_1SSTS = 0x00002000,		//一色四同顺
	HUTYPE_1_1SSJG = 0x00004000,		//一色四节高
	HUTYPE_1_1SSBG = 0x00008000,		//一色四步高
	HUTYPE_1_3G	 = 0x00010000,		//三杠
	HUTYPE_1_HYJ = 0x00020000,		//混幺九
	HUTYPE_1_7D = 0x00040000,		//七对
	HUTYPE_1_7XBK = 0x00080000,		//七星不靠
	HUTYPE_1_QSK = 0x00100000,		//全双刻
	HUTYPE_1_Q1S = 0x00200000,		//清一色
	HUTYPE_1_1S3TS = 0x00400000,		//一色三同顺
	HUTYPE_1_1S3JG = 0x00800000,		//一色三节高
	HUTYPE_1_QD = 0x01000000,		//全大
	HUTYPE_1_QZ = 0x02000000,		//全中
	HUTYPE_1_QX = 0x04000000,		//全小
	HUTYPE_1_QL = 0x08000000,		//清龙
	HUTYPE_1_3SSLH = 0x10000000,		//三色双龙会
	HUTYPE_1_1S3BG = 0x20000000,		//一色三步高
	HUTYPE_1_QDW = 0x40000000,		//全带五
	HUTYPE_1_3TK = 0x80000000,		//三同刻

	HUTYPE_2_3AK = 0x00000001,		//三暗刻
	HUTYPE_2_QBK = 0x00000002,		//全不靠
	HUTYPE_2_ZHL = 0x00000004,		//组合龙
	HUTYPE_2_DY5 = 0x00000008,		//大于五
	HUTYPE_2_XY5 = 0x00000010,		//小于五
	HUTYPE_2_3FK = 0x00000020,		//三风刻
	HUTYPE_2_HL = 0x00000040,		//花龙
	HUTYPE_2_TBD = 0x00000080,		//推不倒
	HUTYPE_2_3S3TS = 0x00000100,		//三色三同顺
	HUTYPE_2_3S3JG = 0x00000200,		//三色三节高
	HUTYPE_2_WFH = 0x00000400,		//无番胡
	HUTYPE_2_MSHC = 0x00000800,		//妙手回春
	HUTYPE_2_HDLY = 0x00001000,		//海底捞月
	HUTYPE_2_GSKH = 0x00002000,		//杠上开花
	HUTYPE_2_QGH = 0x00004000,		//抢杠胡
	HUTYPE_2_PPH = 0x00008000,		//碰碰胡
	HUTYPE_2_H1S = 0x00010000,		//混一色
	HUTYPE_2_3S3BG = 0x00020000,		//三色三步高
	HUTYPE_2_5MQ = 0x00040000,		//五门齐
	HUTYPE_2_QQR = 0x00080000,		//全求人
	HUTYPE_2_SAG = 0x00100000,		//双暗杠
	HUTYPE_2_SJK = 0x00200000,		//双箭刻
	HUTYPE_2_QDY = 0x00400000,		//全带幺
	HUTYPE_2_BQR = 0x00800000,		//不求人
	HUTYPE_2_SMG = 0x01000000,		//双明杠
	HUTYPE_2_HJZ = 0x02000000,		//和绝张
	HUTYPE_2_JK = 0x04000000,		//箭刻
	HUTYPE_2_QFK = 0x08000000,		//圈风刻
	HUTYPE_2_MFK = 0x10000000,		//门风刻
	HUTYPE_2_MQQ = 0x20000000,		//门前清
	HUTYPE_2_PH = 0x40000000,		//平和
	HUTYPE_2_STK = 0x80000000,		//双同刻

	HUTYPE_3_4G1 = 0x00000003,		//四归一	最多2个占2位	
	HUTYPE_3_SAK = 0x00000004,		//双暗刻
	HUTYPE_3_AG = 0x00000008,		//暗杠
	HUTYPE_3_DY = 0x00000010,		//断幺
	HUTYPE_3_YBG = 0x00000060,		//一般高	最多2个占2位
	HUTYPE_3_XXF = 0x00000180,		//喜相逢	最多2个占2位
	HUTYPE_3_LL = 0x00000200,		//连六
	HUTYPE_3_LSF = 0x00000C00,		//老少副	最多2个占2位
	HUTYPE_3_YJK = 0x00007000,		//幺九刻	最多4个占3位
	HUTYPE_3_MG = 0x00008000,		//明杠
	HUTYPE_3_Q1M = 0x00010000,		//缺一门
	HUTYPE_3_WZ = 0x00020000,		//无字
	HUTYPE_3_BZ = 0x00040000,		//边张
	HUTYPE_3_KZ = 0x00080000,		//坎张
	HUTYPE_3_DDJ = 0x00100000,		//单钓将
	HUTYPE_3_ZM = 0x00200000,		//自摸
	HUTYPE_3_HP = 0x03C00000,		//花牌	最多8个占 4位
	HUTYPE_3_TING = 0x04000000,		//听牌
	HUTYPE_3_ZHUANG = 0x08000000	//庄家
};


enum//胡牌的计分
{
	FAN_DSX = 88,		//大四喜
	FAN_DSY = 88,		//大三元
	FAN_LYS = 88,		//绿一色
	FAN_JLBD = 88,		//九莲宝灯
	FAN_4G = 88,			//四杠
	FAN_L7D = 88,		//连七对
	FAN_13Y = 88,		//十三幺
	FAN_QYJ = 64,		//清幺久
	FAN_XSX = 64,		//小四喜
	FAN_XSY = 64,		//小三元
	FAN_ZYS = 64,		//字一色
	FAN_4AK = 64,		//四暗刻
	FAN_1SSLH = 64,		//一色双龙会
	FAN_1SSTS = 48,		//一色四同顺
	FAN_1SSJG = 48,		//一色四节高
	FAN_1SSBG = 32,		//一色四步高
	FAN_3G = 32,		//三杠
	FAN_HYJ = 32,		//混幺九
	FAN_7D = 24,		//七对
	FAN_7XBK = 24,		//七星不靠
	FAN_QSK = 24,		//全双刻
	FAN_Q1S = 24,		//清一色
	FAN_1S3TS = 24,		//一色三同顺
	FAN_1S3JG = 24,		//一色三节高
	FAN_QD = 24,		//全大
	FAN_QZ = 24,		//全中
	FAN_QX = 24,		//全小
	FAN_QL = 16,		//清龙
	FAN_3SSLH = 16,		//三色双龙会
	FAN_1S3BG = 16,		//一色三步高
	FAN_QDW = 16,		//全带五
	FAN_3TK = 16,		//三同刻

	FAN_3AK = 16,		//三暗刻
	FAN_QBK = 12,		//全不靠
	FAN_ZHL = 12,		//组合龙
	FAN_DY5 = 12,		//大于五
	FAN_XY5 = 12,		//小于五
	FAN_3FK = 12,		//三风刻
	FAN_HL = 8,		//花龙
	FAN_TBD = 8,		//推不倒
	FAN_3S3TS = 8,		//三色三同顺
	FAN_3S3JG = 8,		//三色三节高
	FAN_WFH = 8,		//无番胡
	FAN_MSHC = 8,		//妙手回春
	FAN_HDLY = 8,		//海底捞月
	FAN_GSKH = 8,		//杠上开花
	FAN_QGH = 8,		//抢杠胡
	FAN_PPH = 6,		//碰碰胡
	FAN_H1S = 6,		//混一色
	FAN_3S3BG = 6,		//三色三步高
	FAN_5MQ = 6,		//五门齐
	FAN_QQR = 6,		//全求人
	FAN_SAG = 6,		//双暗杠
	FAN_SJK = 6,		//双箭刻
	FAN_QDY = 4,		//全带幺
	FAN_BQR = 4,		//不求人
	FAN_SMG = 4,		//双明杠
	FAN_HJZ = 4,		//和绝张
	FAN_JK = 2,		//箭刻
	FAN_QFK = 2,		//圈风刻
	FAN_MFK = 2,		//门风刻
	FAN_MQQ = 2,		//门前清
	FAN_PH = 2,		//平和
	FAN_4G1 = 2,		//四归一

	FAN_STK = 2,		//双同刻
	FAN_SAK = 2,		//双暗刻
	FAN_AG = 2,		//暗杠
	FAN_DY = 2,		//断幺
	FAN_YBG = 1,		//一般高
	FAN_XXF = 1,		//喜相逢
	FAN_LL = 1,		//连六
	FAN_LSF = 1,		//老少副
	FAN_YJK = 1,		//幺九刻
	FAN_MG = 1,		//明杠
	FAN_Q1M = 1,		//缺一门
	FAN_WZ = 1,		//无字
	FAN_BZ = 1,		//边张
	FAN_KZ = 1,		//坎张
	FAN_DDJ = 1,		//单钓将
	FAN_ZM = 1,		//自摸
	FAN_HP = 1,			//花牌
	FAN_TING = 2,		//听牌
	FAN_ZHUANG = 2		//庄家
};

//牌的额外属性
enum{
	CARDTYPE_LASTGOT = 0x00000001,		//牌墙的最后一张牌
	CARDTYPE_LASTOUT = 0x00000002,		//打出的最后一张牌
	CARDTYPE_AFTERG = 0x00000004,		//自家杠牌后摸的牌
	CARDTYPE_STOPG = 0x00000008,		//抢杠的牌
	CARDTYPE_LASTLEFT = 0x00000010		//胡的牌只剩下一张
};


#endif
