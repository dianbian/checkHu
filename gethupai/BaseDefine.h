#ifndef _BASEDEFINE_H_
#define _BASEDEFINE_H_

//1 3 5 7��ʾ���ƶ�������(16)
//11 13 15��ʾ�����з���(12)
//21-29��ʾ������(36)
//31-39��ʾ������(36)
//41-49��ʾ������(36)
//51-58��ʾ���ƴ����ﶬ÷�����(8)

enum //�����Ƶ�����
{
	CARD_TYPE_FENG = 0,		//����������
	CARD_TYPE_ZI,			//�׷�����
	CARD_TYPE_WAN,			//��
	CARD_TYPE_TIAO,			//��
	CARD_TYPE_TONG,			//Ͳ
	CARD_TYPE_HUA,			//��
};

enum //������ӵ�����
{
	SPECIAL_TYPE_NONE 	= 0x00,		//��
	SPECIAL_TYPE_PENG	= 0x01,		//��
	SPECIAL_TYPE_SHUN = 0x02,		//˳��
	SPECIAL_TYPE_MINGGANG = 0x04,	//����
	SPECIAL_TYPE_ANGANG = 0x08,		//����
	SPECIAL_TYPE_PENGGANG = 0x10,   //���ܣ����¸�
};


enum//���ƵļƷ�����
{
	HU_NO = 0x0000,
	HUTYPE_1_DSX = 0x00000001,		//����ϲ
	HUTYPE_1_DSY = 0x00000002,		//����Ԫ
	HUTYPE_1_LYS = 0x00000004,		//��һɫ
	HUTYPE_1_JLBD = 0x00000008,		//��������
	HUTYPE_1_4G = 0x00000010,			//�ĸ�
	HUTYPE_1_L7D = 0x00000020,		//���߶�
	HUTYPE_1_13Y = 0x00000040,		//ʮ����
	HUTYPE_1_QYJ = 0x00000080,		//���۾�
	HUTYPE_1_XSX = 0x00000100,		//С��ϲ
	HUTYPE_1_XSY = 0x00000200,		//С��Ԫ
	HUTYPE_1_ZYS = 0x00000400,		//��һɫ
	HUTYPE_1_4AK = 0x00000800,		//�İ���
	HUTYPE_1_1SSLH = 0x00001000,		//һɫ˫����
	HUTYPE_1_1SSTS = 0x00002000,		//һɫ��ͬ˳
	HUTYPE_1_1SSJG = 0x00004000,		//һɫ�Ľڸ�
	HUTYPE_1_1SSBG = 0x00008000,		//һɫ�Ĳ���
	HUTYPE_1_3G	 = 0x00010000,		//����
	HUTYPE_1_HYJ = 0x00020000,		//���۾�
	HUTYPE_1_7D = 0x00040000,		//�߶�
	HUTYPE_1_7XBK = 0x00080000,		//���ǲ���
	HUTYPE_1_QSK = 0x00100000,		//ȫ˫��
	HUTYPE_1_Q1S = 0x00200000,		//��һɫ
	HUTYPE_1_1S3TS = 0x00400000,		//һɫ��ͬ˳
	HUTYPE_1_1S3JG = 0x00800000,		//һɫ���ڸ�
	HUTYPE_1_QD = 0x01000000,		//ȫ��
	HUTYPE_1_QZ = 0x02000000,		//ȫ��
	HUTYPE_1_QX = 0x04000000,		//ȫС
	HUTYPE_1_QL = 0x08000000,		//����
	HUTYPE_1_3SSLH = 0x10000000,		//��ɫ˫����
	HUTYPE_1_1S3BG = 0x20000000,		//һɫ������
	HUTYPE_1_QDW = 0x40000000,		//ȫ����
	HUTYPE_1_3TK = 0x80000000,		//��ͬ��

