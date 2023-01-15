#include "klm.h"
#include <stdio.h>

const klm_mat4 m_mat4_identity = 
{
	{1.f, 0.f, 0.f, 0.f},
	{0.f, 1.f, 0.f, 0.f},
	{0.f, 0.f, 1.f, 0.f},
	{0.f, 0.f, 0.f, 1.f}
};
const klm_mat4i m_mat4i_identity =
{
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
};
const klm_mat3 m_mat3_identity =
{
	{1.f, 0.f, 0.f},
	{0.f, 1.f, 0.f},
	{0.f, 0.f, 1.f}
};
const klm_mat3i m_mat3i_identity =
{
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1}
};
const klm_mat2 m_mat2_identity = 
{
	{1.f, 0.f},
	{0.f, 1.f}
};
const klm_mat2i m_mat2i_identity =
{
	{1, 0},
	{0, 1}
};

klm_vec2 	klm_add_v2	(klm_vec2 a,	klm_vec2 b)
{
	klm_vec2 v = {a.x + b.x, a.y + b.y};
	return v;
}
klm_vec2i klm_add_v2i	(klm_vec2i a,	klm_vec2i b)
{
	klm_vec2i v = {a.x + b.x, a.y + b.y};
	return v;
}
klm_vec3 	klm_add_v3	(klm_vec3 a,	klm_vec3 b)
{
	klm_vec3 v = {a.x + b.x, a.y + b.y, a.z + b.z};
	return v;
}
klm_vec3i klm_add_v3i	(klm_vec3i a,	klm_vec3i b)
{
	klm_vec3i v = {a.x + b.x, a.y + b.y, a.z + b.z};
	return v;
}
klm_vec4 	klm_add_v4	(klm_vec4 a,	klm_vec4 b)
{
	klm_vec4 v = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	return v;
}
klm_vec4i klm_add_v4i	(klm_vec4i a,	klm_vec4i b)
{
	klm_vec4i v = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
	return v;
}

klm_mat2 	klm_add_m2	(klm_mat2 a,	klm_mat2 b)
{
	klm_mat2 m = {klm_add_v2(a.i, b.i), klm_add_v2(a.j, b.j)};
	return m;
}
klm_mat2i klm_add_m2i	(klm_mat2i a,	klm_mat2i b)
{
	klm_mat2i m = {klm_add_v2i(a.i, b.i), klm_add_v2i(a.j, b.j)};
	return m;
}
klm_mat3 	klm_add_m3	(klm_mat3 a,	klm_mat3 b)
{
	klm_mat3 m = {klm_add_v3(a.i, b.i), klm_add_v3(a.j, b.j), klm_add_v3(a.k, b.k)};
	return m;
}
klm_mat3i klm_add_m3i	(klm_mat3i a,	klm_mat3i b)
{
	klm_mat3i m = {klm_add_v3i(a.i, b.i), klm_add_v3i(a.j, b.j), klm_add_v3i(a.k, b.k)};
	return m;
}
klm_mat4 	klm_add_m4	(klm_mat4 a,	klm_mat4 b)
{
	klm_mat4 m = {klm_add_v4(a.i, b.i), klm_add_v4(a.j, b.j), klm_add_v4(a.k, b.k), klm_add_v4(a.l, b.l)};
	return m;
}
klm_mat4i klm_add_m4i	(klm_mat4i a,	klm_mat4i b)
{
	klm_mat4i m = {klm_add_v4i(a.i, b.i), klm_add_v4i(a.j, b.j), klm_add_v4i(a.k, b.k), klm_add_v4i(a.l, b.l)};
	return m;
}

