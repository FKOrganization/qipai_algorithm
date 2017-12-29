function cards_num_to_key(cards)
	for i=1,20 do
		local count = cards[i];
		key = key * 4 + count
    end	
end

function add_to_table2(cards, hushu)
	local key = 0;
	--�����Ǻ�1��2.����1��2.����10������
	--ÿ��������2bit��ʾ���ܹ�40bit
	for i=1,20 do
		local count = cards[i];
		key = key * 4 + count
    end
	key = tostring(key)
    local t = cache_table[key]
    if t and t >= hushu then
        return true;
    end
    cache_table[key] = hushu
    return false;
end


local cache_table = {}
function add_to_table(cards, hushu)
    local big_key=0
    local small_key=0
    for i=1,10 do
        big_key = (big_key*10) + cards[i]
        small_key = (small_key*10) + cards[i+10]
    end
	--local key =  big_key .. '-' .. small_key;
	big_key = string.format("%010u",big_key)
	small_key = string.format("%010u",small_key)
	local key =  big_key .. '-' .. small_key;
    local t = cache_table[key]
    if t and t >= hushu then
        return true;
    end
    cache_table[key] = hushu
    return false;
end

--��1��2... ��1��2..��10,ÿ���ƿ��Խ��еĸ��ֲ�����
--card + diffs[1],card + diffs[2],card + diffs[3] ������ֵ��Ӧ������λ�õ���+1�����γ���һ�������ͣ���Ӧ�ĺ�����score
--diffs��ʾ����ڵ�ǰcard��ƫ��
local all_cards_operations =
 {
	--��1
	{
		--���ԶԺ�1���ν���
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	--��2
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
		{diffs = {0,5,8},score = 3}--��2710
	},
	--��3
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	--��4
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	
	--��5
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	
	--��6
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	
	--��7
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
		{diffs = {-5,0,3},score = 3}--��2710
	},
	--��8
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},

	--��9
	{
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
	},
	
	--��10
	{
		{diffs = {0,0,10},score=0},--�ںں�
		{diffs = {0,10,10},score=0},--�ں��
		{diffs = {-8,-3,0},score = 3}--��2710
	},
	
	
	--11
	--��1
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	--��2
	{
		{diffs = {0,1,2},score=0},	--˳��
		{diffs = {0,0,-10},score=0},	--����
		{diffs = {0,-10,-10},score=0},--��ں�
		{diffs = {0,5,8},score = 6}	--��2710
	},
	--��3
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	--��4
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	
	--��5
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	
	--��6
	{
		{diffs = {0,1,2},score=0},--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	
	--��7
	{
		{diffs = {0,1,2},score=0},	--˳��
		{diffs = {0,0,-10},score=0},	--����
		{diffs = {0,-10,-10},score=0},--��ں�
		{diffs = {-5,0,3},score = 6}	--��2710
	},
	--��8
	{
		{diffs = {0,1,2},score=0},	--˳��
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},

	--��9
	{
		{diffs = {0,0,-10},score=0},--����
		{diffs = {0,-10,-10},score=0},--��ں�
	},
	
	--��10
	{
		{diffs = {0,0,-10},score=0},	--����
		{diffs = {0,-10,-10},score=0},--��ں�
		{diffs = {-8,-3,0},score = 6},	--��2710
	}
}


function iterate_each(cards,card,card_num,score)
	if card > 20 then
		return
	end
	if card_num > 20 then
		return
	end
	--��ÿ���ƿ�ʼ���������˳�ӣ�����ʮ������֣���ǰ��1�ţ�������2�ţ�
	for card_next=card,20 do
		local card_operations = all_cards_operations[card_next];
		if card_num + 3 > 20 then
			break;
		end
		--��ĳ�������п��Բ����ģ�����һ��
		for k,operation in pairs(card_operations) do 
			local indexs = {0,0,0};
			for kk,diff in pairs(operation.diffs) do
				indexs[kk] = card_next + diff;
			end
			cards[indexs[1]] = cards[indexs[1]] + 1;
			cards[indexs[2]] = cards[indexs[2]] + 1;
			cards[indexs[3]] = cards[indexs[3]] + 1;
			card_num = card_num + 3;
			local add = false;
			local curr_score = operation.score
			--if card_num <= 20 then
				if cards[indexs[1]]<=2 and cards[indexs[2]] <=2 and cards[indexs[3]]<=2 then
					add = true;				
				end
				if add then
					--ǰһ����ͬkey�ĸ���ֵ�Ѿ�����ˣ��Ͳ���Ҫ�����
					local pre_bigger_added = add_to_table(cards,curr_score + score);
					if not pre_bigger_added then
						iterate_each(cards,card_next,card_num,curr_score + score)
					end
				end
			--end
			cards[indexs[1]] = cards[indexs[1]] - 1;
			cards[indexs[2]] = cards[indexs[2]] - 1;
			cards[indexs[3]] = cards[indexs[3]] - 1;	
			card_num = card_num - 3;
		end
	end
	iterate_each(cards,card+1,card_num,score)
end

function make_table()
	local cards = {0,0,0,0,0, 0,0,0,0,0,
				   0,0,0,0,0, 0,0,0,0,0};
	local begin = os.time()
	print("make_table ���ɿ�ʼ")
    iterate_each(cards,1,0,0,1);
	print("make_table ���ɽ���,��ʱ",os.time()-begin,"s")
	save_to_file('myhushu2.txt',cache_table);
end

function save_to_file(file, tbl)
    local f = io.open(file, "w+")
    for key,hushu in pairs(tbl) do
        f:write(key.."="..hushu.."\n")
    end
    f:close()
end

function load_from_file(file, tbl)
    local f = io.open(file, "r")
    while true do
        local str = f:read("*|")
        if not str then
            break
        end
        local split = string.find("str","=")
        if not split then
            break
        end
        local key = string.sub(str, 1, split-1)
        local hushu = tonumber(string.sub(str, split+1))
        tbl[key] = hushu
    end
end
make_table();
