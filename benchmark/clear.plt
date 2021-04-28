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
set title "{/:Bold Modifier Member Function: clear - Cumulative}\n{/*0.8 uint64\\\_t data with std::allocator on nondescript Linux with GCC 10.2 -O3}"
set output "benchmark/clear.svg"
set key noautotitle
set key left Left reverse

set grid

set xlabel "N elements cleared"
set xtics add ("0" 0.4)
unset mxtics
set logscale x

set ylabel "Time to clear N elements (ns)"
unset mytics
set logscale y

 plot "benchmark/clear.csv" \
   using 6:4:5 with filledcurves \
     title "Min/Max Range" fillstyle linecolor rgb "seagreen", \
     '' using 6:4 linetype -1 , \
     '' using 6:5 linetype -1, \
   '' using ($6 == 0 ? 0.4 : $6):1 with linespoints \
     title "Mean" linewidth 2 linetype rgb "forest-green" pointtype 7 pointsize 0.5
