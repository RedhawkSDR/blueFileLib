#ifndef UTILS_BYTESWAP_H
#define UTILS_BYTESWAP_H

namespace utils
{
	// 16-bit swaps.
	union U16_u
	{
		int16_t  i16;
		uint16_t u16;
		char     cc[2];
	};


	// 32-bit swaps.
	union U32_u
	{
		int32_t  i32;
		uint32_t u32;
		float    f32;
		int16_t  i16[2];
		char     c[4];
	};


	// 64-bit swaps.
	union U64_u
	{
		int64_t  i64;
		uint64_t u64;
		double   f64;
		int32_t  i32[2];
		char     c[8];
	};

	inline void byteswap(int16_t *aa, const int16_t *bb)
	{
		U16_u du, su;
		su.i16 = *bb;
		du.cc[0] = su.cc[1];
		du.cc[1] = su.cc[0];
		*aa = du.i16;
	}

	inline void byteswap(uint16_t *dst, const uint16_t *src)
	{
		U16_u du, su;
		su.u16 = *src;
		du.cc[0] = su.cc[1];
		du.cc[1] = su.cc[0];
		*dst = du.u16;
	}

	inline void byteswap(int32_t *aa, const int32_t *bb)
	{
		U32_u du, su;
		su.i32 = *bb;
		byteswap(du.i16, su.i16+1);
		byteswap(du.i16+1, su.i16);
		*aa = du.i32;
	}

	inline void byteswap(uint32_t *dst, const uint32_t *src)
	{
		U32_u du, su;
		su.u32 = *src;
		byteswap(du.i16, su.i16+1);
		byteswap(du.i16+1, su.i16);
		*dst = du.u32;
	}

	inline void byteswap32(char *dst, const char *src)
	{
		U32_u du, su;
		su.c[0] = src[0];
		su.c[1] = src[1];
		su.c[2] = src[2];
		su.c[3] = src[3];
		byteswap(du.i16, su.i16+1);
		byteswap(du.i16+1, su.i16);
		dst[0] = du.c[0];
		dst[1] = du.c[1];
		dst[2] = du.c[2];
		dst[3] = du.c[3];
	}

	inline void byteswap(float *dst, const float *src)
	{
		byteswap32(reinterpret_cast<char*>(dst), reinterpret_cast<const char*>(src));
	}

	inline void byteswap(int64_t *aa, const int64_t *bb)
	{
		U64_u du, su;
		su.i64 = *bb;
		byteswap(du.i32, su.i32+1);
		byteswap(du.i32+1, su.i32);
		*aa = du.i64;
	}

	inline void byteswap64(char *dst, const char *src)
	{
		U64_u du, su;
		su.c[0] = src[0];
		su.c[1] = src[1];
		su.c[2] = src[2];
		su.c[3] = src[3];
		su.c[4] = src[4];
		su.c[5] = src[5];
		su.c[6] = src[6];
		su.c[7] = src[7];
		byteswap(du.i32, su.i32+1);
		byteswap(du.i32+1, su.i32);
		dst[0] = du.c[0];
		dst[1] = du.c[1];
		dst[2] = du.c[2];
		dst[3] = du.c[3];
		dst[4] = du.c[4];
		dst[5] = du.c[5];
		dst[6] = du.c[6];
		dst[7] = du.c[7];
	}

	inline void byteswap(double *dst, const double *src)
	{
		byteswap64(reinterpret_cast<char*>(dst), reinterpret_cast<const char*>(src));
	}

	inline void byteswap(int64_t *aa)
	{
		byteswap(aa, aa);
	}

	inline void byteswap(double *aa)
	{
		byteswap(aa, aa);
	}

	inline void byteswap(int32_t *aa)
	{
		byteswap(aa, aa);
	}
    
	inline void byteswap(uint32_t *aa)
	{
		byteswap(aa, aa);
	}

	inline void byteswap(float *aa)
	{
		byteswap(aa, aa);
	}

	inline void byteswap(int16_t *aa)
	{
		byteswap(aa, aa);
	}

	inline void byteswap(uint16_t *aa)
	{
		byteswap(aa, aa);
	}

	template<class T>
	inline void byteswap(T *xx, int nn)
	{
		for (int ii=0; ii<nn; ++ii)
			byteswap(xx+ii);    
	}

}

#endif

