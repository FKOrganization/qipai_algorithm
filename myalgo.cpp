#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

const int hupai_hushu = 12;//����������͵���

const int hushu_eat_hei_3 = 1;		//��ɫ���ӣ������γɣ�
const int hushu_own_hei_3 = 3;		//��ɫ���ӣ�ԭ�ֳ��У�
const int hushu_eat_hei_4 = 6;		//��ɫ���ӣ������γɣ�
const int hushu_own_hei_4 = 9;		//��ɫ��ˮ��ԭ�ֳ��У�
const int hushu_both_hei_2710 = 3;	//��ɫ����ʮ��������ԭ�����ԭ�֣�

const int hushu_eat_hong_3 = 3;		//��ɫ���ӣ������γɣ�
const int hushu_own_hong_3 = 6;		//��ɫ���ӣ�ԭ�ֳ��У�
const int hushu_eat_hong_4 = 9;		//��ɫ���ӣ������γɣ�
const int hushu_own_hong_4 = 12;	//��ɫ��ˮ��ԭ�ֳ��У�
const int hushu_both_hong_2710 = 6;	//��ɫ����ʮ��������ԭ�����ԭ�֣�

									//�⼸�ֲ������
const int hushu_hei_lianzi = 0;				//��ɫ����
const int hushu_hong_lianzi = 0;			//��ɫ����
const int hushu_heiheihong_banbianzi = 0;	//�ںں� �����
const int hushu_honghonghei_banbianzi = 0;	//���� �����

typedef struct step
{
	int curr_try_card;	   //���Ե��ƣ�1-20 1-10��Ӧ����1-10,11-20��Ӧ����1-10
	int curr_try_type;	  //���Զ��Ʋ��˳�ӣ�����ӣ����ڣ��ںں죩������ʮ ��4������
	int curr_hushu;
	int curr_is_ok;
}STEP;



