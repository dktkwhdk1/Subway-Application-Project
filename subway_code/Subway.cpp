#include "Subway.h"
using namespace std;

void SubwayGraph::Subway(const char* name, int N)
{
	fstream file;
	file.open(name); // file open

	int start = -1, end = -1; // 시작역과 도착역 초기화
	int min; // 가장 시간이 짧은 도착역 저장
	Station* temp; // file에서 읽어온 역정보를 임시저장
	Station* virtual_temp; // 아무 정보도 없는 class.
	n = N;

	// class field init
	map = new Station[n]; // 지하철 망
	station_name = new string[n];
	check = new color[n];

	int n1, n2, time;
	string s1, s2;

	// 인접리스트를 이용해 지하철망을 만드는 과정
	while (!file.eof())
	{
		file >> n1;
		file >> n2;
		file >> time;
		file >> s1;
		file >> s2;

		// 배열이 0부터 시작하기 떄문에 -1씩 빼준다.
		n1 -= 1;
		n2 -= 1;

		// temp의 n2인덱스에 저장될 역정보
		temp = new Station();
		temp->num = n2;
		temp->time = time;
		if (s1 == s2){
			temp->transfer = 1;
		}
		else {
			temp->transfer = 0;
		}

		// station끼리 연결, 인접리스트를 만드는 과정
		virtual_temp = &map[n1];
		while (virtual_temp->next != NULL)
		{
			virtual_temp = virtual_temp->next;
		}
		virtual_temp->next = temp;

		// temp의 n1인덱스에 저장될 역정보
		temp = new Station();
		temp->num = n1;
		temp->time = time;
		if (s1 == s2){
			temp->transfer = 1;
		}
		else {
			temp->transfer = 0;
		}

		// station끼리 연결, 인접리스트를 만드는 과정
		virtual_temp = &map[n2];
		while (virtual_temp->next != NULL)
		{
			virtual_temp = virtual_temp->next;
		}
		virtual_temp->next = temp;

		station_name[n1] = s1;
		station_name[n2] = s2;

	}
	file.close();
}
