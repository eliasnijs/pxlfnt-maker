///////////////////////////////////////////////////////////
//// NOTE(Elias): Symbolic Constant Functions

internal char * 
string_from_month(Month month)
{
  char *result = "(null)";
  switch (month) 
  {
    case (Month_Jan):
    {
      result = "janunary";
    } break;
    case (Month_Feb):
    {
      result = "february";
    } break;
    case (Month_Mar):
    {
      result = "march";
    } break;
    case (Month_Apr):
    {
      result = "april";
    } break;
    case (Month_May):
    {
      result = "may";
    } break;
    case (Month_Jun):
    {
      result = "juny";
    } break;
    case (Month_Jul):
    {
      result = "july";
    } break;
    case (Month_Aug):
    {
      result = "augustus";
    } break;
    case (Month_Sep):
    {
      result = "september";
    } break;
    case (Month_Oct):
    {
      result = "october";
    } break;
    case (Month_Nov):
    {
      result = "november";
    } break;
    case (Month_Dec):
    {
      result = "december";
    } break;
  }
  return(result);
}

internal char * 
string_from_day_of_week(DayOfWeek day_of_week)
{
  char * result = "(null)";
  switch (day_of_week)
  {
    case(DayOfWeek_Monday):
    {
      result = "monday";
    } break;
    case(DayOfWeek_Tuesday):
    {
      result = "tuesday";
    } break;
    case(DayOfWeek_Wednesday):
    {
      result = "wednesday";
    } break;
    case(DayOfWeek_Thursday):
    {
      result = "thursday";
    } break;
    case(DayOfWeek_Friday):
    {
      result = "friday";
    } break;
    case(DayOfWeek_Saturday):
    {
      result = "saturday";
    } break;
    case(DayOfWeek_Sunday):
    {
      result = "sunday";
    } break;
  }
  return(result);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Float Constant Functions

internal F32 
inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0x7f800000;
  return(r.f);
}
internal F32 
neg_inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0xff800000;
  return(r.f);
}

internal F64 
inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0x7ff00000ff800000;
  return(r.f);
}

internal F64 
neg_inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0xfff00000ff800000;
  return(r.f);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Math functions 

internal F32 
abs_F32(F32 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffff;
  return(r.f);
}

internal F64 
abs_F64(F64 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffffffffffff;
  return(r.f);
}


internal F32 
srqt_F32(F32 x)
{
  return(sqrtf(x));
}

internal F32 
sin_F32(F32 x)
{
  return(sinf(x));
}

internal F32 
cos_F32(F32 x)
{
  return(cosf(x));
}

internal F32 
tan_F32(F32 x)
{
  return(tanf(x));
}

internal F32 
ln_F32(F32 x)
{
  return(logf(x));
}

internal F64 
srqt_F64(F64 x)
{
  return(sqrt(x));
}

internal F64 
sin_F64(F64 x)
{
  return(sin(x));
}

internal F64 
cos_F64(F64 x)
{
  return(cos(x));
}

internal F64 
tan_F64(F64 x)
{
  return(tan(x));
} 

internal F64 
ln_F64(F64 x)
{
  return(log(x));
} 

internal F32 
lerp(F32 a, F32 t, F32 b)
{
  F32 x = a + t*(b - a);
  return(x);
}