//��������ֵ-1˵�����ܺ�����ĳЩ�Ʋ��ܶ��ɷ���;
//����ֵ���ڵ���0˵�����ܺ��ƣ��������ܳɷ���,����������������в��ƿ�������������Ǹ�
int __get_hushu_no_gun_kan(int cards[21])//��0λû�ã�Ϊ�˺�1-10��Ӧ�������㿴
{
	STEP steps[7];
	memset(steps, 0, sizeof(STEP) * 7);

	int max_hushu = -1;
	int curr_step = -1;
	int curr_try_card = 1;
	int curr_type_finded = 1;

	while (true)
	{
	label_next_type:
		if (curr_type_finded)
		{
			curr_type_finded = 0;
			int has_next_card = 0;
			//���Դӵ�ǰ�����curr_try_card��20ÿһ����
			for (int i = curr_try_card; i <= 20; i++)
			{
				if (cards[i] > 0)
				{
					curr_try_card = i;
					curr_step++;
					steps[curr_step].curr_try_card = curr_try_card;
					steps[curr_step].curr_hushu = -1;

					has_next_card = 1;
					break;
				}
			}
			//û����������,���������������һ·�����еĶ��������ȷ�����͡�Ѱ�����ĺ���
			if (!has_next_card)
			{
				int all_hushu = 0;
				for (int i = 0; i <= curr_step; ++i)
					all_hushu += steps[i].curr_hushu;
				if (all_hushu > max_hushu)
					max_hushu = all_hushu;
				//���ݵ���һ��
				goto flag_huishu;
			}
		}
		//��ɫ˳��
		if (steps[curr_step].curr_try_type == 0)//��һ�ν�����״̬
		{
			steps[curr_step].curr_try_type = 11;
			if (curr_try_card <= 8)//
			{
				if (cards[curr_try_card + 1] > 0 && cards[curr_try_card + 2] > 0)//�к�˳
				{
					steps[curr_step].curr_try_card = curr_try_card;
					steps[curr_step].curr_hushu = hushu_hei_lianzi;//��˳���� 
					steps[curr_step].curr_is_ok = 1;
					curr_type_finded = 1;

					cards[curr_try_card] -= 1;
					cards[curr_try_card + 1] -= 1;
					cards[curr_try_card + 2] -= 1;
					goto label_next_type;
				}
			}
		}
		//��ɫ�����:�ں��
		if (steps[curr_step].curr_try_type == 11)
		{
			//��ɫ�����
			steps[curr_step].curr_try_type = 12;
			//�����û�к�ɫ����� �ں��
			if (curr_try_card <= 10 && cards[curr_try_card] >= 1 && cards[curr_try_card + 10] >= 2)
			{
				steps[curr_step].curr_try_card = curr_try_card;
				steps[curr_step].curr_hushu = hushu_honghonghei_banbianzi;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;

				cards[curr_try_card] -= 1;
				cards[curr_try_card + 10] -= 2;
				goto label_next_type;
			}
		}
		//��ɫ�����:�ںں�
		if (steps[curr_step].curr_try_type == 12)
		{
			steps[curr_step].curr_try_type = 13;
			//�����û�к�ɫ����� �ںں�
			if (curr_try_card <= 10 && cards[curr_try_card] >= 2 && cards[curr_try_card + 10] >= 1)
			{
				steps[curr_step].curr_try_card = curr_try_card;
				steps[curr_step].curr_hushu = hushu_heiheihong_banbianzi;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;

				cards[curr_try_card] -= 2;
				cards[curr_try_card + 10] -= 1;
				goto label_next_type;
			}
		}

		//��ɫ2710
		if (steps[curr_step].curr_try_type == 13)
		{
			steps[curr_step].curr_try_type = 14;
			if (curr_try_card <= 10 && curr_try_card == 2 && cards[7] > 0 && cards[10] > 0)
			{
				steps[curr_step].curr_try_card = 2;
				steps[curr_step].curr_hushu = hushu_both_hei_2710;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;

				cards[2] -= 1;
				cards[7] -= 1;
				cards[10] -= 1;
				goto label_next_type;
			}
		}

		//��ɫ˳��
		if (steps[curr_step].curr_try_type == 14) {
			steps[curr_step].curr_try_type = 21;
			if (curr_try_card > 10 && curr_try_card <= 18)
			{
				if (cards[curr_try_card + 1] > 0 && cards[curr_try_card + 2] > 0)
				{
					steps[curr_step].curr_try_card = curr_try_card;
					steps[curr_step].curr_hushu = hushu_hong_lianzi;
					steps[curr_step].curr_is_ok = 1;
					curr_type_finded = true;

					cards[curr_try_card] -= 1;
					cards[curr_try_card + 1] -= 1;
					cards[curr_try_card + 2] -= 1;
					goto label_next_type;
				}
			}
		}
		//��ɫ����֣���ں�
		if (steps[curr_step].curr_try_type == 21)
		{
			steps[curr_step].curr_try_type = 22;
			if (curr_try_card > 10 && cards[curr_try_card] >= 1 && cards[curr_try_card - 10] >= 2)
			{
				steps[curr_step].curr_try_card = curr_try_card;
				steps[curr_step].curr_hushu = hushu_heiheihong_banbianzi;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;
				cards[curr_try_card] -= 1;
				cards[curr_try_card - 10] -= 2;
				goto label_next_type;
			}
		}
		//��ɫ����֣�����
		if (steps[curr_step].curr_try_type == 22)
		{
			steps[curr_step].curr_try_type = 23;
			if (curr_try_card > 10 && cards[curr_try_card] >= 2 && cards[curr_try_card - 10] >= 1)
			{
				steps[curr_step].curr_try_card = curr_try_card;
				steps[curr_step].curr_hushu = hushu_honghonghei_banbianzi;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;
				cards[curr_try_card] -= 2;
				cards[curr_try_card - 10] -= 1;
				goto label_next_type;
			}
		}
		//��ɫ2710
		if (steps[curr_step].curr_try_type == 23)
		{
			steps[curr_step].curr_try_type = 24;
			if (curr_try_card == 12 && cards[17] > 0 && cards[20] > 0)
			{
				steps[curr_step].curr_try_card = 12;
				steps[curr_step].curr_hushu = hushu_both_hong_2710;
				steps[curr_step].curr_is_ok = 1;
				curr_type_finded = true;

				cards[12] -= 1;
				cards[17] -= 1;
				cards[20] -= 1;
				goto label_next_type;
			}
		}

		//����Ƿ�����������������ָ��ǰ����curr_step���curr_try_card�Ķ�Ӧcurr_try_type�ķָ�����curr_is_ok��true
	flag_huishu:
		if (curr_step < 0)
			goto finish;
		if (1 != steps[curr_step].curr_is_ok || steps[curr_step].curr_try_type == 24)//�ü�����ȷ�ģ�23��ʾ���һ��������ж����ˣ�
		{
			memset(&steps[curr_step], 0, sizeof(STEP));
			curr_step--;
			goto flag_huishu;
		}
		//�ҵ��˺Ϸ�������
		curr_try_card = steps[curr_step].curr_try_card;
		int tp = steps[curr_step].curr_try_type;
		if (tp == 11 || tp == 21)//��ɫ���ɫ˳��
		{
			cards[curr_try_card] += 1;
			cards[curr_try_card + 1] += 1;
			cards[curr_try_card + 2] += 1;
		}
		else if (tp == 12)//��ɫ���ں������
		{
			cards[curr_try_card] += 1;
			cards[curr_try_card + 10] += 2;
		}
		else if (tp == 13)//��ɫ���ںں�����
		{
			cards[curr_try_card] += 2;
			cards[curr_try_card + 10] += 1;
		}
		else if (tp == 22)//��ɫ:��ںڰ����
		{
			cards[curr_try_card] += 1;
			cards[curr_try_card - 10] += 2;
		}
		else if (tp == 23)//��ɫ:���ڰ����
		{
			cards[curr_try_card] += 2;
			cards[curr_try_card - 10] += 1;
		}
		else if (tp == 14 || tp == 24)//��ɫ���ɫ2,7,10
		{
			if (curr_try_card != 2 && curr_try_card != 22)
			{
				//__asm{ int 3 };
			}
			cards[2] += 1;
			cards[7] += 1;
			cards[10] += 1;
			////���һ���������ɫ2710����Ҫ����
			//if (tp == 24)
			//{
			//	curr_step--;
			//	if (curr_step == 0)
			//		goto finish;
			//	goto flag_huishu;
			//}

		}
	}

finish:
	return max_hushu;
}


