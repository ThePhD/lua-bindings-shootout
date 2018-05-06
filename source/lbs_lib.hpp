#pragma once

#include <tuple>
#include <string>

namespace lbs {

	inline int magic_value() {
		static const int v = 3;
		return v;
	}

	inline const std::string& magic_value_string() {
		static const std::string v = std::to_string(magic_value());
		return v;
	}

	struct basic {
		double var = 499;
		int var0 = 501;
		int var1 = 502;
		int var2 = 503;
		int var3 = 504;
		int var4 = 505;

		basic() = default;
		basic(double x)
		: var(x) {
		}

		double get() const {
			return var;
		}

		void set(double x) {
			var = x;
		}
	};

	struct basic_large {
		double var = 499;
		int var0 = 500;
		int var1 = 501;
		int var2 = 502;
		int var3 = 503;
		int var4 = 504;
		int var5 = 505;
		int var6 = 506;
		int var7 = 507;
		int var8 = 508;
		int var9 = 509;
		int var10 = 510;
		int var11 = 511;
		int var12 = 512;
		int var13 = 513;
		int var14 = 514;
		int var15 = 515;
		int var16 = 516;
		int var17 = 517;
		int var18 = 518;
		int var19 = 519;
		int var20 = 520;
		int var21 = 521;
		int var22 = 522;
		int var23 = 523;
		int var24 = 524;
		int var25 = 525;
		int var26 = 526;
		int var27 = 527;
		int var28 = 528;
		int var29 = 529;
		int var30 = 530;
		int var31 = 531;
		int var32 = 532;
		int var33 = 533;
		int var34 = 534;
		int var35 = 535;
		int var36 = 536;
		int var37 = 537;
		int var38 = 538;
		int var39 = 539;
		int var40 = 540;
		int var41 = 541;
		int var42 = 542;
		int var43 = 543;
		int var44 = 544;
		int var45 = 545;
		int var46 = 546;
		int var47 = 547;
		int var48 = 548;
		int64_t var49 = 549;

		basic_large() = default;
	};

	struct basic_stateful {
		double storage;

		basic_stateful() = default;

		double operator()(double i) {
			storage = i;
			return storage;
		}
	};

	struct complex_base_a {
		double a = lbs::magic_value() - 2;

		complex_base_a() = default;

		virtual double a_func() const {
			return a;
		}
	};

	struct complex_base_b {
		double b = lbs::magic_value() - 1;

		complex_base_b() = default;

		virtual double b_func() const {
			return b;
		}
	};

	struct complex_ab : complex_base_a, complex_base_b {
		double ab = lbs::magic_value();

		complex_ab() = default;

		virtual double a_func() const override {
			return ab;
		}

		virtual double b_func() const override {
			return ab;
		}

		double ab_func() const {
			return ab;
		}
	};

	inline double basic_call(double x) {
		return x;
	}

	inline basic basic_return(double x) {
		return basic(x);
	}

	inline double basic_get_var(const basic& b) {
		return b.var;
	}

	inline std::tuple<double, double> basic_multi_return(double i) {
		return { i, i * 2 };
	}

	inline void basic_multi_return_out(double i, double& out_1, double& out_2) {
		std::tie(out_1, out_2) = basic_multi_return(i);
	}

} // namespace lbs
