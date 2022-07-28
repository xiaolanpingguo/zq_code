#include <iostream>
#include <time.h>


class CHero
{
public:
	int hp;
	int mp;
};

class CMonster
{
	int m_iHp;
	int m_iMp;
	int m_iAttact;
public:
	virtual void SetShuXing(int hp,int mp,int att)
	{}
	virtual const char* Name()
	{
		return 0;
	}
	virtual void Attack(CHero* pHero)
	{
	
	}
};

class CFire:public CMonster
{
public:
	const char* Name()
	{
		return "ª—Êπ÷";
	}
	void Attack(CHero* pHero)
	{
		//ÀÊª˙π•ª˜”¢–€6 - 10
		pHero->hp -= (rand() % 5) + 6;
	}
};

class CIce:public CMonster
{
public:
	const char* Name()
	{
		return "±˘—©π÷";
	}
	void Attack(CHero* pHero)
	{
		//ÀÊª˙π•ª˜”¢–€6 - 10
		pHero->hp -= (rand() % 3) + 2;
		pHero->mp -= (rand() % 3) + 2;
	}
};

class CBoss : public  CMonster
{
public:
	const char* Name()
	{
		return "Boss";
	}
	void Attack(CHero* pHero)
	{
		if(rand() % 5 == 0)
			pHero->hp = 0;
	}
};



void main()
{
	srand((unsigned int)time(0));

	CHero hero;
	hero.hp = 100;
	hero.mp = 50;
	
	CFire fire;
	CIce ice;
	CBoss boss;

	CMonster* pMonster[] = {&fire,&ice,&boss};

	while(1)
	{
		system("pause");
		int i = rand() % 3;
		//∂‡Ã¨
		std::cout<<"”ˆµΩ¡À"<<pMonster[i]->Name()<<std::endl;

		pMonster[i]->Attack(&hero);

		std::cout<<"”¢–€HP:"<<hero.hp<<" MP:"<<hero.mp<<std::endl;
		if(hero.hp <= 0)
			break;
	}
	system("pause");
}