//��������Ƶĺ���,��ʾ��� cards �����curr_eat_card ���ǳԵ��ƣ�����ʱ�������ɶ��ӡ�curr_eat_card����1-20
int get_hushu(int cards[21], int curr_eat_card = 0)
{
	int gunzi_kanzi_hushu = 0;
	for (int i = 1; i <= 10; ++i) {
		if (cards[i] == 4) //��ɫ��ˮ��ԭ�ֳ��У�
		{
			gunzi_kanzi_hushu += hushu_own_hei_4;
			cards[i] = 0;
		}
		if (cards[i] == 3)//��ɫ���ӣ�ԭ�ֳ��У�	
		{
			gunzi_kanzi_hushu += hushu_own_hei_3;
			cards[i] = 0;
		}
	}

	for (int i = 11; i <= 20; ++i) {
		if (cards[i] == 4) //��ɫ��ˮ��ԭ�ֳ��У�
		{
			gunzi_kanzi_hushu += hushu_own_hong_4;
			cards[i] = 0;
		}
		if (cards[i] == 3)//��ɫ���ӣ�ԭ�ֳ��У�	
		{
			gunzi_kanzi_hushu += hushu_own_hong_3;
			cards[i] = 0;
		}
	}
	//ͳ���Ƶ�����������ֻʣ��ÿ�������2���ˡ�
	int two_num = 0;//ͳ�ƶ�������
	for (int i = 1; i <= 20; i++) {
		if (2 == cards[i] && i != curr_eat_card)
			two_num += 1;
	}
	int total_hushu = gunzi_kanzi_hushu;
	///////////////////////////////////////////////////////////
	/*int other_hushu = -1;
	//����cards��������ǳԵģ���������ɵ����Ķ��ӳɷ�
	if (curr_eat_card !=0)
	{
	int other_hushu1 = -1;
	int other_hushu2 = -1;
	if (cards[curr_eat_card] == 2)//������ƿ�����ɵ��ǵ�������,�ж��º���
	{
	cards[curr_eat_card] = 0;
	other_hushu1 = __get_hushu_no_gun_kan(cards);
	cards[curr_eat_card] = 2;//��ԭ
	}
	else
	{
	other_hushu2 = __get_hushu_no_gun_kan(cards);
	}
	other_hushu = other_hushu1 > other_hushu2 ? other_hushu1 : other_hushu2;
	}
	else//���ϵ��Ʋ������ж��ӵ�������
	{
	other_hushu = __get_hushu_no_gun_kan(cards);
	}
	if (other_hushu < 0)
	return -1;
	else
	return total_hushu + other_hushu;*/
	/////////////////////////////////////////////////////
	/*// �������ӡ�����˳�ӣ�����֣�����ʮ��������ɣ����������ɷ���
	if (sum % 3 == 0) {
	// ���������˳�ӵĺ�Ϣ
	int other_hushu = __get_hushu_no_gun_kan(cards);
	if (other_hushu < 0) //������ɷ�
	return -1;
	return total_hushu + other_hushu;
	}
	else {
	// ������,����ȥ��ÿ�����ӣ��ж�ʣ�µġ�ƽʱ��ͨ���Ӳ��ܳ��֣�ֻ�к���ʱ��ԳɵĶ��Ӳ��ܵ�������
	int max_hushu = -1;
	int tmp_cards[21];
	for (int i = 1; i <= 20; i++) {
	if (cards[i] == 2 && curr_eat_card == i)
	{
	memcpy(tmp_cards, cards, sizeof(tmp_cards));
	tmp_cards[i] = 0;
	int other_hushu = __get_hushu_no_gun_kan(tmp_cards);//�����涼ƥ����ɲ�����ڵ����Ķ���
	if (other_hushu >= 0) {
	if (other_hushu > max_hushu)
	max_hushu = other_hushu;
	}
	}
	}
	if (max_hushu < 0)//�����������еĶ��ӣ���û�ɷ���˵�����ܺ�
	return -1;
	return 	total_hushu + max_hushu;
	}
	*/
	// ��ǰ�Ե���֮�ⲻ�����ӡ�����˳�ӣ�����֣�����ʮ��������ɣ����������ɷ���
	if (two_num == 0) {
		// ���������˳�ӵĺ�Ϣ
		int other_hushu = __get_hushu_no_gun_kan(cards);
		if (other_hushu < 0) //������ɷ�
			return -1;
		return total_hushu + other_hushu;
	}
	else {
		// ��ǰ�Ե���֮�������,����ȥ��ÿ�����ӣ��ж�ʣ�µġ�ƽʱ��ͨ���Ӳ��ܳ��֣�ֻ�к���ʱ��������ҽ��ж��Ӳ��ܵ�������
		int max_hushu = -1;
		int tmp_cards[21];
		for (int i = 1; i <= 20; i++) {
			if (cards[i] == 2 && i != curr_eat_card)// ȥ���������ӣ�����ա��Ե����Ķ��ӱ����ܹ��ɷ�
			{
				memcpy(tmp_cards, cards, sizeof(tmp_cards));
				tmp_cards[i] = 0;
				int other_hushu = __get_hushu_no_gun_kan(tmp_cards);
				if (other_hushu >= 0) {
					if (other_hushu > max_hushu)
						max_hushu = other_hushu;
				}
			}
		}
		if (max_hushu < 0)//�����������еĶ��ӣ���û�ɷ���˵�����ܺ�
			return -1;
		return 	total_hushu + max_hushu;
	}

}


