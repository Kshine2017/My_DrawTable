#ifndef PLACEINFO_H
#define PLACEINFO_H

//#include <vector>
//using namespace std;

class PlaceInfo
{
private:
  int  keynumber;    //场地编号
  char gender[30];  //场地名称
  char nickname[20];//负责人
  char password[20];//电话号码
public:
    PlaceInfo();
};

#endif // PLACEINFO_H