	HUTYPE_2_3AK = 0x00000001,		//������
	HUTYPE_2_QBK = 0x00000002,		//ȫ����
	HUTYPE_2_ZHL = 0x00000004,		//�����
	HUTYPE_2_DY5 = 0x00000008,		//������
	HUTYPE_2_XY5 = 0x00000010,		//С����
	HUTYPE_2_3FK = 0x00000020,		//�����
	HUTYPE_2_HL = 0x00000040,		//����
	HUTYPE_2_TBD = 0x00000080,		//�Ʋ���
	HUTYPE_2_3S3TS = 0x00000100,		//��ɫ��ͬ˳
	HUTYPE_2_3S3JG = 0x00000200,		//��ɫ���ڸ�
	HUTYPE_2_WFH = 0x00000400,		//�޷���
	HUTYPE_2_MSHC = 0x00000800,		//���ֻش�
	HUTYPE_2_HDLY = 0x00001000,		//��������
	HUTYPE_2_GSKH = 0x00002000,		//���Ͽ���
	HUTYPE_2_QGH = 0x00004000,		//���ܺ�
	HUTYPE_2_PPH = 0x00008000,		//������
	HUTYPE_2_H1S = 0x00010000,		//��һɫ
	HUTYPE_2_3S3BG = 0x00020000,		//��ɫ������
	HUTYPE_2_5MQ = 0x00040000,		//������
	HUTYPE_2_QQR = 0x00080000,		//ȫ����
	HUTYPE_2_SAG = 0x00100000,		//˫����
	HUTYPE_2_SJK = 0x00200000,		//˫����
	HUTYPE_2_QDY = 0x00400000,		//ȫ����
	HUTYPE_2_BQR = 0x00800000,		//������
	HUTYPE_2_SMG = 0x01000000,		//˫����
	HUTYPE_2_HJZ = 0x02000000,		//�;���
	HUTYPE_2_JK = 0x04000000,		//����
	HUTYPE_2_QFK = 0x08000000,		//Ȧ���
	HUTYPE_2_MFK = 0x10000000,		//�ŷ��
	HUTYPE_2_MQQ = 0x20000000,		//��ǰ��
	HUTYPE_2_PH = 0x40000000,		//ƽ��
	HUTYPE_2_STK = 0x80000000,		//˫ͬ��

	HUTYPE_3_4G1 = 0x00000003,		//�Ĺ�һ	���2��ռ2λ	
	HUTYPE_3_SAK = 0x00000004,		//˫����
	HUTYPE_3_AG = 0x00000008,		//����
	HUTYPE_3_DY = 0x00000010,		//����
	HUTYPE_3_YBG = 0x00000060,		//һ���	���2��ռ2λ
	HUTYPE_3_XXF = 0x00000180,		//ϲ���	���2��ռ2λ
	HUTYPE_3_LL = 0x00000200,		//����
	HUTYPE_3_LSF = 0x00000C00,		//���ٸ�	���2��ռ2λ
	HUTYPE_3_YJK = 0x00007000,		//�۾ſ�	���4��ռ3λ
	HUTYPE_3_MG = 0x00008000,		//����
	HUTYPE_3_Q1M = 0x00010000,		//ȱһ��
	HUTYPE_3_WZ = 0x00020000,		//����
	HUTYPE_3_BZ = 0x00040000,		//����
	HUTYPE_3_KZ = 0x00080000,		//����
	HUTYPE_3_DDJ = 0x00100000,		//������
	HUTYPE_3_ZM = 0x00200000,		//����
	HUTYPE_3_HP = 0x03C00000,		//����	���8��ռ 4λ
	HUTYPE_3_TING = 0x04000000,		//����
	HUTYPE_3_ZHUANG = 0x08000000	//ׯ��
};


