#include "MethordHuClass.h"
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <set>
using namespace std;

int   Remain(int   Cards[49])
{
	int   sum = 0;
	for (int i = 0; i < 49; i++)
		sum += Cards[i];
	return   sum;
}

char MethordHuClass::alltypeCard[34] = { 1, 3, 5, 7, 11, 13, 15, 21, 22, 23, 24, 25, 26, 27,28, 29, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 45, 46, 47, 48, 49 };
char MethordHuClass::yaoCard[13] = { 1, 3, 5, 7, 11, 13, 15, 21, 29, 31, 39, 41, 49 };

static MethordHuClass* m_pInstance = NULL;

MethordHuClass*  MethordHuClass::getInstance()
{
	if (m_pInstance == NULL){
		m_pInstance = new MethordHuClass();
	}
	return m_pInstance;
}

bool MethordHuClass::CheckCardPile(int Cards[49], int JIANG){


		//   将牌标志，即牌型“三三三三二”中的“二”    
	int nums = Remain(Cards);

	if (!Remain(Cards))  		{

		return   true;
	}           //   递归退出条件：如果没有剩牌，则和牌返回。    
	int i;
    for (i = 0; i < 49; i++){
		if (Cards[i] != 0){
			break;
		}                       //   找到有牌的地方，i就是当前牌,   PAI[i]是个数    
	}
    //printf("i   =   %d\n", i);                         //   跟踪信息

	//   4张组合(杠子)    
	if (Cards[i] >= 4)                               //   如果当前牌数等于4张    
	{
		Cards[i] = 1;                                     //   除开全部4张牌    
		if (CheckCardPile(Cards, JIANG)) {
			Cards[i] = 4;
			return   true;
		}//   如果剩余的牌组合成功，和牌    
		Cards[i] = 4;                                     //   否则，取消4张组合    
	}

	//   3张组合(大对)    
	if (Cards[i] >= 3)                               //   如果当前牌不少于3张    
	{
		Cards[i] -= 3;                                   //   减去3张牌    
		if (CheckCardPile(Cards, JIANG))  {
			Cards[i] += 3;
			return   true;
		}//   如果剩余的牌组合成功，和牌    
		Cards[i] += 3;                                   //   取消3张组合    
	}

	//   2张组合(将牌)    
	if (!JIANG   &&   Cards[i] >= 2)           //   如果之前没有将牌，且当前牌不少于2张    
	{
		JIANG = 1;                                       //   设置将牌标志    
		Cards[i] -= 2;                                   //   减去2张牌    
		if (CheckCardPile(Cards, JIANG)) {
			Cards[i] += 2;                                   //   取消2张组合    
			JIANG = 0;
			return   true;
		}//   如果剩余的牌组合成功，和牌    
		Cards[i] += 2;                                   //   取消2张组合    
		JIANG = 0;                                       //   清除将牌标志    
	}


    if (i >15 && i < 47)   {               //   “东南西北中发白”没有顺牌组合，不和
		//   顺牌组合，注意是从前往后组合！      //   排除数值为8和9的牌   
		if (Cards[i + 1] > 0 && Cards[i + 2] > 0 && Cards[i] > 0)             //   如果后面有连续两张牌    
		{
			Cards[i]--;
			Cards[i + 1]--;
			Cards[i + 2]--;                                     //   各牌数减1    
			if (CheckCardPile(Cards, JIANG)) {
				Cards[i]++;
				Cards[i + 1]++;
				Cards[i + 2]++;
				return   true;
			}//   如果剩余的牌组合成功，和牌    
			Cards[i]++;
			Cards[i + 1]++;
			Cards[i + 2]++;                                     //   恢复各牌数    
		}
	}


	//   无法全部组合，不和！    
	return   false;
}

bool MethordHuClass::CheckCardPile(int Cards[49], std::vector<CMjCardPile> &result)
{
	int nums = Remain(Cards);

	// 递归退出条件：如果没有剩牌，则和牌返回。
	if (nums == 0){
		return   true;
	}

	CMjCardPile p_temp;	//本循环减掉的搭子

	//找到有牌的地方，i就是当前牌,   Cards[i]是个数   
	int i;
	for (i = 0; i < 49; i++){
		if (Cards[i] != 0){
			break;
		}                        
	}

    //printf("i   =   %d\n", i);							//跟踪信息
	
	if (Cards[i] >= 3)	//优先提取碰
	{
		Cards[i] -= 3;
		if (CheckCardPile(Cards, result)) {				//递归，如果剩余牌满足搭子，外加减去的搭子，搭子分解成功
			Cards[i] += 3;
			p_temp.SetCardPile(i + 1,SPECIAL_TYPE_PENG);
			result.push_back(p_temp);
			return   true;
		}
		Cards[i] += 3;  
	}

    if (i >= 20 && i<47){//只有万条筒才可以组成顺子
		if (Cards[i + 1] > 0 && Cards[i + 2] > 0 && Cards[i] > 0)             //如果后面有连续两张牌    
		{
			Cards[i]--;
			Cards[i + 1]--;
			Cards[i + 2]--;                                     //   各牌数减1    
			if (CheckCardPile(Cards, result)) {
				Cards[i]++;
				Cards[i + 1]++;
				Cards[i + 2]++;
				p_temp.SetCardPile(i + 1, SPECIAL_TYPE_SHUN);
				result.push_back(p_temp);
				return   true;
			}//   如果剩余的牌组合成功，和牌    
			Cards[i]++;
			Cards[i + 1]++;
			Cards[i + 2]++;                                     //   恢复各牌数    
		}
	}

	//无法全部组合，不和！    
	return   false;
}

//如果有三连刻，转换成三同顺
bool Check3LP(std::vector<CMjCardPile>& p_source){
	vector<char> v_peng;

	for (std::vector<CMjCardPile>::iterator it = p_source.begin(); it != p_source.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG)
			v_peng.push_back(it->GetPileFirstCard());
	}

	if (v_peng.size() < 3) return false;
	sort(v_peng.begin(), v_peng.end());

	for (int i = 0; i != v_peng.size() - 2; i++){
        if (v_peng[i + 2] == v_peng[i] + 2 && ((v_peng[i+2]/10) == (v_peng[i]/10))){
			for (std::vector<CMjCardPile>::iterator it = p_source.begin(); it != p_source.end(); it++){
				if (it->GetPileType() == SPECIAL_TYPE_PENG &&it->GetPileFirstCard() >= v_peng[i] && it->GetPileFirstCard() <= v_peng[i + 2])
					it->SetCardPile(v_peng[i], SPECIAL_TYPE_SHUN);
			}
			return true;
		}
	}

	return false;
}

//计算暗刻数量 自摸组成的刻子不算暗刻
int GetAKNum(int& num_angang, std::vector<CMjCardPile> &p_hand, char lastcard, bool isZiMo){
	int num_AK = num_angang;

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG && ((!(it->GetPileFirstCard() == lastcard)) || isZiMo)){
			num_AK++;
		}
	}

	return num_AK;
}
//获取所有胡牌组合
bool MethordHuClass::GetGroup(int Cards[49], std::multimap <char, std::vector<CMjCardPile> > &g_result)
{
	int nums = Remain(Cards);

	if (nums % 3 != 2){
		return false;
	}

	for (char i = 0; i < 49; i++){
		if (Cards[i] >= 2){
			Cards[i] -= 2;
			std::vector<CMjCardPile> p_temp;
			if (CheckCardPile(Cards, p_temp))
			{
				g_result.insert(make_pair(i + 1, p_temp));	//满足条件的组合返回

				if (Check3LP(p_temp))
					g_result.insert(make_pair(i + 1, p_temp));
			}
			Cards[i] += 2;
		}
	}

	return (g_result.size() > 0);
}

bool MethordHuClass::CheckTing(int Cards[49], std::list<CMjCardPile>& p_desk, vector<char> &cardting)
{
	std::vector <int> AllCard;
	size_t p_size = p_desk.size();
	for (int i = 0; i != 34; i++){
        if(Cards[alltypeCard[i]-1] == 4)
            continue;

        Cards[alltypeCard[i]-1] +=1;
		AllCard.clear();

        for (int x = 0; x < 49; x++){
            for (int y = 0; y < Cards[x]; y++)
			{
                AllCard.push_back(x + 1);
			}
		}

		//检测特殊牌型

        if (p_size == 0 && Chekc13Y_HU(Cards)){
			cardting.push_back(alltypeCard[i]);
		}
        else if (p_size == 0 && Check7D_HU(Cards)){
			cardting.push_back(alltypeCard[i]);
		}
        else if (CheckQBK_HU(AllCard)){
			cardting.push_back(alltypeCard[i]);
		}
        else if (CheckZHL_HU(Cards)){
			cardting.push_back(alltypeCard[i]);
		}
		else if (CheckCardPile(Cards, false)){
			cardting.push_back(alltypeCard[i]);
		}

        Cards[alltypeCard[i]-1] -= 1;
	}

	return (cardting.size() != 0);
}

bool MethordHuClass::CheckHu(int Cards[49], std::list<CMjCardPile>& p_desk)
{
	std::vector <int> AllCard;
	size_t p_size = p_desk.size();

	for (int x = 0; x < 49; x++){
		for (int y = 0; y < Cards[x]; y++)
		{
			AllCard.push_back(x + 1);
		}
	}

	//检测特殊牌型

	if (p_size == 0 && Chekc13Y_HU(Cards)){
		return true;
	}
	else if (p_size == 0 && Check7D_HU(Cards)){
		return true;
	}
	else if (CheckQBK_HU(AllCard)){
		return true;
	}
	else if (CheckZHL_HU(Cards)){
		return true;
	}
	else if (CheckCardPile(Cards, false)){
		return true;
	}

	return false;
}


