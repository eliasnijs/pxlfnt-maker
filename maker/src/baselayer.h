// include <stdint.h>, <math.h>

#ifndef BASE_LAYER_H

///////////////////////////////////////////////////////////
//// NOTE(Elias): Helper Macros

#define Stmnt(S) do{ S }while(0)

#define AssertBreak() (*(int *)0 = 0)


#if ENABLE_ASSERT
# define Assert(c) Stmnt( if (!(c)){ AssertBreak(); })
#else
# define Assert(c)
#endif

#define ArrayCount(a)   (sizeof(a)/sizeof(*(a)))
#define Min(a,b)        (((a)<(b))?(a):(b))
#define Max(a,b)        (((a)>(b))?(a):(b))
#define Clamp(a,x,b)    (((x)<(a))?(a):((b)<(x))?(b):(x))
#define ClampBot(a,b)   (Max((a),(b)))
#define ClampTop(a,b)   (Min((a),(b)))
#define Abs(a)          (((a)<0)?(-(a)):(a))

#define EvalPrintInt(x)    (printf("%s = %d\n", #x, (int)(x)))
#define EvalPrintChar(x)    (printf("%s = %c\n", #x, (char)(x)))

#define internal static 
#define local_persist static
#define global_variable static 

///////////////////////////////////////////////////////////
//// NOTE(Elias): Basic Types 
  
typedef int8_t   S8;
typedef int16_t  S16;
typedef int32_t  S32;
typedef int64_t  S64;
typedef uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef float    F32;
typedef double   F64;
typedef S8       B8;
typedef S16      B16;
typedef S32      B32;
typedef S64      B64;

///////////////////////////////////////////////////////////
//// NOTE(Elias): Basic Constants 

global_variable S8  min_S8  = (S8)  0x80;
global_variable S16 min_S16 = (S16) 0x8000;
global_variable S32 min_S32 = (S32) 0x80000000;
global_variable S64 min_S64 = (S64) 0x8000000000000000llu;

global_variable S8  max_S8  = (S8)  0x7f;
global_variable S16 max_S16 = (S16) 0x7fff;
global_variable S32 max_S32 = (S32) 0x7fffffff;
global_variable S64 max_S64 = (S64) 0x7fffffffffffffffllu;

global_variable U8  max_U8  = (U8)  0xff;
global_variable U16 max_U16 = (U16) 0xffff;
global_variable U32 max_U32 = (U32) 0xffffffff;
global_variable U64 max_U64 = (U64) 0xffffffffffffffffllu;

global_variable F32 pi_F32         = 3.14159265359f;
global_variable F32 tau_F32        = 6.28318530718f;
global_variable F32 e_F32          = 2.71828182846f;
global_variable F32 gold_big_F32   = 1.61803398875f;
global_variable F32 gold_small_F32 = 0.61803398875f;

global_variable F64 pi_F64         = 3.14159265359;
global_variable F64 tau_F64        = 6.28318530718;
global_variable F64 e_F64          = 2.71828182846;
global_variable F64 gold_big_F64   = 1.61803398875;
global_variable F64 gold_small_F64 = 0.61803398875;

///////////////////////////////////////////////////////////
//// NOTE(Elias): Symbolic Constants

enum Axis {
  Axis_X,
  Axis_Y,
  Axis_Z,
  Axis_W
}; 

enum Side {
  Side_Min,
  Side_Max
};

enum Month {
  Month_Jan,
  Month_Feb,
  Month_Mar,
  Month_Apr,
  Month_May,
  Month_Jun,
  Month_Jul,
  Month_Aug,
  Month_Sep,
  Month_Oct,
  Month_Nov,
  Month_Dec,
};

enum DayOfWeek {
  DayOfWeek_Monday,
  DayOfWeek_Tuesday,
  DayOfWeek_Wednesday,
  DayOfWeek_Thursday,
  DayOfWeek_Friday,
  DayOfWeek_Saturday,
  DayOfWeek_Sunday
};

///////////////////////////////////////////////////////////
//// NOTE(Elias): Compound Types 

union V2S32 {
  S32 v[2];
  struct {
    S32 x;
    S32 y;
  };
};

union V3S32 {
  S32 v[3];
  struct {
    S32 x;
    S32 y;
    S32 z;
  };
};

union V2F32 {
  F32 v[2];
  struct {
    F32 x;
    F32 y;
  };
};

union V3F32 {
  F32 v[3];
  struct {
    F32 x;
    F32 y;
    F32 z;
  };
};

union V4F32 {
  F32 v[4];
  struct {
    F32 x;
    F32 y;
    F32 z;
    F32 w;
  };
};

union I1F32  {
  struct {
    F32 min;
    F32 max;
  };
  F32 v[2];
};

union I1U64  {
  struct {
    U64 min;
    U64 max;
  };
  struct {
    U64 first;
    U64 opl;
  };
  U64 v[2];
};

