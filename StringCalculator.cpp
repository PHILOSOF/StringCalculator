#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<algorithm>

std::string spaceRemover(std::string str)
{
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] == ' ')
		{
			str.erase(i, 1);
			--i;
		}
	}
	return str;
}

void counter(std::vector<int> &i, std::vector<char> &ch,char oper)
{
	while (std::find(ch.begin(), ch.end(), oper) != ch.end())
	{
		size_t index = std::find(ch.begin(), ch.end(), oper) - ch.begin();
		switch (oper)
		{
		case '+':
			i[index] += i[index + 1];
			break;
		case '-':
			i[index] -= i[index + 1];
			break;
		case '*':
			i[index] *= i[index + 1];
			break;
		case '/':
			i[index] /= i[index + 1];
			break;
		}
		i.erase(i.begin() + (index + 1));
		ch.erase(ch.begin() + index);
	}

}

int StringCalcultor(std::string str)
{
	int ret = 0;
	if (str.find(" ", 0) != -1)
		str = spaceRemover(str);
	if (str.find("(", 0) != -1)
	{
		int open = str.find("(", 0);
		int close = str.rfind(")", str.size());
		char tmp[10] = "";
		_itoa(StringCalcultor(str.substr(open+1, close-(open+1))),tmp,10);
		str.erase(str.begin() + open, str.begin() + close+1);
		str.insert(open, tmp);
	}
	std::vector<int> iline;
	std::vector<char> chline;

	std::regex regex("[0-9]+");
	for (std::sregex_token_iterator it(begin(str), end(str), regex), last; it != last; ++it)
	{
		iline.push_back(std::stoi(it->str()));
	}
	std::regex chregex("[\(\)\*\+\/-]");
	for (std::sregex_token_iterator it(begin(str), end(str), chregex), last; it != last; ++it)
	{
		chline.push_back(it->str()[0]);
	}
	while (std::find(chline.begin(), chline.end(), '(') != chline.end())
	{
		size_t index = std::find(chline.begin(), chline.end(), '(')-chline.begin();
		size_t rindex = std::find(chline.begin(), chline.end(), ')') - chline.begin();
		std::string str;
		for (int i = index; i != rindex; ++i)
		{
			char tmp[5]="";
			str.push_back(*(_itoa(iline[index],tmp,10)));
			str.push_back(chline[index + 1]);
		}
	}
	counter(iline, chline, '*');
	counter(iline, chline, '/');
	counter(iline, chline, '-');
	counter(iline, chline, '+');
	return iline.at(0);
}

int main()
{
	std::string str;
	while (true)
	{
		str = "";
		while (str == "")
			std::getline(std::cin, str);
		std::cout << std::endl;
		std::cout << StringCalcultor(str) << std::endl;
	}
	
	return 0;
}