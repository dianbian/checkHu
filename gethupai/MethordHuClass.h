#ifndef __METHORDHUCLASS_H__
#define __METHORDHUCLASS_H__

#include <vector>
#include <map>
#include <string>
#include <list>
#include "MJCard.h"

class MethordHuClass
{
public:

	bool CheckCardPile(int Cards[49], int JIANG);
	bool CheckCardPile(int Cards[49], std::vector<CMjCardPile > &result);

    bool GetGroup(int Cards[49], std::multimap <char, std::vector<CMjCardPile> > &g_result);


	/*
	Cards	已加入最后一张牌的手牌状态
	p_desk	落桌牌信息
	s_fan	番型输出
	maxfannum	最大总番数输出
	feng	玩家的风位
	isZiMo	是否为自摸
	lastcardvalue	胡的是哪张牌
	cardtypeEX		胡的牌的额外属性，包括是否是最后一张牌什么的
	justone			是否单钓胡的牌
	输出 bool 是否听牌
	*/
    bool GetFans(int Cards[49], std::list<CMjCardPile>& p_desk, unsigned int s_fan[],int &maxfannum, int feng, bool isZiMo, char lastcardvalue, int cardtypeEX, bool justone,bool isTing,int num_hua);

	/*
		Cards	未加入最后一张牌的手牌状态
		p_desk	落桌牌信息
		cardting	可以听的牌输出到该容器内
		输出 bool 是否听牌
	*/
	bool CheckTing(int Cards[49], std::list<CMjCardPile>& p_desk, std::vector<char> &cardting);

	/*
	Cards	加入最后一张牌的手牌状态
	p_desk	落桌牌信息
	输出 bool 是否可胡
	*/
	bool CheckHu(int Cards[49], std::list<CMjCardPile>& p_desk);

    static MethordHuClass* getInstance();