bool MethordHuClass::GetFans(int Cards[49], std::list<CMjCardPile >& p_desk, unsigned int s_fan[], int &maxfannum, int feng, bool isZiMo, char lastcardvalue, int cardtypeEX, bool justone, bool isTing, int num_hua)
{
	size_t p_size = p_desk.size();
	//下面定义一系列统计数据
	std::vector <int> AllCard; //所有手牌 序列形式
	int temp_Cards[49];			//所有手牌	key-num形式

	memcpy(temp_Cards, Cards, sizeof(temp_Cards));

	for (int i = 0; i < 49; i++){
		for (int j = 0; j < Cards[i]; j++)
		{
			AllCard.push_back(i + 1);
		}
    }

	bool is_7d = false;

	if (p_size == 0 && Chekc13Y_HU(Cards)){
		s_fan[0] |= HUTYPE_1_13Y;
		maxfannum += FAN_13Y;
	}
	else if (p_size == 0 && CheckL7D_HU(AllCard)){
		s_fan[0] |= HUTYPE_1_L7D;
		maxfannum += FAN_L7D;
	}
	else if (p_size == 0 && Check7D_HU(Cards)){
		s_fan[0] |= HUTYPE_1_7D;
		maxfannum += FAN_7D;

		int num_4G1 = 0;
		for (int i = 0; i != 49; i++){
			if (Cards[i] == 4)
			{
				num_4G1++;
				
			}
		}

		if (num_4G1 != 0){
			s_fan[2] |= (HUTYPE_3_4G1 & num_4G1);
			maxfannum += (FAN_4G1 * num_4G1);
		}

		is_7d = true;
	}
	else if (Check7XBK_HU(AllCard)){
		s_fan[0] |= HUTYPE_1_7XBK;
		maxfannum += FAN_7XBK;
	}
	else if (CheckQBK_HU(AllCard)){
		s_fan[1] |= HUTYPE_2_QBK;
		maxfannum += FAN_QBK;

		if (CheckZHL_HU(Cards, true)){
			s_fan[1] |= HUTYPE_2_ZHL;
			maxfannum += FAN_ZHL;
		}
	}
	else if (CheckZHL_HU(Cards, s_fan, maxfannum,p_desk,feng,isZiMo,lastcardvalue,justone)){
		s_fan[1] |= HUTYPE_2_ZHL;
		maxfannum += FAN_ZHL;
	}

	std::multimap <char, std::vector<CMjCardPile> > g_result;
    if(maxfannum != 0){
		if (CheckL1S_HU(AllCard))
		{
			s_fan[0] |= HUTYPE_1_LYS;
			maxfannum += FAN_LYS;
		}

		if (CheckQY9_HU(AllCard)){
			s_fan[0] |= HUTYPE_1_QYJ;
			maxfannum += FAN_QYJ;
		}

		if (CheckZ1S_HU(AllCard)){
			s_fan[0] |= HUTYPE_1_ZYS;
			maxfannum += FAN_ZYS;
		}

		if (((s_fan[0] & HUTYPE_1_13Y) != HUTYPE_1_13Y) && ((s_fan[0] & HUTYPE_1_ZYS) != HUTYPE_1_ZYS) && ((s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) && CheckHY9_HU(AllCard)){
			s_fan[0] |= HUTYPE_1_HYJ;
			maxfannum += FAN_HYJ;
		}

		if (((s_fan[0] & HUTYPE_1_JLBD) != HUTYPE_1_JLBD) && ((s_fan[0] & HUTYPE_1_L7D) != HUTYPE_1_L7D) && ((s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && (CheckQ1S_HU(AllCard) != -1)){
			s_fan[0] |= HUTYPE_1_Q1S;
			maxfannum += FAN_Q1S;
		}

        if (((s_fan[0] & HUTYPE_1_LYS) != HUTYPE_1_LYS) &&CheckHYS_HU(AllCard)){
            s_fan[1] |= HUTYPE_2_H1S;
            maxfannum += FAN_H1S;
        }

        if (((s_fan[0] & HUTYPE_1_13Y) != HUTYPE_1_13Y) && ((s_fan[0] & HUTYPE_1_7XBK) != HUTYPE_1_7XBK) && ((s_fan[1] & HUTYPE_2_QBK) != HUTYPE_2_QBK) && CheckWMQ_HU(AllCard)){
            s_fan[1] |= HUTYPE_2_5MQ;
            maxfannum += FAN_5MQ;
        }

        if ((cardtypeEX & CARDTYPE_LASTGOT) == CARDTYPE_LASTGOT){
            s_fan[1] |= HUTYPE_2_MSHC;
            maxfannum += FAN_MSHC;
        }

        if ((cardtypeEX & CARDTYPE_LASTOUT) == CARDTYPE_LASTOUT){
            s_fan[1] |= HUTYPE_2_HDLY;
            maxfannum += FAN_HDLY;
        }

        if ((cardtypeEX & CARDTYPE_AFTERG) == CARDTYPE_AFTERG){
            s_fan[1] |= HUTYPE_2_GSKH;
            maxfannum += FAN_GSKH;
        }

        if ((cardtypeEX & CARDTYPE_STOPG) == CARDTYPE_STOPG){
            s_fan[1] |= HUTYPE_2_QGH;
            maxfannum += FAN_QGH;
        }

        if (((s_fan[1] & HUTYPE_2_QGH) != HUTYPE_2_QGH) && (cardtypeEX & CARDTYPE_LASTLEFT) == CARDTYPE_LASTLEFT){
            s_fan[1] |= HUTYPE_2_HJZ;
            maxfannum += FAN_HJZ;
        }

		if (((s_fan[1] & HUTYPE_2_ZHL) != HUTYPE_2_ZHL) && CheckBQR_HU(isZiMo, p_desk)){
			s_fan[1] |= HUTYPE_2_BQR;
			maxfannum += FAN_BQR;
        }

        if(CheckDUY_HU(AllCard)){
			s_fan[2] |= HUTYPE_3_DY;
			maxfannum += FAN_DY;
        }

		if (((s_fan[1] & HUTYPE_2_BQR) != HUTYPE_2_BQR) && ((s_fan[1] & HUTYPE_2_MSHC) != HUTYPE_2_MSHC) && ((s_fan[1] & HUTYPE_2_GSKH) != HUTYPE_2_GSKH) && isZiMo){
            s_fan[2] |= HUTYPE_3_ZM;
            maxfannum += FAN_ZM;
        }
	}

	if ((maxfannum == 0 || is_7d == true ) && GetGroup(Cards, g_result))
	{
		int num_shun(0),num_peng(0),num_angang(0), num_minggang(0);
		for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++)
		{
			it->PutInCharArray(AllCard);
			it->PutInCharArray(temp_Cards);
			if (it->GetPileType() == SPECIAL_TYPE_MINGGANG || it->GetPileType() == SPECIAL_TYPE_PENGGANG)
				num_minggang++;
			else if (it->GetPileType() == SPECIAL_TYPE_ANGANG)
				num_angang++;
			else if (it->GetPileType() == SPECIAL_TYPE_SHUN)
				num_shun++;
			else if (it->GetPileType() == SPECIAL_TYPE_PENG)
				num_peng++;
		}

		sort(AllCard.begin(), AllCard.end()); //排序

		//此处如果是七对还要做对比，因为可能出现一色双龙会的情况
		int MaxFans = maxfannum;
		unsigned int MaxFan_sign[3];
		
        memcpy(MaxFan_sign, s_fan, sizeof(MaxFan_sign));

		for (std::map <char, std::vector<CMjCardPile> >::iterator it = g_result.begin(); it != g_result.end(); it++)
		{
            int totolfans = 0;
			unsigned int t_s_fan[3];
			int num_AK = GetAKNum(num_angang, it->second, lastcardvalue, isZiMo);

            memset(t_s_fan, 0, sizeof(t_s_fan));

			if (CheckD4X_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_DSX;
				totolfans += FAN_DSX;
			}

			if (CheckD3Y_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_DSY;
				totolfans += FAN_DSY;
			}

			if (CheckL1S_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_LYS;
				totolfans += FAN_LYS;
			}

			if (Check9LBD_HU(AllCard, temp_Cards,p_desk)){
				t_s_fan[0] |= HUTYPE_1_JLBD;
				totolfans += FAN_JLBD;
			}

			if (Check4Gang_HU(num_angang, num_minggang)){
				t_s_fan[0] |= HUTYPE_1_4G;
				totolfans += FAN_4G;
			}

			if (CheckQY9_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_QYJ;
				totolfans += FAN_QYJ;
			}

			if (CheckX4X_HU(it->first,it->second,p_desk)){
				t_s_fan[0] |= HUTYPE_1_XSX;
				totolfans += FAN_XSX;
			}

			if (CheckX3Y_HU(it->first, it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_XSY;
				totolfans += FAN_XSY;
			}

			if (CheckZ1S_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_ZYS;
				totolfans += FAN_ZYS;
			}

			if (num_AK == 4){
				t_s_fan[0] |= HUTYPE_1_4AK;
				totolfans += FAN_4AK;
			}

			if (Check1S2LH_HU(it->first,it->second, p_desk,AllCard)){
				t_s_fan[0] |= HUTYPE_1_1SSLH;
				totolfans += FAN_1SSLH;
			}

			if (Check1S4TS_HU(AllCard, it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_1SSTS;
				totolfans += FAN_1SSTS;
			}

			if (Check1S4JG_HU(it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_1SSJG;
				totolfans += FAN_1SSJG;
			}

			if (Check1S4BG_HU(AllCard, it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_1SSBG;
				totolfans += FAN_1SSBG;
			}

			if (Check3Gang_HU(num_angang, num_minggang)){
				t_s_fan[0] |= HUTYPE_1_3G;
				totolfans += FAN_3G;
			}

            if (((t_s_fan[0] & HUTYPE_1_ZYS) != HUTYPE_1_ZYS) && ((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) &&CheckHY9_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_HYJ;
				totolfans += FAN_HYJ;
			}

			if (CheckQSK_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_QSK;
				totolfans += FAN_QSK;
            }

            if (((t_s_fan[0] & HUTYPE_1_JLBD) != HUTYPE_1_JLBD) && ((t_s_fan[0] & HUTYPE_1_L7D) != HUTYPE_1_L7D) && ((t_s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && (CheckQ1S_HU(AllCard)!= -1)){
				t_s_fan[0] |= HUTYPE_1_Q1S;
				totolfans += FAN_Q1S;
			}

            if (((t_s_fan[0] & HUTYPE_1_1SSTS) != HUTYPE_1_1SSTS) && Check1S3TS_HU(it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_1S3TS;
				totolfans += FAN_1S3TS;
			}

            if (((t_s_fan[0] & HUTYPE_1_1SSJG) != HUTYPE_1_1SSJG) && Check1S3JG_HU(it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_1S3JG;
				totolfans += FAN_1S3JG;
			}

			if (CheckQD_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_QD;
				totolfans += FAN_QD;
			}

			if (CheckQZ_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_QZ;
				totolfans += FAN_QZ;
			}

			if (CheckQX_HU(AllCard)){
				t_s_fan[0] |= HUTYPE_1_QX;
				totolfans += FAN_QX;
			}

            if (CheckQL_HU(it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_QL;
				totolfans += FAN_QL;
			}

			if (Check3S2LH_HU(it->first,it->second,p_desk,AllCard)){
				t_s_fan[0] |= HUTYPE_1_3SSLH;
				totolfans += FAN_3SSLH;
			}

			if (((t_s_fan[0] & HUTYPE_1_1SSBG) != HUTYPE_1_1SSBG) && Check1S3BG_HU(it->second, p_desk)){
                t_s_fan[0] |= HUTYPE_1_1S3BG;
                totolfans += FAN_1S3BG;
			}

			if (CheckQD5_HU(it->first, it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_QDW;
				totolfans += FAN_QDW;
			}

			if (Check3TK_HU(it->second, p_desk)){
				t_s_fan[0] |= HUTYPE_1_3TK;
				totolfans += FAN_3TK;
			}

			if (num_AK == 3){
				t_s_fan[1] |= HUTYPE_2_3AK;
				totolfans += FAN_3AK;
			}

            if (((t_s_fan[0] & HUTYPE_1_QD) != HUTYPE_1_QD) && CheckDY5_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_DY5;
				totolfans += FAN_DY5;
			}

            if (((t_s_fan[0] & HUTYPE_1_QX) != HUTYPE_1_QX) && CheckXY5_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_XY5;
				totolfans += FAN_XY5;
			}

            if (((t_s_fan[0] & HUTYPE_1_DSX) != HUTYPE_1_DSX) && ((t_s_fan[0] & HUTYPE_1_XSX) != HUTYPE_1_XSX) && Check3Fk_HU(it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_3FK;
				totolfans += FAN_3FK;
			}

			if (CheckHuaL_HU(it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_HL;
				totolfans += FAN_HL;
			}

			if (CheckTBD_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_TBD;
				totolfans += FAN_TBD;
			}

			if (Check3S3TS_HU(it->second,p_desk)){
				t_s_fan[1] |= HUTYPE_2_3S3TS;
				totolfans += FAN_3S3TS;
			}

			if (Check3S3JG_HU(it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_3S3JG;
				totolfans += FAN_3S3JG;
			}

			if ((cardtypeEX & CARDTYPE_LASTGOT) == CARDTYPE_LASTGOT){
				t_s_fan[1] |= HUTYPE_2_MSHC;
				totolfans += FAN_MSHC;
			}

			if ((cardtypeEX & CARDTYPE_LASTOUT) == CARDTYPE_LASTOUT){
				t_s_fan[1] |= HUTYPE_2_HDLY;
				totolfans += FAN_HDLY;
			}

			if ((cardtypeEX & CARDTYPE_AFTERG) == CARDTYPE_AFTERG){
				t_s_fan[1] |= HUTYPE_2_GSKH;
				totolfans += FAN_GSKH;
			}

			if ((cardtypeEX & CARDTYPE_STOPG) == CARDTYPE_STOPG){
				t_s_fan[1] |= HUTYPE_2_QGH;
				totolfans += FAN_QGH;
			}

            if (((t_s_fan[0] & HUTYPE_1_DSX) != HUTYPE_1_DSX) && ((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) && ((t_s_fan[0] & HUTYPE_1_ZYS) != HUTYPE_1_ZYS)
                && ((t_s_fan[0] & HUTYPE_1_4AK) != HUTYPE_1_4AK) && ((t_s_fan[0] & HUTYPE_1_1SSJG) != HUTYPE_1_1SSJG) && ((t_s_fan[0] & HUTYPE_1_HYJ) != HUTYPE_1_HYJ)
				&& ((t_s_fan[0] & HUTYPE_1_4G) != HUTYPE_1_4G) && ((t_s_fan[0] & HUTYPE_1_QSK) != HUTYPE_1_QSK) && CheckPPH_HU(num_peng, num_angang, num_minggang, it->second)){
				t_s_fan[1] |= HUTYPE_2_PPH;
				totolfans += FAN_PPH;
			}

            if (((t_s_fan[0] & HUTYPE_1_LYS) != HUTYPE_1_LYS) &&CheckHYS_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_H1S;
				totolfans += FAN_H1S;
			}

			if (Check3S3BG_HU(it->second,p_desk)){
				t_s_fan[1] |= HUTYPE_2_3S3BG;
				totolfans += FAN_3S3BG;
			}

            if (((t_s_fan[0] & HUTYPE_1_13Y) != HUTYPE_1_13Y) && ((t_s_fan[0] & HUTYPE_1_7XBK) != HUTYPE_1_7XBK) && ((t_s_fan[1] & HUTYPE_2_QBK) != HUTYPE_2_QBK) && CheckWMQ_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_5MQ;
				totolfans += FAN_5MQ;
			}

			if (CheckQQR_HU(isZiMo,num_angang,it->second)){
                t_s_fan[1] |= HUTYPE_2_QQR;
                totolfans += FAN_QQR;
			}

			if (num_angang == 2){
				t_s_fan[1] |= HUTYPE_2_SAG;
				totolfans += FAN_SAG;
			}

            if (((t_s_fan[0] & HUTYPE_1_DSY) != HUTYPE_1_DSY) && ((t_s_fan[0] & HUTYPE_1_XSY) != HUTYPE_1_XSY) &&CheckSJK_HU(it->second,p_desk)){
				t_s_fan[1] |= HUTYPE_2_SJK;
				totolfans += FAN_SJK;
			}

            if (((t_s_fan[0] & HUTYPE_1_ZYS) != HUTYPE_1_ZYS) && ((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) && ((t_s_fan[0] & HUTYPE_1_HYJ) != HUTYPE_1_HYJ) && CheckQDY_HU(it->first, it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_QDY;
				totolfans += FAN_QDY;
			}

			if (CheckBQR_HU(isZiMo, p_desk)){
				t_s_fan[1] |= HUTYPE_2_BQR;
				totolfans += FAN_BQR;
			}

			if (((t_s_fan[0] & HUTYPE_1_4G) != HUTYPE_1_4G) && ((t_s_fan[0] & HUTYPE_1_3G) != HUTYPE_1_3G) && num_minggang == 2){
				t_s_fan[1] |= HUTYPE_2_SMG;
				totolfans += FAN_SMG;
			}

            if (((t_s_fan[1] & HUTYPE_2_QGH) != HUTYPE_2_QGH) && (cardtypeEX & CARDTYPE_LASTLEFT) == CARDTYPE_LASTLEFT){
				t_s_fan[1] |= HUTYPE_2_HJZ;
				totolfans += FAN_HJZ;
			}

			if (((t_s_fan[0] & HUTYPE_1_DSY) != HUTYPE_1_DSY) && ((t_s_fan[0] & HUTYPE_1_XSY) != HUTYPE_1_XSY) && ((t_s_fan[1] & HUTYPE_2_SJK) != HUTYPE_2_SJK) && CheckJKE_HU(AllCard)){
				t_s_fan[1] |= HUTYPE_2_JK;
				totolfans += FAN_JK;
			}

            if (((t_s_fan[0] & HUTYPE_1_DSX) != HUTYPE_1_DSX) && CheckMFK_HU(feng, it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_MFK;
				totolfans += FAN_MFK;
			}

            if (((t_s_fan[0] & HUTYPE_1_JLBD) != HUTYPE_1_JLBD) && ((t_s_fan[0] & HUTYPE_1_L7D) != HUTYPE_1_L7D) && ((t_s_fan[0] & HUTYPE_1_13Y) != HUTYPE_1_13Y)
                && ((t_s_fan[0] & HUTYPE_1_4AK) != HUTYPE_1_4AK) && ((t_s_fan[0] & HUTYPE_1_7D) != HUTYPE_1_7D) && ((t_s_fan[0] & HUTYPE_1_7XBK) != HUTYPE_1_7XBK)
                && ((t_s_fan[1] & HUTYPE_2_QBK) != HUTYPE_2_QBK) && CheckMQQ_HU(isZiMo, p_desk)){
				t_s_fan[1] |= HUTYPE_2_MQQ;
				totolfans += FAN_MQQ;
			}

            if (((t_s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && ((t_s_fan[0] & HUTYPE_1_3SSLH) != HUTYPE_1_3SSLH) && CheckPHe_HU(it->first, it->second, p_desk)){
				t_s_fan[1] |= HUTYPE_2_PH;
				totolfans += FAN_PH;
			}

			if (((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) && CheckSTK_HU(it->second, p_desk)){
                t_s_fan[1] |= HUTYPE_2_STK;
                totolfans += FAN_STK;
            }

            if (((t_s_fan[0] & HUTYPE_1_1SSTS) != HUTYPE_1_1SSTS) ){
				int num_4G1 = CheckSGY_HU(AllCard, p_desk);
				if (num_4G1 > 0){
					t_s_fan[2] |= (HUTYPE_3_4G1 & num_4G1);
					totolfans += (FAN_4G1 * num_4G1);
				}
			}

			if (((t_s_fan[1] & HUTYPE_2_SAG) != HUTYPE_2_SAG) && num_AK == 2){
				t_s_fan[2] |= HUTYPE_3_SAK;
				totolfans += FAN_SAK;
			}

            if (((t_s_fan[1] & HUTYPE_2_SAG) != HUTYPE_2_SAG) &&num_angang != 0){
				t_s_fan[2] |= HUTYPE_3_AG;
				totolfans += FAN_AG;
			}

            if (((t_s_fan[0] & HUTYPE_1_QSK) != HUTYPE_1_QSK) && ((t_s_fan[0] & HUTYPE_1_QZ) != HUTYPE_1_QZ) && ((t_s_fan[0] & HUTYPE_1_QDW) != HUTYPE_1_QDW) && CheckDUY_HU(AllCard)){
				t_s_fan[2] |= HUTYPE_3_DY;
				totolfans += FAN_DY;
			}

            if (((t_s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && ((t_s_fan[0] & HUTYPE_1_1SSTS) != HUTYPE_1_1SSTS) && ((t_s_fan[0] & HUTYPE_1_1S3TS) != HUTYPE_1_1S3TS)){
				int num_YBG = CheckYBG_HU(it->second, p_desk);
				if (num_YBG > 0)
				{
					t_s_fan[2] |= (HUTYPE_3_YBG & (num_YBG << 5));
					totolfans += (FAN_YBG * num_YBG);
				}
			}

            if (((t_s_fan[0] & HUTYPE_1_3SSLH) != HUTYPE_1_3SSLH) && ((t_s_fan[1] & HUTYPE_2_3S3TS) != HUTYPE_2_3S3TS) ){
				int num_XXF = CheckXXF_HU(it->second, p_desk);
				if (num_XXF > 0){
					t_s_fan[2] |= (HUTYPE_3_XXF & (num_XXF << 7));
					totolfans += (FAN_XXF * num_XXF);
				}
			}

			if (((t_s_fan[0] & HUTYPE_1_1SSBG) != HUTYPE_1_1SSBG) && ((t_s_fan[0] & HUTYPE_1_QL) != HUTYPE_1_QL) && CheckLLI_HU(temp_Cards)){
				t_s_fan[2] |= HUTYPE_3_LL;
				totolfans += FAN_LL;
			}

			if (((t_s_fan[0] & HUTYPE_1_QL) != HUTYPE_1_QL) && ((t_s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && ((t_s_fan[0] & HUTYPE_1_1SSBG) != HUTYPE_1_1SSBG) && ((t_s_fan[0] & HUTYPE_1_3SSLH) != HUTYPE_1_3SSLH)){
				int num_LSF = CheckLSF_HU(it->second, p_desk);
				if (num_LSF > 0){
					t_s_fan[2] |= (HUTYPE_3_LSF & (num_LSF << 10));
					totolfans += (FAN_LSF * num_LSF);
				}
			}

			if (((t_s_fan[0] & HUTYPE_1_DSX) != HUTYPE_1_DSX) && ((t_s_fan[0] & HUTYPE_1_JLBD) != HUTYPE_1_JLBD) && ((t_s_fan[0] & HUTYPE_1_HYJ) != HUTYPE_1_HYJ)
				&& ((t_s_fan[0] & HUTYPE_1_ZYS) != HUTYPE_1_ZYS) && ((t_s_fan[0] & HUTYPE_1_XSX) != HUTYPE_1_XSX) && ((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ)){

				int num_YJK = CheckYJK_HU(it->second, p_desk);

				if (((t_s_fan[1] & HUTYPE_2_3FK) == HUTYPE_2_3FK))
				{
					num_YJK -= 3;
				}
				else{
					if (((t_s_fan[1] & HUTYPE_2_MFK) == HUTYPE_2_MFK)){
						num_YJK -= 1;
					}
				}
				

				if (num_YJK > 0){
					t_s_fan[2] |= (HUTYPE_3_YJK &(num_YJK << 12));
					totolfans += (FAN_YJK * num_YJK);
				}
			}

			if (((t_s_fan[0] & HUTYPE_1_4G) != HUTYPE_1_4G) && ((t_s_fan[0] & HUTYPE_1_3G) != HUTYPE_1_3G) && ((t_s_fan[1] & HUTYPE_2_SMG) != HUTYPE_2_SMG) && num_minggang != 0){
				t_s_fan[2] |= HUTYPE_3_MG;
				totolfans += FAN_MG;
			}

			if (((t_s_fan[0] & HUTYPE_2_3FK) != HUTYPE_2_3FK) && ((t_s_fan[1] & HUTYPE_2_TBD) != HUTYPE_2_TBD) && CheckQ1M_HU(AllCard)){
				t_s_fan[2] |= HUTYPE_3_Q1M;
				totolfans += FAN_Q1M;
			}

            if (((t_s_fan[0] & HUTYPE_1_QYJ) != HUTYPE_1_QYJ) && ((t_s_fan[0] & HUTYPE_1_Q1S) != HUTYPE_1_Q1S) && ((t_s_fan[0] & HUTYPE_1_QD) != HUTYPE_1_QD)
                && ((t_s_fan[0] & HUTYPE_1_QX) != HUTYPE_1_QX) && ((t_s_fan[0] & HUTYPE_1_3SSLH) != HUTYPE_1_3SSLH) && ((t_s_fan[1] & HUTYPE_2_DY5) != HUTYPE_2_DY5)
				&& ((t_s_fan[0] & HUTYPE_1_1SSLH) != HUTYPE_1_1SSLH) && ((t_s_fan[1] & HUTYPE_2_XY5) != HUTYPE_2_XY5) && ((t_s_fan[0] & HUTYPE_1_JLBD) != HUTYPE_1_JLBD)
				&& ((t_s_fan[0] & HUTYPE_1_QDW) != HUTYPE_1_QDW) && ((t_s_fan[0] & HUTYPE_1_QZ) != HUTYPE_1_QZ) && ((t_s_fan[0] & HUTYPE_1_QSK) != HUTYPE_1_QSK) && CheckMYZ_HU(AllCard)){
				t_s_fan[2] |= HUTYPE_3_WZ;
				totolfans += FAN_WZ;
			}

			if (CheckPBH_HU(it->second, lastcardvalue, justone))
			{
				t_s_fan[2] |= HUTYPE_3_BZ;
				totolfans += FAN_BZ;
			}

			if (((t_s_fan[2] & HUTYPE_3_BZ) != HUTYPE_3_BZ) && CheckKZH_HU(it->second, lastcardvalue, justone))
			{
				t_s_fan[2] |= HUTYPE_3_KZ;
				totolfans += FAN_KZ;
			}

            if (((t_s_fan[0] & HUTYPE_1_L7D) != HUTYPE_1_L7D) && ((t_s_fan[0] & HUTYPE_1_13Y) != HUTYPE_1_13Y) && ((t_s_fan[0] & HUTYPE_1_7D) != HUTYPE_1_7D)
                && ((t_s_fan[0] & HUTYPE_1_7XBK) != HUTYPE_1_7XBK) && ((t_s_fan[1] & HUTYPE_2_QBK) != HUTYPE_2_QBK) && ((t_s_fan[1] & HUTYPE_2_QQR) != HUTYPE_2_QQR)
				&& ((t_s_fan[0] & HUTYPE_1_4G) != HUTYPE_1_4G) && ((t_s_fan[2] & HUTYPE_3_BZ) != HUTYPE_3_BZ) && ((t_s_fan[2] & HUTYPE_3_KZ) != HUTYPE_3_KZ) && CheckDDJ_HU(it->first, lastcardvalue, justone))
			{
				t_s_fan[2] |= HUTYPE_3_DDJ;
				totolfans += FAN_DDJ;
			}

			if (((t_s_fan[1] & HUTYPE_2_BQR) != HUTYPE_2_BQR) && ((t_s_fan[1] & HUTYPE_2_MSHC) != HUTYPE_2_MSHC) && ((t_s_fan[1] & HUTYPE_2_GSKH) != HUTYPE_2_GSKH) && isZiMo){
				t_s_fan[2] |= HUTYPE_3_ZM;
				totolfans += FAN_ZM;
			}

			if (totolfans == 0){
                t_s_fan[1] |= HUTYPE_2_WFH;
				totolfans += FAN_WFH;
			}
			
			if (totolfans > MaxFans){
                memcpy(MaxFan_sign, t_s_fan, sizeof(MaxFan_sign));
				MaxFans = totolfans;
			}
		}

		memcpy(s_fan, MaxFan_sign, sizeof(MaxFan_sign));
		maxfannum = MaxFans;
	}

	if (isTing){
		s_fan[2] |= HUTYPE_3_TING;
		maxfannum += FAN_TING;
	}

	if (num_hua > 0){		
		s_fan[2] |= (HUTYPE_3_HP & (num_hua << 22));
		maxfannum += (FAN_HP * num_hua);
	}

	//if (feng == 0){		//东风位表示庄家
	//	s_fan[2] |= HUTYPE_3_ZHUANG;
	//	maxfannum = maxfannum*2;
	//}

	return (maxfannum != 0);
}


//检测是否胡大四喜
bool MethordHuClass::CheckD4X_HU(std::vector <int> &AllCard)
{
	if (AllCard[AllCard.size() - 3] != 7) //检测倒数第三位一定为北风(有序)
        return false;
    return true;
}

//检则是否胡大三元
bool MethordHuClass::CheckD3Y_HU(std::vector <int> &AllCard)
{
    int zhong(0), fa(0), bai(0);
	for (size_t ii = 0; ii < AllCard.size(); ++ii)
    {
		if (AllCard[ii] == 11)
            ++zhong;
		if (AllCard[ii] == 13)
            ++fa;
		if (AllCard[ii] == 15)
            ++bai;
    }
    if (zhong >= 3 && fa >= 3 && bai >= 3)
        return true;
    return false;
}
//检测是否胡绿一色
bool MethordHuClass::CheckL1S_HU(std::vector <int> &AllCard)
{
	for (size_t ii = 0; ii < AllCard.size(); ++ii)
    {
		if (AllCard[ii] != 13 && AllCard[ii] != 42 && AllCard[ii] != 43 &&
			AllCard[ii] != 44 && AllCard[ii] != 46 && AllCard[ii] != 48)
        {
            return false;
        }
    }
    return true;
}

//检测是否胡九莲宝灯
bool MethordHuClass::Check9LBD_HU(std::vector <int> &AllCard, int Card[49], std::list<CMjCardPile >& p_desk)
{
	if (AllCard.size() != 14 && p_desk.size() == 0) return false;
	int q1s_type = CheckQ1S_HU(AllCard);
	if (q1s_type != -1)
	{
        if (Card[q1s_type * 10 ] < 3)
			return false;
		for (int i = 2; i <= 8; i++)
		{
            if (Card[q1s_type * 10 + i - 1 ] < 1)
				return false;
		}

        if (Card[q1s_type * 10 + 8] < 3)
			return false;

		return true;
	}
    return false;
}
//检测是否胡四杠
bool MethordHuClass::Check4Gang_HU(int &num_angang, int &num_minggang) //todo
{
	return ((num_angang + num_minggang) == 4);
}
//检测是否胡连七对
bool MethordHuClass::CheckL7D_HU(std::vector <int> &AllCard)
{
	if (AllCard.size() == 14)
    {
		for (int i = 0; i != 14; i++)
		{
			if (AllCard[i] != AllCard[0] + i / 2)
				return false;
		}

		return true;
    }
    return false;
}
//检测是否胡清幺九
bool MethordHuClass::CheckQY9_HU(std::vector <int> &AllCard)
{
	size_t v_Size = AllCard.size();
	for (size_t ii = 0; ii < v_Size; ++ii)
    {
		if (AllCard[ii] < 20)
            return false;
		int singeCard = AllCard[ii] % 10;
        if (singeCard != 1 && singeCard != 9)
            return false;
    }
    return true;
}
//检测是否胡小四喜
bool MethordHuClass::CheckX4X_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (jiang > 7) return false;

	int num_fengke = 0;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileFirstCard() <= 7)
            num_fengke++;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileFirstCard() <= 7)
            num_fengke++;
	}

	return (num_fengke == 3);
	
}
//检测是否胡小三元
bool MethordHuClass::CheckX3Y_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (jiang/10 != 1) return false;

	int num_zike = 0;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileFirstCard()/10 == 1)
            num_zike++;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileFirstCard() / 10 == 1)
            num_zike++;
	}

	return (num_zike == 2);
}
//检测是否胡字一色
bool MethordHuClass::CheckZ1S_HU(std::vector <int> &AllCard)
{
	if (AllCard[AllCard.size() - 1] < 20)
        return true;
    return false;
}
//检测是否四暗刻
bool MethordHuClass::Check4AK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_ANGANG)
			return false;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
        if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			return false;
	}

	return true;
}
//检测是否一色双龙会
bool MethordHuClass::Check1S2LH_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk, std::vector <int> &AllCard)
{
	if (jiang % 10 != 5)
		return false;

	int q1s_type = CheckQ1S_HU(AllCard);
	if (q1s_type == -1)
		return false;

	int laofu(0), shaofu(0);
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			if (it->GetPileFirstCard() == q1s_type * 10 + 1)
			{
				shaofu += 1;
			}
			else if (it->GetPileFirstCard() == q1s_type * 10 + 7){
				laofu += 1;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			if (it->GetPileFirstCard() == q1s_type * 10 + 1)
			{
				shaofu += 1;
			}
			else if (it->GetPileFirstCard() == q1s_type * 10 + 7){
				laofu += 1;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}

	return (shaofu == 2 && laofu == 2) ;
}
//检测是否一色四同顺
bool MethordHuClass::Check1S4TS_HU(std::vector <int> &AllCard, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (AllCard.size() != 14)
        return false;

	char shun = -1;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN )
		{
            if (shun == -1)
				shun = it->GetPileFirstCard();

			if (shun != it->GetPileFirstCard())
				return false;
		}
		else{
			return false;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
            if (shun == -1)
				shun = it->GetPileFirstCard();

			if (shun != it->GetPileFirstCard())
				return false;
		}
		else{
			return false;
		}
	}

	return true;
}
//检测是否一色四节高
bool MethordHuClass::Check1S4JG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> card_pg;	//碰杠牌的点数
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN)
		{
			card_pg.push_back(it->GetPileFirstCard());
		}
		else{
			return false;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN)
		{
			card_pg.push_back(it->GetPileFirstCard());
		}
		else{
			return false;
		}
	}
	if (card_pg.size() != 4)
		return false;

	sort(card_pg.begin(), card_pg.end());

	return (card_pg[0] + 3 == card_pg[card_pg.size()-1]);
}
//检测是否一色四步高
bool MethordHuClass::Check1S4BG_HU(std::vector <int> &AllCard, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (AllCard.size() != 14)
		return false;

	vector<char> card_s;	//碰杠牌的点数
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			card_s.push_back(it->GetPileFirstCard());
		}
		else{
			return false;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			card_s.push_back(it->GetPileFirstCard());
		}
		else{
			return false;
		}
	}
	if (card_s.size() != 4)
		return false;

	sort(card_s.begin(), card_s.end());
    if(card_s[3] == card_s[2]+1 && card_s[2] == card_s[1]+1 && card_s[1] == card_s[0]+1)
        return true;
    if(card_s[3] == card_s[2]+2 && card_s[2] == card_s[1]+2 && card_s[1] == card_s[0]+2)
        return true;
    return false;
}
//检测是否三杠
bool MethordHuClass::Check3Gang_HU(int &num_angang, int &num_minggang)
{
    return ((num_angang + num_minggang) == 3);
}
//检测是否混幺九
bool MethordHuClass::CheckHY9_HU(std::vector <int> &AllCard)
{
	size_t v_Size = AllCard.size();
	for (size_t ii = 0; ii < v_Size; ++ii)
	{
		if (AllCard[ii] > 20)
		{
			int singeCard = AllCard[ii] % 10;
			if (singeCard != 1 && singeCard != 9)
				return false;
		}
	}

	return true;
}
//检测是否七星不靠
bool MethordHuClass::Check7XBK_HU(std::vector <int> &AllCard)
{
	if (AllCard.size() != 14) //仅手牌
        return false;
	if (AllCard[0] != 1 || AllCard[1] != 3 || AllCard[2] != 5 || AllCard[3] != 7 || AllCard[4] != 11 ||
        AllCard[5] != 13 || AllCard[6] != 15||AllCard[7] <20)
        return false;

	char point_num[9];
	memset(point_num, 0, sizeof(point_num));
	for (size_t ii = 7; ii < 13; ++ii)
	{
		if ((AllCard[ii + 1] / 10 == AllCard[ii] / 10) && (((AllCard[ii + 1] - AllCard[ii]) <= 2) || ((AllCard[ii + 1] - AllCard[ii]) % 3 != 0)))	//万条筒必须是不靠
			return false;

        point_num[(AllCard[ii] % 10)-1]++;

        if (point_num[(AllCard[ii] % 10)-1]>1)
			return false;
	}

    if (point_num[(AllCard[13] % 10) -1] != 0)
		return false;

	return true;
}
//检测是否全双刻
bool MethordHuClass::CheckQSK_HU(std::vector <int> &AllCard)
{
	size_t v_Size = AllCard.size();
	for (size_t ii = 0; ii < v_Size; ++ii)
    {
		if (AllCard[ii] % 2 != 0)
			return false;
    }
    return true;
}
//判断清一色
int MethordHuClass::CheckQ1S_HU(std::vector <int> &AllCard)
{
	size_t v_Size = AllCard.size();

	for (int i = CARD_TYPE_WAN; i <= CARD_TYPE_TONG; i++)
	{
        if ((AllCard[0] >= (i * 10 + 1)) && (AllCard[v_Size - 1] <= (i * 10 + 9)))
		{
			return i;
		}
	}

    return -1;
}
//检测是否一色三同顺
bool MethordHuClass::Check1S3TS_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> shun_firstcards;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			shun_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			shun_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	if (shun_firstcards.size() < 3)
		return false;

	sort(shun_firstcards.begin(), shun_firstcards.end());

	for (int i = 0; i <= shun_firstcards.size() - 3; i++){
		if (shun_firstcards[i] == shun_firstcards[i + 2]){
			return true;
		}
	}

	return false; 
}
//检测是否一色三节高
bool MethordHuClass::Check1S3JG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> peng_firstcards;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN)
		{
			peng_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG){
			peng_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	if (peng_firstcards.size() < 3)
		return false;

	sort(peng_firstcards.begin(), peng_firstcards.end());

	for (int i = 0; i <= peng_firstcards.size() - 3; i++){
		if (peng_firstcards[i]+2 == peng_firstcards[i + 2]){
			return true;
		}
	}

	return false;
}
//检测是否全大
bool MethordHuClass::CheckQD_HU(std::vector <int> &AllCard)
{
	size_t cardsize = AllCard.size();
	for (size_t ii = 0; ii < cardsize; ++ii)
    {
		int remTmp = AllCard[ii] / 10;
		int modTmp = AllCard[ii] % 10;
        if (remTmp < 2 ||  modTmp < 7) //27 29....
            return false;
    }
    return true;
}
//检测是否全中
bool MethordHuClass::CheckQZ_HU(std::vector <int> &AllCard)
{
	size_t cardsize = AllCard.size();
	for (size_t ii = 0; ii < cardsize; ++ii)
    {
		int remTmp = AllCard[ii] / 10;
		int modTmp = AllCard[ii] % 10;
        if (remTmp < 2 ||  modTmp < 4 || modTmp > 6) //24 26....
            return false;
    }
    return true;
}
//检测是否全小
bool MethordHuClass::CheckQX_HU(std::vector <int> &AllCard)
{
	size_t cardsize = AllCard.size();
	for (size_t ii = 0; ii < cardsize; ++ii)
    {
		int remTmp = AllCard[ii] / 10;
		int modTmp = AllCard[ii] % 10;
        if (remTmp < 2 ||  modTmp > 3) //21 23....
            return false;
    }
    return true;
}
//检测是否青龙
bool MethordHuClass::CheckQL_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	char shun_sign[9];		//分别对应 1w 4w 7w 1t 4t 7t 1o 4o 7o 对应的序列牌
	memset(shun_sign, 0, sizeof(shun_sign));
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		char firstcard = it->GetPileFirstCard();
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && (firstcard > 20 && (firstcard % 10 == 1 || firstcard % 10 == 4 || firstcard % 10 == 7)))
		{
			shun_sign[(firstcard / 10 - 2) * 3 + (firstcard % 10) / 3] ++;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		char firstcard = it->GetPileFirstCard();
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && (firstcard > 20 && (firstcard % 10 == 1 || firstcard % 10 == 4 || firstcard % 10 == 7)))
		{
			shun_sign[(firstcard / 10 - 2) * 3 + (firstcard % 10) / 3] ++;
		}
	}

	for (int i = 0; i != 3; i++){
		if (shun_sign[i * 3] > 0 && shun_sign[i * 3 + 1] > 0 && shun_sign[i * 3 + 2] > 0)
			return true;
	}

    return false;
}
//检测是否三色双龙会
bool MethordHuClass::Check3S2LH_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk, std::vector <int> &AllCard)
{
	char laoshao[6];
	memset(laoshao, 0, sizeof(laoshao));

	if (jiang % 10 != 5)
		return false;

	//将将牌的老少位置置为 1
	laoshao[(jiang / 10 - 2) * 2] = 1;
	laoshao[(jiang / 10 - 2) * 2+1] = 1;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			if (it->GetPileFirstCard()%10 ==  1)
			{
				laoshao[(it->GetPileFirstCard() / 10 - 2) * 2] = 1;
			}
			else if (it->GetPileFirstCard() % 10 == 7){
				laoshao[(it->GetPileFirstCard() / 10 - 2) * 2+1] = 1;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			if (it->GetPileFirstCard() % 10 == 1)
			{
				laoshao[(it->GetPileFirstCard() / 10 - 2) * 2] = 1;
			}
			else if (it->GetPileFirstCard() % 10 == 7){
				laoshao[(it->GetPileFirstCard() / 10 - 2) * 2 + 1] = 1;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}

	for (int i = 0; i != 6; i++)
	{
		if (laoshao[i] != 1)
			return false;
	}

	return true;
}
//检测是否一色三步高
bool MethordHuClass::Check1S3BG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> shun_firstcards;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			shun_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			shun_firstcards.push_back(it->GetPileFirstCard());
		}
	}

	int shun_size = shun_firstcards.size();
	sort(shun_firstcards.begin(), shun_firstcards.end());
	if (shun_size == 3)
	{
		if ((shun_firstcards[0] + 1 == shun_firstcards[1]) && (shun_firstcards[1] + 1 == shun_firstcards[2]) || (shun_firstcards[0] + 2 == shun_firstcards[1]) && (shun_firstcards[1] + 2 == shun_firstcards[2]))
			return true;
	}

	if (shun_size == 4){
		for (int i = 0; i < shun_firstcards.size(); i++){		//遍历所有3个顺的组合
			vector<char> temp_cards;
			temp_cards.assign(shun_firstcards.begin(), shun_firstcards.end());
			temp_cards.erase(temp_cards.begin() + i);
			if ((temp_cards[0] + 1 == temp_cards[1]) && (temp_cards[1] + 1 == temp_cards[2]) || (temp_cards[0] + 2 == temp_cards[1]) && (temp_cards[1] + 2 == temp_cards[2]))
				return true;
		}
	}
	

	return false;
}
//全带五
bool MethordHuClass::CheckQD5_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (jiang<20 || jiang%10 != 5){
		return false;
	}

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
            if(it->GetPileFirstCard()%10<3 || it->GetPileFirstCard()%10>5)
				return false;
		}
		else{
            if(it->GetPileFirstCard()<20||it->GetPileFirstCard()%10 != 5)
                return false;
		}
	}

	vector<char> handpeng_fisrtcards;
	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
            if (it->GetPileFirstCard()%10<3 || it->GetPileFirstCard()%10>5)
				return false;
		}
		else{
            if(it->GetPileFirstCard()<20||it->GetPileFirstCard()%10 != 5)
                return false;
		}
	}

    return true;
}
//三同刻
bool MethordHuClass::Check3TK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	map<char, int> point_num;		//key 序列号 value 相同序列号的刻的数量
    
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard() >20 )
		{
            char card_point = it->GetPileFirstCard() % 10;
			if (point_num.count(card_point))
			{
				point_num[card_point]++;
			}
			else{
				point_num.insert(make_pair(card_point, 1));
			}
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard() > 20)
		{
            char card_point = it->GetPileFirstCard() % 10;
			if (point_num.count(card_point))
			{
				point_num[card_point]++;
			}
			else{
				point_num.insert(make_pair(card_point, 1));
			}
		}
	}

	for (map<char, int>::iterator it = point_num.begin(); it != point_num.end(); it++){
		if (it->second >= 3)
			return true;
	}

	return false;
}
//三暗刻
bool MethordHuClass::Check3AK_HU(int &angangnum, std::vector<CMjCardPile> &p_hand)
{
	int totolAK = angangnum;
    
	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG)
			totolAK++;
	}

    return (totolAK == 3);
}
//全不靠
bool MethordHuClass::CheckQBK_HU(std::vector <int> &AllCard)
{
	if (AllCard.size() != 14) //仅手牌
		return false;

	char point_num[9];
	memset(point_num, 0, sizeof(point_num));

    for (size_t ii = 0; ii < 13; ++ii)
	{
		if (AllCard[ii] < 20){		//字牌必须单张
			if (AllCard[ii + 1] == AllCard[ii])
				return false;
		}
		else{
            if ((AllCard[ii + 1] / 10 == AllCard[ii] / 10) && (((AllCard[ii + 1] - AllCard[ii]) <= 2) || ((AllCard[ii + 1] - AllCard[ii])%3 != 0)))	//万条筒必须是不靠
				return false;

            point_num[AllCard[ii] % 10-1]++;

            if (point_num[AllCard[ii] % 10-1]>1)
				return false;
			
		}

	}

    if (point_num[AllCard[13] % 10-1]!=0)
        return false;

	return true;
}