typedef struct {
	int can_hupai;		//�����ܷ����
	int hushu;
	int eat_count;		//�ܳԵ���������
	int eat_with[6][4];	//�ܱ���Щ���ͳ�
	int eat_kind;	//�ܷ�ԣ��Ƿ���Ҫ����
}EatResult;
//  2 3 4 5 6 7 8
//i   x x x		����
//i		x x x	����
//i		  x	x x ����
//		  xx	�Գɿ���
//		  XX	�����
//		 2710	����ʮ

//��������
//��ɫ
const int EatTo_hong_4 = 1;
const int EatTo_hong_3 = 2;
const int EatTo_hong_2710 = 3;
const int EatTo_hong_lianzi = 4;
const int EatTo_hong_banbianzi = 5;//����
const int EatTo_hong_duizi = 6;
//��ɫ
const int EatTo_hei_4 = 7;
const int EatTo_hei_3 = 8;
const int EatTo_hei_2710 = 9;
const int EatTo_hei_lianzi = 10;
const int EatTo_hei_banbianzi = 11;//�ںں�
const int EatTo_hei_duizi = 12;

const char * EatName[13] = {
	NULL,
	"�� ��ˮ",
	"�� ����",
	"�� 2710",
	"�� ����",
	"�� �����",
	"�� ����",

	"�� ��ˮ",
	"�� ����",
	"�� 2710",
	"�� ����",
	"�� �����",
	"�� ����",
};

