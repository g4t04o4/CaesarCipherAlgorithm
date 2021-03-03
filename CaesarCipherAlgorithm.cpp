#include <ostream>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <cstdio>
#include <chrono>
#include <utility>

std::wstring get_file_contents(const char* filename)
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	return (std::wstring((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
}

std::wstring get_ceasar_string(std::wstring str)
{
	const wchar_t shift = 3;

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

char encode(char ch, const wchar_t shift)
{
	const char alphabet[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
	if (islower(ch))
	{
		return alphabet[ch - 'a' + shift];
	}
	return toupper(alphabet[tolower(ch) - 'a' + shift]);
}

std::wstring n_get_ceasar_string(std::wstring str, const wchar_t shift)
{
	std::wstring res{std::move(str)};

	for (auto& ch : res)
	{
		if (isalpha(ch))
		{
			ch = encode(ch, shift);
		}
	}

	return res;
}

bool isEqual(std::wstring a, std::wstring b)
{
	return a == b;
}


int main()
{
	const wchar_t shift = 3;
	const std::wstring str = L"Somebody once told me the world is gonna roll me!";

	const std::wstring text = get_file_contents("A Tale of Two Cities.txt");


	//original function
	auto start = std::chrono::steady_clock::now();
	std::wstring str_crypted;

	str_crypted = get_ceasar_string(text);

	auto end = std::chrono::steady_clock::now();
	auto difference = end - start;


	//new optimized function
	auto n_start = std::chrono::steady_clock::now();
	std::wstring n_str_crypted;

	n_str_crypted = n_get_ceasar_string(text, shift);

	auto n_end = std::chrono::steady_clock::now();
	auto n_difference = n_end - n_start;

	//output
	//std::wcout << str << '\n' << str_crypted << '\n';
	std::wcout << std::chrono::duration<double, std::milli>(difference).count() << " ms" << '\n';

	//std::wcout << str << '\n' << n_str_crypted << '\n';
	std::wcout << std::chrono::duration<double, std::milli>(n_difference).count() << " ms" << '\n';

	std::wcout << (isEqual(str_crypted, n_str_crypted) ? "CORRECT" : "FAIL") << '\n';
	return 0;
}
