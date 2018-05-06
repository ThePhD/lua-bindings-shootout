%module swig_lib
%include <typemaps.i> // this is all the typemaps for this
%apply double& OUTPUT{ double& out_1 };
%apply double& OUTPUT{ double& out_2 };
%{
#include "lbs_lib.hpp"
using namespace lbs;
%}

struct basic {
	double var;
	int var0;
	int var1;
	int var2;
	int var3;
	int var4;

	basic();
	basic(double x);

	double get() const;

	void set(double x);
};

struct basic_large {
	double var;
	int var0;
	int var1;
	int var2;
	int var3;
	int var4;
	int var5;
	int var6;
	int var7;
	int var8;
	int var9;
	int var10;
	int var11;
	int var12;
	int var13;
	int var14;
	int var15;
	int var16;
	int var17;
	int var18;
	int var19;
	int var20;
	int var21;
	int var22;
	int var23;
	int var24;
	int var25;
	int var26;
	int var27;
	int var28;
	int var29;
	int var30;
	int var31;
	int var32;
	int var33;
	int var34;
	int var35;
	int var36;
	int var37;
	int var38;
	int var39;
	int var40;
	int var41;
	int var42;
	int var43;
	int var44;
	int var45;
	int var46;
	int var47;
	int var48;
	int64_t var49;

	basic_large();
};

struct complex_base_a {
	complex_base_a();

	virtual double a_func() const;
};

struct complex_base_b {
	complex_base_b();

	virtual double b_func() const;
};

struct complex_ab : complex_base_a, complex_base_b {
	complex_ab();

	virtual double a_func() const;

	virtual double b_func() const;

	double ab_func() const;
};

double basic_call(double x);

basic basic_return(double x);

double basic_get_var(const basic& b);

void basic_multi_return_out(double i, double& out_1, double& out_2);
