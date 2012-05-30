#ifndef LOB_COMPONENTS_LIMIT_H
#define LOB_COMPONENTS_LIMIT_H

#include "lob/api.h"
#include "lob/models/samemodel.h"

struct lob_natsize {
	Lob base;
	Lob *delegate;
	Size size;
};
typedef struct lob_natsize LobNatSize;
Lob *lob_natsize(Region *reg, Lob *delegate);

struct lob_samew {
	LobDelegate base2;
	LobSameModel *model;
	Size size;
};
typedef struct lob_samew LobSameW;
Lob *lob_samew(Region *reg, Lob *delegate, LobSameModel *m);


#endif