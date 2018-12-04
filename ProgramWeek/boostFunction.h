#define CMD_COLS  137
#define CMD_LINES  35

#include <time.h>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

void SetScreenGrid();
void SetSysCaption();

string getTime();   //获得系统时间

void renameFilename(string &oldfile,string &newfile);

int vecMAX(vector<string> &vec);
int vecSUM(vector<string> &vec);

vector< vector<string> > getTablecontent(string &path );
inline int cmp(std::vector< string > v1,std::vector<string> v2){
    return  atoi(v1.at(7).c_str()) > atoi(v2.at(7).c_str());
}

inline bool cmpPair(const pair<string, int>& lhs, const pair<string, int>& rhs) {
  return lhs.second > rhs.second;
}