bool MethordHuClass::CheckZHL_HU(int Card[49], unsigned int s_fan[], int &maxfannum, std::list<CMjCardPile >& p_desk, int feng, bool isZiMo, char lastcardvalue, bool justone){
	char zuhe[6][9] = {
		{ 21, 24, 27, 32, 35, 38, 43, 46, 49 },
		{ 21, 24, 27, 33, 36, 39, 42, 45, 48 },
		{ 22, 25, 28, 31, 34, 37, 43, 46, 49 },
		{ 22, 25, 28, 33, 36, 39, 41, 44, 47 },
		{ 23, 26, 29, 32, 35, 38, 41, 44, 47 },
		{ 23, 26, 29, 31, 34, 37, 42, 45, 48 }
	};

	int temp[49];
	for (int i = 0; i != 6; i++){
		memcpy(temp, Card, sizeof(temp));
		bool hadcard = true;
		for (int j = 0; j != 9; j++){
            if (temp[(zuhe[i][j] -1)] >= 1){
                temp[(zuhe[i][j] -1)] -= 1;
			}
			else{
				hadcard = false;
				break;
			}

		}

		if (!hadcard)
            continue;

		std::vector<CMjCardPile > p_result;
		CMjCardPile *ptemp_pile;
		for (int y = 0; y != 49; y++){
			if (temp[y] >= 2){
				temp[y] -= 2;
				p_result.clear();
				if (CheckCardPile(temp, p_result)){

					if (p_result.size() != 0)
						ptemp_pile = &p_result[0];

					if (p_desk.size() != 0)
						ptemp_pile = &(*p_desk.begin());
					int p_piletype = ptemp_pile->GetPileType();
					int p_firstcard = ptemp_pile->GetPileFirstCard();

					if (p_piletype != SPECIAL_TYPE_SHUN && ((p_firstcard / 10) == 1))
					{
						s_fan[1] |= HUTYPE_2_JK;
						maxfannum += FAN_JK;
					}

					if (p_piletype != SPECIAL_TYPE_SHUN && (p_firstcard == 1 + feng * 2))
					{
						s_fan[1] |= HUTYPE_2_MFK;
						maxfannum += FAN_MFK;
					}

					if (p_desk.size() == 0 || p_piletype == SPECIAL_TYPE_ANGANG){
						if (isZiMo){
							s_fan[1] |= HUTYPE_2_BQR;
                            maxfannum += FAN_BQR;
						}
						else{
							s_fan[1] |= HUTYPE_2_MQQ;
							maxfannum += FAN_MQQ;
						}
					}

					if (p_piletype == SPECIAL_TYPE_SHUN){
						s_fan[1] |= HUTYPE_2_PH;
						maxfannum += FAN_PH;
					}

					if (p_piletype == SPECIAL_TYPE_PENG){
						for (int x = 0; x != 9; x++){
							if (zuhe[i][x] == p_firstcard){
								s_fan[2] |= (HUTYPE_3_4G1 & 1);
								maxfannum += FAN_4G1;
								break;
							}
						}
					}

					if (p_piletype == SPECIAL_TYPE_ANGANG){
						s_fan[2] |= HUTYPE_3_AG;
						maxfannum += FAN_AG;
					}

					if ((s_fan[1] & HUTYPE_2_MFK) != HUTYPE_2_MFK  && p_piletype == SPECIAL_TYPE_PENG && (p_firstcard < 10 || (p_firstcard>=20 && (p_firstcard % 10 == 1 || p_firstcard % 10 == 9))))
					{
                        s_fan[2] |= (HUTYPE_3_YJK &(1 << 12));
						maxfannum += FAN_YJK;
					}

					if (p_piletype == SPECIAL_TYPE_MINGGANG){
						s_fan[2] |= HUTYPE_3_MG;
						maxfannum += FAN_MG;
					}

					if (y>20 && p_firstcard > 20){
						s_fan[2] |= HUTYPE_3_WZ;
						maxfannum += FAN_WZ;
					}

					if (CheckDDJ_HU(y+1, lastcardvalue, justone))
					{
						s_fan[2] |= HUTYPE_3_DDJ;
						maxfannum += FAN_DDJ;
					}

					return true;
				}
				temp[y] += 2;
			}
		}
	}

	return false;
}
//组合龙
bool MethordHuClass::CheckZHL_HU(int Card[49], bool IsQBK)
{
	char zuhe[6][9] = {
		{21,24,27,32,35,38,43,46,49},
		{ 21, 24, 27, 33, 36, 39, 42, 45, 48 },
		{ 22, 25, 28, 31, 34, 37, 43, 46, 49 },
		{ 22, 25, 28, 33, 36, 39, 41, 44, 47 },
		{ 23, 26, 29, 32, 35, 38, 41, 44, 47 },
		{ 23, 26, 29, 31, 34, 37, 42, 45, 48 }
	};

	int temp[49];
    for (int i = 0; i != 6; i++){
        memcpy(temp, Card, sizeof(temp));
		bool hadcard = true;
		for (int j = 0; j != 9; j++){
            if (temp[(zuhe[i][j] -1)] >= 1){
                temp[(zuhe[i][j] -1)] -= 1;
			}
			else{
				hadcard = false;
				break;
			}
				
		}

		if (!hadcard)
            continue;

		if (IsQBK)
			return true;

		if (CheckCardPile(temp,false))
			return true;

	}

	return false;
}
//大于五
bool MethordHuClass::CheckDY5_HU(std::vector <int> &AllCard)
{
	if (AllCard[0] <= 15)
        return false;
	int v_size = AllCard.size();
	for (size_t ii = 0; ii < v_size; ++ii)
    {
        if (AllCard[ii] % 10 <= 5)
            return false;
    }
    return true;
}
//小于五
bool MethordHuClass::CheckXY5_HU(std::vector <int> &AllCard)
{
	if (AllCard[0] <= 15)
        return false;
	int v_size = AllCard.size();
	for (size_t ii = 0; ii < v_size; ++ii)
    {
        if (AllCard[ii] % 10 >= 5)
            return false;
    }
    return true;
}
//三风刻
bool MethordHuClass::Check3Fk_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
    int fengKeNum = 0;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileFirstCard() < 10)
			fengKeNum++;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileFirstCard() < 10)
			fengKeNum++;
	}
	return (fengKeNum >= 3);
}
//花龙
bool MethordHuClass::CheckHuaL_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> v_firstcard_shun;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			v_firstcard_shun.push_back(it->GetPileFirstCard());
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			v_firstcard_shun.push_back(it->GetPileFirstCard());
	}

	int s_size = v_firstcard_shun.size();
	if (s_size < 3) return false;

	map<char, vector<int> >	m_firstcard_type;

	for (vector<char>::iterator it = v_firstcard_shun.begin(); it != v_firstcard_shun.end(); it++){
		if (*it > 20 && (*it % 10 == 1 || *it % 10 == 4 || *it % 10 == 7)){
			if (m_firstcard_type.find(*it % 10) == m_firstcard_type.end())
				m_firstcard_type.insert(make_pair(*it % 10, vector<int>(0)));

			m_firstcard_type[*it % 10].push_back(*it / 10);
		}
	}

	if (m_firstcard_type.size() != 3) return false;		//必须137都有

	int totol_sign = 0;

	for (vector<int>::iterator it1 = m_firstcard_type[1].begin(); it1 != m_firstcard_type[1].end(); it1++){
		for (vector<int>::iterator it2 = m_firstcard_type[4].begin(); it2 != m_firstcard_type[4].end(); it2++){
			for (vector<int>::iterator it3 = m_firstcard_type[7].begin(); it3 != m_firstcard_type[7].end(); it3++){
				if ((*it1 != *it2) && (*it2 != *it3) && (*it1 != *it3))
					return true;
			}
		}
	}
	
	return false;

}
//推不倒
bool MethordHuClass::CheckTBD_HU(std::vector <int> &AllCard)
{
	int s_size = AllCard.size();
	for (size_t ii = 0; ii < s_size; ++ii)
    {
        if (AllCard[ii] == 15 || AllCard[ii] == 42 || AllCard[ii] == 44 || AllCard[ii] == 45 || AllCard[ii] == 46 ||
            AllCard[ii] == 48 || AllCard[ii] == 49 || AllCard[ii] == 31 || AllCard[ii] == 32 || AllCard[ii] == 33 ||
            AllCard[ii] == 34 || AllCard[ii] == 35 || AllCard[ii] == 38 || AllCard[ii] == 39){
			continue;
		}
		else{
			return false;
		}
            
    }

	return true;
}
//三色三同顺
bool MethordHuClass::Check3S3TS_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> v_card_shun;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN){
			v_card_shun.push_back(it->GetPileFirstCard());
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN){
			v_card_shun.push_back(it->GetPileFirstCard());
		}
	}

	if (v_card_shun.size() < 3) return false;

	map<char, char> m_point_sign;

	for (vector<char>::iterator it = v_card_shun.begin(); it != v_card_shun.end(); it++){
		if (m_point_sign.count(*it % 10) == 0)
			m_point_sign[*it % 10] = 0;

		m_point_sign[*it % 10] |= (1<<(*it/10));
	}

	for (map<char, char>::iterator it = m_point_sign.begin(); it != m_point_sign.end(); it++){
		if (it->second == 28)
			return true;
	}

	return false;
}
//三色三节高
bool MethordHuClass::Check3S3JG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> v_card_peng;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard()>20 ){
			v_card_peng.push_back((it->GetPileFirstCard() / 10) + (it->GetPileFirstCard()%10*10));
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard()>20){
			v_card_peng.push_back((it->GetPileFirstCard() / 10) + (it->GetPileFirstCard() % 10 * 10));
		}
	}

    if (v_card_peng.size() < 3) return false;

	sort(v_card_peng.begin(), v_card_peng.end());

	if (v_card_peng.size() == 3){
        if ((v_card_peng[2] / 10 == v_card_peng[1] / 10 + 1) && (v_card_peng[1] / 10 == v_card_peng[0] / 10 + 1) && (v_card_peng[1] % 10 != v_card_peng[0] % 10) && (v_card_peng[1] % 10 != v_card_peng[2] % 10)&& (v_card_peng[0] % 10 != v_card_peng[2] % 10))
			return true;
	}

	if (v_card_peng.size() == 4){
		for (int i = 0; i != v_card_peng.size(); i++){
			vector<char> v_card_peng_temp(v_card_peng.begin(), v_card_peng.end());
			v_card_peng_temp.erase(v_card_peng_temp.begin() + i);
            if ((v_card_peng_temp[2] / 10 == v_card_peng_temp[1] / 10 + 1) && (v_card_peng_temp[1] / 10 == v_card_peng_temp[0] / 10 + 1) && (v_card_peng_temp[1] % 10 != v_card_peng_temp[0] % 10) && (v_card_peng_temp[1] % 10 != v_card_peng_temp[2] % 10)&& (v_card_peng_temp[0] % 10 != v_card_peng_temp[2] % 10))
				return true;
		}
	}

	return false; 
}
//无番和
bool MethordHuClass::CheckWFH_HU()
{
	return false;
}
//妙手回春
bool MethordHuClass::CheckMSHC_HU()
{
	return false;
}
//海底捞月
bool MethordHuClass::CheckHDLY_HU()
{
	return false;
}
//杠上开花
bool MethordHuClass::CheckGSKH_HU()
{
	return false;
}
//抢杠胡
bool MethordHuClass::CheckQGH_HU()
{
	return false;
}
//碰碰和
bool MethordHuClass::CheckPPH_HU(int &num_peng, int &num_angang, int &num_minggang, std::vector<CMjCardPile> &p_hand)
{
	int num = num_peng + num_angang + num_minggang;
	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG){
			num++;
		}
	}

	return num == 4;
}
//混一色
bool MethordHuClass::CheckHYS_HU(std::vector <int> &AllCard)
{
	int s_size = AllCard.size();
    if (AllCard[0] > 15 || AllCard[s_size-1] <=15) //mei zi pai
        return false;
	
	for (int i = 0; i != s_size-1; i++){
		if (AllCard[i] > 20)
		{
            if (AllCard[i+1] / 10 != AllCard[i] / 10)
				return false;
		}
	}
    
	return true;
}
//三色三步高
bool MethordHuClass::Check3S3BG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	vector<char> v_card_shun;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && it->GetPileFirstCard() > 20){
			v_card_shun.push_back((it->GetPileFirstCard() / 10) + (it->GetPileFirstCard() % 10 * 10));
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && it->GetPileFirstCard() > 20){
			v_card_shun.push_back((it->GetPileFirstCard() / 10) + (it->GetPileFirstCard() % 10 * 10));
		}
	}

    if (v_card_shun.size() < 3) return false;

	sort(v_card_shun.begin(), v_card_shun.end());

	if (v_card_shun.size() == 3){
		if ((v_card_shun[2] / 10 == v_card_shun[1] / 10 + 1) && (v_card_shun[1] / 10 == v_card_shun[0] / 10 + 1) && (v_card_shun[1] % 10 != v_card_shun[0] % 10) && (v_card_shun[1] % 10 != v_card_shun[2] % 10))
			return true;
	}

	if (v_card_shun.size() == 4){
		for (int i = 0; i != v_card_shun.size(); i++){
			vector<char> v_card_shun_temp(v_card_shun.begin(), v_card_shun.end());
			v_card_shun_temp.erase(v_card_shun_temp.begin() + i);
			if ((v_card_shun_temp[2] / 10 == v_card_shun_temp[1] / 10 + 1) && (v_card_shun_temp[1] / 10 == v_card_shun_temp[0] / 10 + 1) && (v_card_shun_temp[1] % 10 != v_card_shun_temp[0] % 10) && (v_card_shun_temp[1] % 10 != v_card_shun_temp[2] % 10))
				return true;
		}
	}

	return false;
}
//五门齐
bool MethordHuClass::CheckWMQ_HU(std::vector <int> &AllCard)
{
	char men[5];
	memset(men, 0, sizeof(men));
	size_t s_size = AllCard.size();
	for (size_t ii = 0; ii < s_size; ++ii)
    {
		men[AllCard[ii] / 10]++;
    }
	for (int i = 0; i != 5; i++)
	{
		if (men[i] == 0)
			return false;
	}
    
	return true;
}
//全求人
bool MethordHuClass::CheckQQR_HU(bool isZiMo, int &num_angang, std::vector<CMjCardPile> &p_hand)
{
    return (!isZiMo && (num_angang == 0) && (p_hand.size() == 0));
}

