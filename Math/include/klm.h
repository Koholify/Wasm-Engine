#ifndef LINALG_DEF_H
#define LINALG_DEF_H

typedef struct klm_vec2
{
	float x;
	float y;
} klm_vec2;

typedef struct klm_vec2i
{
	int x;
	int y;
} klm_vec2i;

typedef struct klm_vec3
{
	float x;
	float y;
	float z;
} klm_vec3;

typedef struct klm_vec3i
{
	int x;
	int y;
	int z;
} klm_vec3i;

typedef struct klm_vec4
{
	float x;
	float y;
	float z;
	float w;
} klm_vec4;

typedef struct klm_vec4i
{
	int x;
	int y;
	int z;
	int w;
} klm_vec4i;

typedef struct klm_mat2
{
	klm_vec2 i;
	klm_vec2 j;
} klm_mat2;

typedef struct klm_mat2i
{
	klm_vec2i i;
	klm_vec2i j;
} klm_mat2i;

typedef struct klm_mat3
{
	klm_vec3 i;
	klm_vec3 j;
	klm_vec3 k;
} klm_mat3;

typedef struct klm_mat3i
{
	klm_vec3i i;
	klm_vec3i j;
	klm_vec3i k;
} klm_mat3i;

typedef struct klm_mat4
{
	klm_vec4 i;
	klm_vec4 j;
	klm_vec4 k;
	klm_vec4 l;
} klm_mat4;

typedef struct klm_mat4i
{
	klm_vec4i i;
	klm_vec4i j;
	klm_vec4i k;
	klm_vec4i l;
} klm_mat4i;

extern const klm_mat4 	m_mat4_identity;
extern const klm_mat4i 	m_mat4i_identity;
extern const klm_mat3 	m_mat3_identity;
extern const klm_mat3i 	m_mat3i_identity;
extern const klm_mat2 	m_mat2_identity;
extern const klm_mat2i 	m_mat2i_identity;

klm_vec2 	klm_add_v2	(klm_vec2 a,	klm_vec2 b);
klm_vec2i klm_add_v2i	(klm_vec2i a,	klm_vec2i b);
klm_vec3 	klm_add_v3	(klm_vec3 a,	klm_vec3 b);
klm_vec3i klm_add_v3i	(klm_vec3i a,	klm_vec3i b);
klm_vec4 	klm_add_v4	(klm_vec4 a,	klm_vec4 b);
klm_vec4i klm_add_v4i	(klm_vec4i a,	klm_vec4i b);

klm_mat2 	klm_add_m2	(klm_mat2 a,	klm_mat2 b);
klm_mat2i klm_add_m2i	(klm_mat2i a,	klm_mat2i b);
klm_mat3 	klm_add_m3	(klm_mat3 a,	klm_mat3 b);
klm_mat3i klm_add_m3i	(klm_mat3i a,	klm_mat3i b);
klm_mat4 	klm_add_m4	(klm_mat4 a,	klm_mat4 b);
klm_mat4i klm_add_m4i	(klm_mat4i a,	klm_mat4i b);

klm_vec2 	klm_sub_v2	(klm_vec2 a,	klm_vec2 b);
klm_vec2i klm_sub_v2i	(klm_vec2i a,	klm_vec2i b);
klm_vec3 	klm_sub_v3	(klm_vec3 a,	klm_vec3 b);
klm_vec3i klm_sub_v3i	(klm_vec3i a,	klm_vec3i b);
klm_vec4 	klm_sub_v4	(klm_vec4 a,	klm_vec4 b);
klm_vec4i klm_sub_v4i	(klm_vec4i a,	klm_vec4i b);

klm_mat2 	klm_sub_m2	(klm_mat2 a,	klm_mat2 b);
klm_mat2i klm_sub_m2i	(klm_mat2i a,	klm_mat2i b);
klm_mat3 	klm_sub_m3	(klm_mat3 a,	klm_mat3 b);
klm_mat3i klm_sub_m3i	(klm_mat3i a,	klm_mat3i b);
klm_mat4 	klm_sub_m4	(klm_mat4 a,	klm_mat4 b);
klm_mat4i klm_sub_m4i	(klm_mat4i a, klm_mat4i b);

