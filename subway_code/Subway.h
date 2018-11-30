
#ifndef SUBWAY_H
#define SUBWAY_H

#include <iostream>
#include <fstream>
#include <stack> // 지하철 경로를 출력할때 필요
#include <string> 
using namespace std;

enum color { white, gray }; // 역을 지났는지 안지났는지 판단

class Station // 역에 대한 정보
{
public:
	int num; // 역에 매겨진 숫자
	int time; // 이동시간
	int transfer; // 환승 횟수	
	Station* next; // 다음 역을 가르키는 포인터
	bool check; // 환승역인지 아닌지 check
	Station() : next(NULL) {}
};
class SubwayGraph // 지하철망
{
private:
	string* station_name; // 역이름
	Station* map; 
	int n; // 지하철 역 갯수
public:
	void Subway(const char* name, int N);

}
