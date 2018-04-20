# # lua bindings shootout
# The MIT License (MIT)
#
# Copyright � 2018 ThePhD
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import matplotlib
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.ticker as mticker
import csv
import json
import math
import random
import bisect
import os
import argparse
import fnmatch
import sys


def parse_csv(c, data_point_names, time_scales):
	benchmarks = {}
	benchmark_heuristics = {}
	return benchmarks, benchmark_heuristics


def parse_json(j, data_point_names, time_scales):
	timescale_units = [x[0] for x in time_scales]

	benchmarks = []
	benchmark_heuristics = {
	    "min": sys.float_info.max,
	    "max": sys.float_info.min
	}

	j_benchmarks_array = j["benchmarks"]
	for j_benchmark in j_benchmarks_array:
		name = j_benchmark['name']
		base_name = j_benchmark['base_name']
		potential_targets = [b for b in benchmarks if b['name'] == base_name]
		if (len(potential_targets) < 1):
			benchmarks.append({
			    "name": base_name,
			    "data": {},
			    "statistics": {},
			    "name_index": {},
			    "color_index": {}
			})
		benchmark = benchmarks[-1]
		data = benchmark["data"]
		statistics = benchmark["statistics"]
		for point_name_lower in data_point_names:
			point_name = point_name_lower[0]
			if point_name not in data:
				data[point_name] = []
		time_unit = j_benchmark['time_unit']
		unit_index = timescale_units.index(time_unit)
		time_scale = time_scales[unit_index]
		to_seconds_multiplier = time_scale[2]
		if name == base_name:
			# is a data point
			for point_name_lower in data_point_names:
				point_name = point_name_lower[0]
				point_list = data[point_name]
				point = j_benchmark[point_name]
				point_adjusted = point * to_seconds_multiplier
				point_list.append(point_adjusted)
				benchmark_heuristics["max"] = max(
				    benchmark_heuristics["max"], point_adjusted)
				benchmark_heuristics["min"] = min(
				    benchmark_heuristics["min"], point_adjusted)
		else:
			# is a statistic
			statistic_name = name.replace(base_name + "_", "")
			if statistic_name not in statistics:
				statistics[statistic_name] = {}
			statistic = statistics[statistic_name]
			for point_name_lower in data_point_names:
				point_name = point_name_lower[0]
				point = j_benchmark[point_name]
				point_adjusted = point * to_seconds_multiplier
				statistic[point_name] = point_adjusted

	def name_sorter(b):
		return b["name"]

	def mean_sorter(b):
		data_point_name_lower = data_point_names[0]
		data_point_name = data_point_name_lower[0]
		return b["statistics"]["mean"][data_point_name]

	# first, sort by name so we can assign colors to each
	# benchmark appropriately (and make those color assignments)
	# stable
	benchmarks.sort(key=name_sorter)
	for bi, b in enumerate(benchmarks):
		b["name_index"] = bi
		ci = b["color_index"]
		if (len(data_point_names) < 2):
			dp = data_point_names[0]
			ci[dp[0]] = bi
		else:
			for dpi, dp in enumerate(data_point_names):
				ci[dp[0]] = dpi

	# second, sort by mean
	# so the actual benchmark
	# ordering of graphs and the like
	# is based on lowest to highest mean
	lower_is_better = data_point_names[0][1]
	benchmarks.sort(key=mean_sorter, reverse=lower_is_better)

	return benchmarks, benchmark_heuristics