//�ܷ���ƣ����Ƶ� card��Ӧ��1-20��shown_hushu��֮ǰ�ĺ���
EatResult can_eat(int cards[21], int card, int shown_hushu)
{
	EatResult result;
	memset(&result, 0, sizeof(EatResult));
	int tmp[21] = { 0 };
	//�ȳ�����ƣ�Ȼ���ж��Ƿ����
	memcpy(tmp, cards, sizeof(tmp));
	tmp[card]++;
	int hushu = get_hushu(tmp, card);
	if (hushu > -1 && shown_hushu + hushu > hupai_hushu) {
		result.can_hupai = 1;
		result.hushu = shown_hushu + hushu;
	}
	else {
		result.can_hupai = 0;
		result.hushu = -1;
	}
	//�п��ؿ�
	if (cards[card] == 3) {
		memcpy(tmp, cards, sizeof(tmp));
		tmp[card]++;

		result.eat_with[result.eat_count][0] = card;
		result.eat_with[result.eat_count][1] = card;
		result.eat_with[result.eat_count][2] = card;
		if (card <= 10)
			result.eat_with[result.eat_count][3] = EatTo_hei_4;//�ڿ�ˮ
		else
			result.eat_with[result.eat_count][3] = EatTo_hong_4;//�쿪ˮ
		result.eat_count++;
		result.eat_kind = 5;//��
	}
	else {
		//ȥ�������4�ţ�3��
		memcpy(tmp, cards, sizeof(tmp));
		for (int i = 1; i <= 20; i++)
		{
			if (tmp[i] == 4 || tmp[i] == 3)
				tmp[i] = 0;
		}

		//�ܷ���ƣ��ܳ���Щ�ƣ����ж��Ƿ���Ҫ���ƺͰ���Щ��
		if (card <= 10)
		{
			// x 7 10
			if (card == 2 && tmp[7] >= 1 && tmp[10] >= 1)
			{
				result.eat_with[result.eat_count][0] = 7;
				result.eat_with[result.eat_count][1] = 10;
				result.eat_with[result.eat_count][3] = EatTo_hei_2710;//��2710
				result.eat_count++;
			}
			// 2 x 10
			if (card == 7 && tmp[2] >= 1 && tmp[10] >= 1)
			{
				result.eat_with[result.eat_count][0] = 2;
				result.eat_with[result.eat_count][1] = 10;
				result.eat_with[result.eat_count][3] = EatTo_hei_2710;//��2710
				result.eat_count++;
			}
			//2 7 x
			if (card == 10 && tmp[2] >= 1 && tmp[7] >= 1)
			{
				result.eat_with[result.eat_count][0] = 2;
				result.eat_with[result.eat_count][1] = 7;
				result.eat_with[result.eat_count][3] = EatTo_hei_2710;//��2710
				result.eat_count++;
			}
			// xxx
			if (tmp[card] == 2)
			{
				result.eat_with[result.eat_count][0] = card;
				result.eat_with[result.eat_count][1] = card;
				result.eat_with[result.eat_count][3] = EatTo_hei_3;//�ڿ���
				result.eat_count++;
			}

			//����˳��
			// ����ɣ�card-2,card-1,card
			if (card - 2 >= 1 && tmp[card - 2] >= 1 && tmp[card - 1] >= 1) {
				result.eat_with[result.eat_count][0] = card - 2;
				result.eat_with[result.eat_count][1] = card - 1;
				result.eat_with[result.eat_count][3] = EatTo_hei_lianzi;//������
				result.eat_count++;
			}
			//����ɣ�card - 1, card, card + 1
			if ((card - 1 >= 1) && (card + 1 <= 10) && tmp[card - 1] >= 1 && tmp[card + 1] >= 1) {
				result.eat_with[result.eat_count][0] = card - 1;
				result.eat_with[result.eat_count][1] = card + 1;
				result.eat_with[result.eat_count][3] = EatTo_hei_lianzi;//������
				result.eat_count++;
			}
			//����ɣ�card , card+1, card + 2
			if ((card + 2 <= 10) && tmp[card + 1] >= 1 && tmp[card + 2] >= 1) {
				result.eat_with[result.eat_count][0] = card + 1;
				result.eat_with[result.eat_count][1] = card + 2;
				result.eat_with[result.eat_count][3] = EatTo_hei_lianzi;//������
				result.eat_count++;
			}
			//����� ����
			if (tmp[card + 10] >= 2)
			{
				result.eat_with[result.eat_count][0] = card + 10;
				result.eat_with[result.eat_count][1] = card + 10;
				result.eat_with[result.eat_count][3] = EatTo_hong_banbianzi;//������
				result.eat_count++;
			}
			//����� �ںں�
			if (tmp[card] >= 2 && tmp[card + 10] >= 1)
			{
				result.eat_with[result.eat_count][0] = card;
				result.eat_with[result.eat_count][1] = card + 10;
				result.eat_with[result.eat_count][3] = EatTo_hei_banbianzi;//�ڰ����
				result.eat_count++;
			}
		}
		//��ɫ
		if (card > 10)
		{
			// x 7 10
			if (card == 12 && tmp[17] >= 1 && tmp[20] >= 1)
			{
				result.eat_with[result.eat_count][0] = 17;
				result.eat_with[result.eat_count][1] = 20;
				result.eat_with[result.eat_count][3] = EatTo_hong_2710;//��2710
				result.eat_count++;
			}
			// 2 x 10
			if (card == 17 && tmp[12] >= 1 && tmp[20] >= 1)
			{
				result.eat_with[result.eat_count][0] = 12;
				result.eat_with[result.eat_count][1] = 20;
				result.eat_with[result.eat_count][3] = EatTo_hong_2710;//��2710
				result.eat_count++;
			}
			//2 7 x
			if (card == 10 && tmp[12] >= 1 && tmp[17] >= 1)
			{
				result.eat_with[result.eat_count][0] = 12;
				result.eat_with[result.eat_count][1] = 17;
				result.eat_with[result.eat_count][3] = EatTo_hong_2710;//��2710
				result.eat_count++;
			}
			// xxx
			if (tmp[card] == 2)
			{
				result.eat_with[result.eat_count][0] = card;
				result.eat_with[result.eat_count][1] = card;
				result.eat_with[result.eat_count][3] = EatTo_hong_3;//�쿲��
				result.eat_count++;
			}

			//����˳��
			// ����ɣ�card-2,card-1,card
			if (card - 2 >= 11 && tmp[card - 2] >= 1 && tmp[card - 1] >= 1) {
				result.eat_with[result.eat_count][0] = card - 2;
				result.eat_with[result.eat_count][1] = card - 1;
				result.eat_with[result.eat_count][3] = EatTo_hong_lianzi;//������
				result.eat_count++;
			}
			//����ɣ�card - 1, card, card + 1
			if ((card - 1 >= 11) && (card + 1 <= 20) && tmp[card - 1] >= 1 && tmp[card + 1] >= 1) {
				result.eat_with[result.eat_count][0] = card - 1;
				result.eat_with[result.eat_count][1] = card + 1;
				result.eat_with[result.eat_count][3] = EatTo_hong_lianzi;//������
				result.eat_count++;
			}
			//����ɣ�card , card+1, card + 2
			if ((card + 2 <= 20) && tmp[card + 1] >= 1 && tmp[card + 2] >= 1) {
				result.eat_with[result.eat_count][0] = card + 1;
				result.eat_with[result.eat_count][1] = card + 2;
				result.eat_with[result.eat_count][3] = EatTo_hong_lianzi;//������
				result.eat_count++;
			}

			//����� �ںں�
			if (tmp[card - 10] >= 2)
			{
				result.eat_with[result.eat_count][0] = card - 10;
				result.eat_with[result.eat_count][1] = card - 10;
				result.eat_with[result.eat_count][3] = EatTo_hei_banbianzi;//�ڰ����
				result.eat_count++;
			}
			//����� ����
			if (tmp[card] >= 2 && tmp[card - 10] >= 1)
			{
				result.eat_with[result.eat_count][0] = card - 10;
				result.eat_with[result.eat_count][1] = card;
				result.eat_with[result.eat_count][3] = EatTo_hong_banbianzi;//������
				result.eat_count++;
			}
		}
		if (tmp[card] == 0 && result.eat_count == 0)//֮ǰû���ƣ�����Ҳû�п��Գɷ��ģ��������ܳ�
			result.eat_kind = -1;
		else if (tmp[card] == 0 && result.eat_count >= 1)//֮ǰû���ƣ�������1�������ɷ��ģ���ô��1�������ƿ���ѡ���,����Ҫ���ơ�
			result.eat_kind = 1;
		else if (tmp[card] == 1 && result.eat_count == 0)//֮ǰ��һ����,����Ҳû�п��Գɷ��ģ��������ܳԡ�
			result.eat_kind = -3;
		else if (tmp[card] == 1 && result.eat_count == 1)//֮ǰ��һ����,ֻ��һ����Գɷ�����ô���ƺ�ڲ���
			result.eat_kind = -2;
		else if (tmp[card] == 1 && result.eat_count > 1)//֮ǰ��һ���ƣ��ж�����Գɷ�����ô��1�������ƿ���ѡ��ԡ�
			result.eat_kind = 2;
		else if (tmp[card] == 2 && result.eat_count == 1)//֮ǰ�������ƣ�����ֻ��һ����Գɷ���˵����ֻ�����3�ŵĿ��ӣ�����ôֻ��һ����Գԣ���ɿ���
			result.eat_kind = 3;
		else if (tmp[card] == 2 && result.eat_count > 1)//֮ǰ�������ƣ������ж�����Գɷ���˵���������3�ŵĿ��� + ���ӡ�����֡�2710�����ж������ѡ��ԡ�
			result.eat_kind = 4;
	}
	return result;
}


