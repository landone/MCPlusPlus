#include "Items.h"

using namespace std;

string Items::names[MAX_ITEM][2] = {
{"", "Nothing"},
{"diamond", "Diamond"}
};

string Items::getName(ITEM item, bool fileName) {

	return names[item][fileName ? 0 : 1];

}