def draw_graph(name, benchmarks, benchmark_heuristics, data_point_names,
               time_scales):
	# initialize figures
	figures, axes = plt.subplots()

	# get the values of the time scale to perform bisecting
	time_scale_values_from_seconds = [x[2] for x in time_scales]
	benchmarks_max = benchmark_heuristics["max"]
	benchmarks_min = benchmark_heuristics["min"]

	# some pattern constants, to help us be pretty
	# some color constants, to help us be pretty!
	# and differentiate graphs
	# yapf: disable
	data_point_aesthetics = [
	 ('#a6cee3', '/'),
	 ('#f255bb', 'O'),
	 ('#00c9ab', '\\'),
	 ('#b15928', 'o'),
	 ('#33a02c', '.'),
	 ('#fb9a99', '*'),
	 ('#e31a1c', '+'),
	 ('#fdbf6f', 'x'),
	 ('#ff7f00', '|'),
	 ('#cab2d6', None),
	 ('#6a3d9a', '-'),
	 ('#ffff99', 'xx'),
	 ('#f5f5f5', '..'),
	 ('#1f78b4', '||'),
	 ('#b2df8a', '**'),
	 ('#cc33cc', '--')
	]
	#yapf: enable

	# transpose data into forms we need
	benchmark_names = [b["name"] for b in benchmarks]
	bars = []
	scatters = []
	num_data_points = len(data_point_names)
	bar_padding = 0.15
	bar_height = 0.35
	bar_all_sizes = bar_height * num_data_points + bar_padding
	quarter_bar_height = bar_height * 0.25
	bar_y_positions = []

	# draw mean-based bars with error indicators
	# and draw scatter-plot points
	for bi, benchmark in enumerate(benchmarks):
		for di, data_point_name_lower in enumerate(data_point_names):
			data_point_name = data_point_name_lower[0]
			bar_y = (bi * bar_all_sizes) + (di * bar_height) + (
			    bar_padding * 0.5)
			bar_y_positions.append(bar_y)
			mean = benchmark["statistics"]["mean"][data_point_name]
			stddev = benchmark["statistics"]["stddev"][data_point_name]
			color_index = benchmark["color_index"][data_point_name]
			aesthetics = data_point_aesthetics[color_index]
			color = aesthetics[0]
			colorhsv = matplotlib.colors.rgb_to_hsv(
			    matplotlib.colors.hex2color(color))
			colorhsv[2] *= 0.6
			edgecolor = matplotlib.colors.hsv_to_rgb(colorhsv)
			#color = 'green'
			hatch = aesthetics[1]
			bar = axes.barh(
			    bar_y,
			    mean,
			    height=bar_height,
			    xerr=stddev,
			    linewidth=0.2,
			    edgecolor=edgecolor,
			    color=color,
			    hatch=hatch,
			    align='edge',
			    error_kw={
			        "capsize": 5.0,
			        "mew": 1.2,
			        "ecolor": 'black',
			    },
			    alpha=0.82)
			bars.append(bar)
			# the scatter plot should be semi-transparent in color...
			xscatter = benchmark["data"][data_point_name]
			xscatter_len = len(xscatter)
			yscatter = [
			    bar_y + random.uniform(quarter_bar_height,
			                           bar_height - quarter_bar_height)
			    for _ in xscatter
			]
			scatter_alpha = 0.20 if xscatter_len < 11 else 0.10 if xscatter_len < 101 else 0.05 if xscatter_len < 1001 else 0.002
			scatter = axes.scatter(
			    xscatter,
			    yscatter,
			    color=color,
			    edgecolor='black',
			    linewidth=0.5,
			    alpha=scatter_alpha)
			scatters.append(scatter)

	xscaleindex = bisect.bisect_left(time_scale_values_from_seconds,
	                                 benchmarks_max)
	xscale = time_scales[xscaleindex - 1]

	def time_axis_formatting(value, pos):
		if value == 0:
			return '0'
		if value.is_integer():
			return '{0:.0f}'.format(value * xscale[3])
		return '{0:.2f}'.format(value * xscale[3])

	absoluterange = benchmarks_max - benchmarks_min
	axes.set_xlim([0, benchmarks_max + (absoluterange * 0.25)])
	axes.xaxis.set_major_formatter(
	    mticker.FuncFormatter(time_axis_formatting))

	# have ticks drawn from base of bar graph
	# to text labels
	y_ticks = [((y + 0.5) * bar_all_sizes)
	           for y in range(0, int(len(bar_y_positions) / num_data_points))]
	axes.set_yticks(y_ticks)
	# label each group (each cluster along the x axes)
	# with the names of the benchmarks we ran
	axes.set_yticklabels(benchmark_names)

	# if we have 2 or more data points,
	# a legend will help us label it all
	if (num_data_points > 1):
		# a proper legend for each name in data_point_names
		legend_texts = [(data_point_name[0] +
		                 ('- lower=good'
		                  if data_point_name[1] else 'higher=good')
		                 for data_point_name in data_point_names)]
		# retrieve the color/shape of the bar as a reference so we can construct
		bar_style_references = [bar[0] for bar in bars]
		# make legend
		axes.legend(bar_style_references, legend_texts)
		axes.set_xlabel('measured in ' + xscale[1])
	else:
		# no need to put a legend, it's basically fine as-is
		data_point_name = data_point_names[0]
		legend_text = (data_point_name[0], 'lower is better'
		               if data_point_name[1] else 'higher is better')
		axes.set_xlabel(legend_text[0] + ' measured in ' + xscale[1] +
		                ' - ' + legend_text[1])

	# set the benchmark name, typically derived from the file name
	axes.set_title(name)
	# get a nice, clean layout
	figures.tight_layout()

	# make sure to adjust top and bottoms
	figures.subplots_adjust(bottom=0.2)

	return figures, axes