enum//���ƵļƷ�
{
	FAN_DSX = 88,		//����ϲ
	FAN_DSY = 88,		//����Ԫ
	FAN_LYS = 88,		//��һɫ
	FAN_JLBD = 88,		//��������
	FAN_4G = 88,			//�ĸ�
	FAN_L7D = 88,		//���߶�
	FAN_13Y = 88,		//ʮ����
	FAN_QYJ = 64,		//���۾�
	FAN_XSX = 64,		//С��ϲ
	FAN_XSY = 64,		//С��Ԫ
	FAN_ZYS = 64,		//��һɫ
	FAN_4AK = 64,		//�İ���
	FAN_1SSLH = 64,		//һɫ˫����
	FAN_1SSTS = 48,		//һɫ��ͬ˳
	FAN_1SSJG = 48,		//һɫ�Ľڸ�
	FAN_1SSBG = 32,		//һɫ�Ĳ���
	FAN_3G = 32,		//����
	FAN_HYJ = 32,		//���۾�
	FAN_7D = 24,		//�߶�
	FAN_7XBK = 24,		//���ǲ���
	FAN_QSK = 24,		//ȫ˫��
	FAN_Q1S = 24,		//��һɫ
	FAN_1S3TS = 24,		//һɫ��ͬ˳
	FAN_1S3JG = 24,		//һɫ���ڸ�
	FAN_QD = 24,		//ȫ��
	FAN_QZ = 24,		//ȫ��
	FAN_QX = 24,		//ȫС
	FAN_QL = 16,		//����
	FAN_3SSLH = 16,		//��ɫ˫����
	FAN_1S3BG = 16,		//һɫ������
	FAN_QDW = 16,		//ȫ����
	FAN_3TK = 16,		//��ͬ��

	FAN_3AK = 16,		//������
	FAN_QBK = 12,		//ȫ����
	FAN_ZHL = 12,		//�����
	FAN_DY5 = 12,		//������
	FAN_XY5 = 12,		//С����
	FAN_3FK = 12,		//�����
	FAN_HL = 8,		//����
	FAN_TBD = 8,		//�Ʋ���
	FAN_3S3TS = 8,		//��ɫ��ͬ˳
	FAN_3S3JG = 8,		//��ɫ���ڸ�
	FAN_WFH = 8,		//�޷���
	FAN_MSHC = 8,		//���ֻش�
	FAN_HDLY = 8,		//��������
	FAN_GSKH = 8,		//���Ͽ���
	FAN_QGH = 8,		//���ܺ�
	FAN_PPH = 6,		//������
	FAN_H1S = 6,		//��һɫ
	FAN_3S3BG = 6,		//��ɫ������
	FAN_5MQ = 6,		//������
	FAN_QQR = 6,		//ȫ����
	FAN_SAG = 6,		//˫����
	FAN_SJK = 6,		//˫����
	FAN_QDY = 4,		//ȫ����
	FAN_BQR = 4,		//������
	FAN_SMG = 4,		//˫����
	FAN_HJZ = 4,		//�;���
	FAN_JK = 2,		//����
	FAN_QFK = 2,		//Ȧ���
	FAN_MFK = 2,		//�ŷ��
	FAN_MQQ = 2,		//��ǰ��
	FAN_PH = 2,		//ƽ��
	FAN_4G1 = 2,		//�Ĺ�һ

	FAN_STK = 2,		//˫ͬ��
	FAN_SAK = 2,		//˫����
	FAN_AG = 2,		//����
	FAN_DY = 2,		//����
	FAN_YBG = 1,		//һ���
	FAN_XXF = 1,		//ϲ���
	FAN_LL = 1,		//����
	FAN_LSF = 1,		//���ٸ�
	FAN_YJK = 1,		//�۾ſ�
	FAN_MG = 1,		//����
	FAN_Q1M = 1,		//ȱһ��
	FAN_WZ = 1,		//����
	FAN_BZ = 1,		//����
	FAN_KZ = 1,		//����
	FAN_DDJ = 1,		//������
	FAN_ZM = 1,		//����
	FAN_HP = 1,			//����
	FAN_TING = 2,		//����
	FAN_ZHUANG = 2		//ׯ��
};

//�ƵĶ�������
enum{
	CARDTYPE_LASTGOT = 0x00000001,		//��ǽ�����һ����
	CARDTYPE_LASTOUT = 0x00000002,		//��������һ����
	CARDTYPE_AFTERG = 0x00000004,		//�ԼҸ��ƺ�������
	CARDTYPE_STOPG = 0x00000008,		//���ܵ���
	CARDTYPE_LASTLEFT = 0x00000010		//������ֻʣ��һ��
};


#endif
