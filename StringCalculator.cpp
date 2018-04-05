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
	
	std::vector<int> iline;
	std::vector<char> chline;
	std::regex regex("[0-9]+");
	for (std::sregex_token_iterator it(begin(str), end(str), regex), last; it != last; ++it)
	{
		iline.push_back(std::stoi(it->str()));
	}
	std::regex chregex("[\*\+\/-\(\)]");
	for (std::sregex_token_iterator it(begin(str), end(str), chregex), last; it != last; ++it)
	{
		chline.push_back(it->str()[0]);
	}
	counter(iline, chline, '*');
	counter(iline, chline, '/');
	counter(iline, chline, '-');
	counter(iline, chline, '+');
	return iline.at(0);
}

int main()
{
	std::string string;
	std::getline(std::cin, string);
	std::cout << std::endl;
	std::cout << StringCalcultor(string) << std::endl;
	return 0;
}