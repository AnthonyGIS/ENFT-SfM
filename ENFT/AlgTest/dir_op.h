#pragma once
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;



class DirOp {

public:

	static bool CheckDirExist(std::string dir_path,bool no_exist_create = true)
	{

		if (_access(dir_path.c_str(), 0) == -1 && no_exist_create)
		{
			return false;
		}

		return true;
	}


	static vector<string> &Split(const string &str, const string &delimiters, vector<string> &elems, bool skip_empty = true)
	{
		string::size_type pos, prev = 0;
		while ((pos = str.find_first_of(delimiters,prev))!=string::npos	)
		{
			if (pos > prev)
			{
				if (skip_empty && 0 == pos - prev)break;
				elems.emplace_back(str, prev, pos - prev);
			}
			prev = pos + 1;
		}

		if (prev < str.size())
			elems.emplace_back(str, prev, str.size() - prev);

		return elems;
	}

	static void test_split()
	{
		string str("windows, Linux||MacOS ALL");
		vector<string> result;

		for (const auto &s:Split(str," ,|",result))
		{
			std::cout << s << "\n";
		}
	}



	// 分隔符允许是‘\\’, 或 '/'
	static void MakeDirs(string dir_path)
	{

		vector<string> psegs;
		string increase_path;
		int i = 0, mk_dir_result;

		increase_path = "";
		for (const auto &path_seg : Split(dir_path, "\\/", psegs))
		{
			increase_path += path_seg + "\\";
			if (i==0 && ( path_seg.find(":") != string::npos || increase_path == "..\\"))
				continue;


			if (_access(increase_path.c_str(), 0) == -1) {
				
				mk_dir_result = _mkdir(increase_path.c_str());
				if (mk_dir_result == -1)
				{
					cout << "mkdir error: " << increase_path << endl;
				}
			}

			// next loop
			i++;
		}
	}



	static void test_mkdirs()
	{
		MakeDirs("..\\a\\bb\\cb");
	}


};