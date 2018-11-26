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
}
