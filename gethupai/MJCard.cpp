#include "MJCard.h"
#include <algorithm>

//----------------------------------------------------------------------------------------------------------
//	【CMjCard】
//----------------------------------------------------------------------------------------------------------

CMjCard::CMjCard() :m_card(0)
{
}

CMjCard::CMjCard(const CMjCard &card) : m_card(card.m_card)
{
}

CMjCard::CMjCard(char card) : m_card(card)
{
}

CMjCard::CMjCard(char type, char value) : m_card(value)
{
	m_card |= type << 4;
}

CMjCard::operator char() const
{
	return char(m_card);
}

CMjCard::~CMjCard()
{

}

char CMjCard::MakeCardChar(char type, char c)
{
	return c | (type << 4);
}

char CMjCard::AsCard()
{
	return m_card;
}

char CMjCard::Type() const
{
	return (char)(m_card >> 4);
}

char CMjCard::Name() const
{
	return m_card & 0xf;
}

char CMjCard::Value() const
{
	char temp_this = m_card & 0xf;
	return temp_this;
}

CMjCard & CMjCard::operator = (const CMjCard &c)
{
	if (&c == this)
	{
		return *this;
	}
	m_card = c.m_card;
	return *this;
}

CMjCard & CMjCard::operator = (char card)
{
	m_card = card;
	return *this;
}

bool CMjCard::operator == (const CMjCard &c) const
{
	if (c.Name() == this->Name() && c.Type() == this->Type())
	{
		return true;
	}
	else
	{
		return false;
	}
}


//----------------------------------------------------------------------------------------------------------
//	【CMjCardPile】
//----------------------------------------------------------------------------------------------------------

// 设置结构牌【碰或杠】


void CMjCardPile::SetCardPile(char FirstCard, int iCardType)
{
	m_iCardType = iCardType;
	m_FirstCard = FirstCard;
}

int CMjCardPile::GetPileCardNums()
{
	if (m_iCardType == SPECIAL_TYPE_MINGGANG || m_iCardType == SPECIAL_TYPE_ANGANG || m_iCardType == SPECIAL_TYPE_PENGGANG)
	{
		return 4;
	}
	else if (m_iCardType == SPECIAL_TYPE_PENG || m_iCardType == SPECIAL_TYPE_SHUN)
	{
		return 3;
	}
}

CMjCardPile::CMjCardPile(int iCardType, int FirstCard)
{
	SetCardPile(FirstCard,iCardType);
}

void CMjCardPile::PutInCharArray(std::vector <int> &p_cards)
{
	if (m_iCardType == SPECIAL_TYPE_SHUN){
		p_cards.push_back(m_FirstCard.AsCard());
		p_cards.push_back(m_FirstCard.AsCard()+1);
		p_cards.push_back(m_FirstCard.AsCard()+2);
	}
	else
	{
		int cardnum = 0;
		if (m_iCardType == SPECIAL_TYPE_PENG)
		{
			cardnum = 3;
		}
		else{
			cardnum = 4;
		}
		for (int i = 0; i != cardnum; i++){
			p_cards.push_back(m_FirstCard.AsCard());
		}
	}
}

void CMjCardPile::PutInCharArray(int cards[49])
{
	if (m_iCardType == SPECIAL_TYPE_SHUN){
		cards[m_FirstCard.AsCard()-1] += 1;
		cards[m_FirstCard.AsCard()] += 1;
		cards[m_FirstCard.AsCard()+1] += 1;
	}
	else
	{
		int cardnum = 0;
		if (m_iCardType == SPECIAL_TYPE_PENG)
		{
			cardnum = 3;
		}
		else{
			cardnum = 4;
		}
		cards[m_FirstCard.AsCard()-1] += cardnum;
	}
}