internal F32 
unlerp(F32 a, F32 x, F32 b)
{
  F32 t = 0.f;
  if (a != b)
  {
    t = (x - a) / (b - a);
  }
  return(t);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Compound Type functions 

internal V2S32 
v2s32(S32 x, S32 y)
{
  V2S32 r = {x, y};
  return(r);
}

internal V2F32 
v2f32(F32 x, F32 y)
{
  V2F32 r = {x, y};
  return(r);
}
internal V3F32 
v3f32(F32 x, F32 y, F32 z)
{
  V3F32 r = {x, y, z};
  return(r);
}
internal V4F32 
v4f32(F32 x, F32 y, F32 z, F32 w)
{
  V4F32 r = {x, y, z, w};
  return(r);
}

internal I1F32 
i1f32(F32 min, F32 max)
{
  I1F32 r = {min, max};
  if (max < min)
  {
    r.min = max;
    r.max = min;
  }
  return(r);
}
internal I1U64 
i1u64(U64 min, U64 max)
{
  I1U64 r = {min, max};
  if (max < min)
  {
    r.min = max;
    r.max = min;
  }
  return(r);
}

internal I2S32 
i2s32(S32 x0, S32 y0, S32 x1, S32 y1)
{
  I2S32 r = {x0, y0, x1, y1};
  if (x1 < x0)
  {
    r.x0 = x1;
    r.x1 = x0;
  }
  if (y1 < y0)
  {
    r.y0 = y1;
    r.y1 = y0;
  }
  return(r);
}
internal I2S32 
i2s32_vec(V2S32 min, V2S32 max)
{
  I2S32 r = i2s32(min.x, min.y, max.x, max.y);
  return(r);
}

internal I2F32 
i2f32(F32 x0, F32 y0, F32 x1, F32 y1)
{
  I2F32 r = {x0, y0, x1, y1};
  if (x1 < x0)
  {
    r.x0 = x1;
    r.x1 = x0;
  }
  if (y1 < y0)
  {
    r.y0 = y1;
    r.y1 = y0;
  }
  return(r);
}
internal I2F32 
i2f32_vec(V2F32 min, V2F32 max)
{
  I2F32 r = i2f32(min.x, min.y, max.x, max.y);
  return(r);
}
internal I2S32 
i2f32_range(I1F32 x, I1F32 y)
{
  I2S32 r = i2s32(x.min, y.min, x.max, y.max);
  return(r);
}

internal V2S32 
operator+(const V2S32 &a, const V2S32 &b)
{
  V2S32 r = {a.x + b.x, a.y + b.y};
  return(r);
}
internal V2F32 
operator+(const V2F32 &a, const V2F32 &b)
{
  V2F32 r = {a.x + b.x, a.y + b.y};
  return(r);
}
internal V3F32 
operator+(const V3F32 &a, const V3F32 &b)
{
  V3F32 r = {a.x + b.x, a.y + b.y, a.z + b.z};
  return(r);
}
internal V4F32 
operator+(const V4F32 &a, const V4F32 &b)
{
  V4F32 r = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
  return(r);
}
 
internal V2S32 
operator-(const V2S32 &a, const V2S32 &b)
{
  V2S32 r = {a.x - b.x, a.y - b.y};
  return(r);
}
internal V2F32 
operator-(const V2F32 &a, const V2F32 &b)
{
  V2F32 r = {a.x - b.x, a.y - b.y};
  return(r);
}
internal V3F32 
operator-(const V3F32 &a, const V3F32 &b)
{
  V3F32 r = {a.x - b.x, a.y - b.y, a.z - b.z};
  return(r);
}
internal V4F32 
operator-(const V4F32 &a, const V4F32 &b)
{
  V4F32 r = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
  return(r);
}
                                                 
internal V2S32 
operator*(const V2S32 &v, const S32 &s)
{
  V2S32 r = {v.x*s, v.y*s};
  return(r);
}
internal V2F32 
operator*(const V2F32 &v, const F32 &s)
{
  V2F32 r = {v.x*s, v.y*s};
  return(r);
}
internal V3F32 
operator*(const V3F32 &v, const F32 &s)
{
  V3F32 r = {v.x*s, v.y*s, v.z*s};
  return(r);
}
internal V4F32 
operator*(const V4F32 &v, const F32 &s)
{
  V4F32 r = {v.x*s, v.y*s, v.z*s, v.w*s};
  return(r);
}
 
internal V2S32 
operator*(const S32 &s, const V2S32 &v)
{
  V2S32 r = {v.x*s, v.y*s};
  return(r);
}
internal V2F32 
operator*(const F32 &s, const V2F32 &v)
{
  V2F32 r = {v.x*s, v.y*s};
  return(r);
}
internal V3F32 
operator*(const F32 &s, const V3F32 &v)
{
  V3F32 r = {v.x*s, v.y*s, v.z*s};
  return(r);
}
internal V4F32 
operator*(const F32 &s, const V4F32 &v)
{
  V4F32 r = {v.x*s, v.y*s, v.z*s, v.w*s};
  return(r);
}
 
internal V2F32 
vec_hadamard(V2F32 a, V2F32 b)
{
  V2F32 r = {a.x*b.x, a.y*b.y};
  return(r); 
}
internal V3F32 
vec_hadamard(V3F32 a, V3F32 b)
{
  V3F32 r = {a.x*b.x, a.y*b.y, a.z*b.z};
  return(r);
}
internal V4F32 
vec_hadamard(V4F32 a, V4F32 b)
{
  V4F32 r = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w};
  return(r);
}
 