klm_vec2 	klm_sub_v2	(klm_vec2 a,	klm_vec2 b)
{
	klm_vec2 v = { a.x - b.x, a.y - b.y };
	return v;
}
klm_vec3 	klm_sub_v3	(klm_vec3 a,	klm_vec3 b)
{
	klm_vec3 v = { a.x - b.x, a.y - b.y, a.z - b.z };
	return v;
}
klm_vec4 	klm_sub_v4	(klm_vec4 a,	klm_vec4 b)
{
	klm_vec4 v = { a.x -b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return v;
}

klm_vec2i klm_sub_v2i	(klm_vec2i a,	klm_vec2i b)
{
	klm_vec2i v = { a.x - b.x, a.y - b.y };
	return v;
}
klm_vec3i klm_sub_v3i	(klm_vec3i a,	klm_vec3i b)
{
	klm_vec3i v = {a.x - b.x, a.y - b.y, a.z - b.z };
	return v;
}
klm_vec4i klm_sub_v4i	(klm_vec4i a,	klm_vec4i b)
{
	klm_vec4i v = { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w };
	return v;
}

klm_mat2 	klm_sub_m2	(klm_mat2 a,	klm_mat2 b)
{
	klm_mat2 m = { klm_sub_v2(a.i, b.i), klm_sub_v2(a.j, b.j) };
	return m;
}
klm_mat3 	klm_sub_m3	(klm_mat3 a,	klm_mat3 b)
{
	klm_mat3 m = { klm_sub_v3(a.i, b.i), klm_sub_v3(a.j, b.j), klm_sub_v3(a.k, b.k) };
	return m;
}
klm_mat4 	klm_sub_m4	(klm_mat4 a,	klm_mat4 b)
{
	klm_mat4 m = { klm_sub_v4(a.i, b.i), klm_sub_v4(a.j, b.j), klm_sub_v4(a.k, b.k), klm_sub_v4(a.l, b.l) };
	return m;
}
klm_mat2i klm_sub_m2i	(klm_mat2i a,	klm_mat2i b)
{
	klm_mat2i m = { klm_sub_v2i(a.i, b.i), klm_sub_v2i(a.j, b.j) };
	return m;
}
klm_mat3i klm_sub_m3i	(klm_mat3i a,	klm_mat3i b)
{
	klm_mat3i m = { klm_sub_v3i(a.i, b.i), klm_sub_v3i(a.j, b.j), klm_sub_v3i(a.k, b.k) };
	return m;
}
klm_mat4i klm_sub_m4i	(klm_mat4i a, klm_mat4i b)
{
	klm_mat4i m = { klm_sub_v4i(a.i, b.i), klm_sub_v4i(a.j, b.j), klm_sub_v4i(a.k, b.k), klm_sub_v4i(a.l, b.l) };
	return m;
}

float 	klm_dot_v2	(klm_vec2 a,	klm_vec2 b) 	{ return a.x * b.x + a.y * b.y; }
int 	klm_dot_v2i	(klm_vec2i a,	klm_vec2i b)	{ return a.x * b.x + a.y * b.y; }
float 	klm_dot_v3	(klm_vec3 a,	klm_vec3 b)	{ return a.x * b.x + a.y * b.y + a.z * b.z; }
int 	klm_dot_v3i	(klm_vec3i a,	klm_vec3i b)	{ return a.x * b.x + a.y * b.y + a.z * b.z; }
float 	klm_dot_v4	(klm_vec4 a,	klm_vec4 b)	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
int		klm_dot_v4i	(klm_vec4i a,	klm_vec4i b)	{ return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; } 

klm_mat2 	klm_mult_m2	(klm_mat2 a,	klm_mat2 b)
{
	klm_vec2 a1 = { a.i.x, a.j.x };
	klm_vec2 a2 = { a.i.y, a.j.y };
	klm_mat2 m = 
	{
		{ klm_dot_v2(a1, b.i), klm_dot_v2(a2, b.j) },
		{ klm_dot_v2(a1, b.i), klm_dot_v2(a2, b.j) }
	};
	return m;
}
klm_mat2i klm_mult_m2i	(klm_mat2i a,	klm_mat2i b)
{
	klm_mat2i m = 
	{
		{ klm_dot_v2i(a.i, b.i), klm_dot_v2i(a.i, b.j) },
		{ klm_dot_v2i(a.j, b.i), klm_dot_v2i(a.j, b.j) }
	};
	return m;
}
klm_mat3 	klm_mult_m3	(klm_mat3 a,	klm_mat3 b)
{
	klm_vec3 a1 = { a.i.x, a.j.x, a.k.x };
	klm_vec3 a2 = { a.i.y, a.j.y, a.k.y };
	klm_vec3 a3 = { a.i.z, a.j.z, a.k.z };

	klm_mat3 m =
	{
		{ klm_dot_v3(a1, b.i), klm_dot_v3(a2, b.i), klm_dot_v3(a3, b.i) },
		{ klm_dot_v3(a1, b.j), klm_dot_v3(a2, b.j), klm_dot_v3(a3, b.j) },
		{ klm_dot_v3(a1, b.k), klm_dot_v3(a2, b.k), klm_dot_v3(a3, b.k) },
	};
	return m;
}
klm_mat3i klm_mult_m3i	(klm_mat3i a,	klm_mat3i b)
{
	klm_vec3i a1 = { a.i.x, a.j.x, a.k.x };
	klm_vec3i a2 = { a.i.y, a.j.y, a.k.y };
	klm_vec3i a3 = { a.i.z, a.j.z, a.k.z };

	klm_mat3i m =
	{
		{ klm_dot_v3i(a1, b.i), klm_dot_v3i(a2, b.i), klm_dot_v3i(a3, b.i) },
		{ klm_dot_v3i(a1, b.j), klm_dot_v3i(a2, b.j), klm_dot_v3i(a3, b.j) },
		{ klm_dot_v3i(a1, b.k), klm_dot_v3i(a2, b.k), klm_dot_v3i(a3, b.k) },
	};
	return m;
}
klm_mat4 	klm_mult_m4	(klm_mat4 a,	klm_mat4 b)
{
	klm_vec4 a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	klm_vec4 a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	klm_vec4 a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	klm_vec4 a4 = { a.i.w, a.j.w, a.k.w, a.l.w };

	klm_mat4 m =
	{
		{ klm_dot_v4(a1, b.i), klm_dot_v4(a2, b.i), klm_dot_v4(a3, b.i), klm_dot_v4(a4, b.i) },
		{ klm_dot_v4(a1, b.j), klm_dot_v4(a2, b.j), klm_dot_v4(a3, b.j), klm_dot_v4(a4, b.j) },
		{ klm_dot_v4(a1, b.k), klm_dot_v4(a2, b.k), klm_dot_v4(a3, b.k), klm_dot_v4(a4, b.k) },
		{ klm_dot_v4(a1, b.l), klm_dot_v4(a2, b.l), klm_dot_v4(a3, b.l), klm_dot_v4(a4, b.l) },
	};
	return m;
}
klm_mat4i	klm_mult_m4i	(klm_mat4i a,	klm_mat4i b)
{
	klm_vec4i a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	klm_vec4i a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	klm_vec4i a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	klm_vec4i a4 = { a.i.w, a.j.w, a.k.w, a.l.w };

	klm_mat4i m =
	{
		{ klm_dot_v4i(a1, b.i), klm_dot_v4i(a2, b.i), klm_dot_v4i(a3, b.i), klm_dot_v4i(a4, b.i) },
		{ klm_dot_v4i(a1, b.j), klm_dot_v4i(a2, b.j), klm_dot_v4i(a3, b.j), klm_dot_v4i(a4, b.j) },
		{ klm_dot_v4i(a1, b.k), klm_dot_v4i(a2, b.k), klm_dot_v4i(a3, b.k), klm_dot_v4i(a4, b.k) },
		{ klm_dot_v4i(a1, b.l), klm_dot_v4i(a2, b.l), klm_dot_v4i(a3, b.l), klm_dot_v4i(a4, b.l) },
	};
	return m;
}

klm_vec2 	klm_mult_mv2	(klm_mat2 a,	klm_vec2 b)
{
	klm_vec2 a1 = { a.i.x, a.j.x };
	klm_vec2 a2 = { a.i.y, a.j.y };
	klm_vec2 v = { klm_dot_v2(a1, b), klm_dot_v2(a2, b) };
	return v;
}
klm_vec2i klm_mult_mv2i	(klm_mat2i a,	klm_vec2i b)
{
	klm_vec2i a1 = { a.i.x, a.j.x };
	klm_vec2i a2 = { a.i.y, a.j.y };
	klm_vec2i v = { klm_dot_v2i(a1, b), klm_dot_v2i(a2, b) };
	return v;
}
klm_vec3 	klm_mult_mv3	(klm_mat3 a,	klm_vec3 b)
{
	klm_vec3 a1 = { a.i.x, a.j.x, a.k.x };
	klm_vec3 a2 = { a.i.y, a.j.y, a.k.y };
	klm_vec3 a3 = { a.i.z, a.j.z, a.k.z };
	klm_vec3 v = { klm_dot_v3(a1, b), klm_dot_v3(a2, b), klm_dot_v3(a3, b) };
	return v;
}
klm_vec3i klm_mult_mv3i	(klm_mat3i a, klm_vec3i b)
{
	klm_vec3i a1 = { a.i.x, a.j.x, a.k.x };
	klm_vec3i a2 = { a.i.y, a.j.y, a.k.y };
	klm_vec3i a3 = { a.i.z, a.j.z, a.k.z };
	klm_vec3i v = { klm_dot_v3i(a1, b), klm_dot_v3i(a2, b), klm_dot_v3i(a3, b) };
	return v;
}
klm_vec4 	klm_mult_mv4	(klm_mat4 a,	klm_vec4 b)
{
	klm_vec4 a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	klm_vec4 a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	klm_vec4 a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	klm_vec4 a4 = { a.i.w, a.j.w, a.k.w, a.l.w };
	klm_vec4 v = { klm_dot_v4(a1, b), klm_dot_v4(a2, b), klm_dot_v4(a3, b), klm_dot_v4(a4, b) };
	return v;
}
klm_vec4i	klm_mult_mv4i	(klm_mat4i a, klm_vec4i b)
{
	klm_vec4i a1 = { a.i.x, a.j.x, a.k.x, a.l.x };
	klm_vec4i a2 = { a.i.y, a.j.y, a.k.y, a.l.y };
	klm_vec4i a3 = { a.i.z, a.j.z, a.k.z, a.l.z };
	klm_vec4i a4 = { a.i.w, a.j.w, a.k.w, a.l.w };
	klm_vec4i v = { klm_dot_v4i(a1, b), klm_dot_v4i(a2, b), klm_dot_v4i(a3, b), klm_dot_v4i(a4, b) };
	return v;
}

klm_vec2 	klm_mult_vm2	(klm_vec2 a, 	klm_mat2 b)
{
	klm_vec2 v = { klm_dot_v2(a, b.i), klm_dot_v2(a, b.j) };
	return v;
}
klm_vec2i klm_mult_vm2i	(klm_vec2i a, klm_mat2i b)
{
	klm_vec2i v = { klm_dot_v2i(a, b.i), klm_dot_v2i(a, b.j) };
	return v;
}
klm_vec3 	klm_mult_vm3	(klm_vec3 a, 	klm_mat3 b)
{
	klm_vec3 v = { klm_dot_v3(a, b.i), klm_dot_v3(a, b.j), klm_dot_v3(a, b.k) };
	return v;
}
klm_vec3i klm_mult_vm3i	(klm_vec3i a, klm_mat3i b)
{
	klm_vec3i v = { klm_dot_v3i(a, b.i), klm_dot_v3i(a, b.j), klm_dot_v3i(a, b.k) };
	return v;
}
klm_vec4 	klm_mult_vm4	(klm_vec4 a, 	klm_mat4 b)
{
	klm_vec4 v = { klm_dot_v4(a, b.i), klm_dot_v4(a, b.j), klm_dot_v4(a, b.k), klm_dot_v4(a, b.l) };
	return v;
}
klm_vec4i	klm_mult_vm4i	(klm_vec4i a, klm_mat4i b)
{
	klm_vec4i v = { klm_dot_v4i(a, b.i), klm_dot_v4i(a, b.j), klm_dot_v4i(a, b.k), klm_dot_v4i(a, b.l) };
	return v;
}

klm_vec2 	klm_mult_sv2	(float a,	klm_vec2 b)
{
	klm_vec2 v = { b.x * a, b.y * a };
	return v;
}
klm_vec2i klm_mult_sv2i	(int a,		klm_vec2i b)
{
	klm_vec2i v = { b.x * a, b.y * a };
	return v;
}
klm_vec3 	klm_mult_sv3	(float a,	klm_vec3 b)
{
	klm_vec3 v = { b.x * a, b.y * a, b.z * a };
	return v;
}
klm_vec3i klm_mult_sv3i	(int  a, 	klm_vec3i b)
{
	klm_vec3i v = { b.x * a, b.y * a, b.z * a };
	return v;
}
klm_vec4 	klm_mult_sv4	(float a,	klm_vec4 b)
{
	klm_vec4 v = { b.x * a, b.y * a, b.z * a, b.w * a };
	return v;
}
klm_vec4i	klm_mult_sv4i	(int  a, 	klm_vec4i b)
{
	klm_vec4i v = { b.x * a, b.y * a, b.z * a, b.w * a };
	return v;
}

klm_mat2 	klm_mult_sm2	(float a, 	klm_mat2 b)
{
	klm_mat2 m = 
	{
		klm_mult_sv2(a, b.i),
		klm_mult_sv2(a, b.j)
	};
	return m;
}
klm_mat3 	klm_mult_sm3	(float a, 	klm_mat3 b)
{
	klm_mat3 m = 
	{
		klm_mult_sv3(a, b.i),
		klm_mult_sv3(a, b.j),
		klm_mult_sv3(a, b.k)
	};
	return m;
}
klm_mat4 	klm_mult_sm4	(float a, 	klm_mat4 b)
{
	klm_mat4 m = 
	{
		klm_mult_sv4(a, b.i),
		klm_mult_sv4(a, b.j),
		klm_mult_sv4(a, b.k)
	};
	return m;
}
klm_mat2i klm_mult_sm2i	(int a,		klm_mat2i b)
{
	klm_mat2i m =
	{
		klm_mult_sv2i(a, b.i),
		klm_mult_sv2i(a, b.j)
	};
	return m;
}
klm_mat3i klm_mult_sm3i	(int a, 	klm_mat3i b)
{
	klm_mat3i m = 
	{
		klm_mult_sv3i(a, b.i),
		klm_mult_sv3i(a, b.j),
		klm_mult_sv3i(a, b.k),
	};
	return m;
}
klm_mat4i	klm_mult_sm4i	(int a, 	klm_mat4i b)
{
	klm_mat4i m = 
	{
		klm_mult_sv4i(a, b.i),
		klm_mult_sv4i(a, b.j),
		klm_mult_sv4i(a, b.k),
		klm_mult_sv4i(a, b.l),
	};
	return m;
}

klm_mat2 	klm_element_mult_m2	(klm_mat2  a,	klm_mat2 b)
{
	klm_mat2 m = 
	{
		klm_element_mult_v2(a.i, b.i),
		klm_element_mult_v2(a.j, b.j)
	};
	return m;
}
klm_mat2i klm_element_mult_m2i	(klm_mat2i a,	klm_mat2i b)
{
	klm_mat2i m = 
	{
		klm_element_mult_v2i(a.i, b.i),
		klm_element_mult_v2i(a.j, b.j)
	};
	return m;
}
klm_mat3 	klm_element_mult_m3	(klm_mat3	 a,	klm_mat3 b)
{
	klm_mat3 m = 
	{
		klm_element_mult_v3(a.i, b.i),
		klm_element_mult_v3(a.j, b.j),
		klm_element_mult_v3(a.k, b.k)
	};
	return m;
}
klm_mat3i klm_element_mult_m3i	(klm_mat3i a,	klm_mat3i b)
{
	klm_mat3i m = 
	{
		klm_element_mult_v3i(a.i, b.i),
		klm_element_mult_v3i(a.j, b.j),
		klm_element_mult_v3i(a.k, b.k)
	};
	return m;
}
klm_mat4 	klm_element_mult_m4	(klm_mat4  a,	klm_mat4 b)
{
	klm_mat4 m = 
	{
		klm_element_mult_v4(a.i, b.i),
		klm_element_mult_v4(a.j, b.j),
		klm_element_mult_v4(a.k, b.k),
		klm_element_mult_v4(a.l, b.l)
	};
	return m;
}
klm_mat4i	klm_element_mult_m4i	(klm_mat4i a,	klm_mat4i b)
{
	klm_mat4i m = 
	{
		klm_element_mult_v4i(a.i, b.i),
		klm_element_mult_v4i(a.j, b.j),
		klm_element_mult_v4i(a.k, b.k),
		klm_element_mult_v4i(a.l, b.l)
	};
	return m;
}

klm_vec2 	klm_element_mult_v2	(klm_vec2  a,	klm_vec2 b)
{
	klm_vec2 v = { a.x * b.x, a.y * b.y };
	return v;
}
klm_vec2i klm_element_mult_v2i	(klm_vec2i a,	klm_vec2i b)
{
	klm_vec2i v = { a.x * b.x, a.y * b.y };
	return v;
}
klm_vec3 	klm_element_mult_v3	(klm_vec3	 a,	klm_vec3 b)
{
	klm_vec3 v = { a.x * b.x, a.y * b.y, a.z * b.z };
	return v;
}
klm_vec3i klm_element_mult_v3i	(klm_vec3i a,	klm_vec3i b)
{
	klm_vec3i v = { a.x * b.x, a.y * b.y, a.z * b.z };
	return v;
}
klm_vec4 	klm_element_mult_v4	(klm_vec4  a,	klm_vec4 b)
{
	klm_vec4 v = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return v;
}
klm_vec4i	klm_element_mult_v4i	(klm_vec4i a,	klm_vec4i b)
{
	klm_vec4i v = { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w };
	return v;
}

void klm_print_m4(klm_mat4 m)
{
	printf(	"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n"
			"[ %f %f %f %f ]\n", 
			m.i.x, m.j.x, m.k.x, m.l.x,
			m.i.y, m.j.y, m.k.y, m.l.y, 
			m.i.z, m.j.z, m.k.z, m.l.z, 
			m.i.w, m.j.w, m.k.w, m.l.w);
}
