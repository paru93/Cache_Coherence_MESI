#ifndef CACHEOPERATION_H_INCLUDED
#define CACHEOPERATION_H_INCLUDED

unsigned char CacheRead(CacheCtrl_t , CacheMem_t *);
void CacheWrite(CacheMem_t *, CacheCtrl_t , unsigned char );
unsigned char AccessCache(CacheMem_t *, CacheCtrl_t , unsigned char *, unsigned char *, unsigned char *,unsigned char *, unsigned char );
void ReqDataFrmOthrSrc(CacheMem_t *, CacheCtrl_t , unsigned char *, unsigned char *);

#endif // CACHEOPERATION_H_INCLUDED