//双箭刻
bool MethordHuClass::CheckSJK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	int num_jk = 0;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileFirstCard()/10 == 1)
			num_jk++;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileFirstCard() / 10 == 1)
			num_jk++;
	}

	return (num_jk == 2);
}
//全带幺
bool MethordHuClass::CheckQDY_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (jiang > 20 && (jiang % 10 != 1) && (jiang % 10 != 9))	return false;

	vector<char> shun_firstcards;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		char cardvalue = it->GetPileFirstCard();
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && (cardvalue % 10 != 1) && (cardvalue % 10 != 7))
			return false;
        if (it->GetPileType() != SPECIAL_TYPE_SHUN && (cardvalue % 10 != 1) && (cardvalue % 10 != 9) && (cardvalue > 20))
			return false;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		char cardvalue = it->GetPileFirstCard();
		if (it->GetPileType() == SPECIAL_TYPE_SHUN && (cardvalue % 10 != 1) && (cardvalue % 10 != 7))
			return false;
        if (it->GetPileType() != SPECIAL_TYPE_SHUN && (cardvalue % 10 != 1) && (cardvalue % 10 != 9) && (cardvalue > 20))
			return false;
	}

	return true;
}
//不求人	待考究
bool MethordHuClass::CheckBQR_HU(bool isZiMo, std::list<CMjCardPile >& p_desk)
{
	if (!isZiMo) return false;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType()!= SPECIAL_TYPE_ANGANG)
			return false;
	}

	return isZiMo;
}
//和绝张
bool MethordHuClass::CheckHJZ_HU(bool isJue)
{
    if (isJue)
        return true;
    return false;
}
//箭刻
bool MethordHuClass::CheckJKE_HU(std::vector <int> &AllCard)
{   
	size_t s_size = AllCard.size();

	for (int i = 0; i != AllCard.size()-2; i++){
        if (AllCard[i] > 15)
			return false;

        if(AllCard[i] <10)
            continue;

		if (AllCard[i] == AllCard[i + 2])
			return true;
	}

	return false;
}
//圈风刻
bool MethordHuClass::CheckQFK_HU()
{
	return false;
}
//门风刻
bool MethordHuClass::CheckMFK_HU(int &feng, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileFirstCard() == 1 + feng * 2)
			return true;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileFirstCard() == 1 + feng * 2)
			return true;
	}
    return false;
}
//门前清
bool MethordHuClass::CheckMQQ_HU(bool isZiMo, std::list<CMjCardPile >& p_desk)
{
	return (p_desk.size() == 0 && (!isZiMo));
}
//平和
bool MethordHuClass::CheckPHe_HU(char jiang, std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	if (jiang < 20) return false;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
        if (it->GetPileType() != SPECIAL_TYPE_SHUN || it->GetPileFirstCard() < 20 )
			return false;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
        if (it->GetPileType() != SPECIAL_TYPE_SHUN || it->GetPileFirstCard() < 20)
			return false;
	}
	return true;
}
//四归一
int MethordHuClass::CheckSGY_HU(std::vector <int> &AllCard, std::list<CMjCardPile >& p_desk)
{
	int num_4G1 = 0;
	size_t s_size = AllCard.size();
	for (int i = 0; i != s_size-3; i++){
		if (AllCard[i] >20 && AllCard[i + 3] == AllCard[i])
		{
			num_4G1++;
			for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
				if ((it->GetPileType() == SPECIAL_TYPE_ANGANG || it->GetPileType() == SPECIAL_TYPE_MINGGANG) &&  AllCard[i] == it->GetPileFirstCard())
					num_4G1--;
			}

			
		}
	}

	return num_4G1;
}
//双同刻
bool MethordHuClass::CheckSTK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	char num_point[9];
	memset(num_point, 0, sizeof(num_point));
    
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
        if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard() > 20)
            num_point[it->GetPileFirstCard() % 10-1]++;
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
        if (it->GetPileType() != SPECIAL_TYPE_SHUN && it->GetPileFirstCard() > 20)
            num_point[it->GetPileFirstCard() % 10-1]++;
	}

	for (int i = 0; i != 9; i++){
		if (num_point[i] == 2)
			return true;
	}

    return false;
}
//双暗刻
bool MethordHuClass::CheckSAK_HU(int &angangnum, std::vector<CMjCardPile> &p_hand)
{
	int num_anke = angangnum;

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_PENG)
			num_anke++;
	}

    return num_anke == 2;
}
//暗杠
bool MethordHuClass::CheckANG_HU(int &angangnum)
{
	return (angangnum != 0);
}
//断幺
bool MethordHuClass::CheckDUY_HU(std::vector <int> &AllCard)
{
	for (vector <int>::iterator it = AllCard.begin(); it != AllCard.end(); it++){
		if (*it < 20 || *it % 10 == 1 || *it % 10 == 9)
			return false;
	}

    return true;
}
//一般高
int MethordHuClass::CheckYBG_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	int num_YBG = 0;
	vector<char> card_shun;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			card_shun.push_back(it->GetPileFirstCard());
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			card_shun.push_back(it->GetPileFirstCard());
	}

	sort(card_shun.begin(), card_shun.end());

	if (card_shun.size() >= 2){
		for (int i = 0; i < card_shun.size() - 1; i++){
			if (card_shun[i] == card_shun[i + 1]){
				num_YBG++;
				i++;
			}
		}
	}

	return num_YBG;
}
//喜相逢
int MethordHuClass::CheckXXF_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	int num_xxf = 0;
	vector<char> card_shun;

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			card_shun.push_back(it->GetPileFirstCard());
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
			card_shun.push_back(it->GetPileFirstCard());
	}

	if (card_shun.size() >= 2) {
		for (vector<char>::iterator it1 = card_shun.begin(); it1 != (card_shun.end() - 1);){
			bool gotone = false;
			for (vector<char>::iterator it2 = it1 + 1; it2 != card_shun.end(); it2++){
				if (*it1 % 10 == *it2 % 10 && *it1 / 10 != *it2 / 10){
					gotone = true;
					card_shun.erase(it2);
					card_shun.erase(it1);
					num_xxf++;
					break;
				}
			}

			if (gotone){
				if (card_shun.size() < 2)
					return num_xxf;
				it1 = card_shun.begin();
			}
			else{
				it1++;
			}
		}
	}

	return num_xxf;
}
//连六
bool MethordHuClass::CheckLLI_HU(int Card[49])
{
    for (int i = 20; i != 44; i++){
		if (Card[i] > 0 && Card[i + 1] > 0 && Card[i + 2] > 0 && Card[i + 3] > 0 && Card[i + 4] > 0 && Card[i + 5] > 0)
			return true;
	}
    return false;
}
//老少副
int MethordHuClass::CheckLSF_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	int num_LSF = 0;
	char laoshao[6];
	memset(laoshao, 0, sizeof(laoshao));

	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			char firstcardvalue = it->GetPileFirstCard();
			if (firstcardvalue % 10 == 1){
                laoshao[(firstcardvalue / 10 - 2)*2] += 1;
			}
			else if (firstcardvalue % 10 == 7){
                laoshao[(firstcardvalue / 10 - 2)*2+1] += 1;
			}
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() == SPECIAL_TYPE_SHUN)
		{
			char firstcardvalue = it->GetPileFirstCard();
			if (firstcardvalue % 10 == 1){
                laoshao[(firstcardvalue / 10 - 2)*2] += 1;
			}
			else if (firstcardvalue % 10 == 7){
                laoshao[(firstcardvalue / 10 - 2)*2 + 1] += 1;
			}
		}
	}

	for (int i = 0; i != 3;){
		if (laoshao[i * 2] >= 1 && laoshao[i * 2 + 1] >= 1){
            laoshao[i * 2] -= 1;
            laoshao[i * 2 + 1] -= 1;
			num_LSF++;
		}
		else{
			i++;
		}
	}

	return num_LSF;
}
//幺九刻	箭牌不计幺九刻
int MethordHuClass::CheckYJK_HU(std::vector<CMjCardPile> &p_hand, std::list<CMjCardPile >& p_desk)
{
	int num_YJK = 0;
	for (std::list<CMjCardPile >::iterator it = p_desk.begin(); it != p_desk.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN)
		{
			char firstcardvalue = it->GetPileFirstCard();
			if (firstcardvalue < 10 || (firstcardvalue >= 20 && (firstcardvalue % 10 == 1 || firstcardvalue % 10 == 9)))
				num_YJK++;
		}
	}

	for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
		if (it->GetPileType() != SPECIAL_TYPE_SHUN)
		{
			char firstcardvalue = it->GetPileFirstCard();
			if (firstcardvalue < 10 || (firstcardvalue >= 20 && (firstcardvalue % 10 == 1 || firstcardvalue % 10 == 9)))
				num_YJK++;
		}
	}

	return num_YJK;
}
//明杠
bool MethordHuClass::CheckMGA_HU(int &num_minggang)
{
	if (num_minggang == 1)
        return true;
    return false;
}
//缺一门 
bool MethordHuClass::CheckQ1M_HU(std::vector <int> &AllCard)
{
	size_t s_size = AllCard.size();
    int oneMen(0), twoMen(0), thrMen(0);
	for (size_t ii = 0; ii < s_size; ++ii)
    {
		int remTmp = AllCard[ii] / 10;
        if (remTmp == 2)
            ++oneMen;
        if (remTmp == 3)
            ++twoMen;
        if (remTmp == 4)
            ++thrMen;
    }
    if (oneMen == 0 && twoMen > 0 && thrMen > 0)
        return true;
    if (oneMen > 0 && twoMen == 0 && thrMen > 0)
        return true;
    if (oneMen > 0 && twoMen > 0 && thrMen == 0)
        return true;
    return false;
}
//无字
bool MethordHuClass::CheckMYZ_HU(std::vector <int> &AllCard)
{
	if (AllCard[0] > 15)
        return true;
    return false;
}
//边张
bool MethordHuClass::CheckPBH_HU(std::vector<CMjCardPile> &p_hand, char lastcardvalue, bool justone){
	if (!justone) return false;

	if (lastcardvalue % 10 == 3){
		for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
			if (it->GetPileType() == SPECIAL_TYPE_SHUN && (it->GetPileFirstCard() == (lastcardvalue - 2)))
				return true;
		}
	}else if (lastcardvalue % 10 == 7){
		for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
            if (it->GetPileType() == SPECIAL_TYPE_SHUN && (it->GetPileFirstCard() == lastcardvalue))
				return true;
		}
	}

	return false;
}
//坎张
bool MethordHuClass::CheckKZH_HU(std::vector<CMjCardPile> &p_hand, char lastcardvalue, bool justone){
	if (!justone) return false;

	if (lastcardvalue % 10 >= 2 && lastcardvalue % 10<=8){
		for (std::vector<CMjCardPile>::iterator it = p_hand.begin(); it != p_hand.end(); it++){
			if (it->GetPileType() == SPECIAL_TYPE_SHUN && (it->GetPileFirstCard() == (lastcardvalue - 1)))
				return true;
		}
	}

	return false;
}
//单调将
bool MethordHuClass::CheckDDJ_HU(char jiang, char lastcardvalue, bool justone)
{
	if (jiang == lastcardvalue && justone)
		return true;
    return false;
}
//自摸
bool MethordHuClass::CheckZMH_HU(bool isZiMo)
{
    if (isZiMo)
        return true;
    return false;
}
//花牌
bool CheckHUAP_HU();

//检查七对
bool MethordHuClass::Check7D_HU(int Card[])
{
	int num = 0;

	for (int i = 0; i != 34; i++){
        char cardvalue = alltypeCard[i]-1;
        int temp_num = Card[cardvalue];
		if (temp_num %2 != 0)
			return false;
		num += temp_num;
	}

	return (num == 14);
}
//检查十三幺
bool MethordHuClass::Chekc13Y_HU(int Card[])
{
	int num_y = 0;

	for (int i = 0; i != 13; i++){
        int temp_num = Card[yaoCard[i]-1];
		if (temp_num == 0)
			return false;
		num_y += temp_num;
	}

	return (num_y == 14);
}
