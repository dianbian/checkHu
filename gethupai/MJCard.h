#ifndef _MJ_CARD_H_
#define _MJ_CARD_H_

#include <vector>
#include <string>
#include "BaseDefine.h"

//----------------------------------------------------------------------------------------------------------
//	【CMjCard】类 
//----------------------------------------------------------------------------------------------------------

class CMjCard
{
public:

	CMjCard();
	CMjCard(const CMjCard &card);
	CMjCard(char card);
	CMjCard(char type, char name);
	~CMjCard();

	static char MakeCardChar(char type, char c);

	char AsCard();
	char Type() const;
	char Name() const;
	char Value() const;
	operator char() const;


	CMjCard & operator = (const CMjCard &c);
	CMjCard & operator = (char card);
	bool operator > (const CMjCard &c) const;
	bool operator < (const CMjCard &c) const;
	bool operator >= (const CMjCard &c) const;
	bool operator <= (const CMjCard &c) const;
	bool operator == (const CMjCard &c) const;

private:
	char m_card;
};


//----------------------------------------------------------------------------------------------------------
//	【CMjCardPile】
//----------------------------------------------------------------------------------------------------------

class CMjCardPile
{
public:
	CMjCardPile(int iCardType, int FirstCard);
	CMjCardPile(void) :m_iCardType(SPECIAL_TYPE_NONE){}
	~CMjCardPile(void){}
public:
	int	    GetPileCardNums();										// 结构牌数量

	void	SetCardPile(char FirstCard, int iCardType);			//设置结构牌

	int     GetPileType(){ return m_iCardType; }

	char	GetPileFirstCard(){ return m_FirstCard.AsCard(); }

	void    PutInCharArray(std::vector <int> &p_cards);//放到数组里
	void    PutInCharArray(int cards[49]);//放到数组里

private:
	CMjCard		m_FirstCard;//放牌
	int         m_iCardType;//结构牌的类型
};

#endif	//_MJ_CARD_H_


