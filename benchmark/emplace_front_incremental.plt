#!/usr/bin/gnuplot
#_______ _____  ______ ______
#  |____|  __ \|  ____|  ____|  Tree data structure for modern C++
#  | |  | |__) | |__  | |__  version 0.1.0
#  | |  |  _  /|  __| |  __| https://github.com/FrancoisCarouge/Tree
#  | |  | | \ \| |____| |____
#  |_|  |_|  \_\______|______|
#
# Licensed under the MIT License <http://opensource.org/licenses/MIT>.
# SPDX-License-Identifier: MIT
# Copyright 2020 Francois Carouge.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

set terminal svg
set datafile separator ","
set title "{/:Bold Modifier Member Function: emplace\\\_front - Incremental}\n{/*0.8 fcarouge::tree<uint64\\\_t, std::allocator>::emplace\\\_front() on nondescript x86\\\_64 Linux with GCC 11.0 and -O3 option}"
set key noautotitle
set xlabel "N elements emplaced"
set logscale x
set ylabel "Time to emplace the N+1th element (ns)"
set yrange [0:200]
set output "benchmark/emplace_front_incremental.svg"
set style line 1 \
  linewidth 4 \
  linetype rgb "forest-green" \
  pointtype 7 \
  pointsize 1.2

plot "benchmark/emplace_front_incremental.csv" using 1:2 with linespoints ls 1
