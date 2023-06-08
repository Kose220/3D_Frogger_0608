#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	// 1. ファイルを開く
	// 1-1. fstreamクラスのコンストラクタに指定
	fstream file("sample.txt", ios::in);
	// 1-2. fstreamクラスのopenメンバ関数を利用
	//fstream file;
	//file.open("sample.txt", ios::in);
	// 1-3. ifstreamクラスを使用
	//ifstream file("sample.txt");

	// エラー処理: ファイルが正常に開けたかどうかチェック
	if (!file.is_open())
	{
		cerr << "ERROR: cannot open file." << endl;
		system("pause");
		return EXIT_FAILURE;
	}

	// 2. ファイルからデータを取得
	//int num;
	//file >> num;

	//float num2;
	//file >> num2;

	// ファイル終端まで１行ずつ読み込む
	vector<string> file_lines;
	while (true)
	{
		string line;
		getline(file, line);
		if (file.eof())
			break;

		file_lines.emplace_back(line);
	}

	// 3. ファイルを閉じる
	file.close();

	// 4. 取得したデータを処理
	for (const auto& line : file_lines)
	{
		cout << line << endl;
		// 取得したデータをstring型からint型へ変換
		//int num = line;	// 上手くいかない
		//try
		//{
		//	int num = stoi(line);	// stoi関数(int型にしたいstring型の変数);
		//	cout << num << endl;
		//}
		//catch (const std::exception&)
		//{
		//}
	}

	system("pause");
	return EXIT_SUCCESS;
}