union I2F32  {
  struct {
    V2F32 min;
    V2F32 max;
  };
  struct {
    V2F32 p0;
    V2F32 p1;
  };
  struct {
    F32 x0;
    F32 y0;
    F32 x1;
    F32 y1;
  };
  V2F32 p[2];
  F32 v[4];
};

union I2S32  {
  struct {
    V2S32 min;
    V2S32 max;
  };
  struct {
    V2S32 p0;
    V2S32 p1;
  };
  struct {
    S32 x0;
    S32 y0;
    S32 x1;
    S32 y1;
  };
  V2S32 p[2];
  S32 v[4];
};

///////////////////////////////////////////////////////////
//// NOTE(Elias): Symbolic Constant Functions

internal char * string_from_month(Month month);
internal char * string_from_day_of_week(DayOfWeek day_of_week);

///////////////////////////////////////////////////////////
//// NOTE(Elias): Float Constant Functions

internal F32 inf_F32(void);
internal F32 neg_inf_F32(void);
internal F64 inf_F64(void);
internal F64 neg_inf_F64(void);

///////////////////////////////////////////////////////////
//// NOTE(Elias): Math functions 

internal F32 abs_F32(F32 x);
internal F64 abs_F64(F64 x);

internal F32 srqt_F32(F32 x);
internal F32 sin_F32(F32 x);
internal F32 cos_F32(F32 x);
internal F32 tan_F32(F32 x);
internal F32 ln_F32(F32 x);

internal F64 srqt_F64(F64 x);
internal F64 sin_F64(F64 x);
internal F64 cos_F64(F64 x);
internal F64 ln_F64(F64 x);

internal F32 lerp(F32 a, F32 t, F32 b);
internal F32 unlerp(F32 a, F32 x, F32 b);

///////////////////////////////////////////////////////////
//// NOTE(Elias): Compound Type functions 

internal V2S32 v2s32(S32 x, S32 y);

internal V2F32 v2f32(F32 x, F32 y);
internal V3F32 v3f32(F32 x, F32 y, F32 z);
internal V4F32 v4f32(F32 x, F32 y, F32 z, F32 w);

internal I1F32 i1f32(F32 min, F32 max);
internal I1U64 i1u64(U64 min, U64 max);

internal I2S32 i2s32(S32 x0, S32 y0, S32 x1, S32 y1);
internal I2S32 i2s32_vec(V2S32 x, V2S32 y);

internal I2F32 i2f32(F32 x0, F32 y0, F32 x1, F32 y1);
internal I2F32 i2f32_vec(V2F32 x, V2F32 y);
internal I2S32 i2f32_range(I1F32 x, I1F32 y);

internal V2S32 operator+(const V2S32 &a, const V2S32 &b);
internal V2F32 operator+(const V2F32 &a, const V2F32 &b);
internal V3F32 operator+(const V3F32 &a, const V3F32 &b);
internal V4F32 operator+(const V4F32 &a, const V4F32 &b);
 
internal V2S32 operator-(const V2S32 &a, const V2S32 &b);
internal V2F32 operator-(const V2F32 &a, const V2F32 &b);
internal V3F32 operator-(const V3F32 &a, const V3F32 &b);
internal V4F32 operator-(const V4F32 &a, const V4F32 &b);
                                                 
internal V2S32 operator*(const V2S32 &v, const S32 &s);
internal V2F32 operator*(const V2F32 &v, const F32 &s);
internal V3F32 operator*(const V3F32 &v, const F32 &s);
internal V4F32 operator*(const V4F32 &v, const F32 &s);
 
internal V2S32 operator*(const S32 &s, const V2S32 &v);
internal V2F32 operator*(const F32 &s, const V2F32 &v);
internal V3F32 operator*(const F32 &s, const V3F32 &v);
internal V4F32 operator*(const F32 &s, const V4F32 &v);
 
internal V2F32 vec_hadamard(V2F32 a, V2F32 b);
internal V3F32 vec_hadamard(V3F32 a, V3F32 b);
internal V4F32 vec_hadamard(V4F32 a, V4F32 b);
 
internal F32 vec_dot(V2F32 a, V2F32 b);
internal F32 vec_dot(V3F32 a, V3F32 b);
internal F32 vec_dot(V4F32 a, V4F32 b);

internal B32 intrvl_overlaps(I1F32 a, I1F32 b); 
internal B32 intrvl_overlaps(I2F32 a, I2F32 b); 
internal B32 intrvl_overlaps(I2S32 a, I2S32 b);

internal B32 intrvl_contains(I1F32 r, F32 x);
internal B32 intrvl_contains(I2F32 r, V2F32 x);
internal B32 intrvl_contains(I2S32 r, V2S32 x);

internal F32 intrvl_dim(I1F32 r);
internal U64 intrvl_dim(I1U64 r); 
internal V2F32 intrvl_dim(I2F32 r);
internal V2S32 intrvl_dim(I2S32 r);

internal F32 intrvl_center(I1F32 r);
internal V2F32 intrvl_center(I2F32 r);

internal I1F32 intrvl_axis(I2F32 r, Axis axis); 


#define BASE_LAYER_H
#endif 