    //检测是否胡大四喜
	bool CheckD4X_HU(std::vector <int> &AllCard);
    //检则是否胡大三元
	bool CheckD3Y_HU(std::vector <int> &AllCard);
    //检测是否胡绿一色
	bool CheckL1S_HU(std::vector <int> &AllCard);
    //检测是否胡九莲宝灯
	bool Check9LBD_HU(std::vector <int> &AllCard, int Card[49], std::list<CMjCardPile >& p_desk);
    //检测是否胡四杠
	bool Check4Gang_HU(int &num_angang, int &num_minggang);
    //检测是否胡连七对
	bool CheckL7D_HU(std::vector <int> &AllCard);
    //检测是否胡十三幺
	bool Chekc13Y_HU(int Card[]);
    //检测是否胡清幺九
	bool CheckQY9_HU(std::vector <int> &AllCard);
    //检测是否胡小四喜
	bool CheckX4X_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否胡小三元
	bool CheckX3Y_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否胡字一色
	bool CheckZ1S_HU(std::vector <int> &AllCard);
    //检测是否四暗刻
	bool Check4AK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否一色双龙会
	bool Check1S2LH_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk, std::vector <int> &AllCard);
    //检测是否一色四同顺
	bool Check1S4TS_HU(std::vector <int> &AllCard,std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否一色四节高
	bool Check1S4JG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否一色四步高
	bool Check1S4BG_HU(std::vector <int> &AllCard, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否三杠
	bool Check3Gang_HU(int &num_angang, int &num_minggang);
    //检测是否混幺九
	bool CheckHY9_HU(std::vector <int> &AllCard);
    //检测是否七对
	bool Check7D_HU(int Card[]);
    //检测是否七星不靠
	bool Check7XBK_HU(std::vector <int> &AllCard);
    //检测是否全双刻？
	bool CheckQSK_HU(std::vector <int> &AllCard);
    //清一色
	int CheckQ1S_HU(std::vector <int> &AllCard);
    //检测是否一色三同顺
	bool Check1S3TS_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否一色三节高
	bool Check1S3JG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否全大
	bool CheckQD_HU(std::vector <int> &AllCard);
    //检测是否全中
	bool CheckQZ_HU(std::vector <int> &AllCard);
    //检测是否全小
	bool CheckQX_HU(std::vector <int> &AllCard);
    //检测是否青龙
	bool CheckQL_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //检测是否三色双龙会
	bool Check3S2LH_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk, std::vector <int> &AllCard);
    //检测是否一色三步高
	bool Check1S3BG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //全带五
	bool CheckQD5_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //三同刻
	bool Check3TK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //三暗刻
	bool Check3AK_HU(int &angangnum, std::vector<CMjCardPile> &p_hand);
	//全不靠
	bool CheckQBK_HU(std::vector <int> &AllCard);
    //组合龙	兼容全不靠
	bool CheckZHL_HU(int Card[49],bool IsQBK = false);
	//同样用于检测组合龙,该函数还输出番型信息	此检测不做组合龙与全不靠的兼容检测 
	bool CheckZHL_HU(int Card[49], unsigned int s_fan[], int &maxfannum, std::list<CMjCardPile >& p_desk, int feng, bool isZiMo, char lastcardvalue, bool justone);
    //大于五
	bool CheckDY5_HU(std::vector <int> &AllCard);
    //小于五
	bool CheckXY5_HU(std::vector <int> &AllCard);
    //三风刻
	bool Check3Fk_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //花龙
	bool CheckHuaL_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //推不倒
	bool CheckTBD_HU(std::vector <int> &AllCard);
    //三色三同顺
	bool Check3S3TS_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //三色三节高
	bool Check3S3JG_HU( std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //无番和
    bool CheckWFH_HU();
    //妙手回春
    bool CheckMSHC_HU();
    //海底捞月
    bool CheckHDLY_HU();
    //杠上开花
    bool CheckGSKH_HU();
    //抢杠胡
    bool CheckQGH_HU();
    //碰碰和
	bool CheckPPH_HU(int &num_peng,int &num_angang, int &num_minggang, std::vector<CMjCardPile> &p_hand);
    //混一色
	bool CheckHYS_HU(std::vector <int> &AllCard);
    //三色三步高
	bool Check3S3BG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //五门齐
	bool CheckWMQ_HU(std::vector <int> &AllCard);
    //全求人
	bool CheckQQR_HU(bool isZiMo, int &num_angang, std::vector<CMjCardPile> &p_hand);
    //双箭刻
	bool CheckSJK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //全带幺
	bool CheckQDY_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //不求人
	bool CheckBQR_HU(bool isZiMo, std::list<CMjCardPile >& p_desk);
    //和绝张
    bool CheckHJZ_HU(bool isJue = false);
    //箭刻
	bool CheckJKE_HU(std::vector <int> &AllCard);
    //圈风刻
    bool CheckQFK_HU();
    //门风刻
	bool CheckMFK_HU(int &feng, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //门前清
	bool CheckMQQ_HU(bool isZiMo, std::list<CMjCardPile >& p_desk);
    //平和
	bool CheckPHe_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //四归一
	int CheckSGY_HU(std::vector <int> &AllCard, std::list<CMjCardPile >& p_desk);
    //双同刻
	bool CheckSTK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //双暗刻
	bool CheckSAK_HU(int &angangnum,std::vector<CMjCardPile> &p_hand);
    //暗杠
	bool CheckANG_HU(int &angangnum);
    //断幺
	bool CheckDUY_HU(std::vector <int> &AllCard);
    //一般高
	int CheckYBG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //喜相逢
	int CheckXXF_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //连六
	bool CheckLLI_HU(int Card[49]);
    //老少副
	int CheckLSF_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //幺九刻
	int CheckYJK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk);
    //明杠
	bool CheckMGA_HU(int &num_minggang);
    //缺一门
	bool CheckQ1M_HU(std::vector <int> &AllCard);
    //无字
	bool CheckMYZ_HU(std::vector <int> &AllCard);
    //边张
	bool CheckPBH_HU(std::vector<CMjCardPile> &p_hand, char lastcardvalue,bool justone);
    //坎张
	bool CheckKZH_HU(std::vector<CMjCardPile> &p_hand, char lastcardvalue, bool justone);
    //单调将
	bool CheckDDJ_HU(char jiang, char lastcardvalue, bool justone);
    //自摸
    bool CheckZMH_HU(bool isZiMo = false);
    //花牌
    bool CheckHUAP_HU();

private:

	static char alltypeCard[34];	//所有牌的值
	static char yaoCard[13];	//所有幺牌的值
};

#endif 
