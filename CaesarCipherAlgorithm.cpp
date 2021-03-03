#include <ostream>
#include <iostream>
#include <cstdio>
#include <chrono>

std::wstring get_ceasar_string(std::wstring str, const wchar_t shift)
{
	std::wstring res;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] >= L'a' && str[i] <= L'z')
		{
			res += L'a' + (str[i] - L'a' + shift) % (L'z' - L'a' + 1);
			continue;
		}

		if (str[i] >= L'A' && str[i] <= L'Z')
		{
			res += L'A' + (str[i] - L'A' + shift) % (L'z' - L'a' + 1);
			continue;
		}

		res += str[i];
	}

	return res;
}

std::wstring n_get_ceasar_string(std::wstring str, const wchar_t shift)
{
	std::wstring res;

	for (size_t i = 0; i < str.size(); i++)
	{
		char curr = str[i];
		if (islower(curr))
		{
			res += char(int(curr + shift - 97) % 26 + 97);
			continue;
		}

		if (isupper(curr))
		{
			res += char(int(curr + shift - 65) % 26 + 65);
			continue;
		}

		res += curr;
	}

	return res;
}

int main()
{
	const wchar_t shift = 3;
	std::wstring str = L"Somebody once told me the world is gonna roll me!";

	//original function
	auto start = std::chrono::steady_clock::now();
	std::wstring str_crypted;

	for (int i = 0; i < 1000; i++)
	{
		str_crypted = get_ceasar_string(str, shift);
	}

	auto end = std::chrono::steady_clock::now();
	auto difference = end - start;


	//new optimized function
	auto n_start = std::chrono::steady_clock::now();
	std::wstring n_str_crypted;

	for (int i = 0; i < 1000; i++)
	{
		n_str_crypted = n_get_ceasar_string(str, shift);
	}

	auto n_end = std::chrono::steady_clock::now();
	auto n_difference = n_end - n_start;

	//output
	std::wcout << str << std::endl;
	std::wcout << str_crypted << std::endl;
	std::wcout << std::chrono::duration<double, std::milli>(difference).count() << " ms" << std::endl;
	std::wcout << str << std::endl;
	std::wcout << n_str_crypted << std::endl;
	std::wcout << std::chrono::duration<double, std::milli>(n_difference).count() << " ms" << std::endl;

	return 0;
}
