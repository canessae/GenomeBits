#ifndef COMMON_H
#define COMMON_H

#define SAFE_DELETE(a)          if(a) {delete (a); (a) = NULL;}
#define SAFE_DELETEM(a)			if (a) {delete[] (a); (a)=NULL;}

#endif // COMMON_H
