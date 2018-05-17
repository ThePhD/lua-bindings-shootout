// lua bindings shootout
// The MIT License (MIT)

// Copyright © 2018 ThePhD

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#ifndef LUA_BINDINGS_SHOOTOUT_BENCHMARK_HPP
#define LUA_BINDINGS_SHOOTOUT_BENCHMARK_HPP

#include <benchmark/benchmark.h>

namespace lbs {
	template <typename T, typename U>
	inline void expect(benchmark::State& benchmark_state, const T& left, const U& right) {
		if (left != right) {
			benchmark_state.SkipWithError("unexpected result");
		}
	}

	inline void unsupported(benchmark::State& benchmark_state, const char* message) {
		benchmark_state.SkipWithError(message);
	}

	inline void unsupported(benchmark::State& benchmark_state) {
		unsupported(benchmark_state, "unsupported");
	}

	inline const std::size_t repetition() {
		static const std::size_t value = 50;
		return value;
	}

	inline const std::string& repetition_s() {
		static const std::string value = std::to_string(repetition());
		return value;
	}

	inline std::string repeated_code(std::string code) {
		return "for i=0," + repetition_s() + " do " + code + " end";
	}

} // namespace lbs

#endif //LUA_BINDINGS_SHOOTOUT_BENCHMARK_HPP