void get_random_cards(int num, int *cards)
{
	int all_cards[80] = {};
	for (int i = 0; i < 80; i++)
	{
		all_cards[i] = i;
	}
	int left_count = 80;
	for (int i = 1; i <= num; i++)
	{

		int r = rand() % left_count;
		cards[i] = r + 1;//r��0-79����Ӧ��Ӧ����1-80
		all_cards[i] = -1;
		left_count--;
		for (int j = i; j < left_count; j++)
		{
			all_cards[j] = all_cards[j + 1];
		}
	}
}

void collect_cards(int num, int *cards, int *collect_to)
{

	int collected[21] = { 0 };
	for (int i = 0; i < num; i++)
	{
		int card = cards[i];
		int color = (card - 1) / 40;
		int point = (card - 1) % 10 + 1;

		int index_of_20 = color * 10 + point;
		collected[index_of_20]++;
	}
	memcpy(collect_to, collected, sizeof(collected));
}

void dump_cards(int cards[21])
{
	for (int i = 1; i <= 20; i++)
	{
		int card_count = cards[i];
		if (card_count)
		{
			char * color = "��";
			if (i <= 10)
				color = "��";
			else
				color = "��";
			int point = i > 10 ? i - 10 : i;
			if (card_count == 1)
				printf("%s%d	", color, point);
			if (card_count == 2)
				printf("%s%d %d	", color, point, point);
			if (card_count == 3)
				printf("%s%d %d %d	", color, point, point, point);
			if (card_count == 4)
				printf("%s%d %d %d %d	", color, point, point, point, point);

			if (i == 10)
				printf("\n");
		}
	}
}
int main()
{
	if (freopen("file.txt", "w", stdout) == NULL)
		fprintf(stderr, "error\n");
	//    1  2  3  4  5  6  7  8  9  10
	int cards[21] = { 0,1,2,1,0,0,1,1,0,2,1,0,0,1,1,1,2,1,1,2,0 };
	EatResult result = can_eat(cards, 0, 0);
	int hushu = __get_hushu_no_gun_kan(cards);
	for (int i = 0; i < 1000; ++i)
	{
		if (i == 352)
			printf("");
		int test_cards[22] = {};
		get_random_cards(20, test_cards);
		int collected[21] = { 0 };
		collect_cards(21, test_cards, collected);
		printf("\n\n��%d��ģ���жϿ��Ƴ���==============\n", i);
		dump_cards(collected);
		for (int card = 1; card <= 20; card++)
		{
			printf("\n��ǰ���Գ���:");
			if (card == 17)
				printf("");
			int point = (card - 1) % 10 + 1;
			printf(card <= 10 ? "��%d\n" : "��%d\n", point);
			EatResult result = can_eat(collected, card, 0);

			if (result.can_hupai)
				printf("�Ƿ���Ժ��ƣ����Ժ���\n");
			else
				printf("�Ƿ���Ժ��ƣ����ܺ���\n");

			if (result.eat_kind == -1)//���ܳ�
			{
				printf("�����Բ���\n");
			}
			else if (result.eat_kind == -2)//ֻ�ܳ�һ��,����Ҫ���ƣ����Բ��ܰ��ƣ����ܳ�
			{
				printf("�Ժ�ڲ��𣬲��ܳ�\n");
			}
			else if (result.eat_kind == 1)//֮ǰû���ƣ�������1�������ɷ��ģ���ô��1�������ƿ���ѡ���,����Ҫ���ơ�
			{
				printf("ֱ�ӿ��Գԣ���һ�������ƣ�,����Ҫ���ơ���");
				for (int k = 0; k < 3; k++) {
					int c = result.eat_with[0][k];
					if (c == 0)
						break;
					int point = (c - 1) % 10 + 1;
					printf(c <= 10 ? "��%d " : "��%d ", point);
				}
				printf("���");
				printf(EatName[result.eat_with[0][3]]);
				printf("\n");
			}
			else if (result.eat_kind == 2)//֮ǰ��һ���ƣ��ж�����Գɷ�����ô�ж���ƿ���ѡ���,��Ҫ���ơ�
			{
				printf("ֱ�ӳԣ�������Ҫ���ƣ���");
				for (int j = 0; j < result.eat_count; j++)
				{
					for (int k = 0; k < 3; k++) {
						int c = result.eat_with[j][k];
						if (c == 0)
							break;
						int point = (c - 1) % 10 + 1;
						printf(c <= 10 ? "��%d " : "��%d ", point);
					}
					printf("���");
					printf(EatName[result.eat_with[j][3]]);
					printf("\n");
				}
			}
			else if (result.eat_kind == -3)//֮ǰ��һ����,����Ҳû�п��Գɷ��ģ��������ܳԡ�
			{
				printf("֮ǰ��һ���ƣ�������ɷ������ܳ�");
			}
			else if (result.eat_kind == 3)//֮ǰ�������ƣ�����ֻ��һ����Գɷ���˵����ֻ�����3�ŵĿ��ӣ�����ôֻ��һ����Գԣ���ɿ��ӣ�����Ҫ����
			{
				printf("����ɿ��ӣ�����Ҫ���ƣ���");
				for (int j = 0; j < result.eat_count; j++)
				{
					for (int k = 0; k < 3; k++) {
						int c = result.eat_with[j][k];
						if (c == 0)
							break;
						int point = (c - 1) % 10 + 1;
						printf(c <= 10 ? "��%d " : "��%d ", point);
					}
					printf("���");
					printf(EatName[result.eat_with[j][3]]);
					printf("\n");
				}
			}
			else if (result.eat_kind == 4)//֮ǰ�������ƣ������ж�����Գɷ���˵���������3�ŵĿ��� + ���ӡ�����֡�2710�����ж������ѡ��ԡ�
			{
				printf("ֱ�ӳԣ�������Ҫ���ƣ���");
				for (int j = 0; j < result.eat_count; j++)
				{
					for (int k = 0; k < 3; k++) {
						int c = result.eat_with[j][k];
						if (c == 0)
							break;
						int point = (c - 1) % 10 + 1;
						printf(c <= 10 ? "��%d " : "��%d ", point);
					}
					printf("���");
					printf(EatName[result.eat_with[j][3]]);
					printf("\n");
				}
			}
			else if (result.eat_kind == 5)//��
			{
				printf("��ˮ����");
				for (int j = 0; j < result.eat_count; j++)
				{
					for (int k = 0; k < 3; k++) {
						int c = result.eat_with[j][k];
						if (c == 0)
							break;
						int point = (c - 1) % 10 + 1;
						printf(c <= 10 ? "��%d " : "��%d ", point);
					}
					printf("���");
					printf(EatName[result.eat_with[j][3]]);
					printf("\n");
				}
			}

			if (result.can_hupai)
				printf("========�ɺ���=====");
		}


		int hushu = get_hushu(collected);
		if (hushu > 0)//���ƿɺ�
		{
			printf("##########���ƾͺ��ˣ�����:%d\n\n", hushu);
		}

	}

	return 0;
}