internal F32 
vec_dot(V2F32 a, V2F32 b)
{
  F32 r = a.x*b.x + a.y*b.y;
  return(r);
}
internal F32 
vec_dot(V3F32 a, V3F32 b)
{
  F32 r = a.x*b.x + a.y*b.y + a.z*b.z;
  return(r);
}
internal F32 
vec_dot(V4F32 a, V4F32 b)
{
  F32 r = a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
  return(r);
}

internal B32 
intrvl_overlaps(I1F32 a, I1F32 b)
{
  B32 result = (b.min < a.max && a.min < b.max);
  return(result);
}
internal B32 
intrvl_overlaps(I2F32 a, I2F32 b)
{
  B32 result = (b.x0 < a.x1 && a.x0 < b.x1 &&
                b.x0 < a.x1 && a.x0 < b.x1);
  return(result);
}
internal B32 
intrvl_overlaps(I2S32 a, I2S32 b)
{
  B32 result = (b.x0 < a.x1 && a.x0 < b.x1 &&
                b.x0 < a.x1 && a.x0 < b.x1);
  return(result);
}

internal B32 
intrvl_contains(I1F32 r, F32 x)
{
  B32 result = (r.min <= x && x < r.max);
  return(result);
}
internal B32 
intrvl_contains(I2F32 r, V2F32 p)
{
  B32 result = (r.x0 <= p.x && p.x < r.x1 && 
                r.y0 <= p.x && p.x < r.y1);
  return(result);
}
internal B32 
intrvl_contains(I2S32 r, V2S32 p)
{
  B32 result = (r.x0 <= p.x && p.x < r.x1 && 
                r.y0 <= p.x && p.x < r.y1);
  return(result);
}

internal F32 
intrvl_dim(I1F32 r)
{
  F32 result = r.max - r.min;
  return(result);
}
internal U64 
intrvl_dim(I1U64 r) 
{
  U64 result = r.max - r.min;
  return(result);
}
internal V2F32 
intrvl_dim(I2F32 r)
{
  V2F32 result = {r.x1 - r.x0, r.y1 - r.x0};
  return(result);
}
internal V2S32 
intrvl_dim(I2S32 r)
{
  V2S32 result = {r.x1 - r.x0, r.y1 - r.x0};
  return(result);
}

internal F32 
intrvl_center(I1F32 r)
{
  F32 result = (r.max + r.min) * 0.5f;
  return(result);
}
internal V2F32 
intrvl_center(I2F32 r)
{
  V2F32 result = {
    (r.x0 + r.x1) * 0.5f, 
    (r.y0 + r.y1) * 0.5f
  };
  return(result);
}

internal I1F32 
intrvl_axis(I2F32 r, Axis axis)
{
  I1F32 result = {r.p[0].v[axis], r.p[1].v[axis]};
  return(result);
}