def main():
	parser = argparse.ArgumentParser(
	    description=
	    'Generate graphs from a Google-Benchmark compatible json/csv listing of data'
	)
	parser.add_argument(
	    '-i',
	    '--input',
	    nargs='?',
	    default='ptrptr_benchmarks.json',
	    type=argparse.FileType('r'))
	parser.add_argument('-f', '--input_format', nargs='?')
	parser.add_argument('-o', '--output', nargs='?')
	parser.add_argument(
	    '-d', '--data_point_names', nargs='+', default=['real_time'])
	parser.add_argument('-l', '--lower', nargs='+', default=['real_time'])
	args = parser.parse_args()
	args.input_format = args.input_format or ("csv" if fnmatch.fnmatch(
	    args.input.name, "*.csv") else "json")
	if not args.output:
		directoryname, filename = os.path.split(args.input.name)
		file = os.path.splitext(filename)[0]
		args.output = os.path.join(directoryname, file + ".png")
	if len(args.data_point_names) < 1:
		print(
		    "You must specify 1 or more valid data point names",
		    file=sys.stderr)
		sys.exit(1)

	data_point_names = [(dpn, dpn in args.lower)
	                    for dpn in args.data_point_names]

	random.seed(1782905257495843795)

	name = os.path.split(args.input.name)[1]
	name = os.path.splitext(name)[0]

	time_scales = [
	    ("fs", "femtoseconds", 1e-15, 1e+15),
	    ("ps", "picoseconds", 1e-12, 1e+12),
	    ("ns", "nanoseconds", 1e-9, 1e+9),
	    ("µs", "microseconds", .00001, 1000000),
	    ("us", "microseconds", .00001, 1000000),
	    ("ms", "milliseconds", .001, 1000),
	    ("s", "seconds", 1, 1),
	    ("m", "minutes", 60, 1 / 60),
	    ("h", "hours", 60 * 60, (1 / 60) / 60),
	]

	is_csv = args.input_format == "csv"
	is_json = args.input_format == "json"
	if (not is_csv and not is_json):
		print(
		    "You must specify either 'json' or 'csv' as the format.",
		    file=sys.stderr)
		sys.exit(1)

	if is_csv:
		c = csv.reader(args.input)
		benchmarks, benchmark_heuristics = parse_csv(c, data_point_names,
		                                             time_scales)
		draw_graph(name, benchmarks, benchmark_heuristics, data_point_names,
		           time_scales)
	elif is_json:
		j = json.load(args.input)
		benchmarks, benchmark_heuristics = parse_json(
		    j, data_point_names, time_scales)

		draw_graph(name, benchmarks, benchmark_heuristics, data_point_names,
		           time_scales)
	else:
		pass

	plt.savefig(args.output, bbox_inches='tight', transparent=False)


if __name__ == "__main__":
	main()