float 	klm_dot_v2	(klm_vec2 a,	klm_vec2 b);
int 		klm_dot_v2i	(klm_vec2i a,	klm_vec2i b);
float 	klm_dot_v3	(klm_vec3 a,	klm_vec3 b);
int 		klm_dot_v3i	(klm_vec3i a,	klm_vec3i b);
float 	klm_dot_v4	(klm_vec4 a,	klm_vec4 b);
int			klm_dot_v4i	(klm_vec4i a,	klm_vec4i b);

klm_mat2 	klm_mult_m2	(klm_mat2 a,	klm_mat2 b);
klm_mat2i klm_mult_m2i	(klm_mat2i a,	klm_mat2i b);
klm_mat3 	klm_mult_m3	(klm_mat3 a,	klm_mat3 b);
klm_mat3i klm_mult_m3i	(klm_mat3i a,	klm_mat3i b);
klm_mat4 	klm_mult_m4	(klm_mat4 a,	klm_mat4 b);
klm_mat4i	klm_mult_m4i	(klm_mat4i a,	klm_mat4i b);

klm_vec2 	klm_mult_mv2	(klm_mat2 a,	klm_vec2 b);
klm_vec2i klm_mult_mv2i	(klm_mat2i a,	klm_vec2i b);
klm_vec3 	klm_mult_mv3	(klm_mat3 a,	klm_vec3 b);
klm_vec3i klm_mult_mv3i	(klm_mat3i a, klm_vec3i b);
klm_vec4 	klm_mult_mv4	(klm_mat4 a,	klm_vec4 b);
klm_vec4i	klm_mult_mv4i	(klm_mat4i a, klm_vec4i b);

klm_vec2 	klm_mult_vm2	(klm_vec2 a, 	klm_mat2 b);
klm_vec2i klm_mult_vm2i	(klm_vec2i a, klm_mat2i b);
klm_vec3 	klm_mult_vm3	(klm_vec3 a, 	klm_mat3 b);
klm_vec3i klm_mult_vm3i	(klm_vec3i a, klm_mat3i b);
klm_vec4 	klm_mult_vm4	(klm_vec4 a, 	klm_mat4 b);
klm_vec4i	klm_mult_vm4i	(klm_vec4i a, klm_mat4i b);

klm_vec2 	klm_mult_sv2	(float a,	klm_vec2 b);
klm_vec2i klm_mult_sv2i	(int a,		klm_vec2i b);
klm_vec3 	klm_mult_sv3	(float a,	klm_vec3 b);
klm_vec3i klm_mult_sv3i	(int  a, 	klm_vec3i b);
klm_vec4 	klm_mult_sv4	(float a,	klm_vec4 b);
klm_vec4i	klm_mult_sv4i	(int  a, 	klm_vec4i b);

klm_mat2 	klm_mult_sm2	(float a, 	klm_mat2 b);
klm_mat2i klm_mult_sm2i	(int a,		klm_mat2i b);
klm_mat3 	klm_mult_sm3	(float a, 	klm_mat3 b);
klm_mat3i klm_mult_sm3i	(int a, 	klm_mat3i b);
klm_mat4 	klm_mult_sm4	(float a, 	klm_mat4 b);
klm_mat4i	klm_mult_sm4i	(int  a, 	klm_mat4i b);

klm_mat2 	klm_element_mult_m2	(klm_mat2  a,	klm_mat2 b);
klm_mat2i klm_element_mult_m2i	(klm_mat2i a,	klm_mat2i b);
klm_mat3 	klm_element_mult_m3	(klm_mat3	 a,	klm_mat3 b);
klm_mat3i klm_element_mult_m3i	(klm_mat3i a,	klm_mat3i b);
klm_mat4 	klm_element_mult_m4	(klm_mat4  a,	klm_mat4 b);
klm_mat4i	klm_element_mult_m4i	(klm_mat4i a,	klm_mat4i b);

klm_vec2 	klm_element_mult_v2	(klm_vec2  a,	klm_vec2 b);
klm_vec2i klm_element_mult_v2i	(klm_vec2i a,	klm_vec2i b);
klm_vec3 	klm_element_mult_v3	(klm_vec3	 a,	klm_vec3 b);
klm_vec3i klm_element_mult_v3i	(klm_vec3i a,	klm_vec3i b);
klm_vec4 	klm_element_mult_v4	(klm_vec4  a,	klm_vec4 b);
klm_vec4i	klm_element_mult_v4i	(klm_vec4i a,	klm_vec4i b);

void klm_print_m4(klm_mat4 m);

#endif /* LINALG_DEF_H */
