
name_axe_y = 'Base Sequence Series'
name_axe_x = 'Base Position' 
name_acgt = 'Adenine (A) Nucleobase'

name_output = 'Fig-A.png' 

name_1_protein = 21563
name_2_protein = 25384
name_3_protein = 18000 
name_4_protein = 'S-Protein Wuhan Seq.' 


name_11 = '1-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'
name_12 = '2-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'
name_13 = '3-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'

name_21 = '4-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'
name_22 = '5-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'
name_23 = '6-input-PLOTS/00-FIGURES-PAPER/multiALL-A-sum01-complete.txt'

name_x0 = 0 
name_x1 = 5000 
name_x2 = 30000 

name_y0 = -100
name_y1 = 50 
name_y2 = 100 


#-----------------------------------------------
set terminal pngcairo size 1600,1200 font "Times-Roman, 14" enhanced
set output name_output
#-----------------------------------------------


mpl_top    = 0.4 #inch  outer top margin, title goes here
mpl_bot    = 0.7 #inch  outer bottom margin, x label goes here
mpl_left   = 0.9 #inch  outer left margin, y label goes here
mpl_right  = 0.1 #inch  outer right margin, y2 label goes here
mpl_height = 1.5 #inch  height of individual plots
mpl_width  = 4.0 	# 2.0 inch  width of individual plots
##mpl_dx     = 0.1 	# 0.1 inch  inter-plot horizontal spacing
##mpl_dy     = 0.1 	# 0.1 inch  inter-plot vertical spacing
mpl_dx     = 0.05 	# 0.1 inch  inter-plot horizontal spacing
mpl_dy     = 0.05 	# 0.1 inch  inter-plot vertical spacing
mpl_ny     = 3   	# number of rows
mpl_nx     = 2   	# number of columns

# calculate full dimensions
xsize = mpl_left+mpl_right+(mpl_width*mpl_nx)+(mpl_nx-1)*mpl_dx
ysize = mpl_top+mpl_bot+(mpl_ny*mpl_height)+(mpl_ny-1)*mpl_dy

# placement functions
#   rows are numbered from bottom to top
bot(n) = (mpl_bot+(n-1)*mpl_height+(n-1)*mpl_dy)/ysize
top(n)  = 1-((mpl_top+(mpl_ny-n)*(mpl_height+mpl_dy))/ysize)
#   columns are numbered from left to right
left(n) = (mpl_left+(n-1)*mpl_width+(n-1)*mpl_dx)/xsize
right(n)  = 1-((mpl_right+(mpl_nx-n)*(mpl_width+mpl_dx))/xsize)


set offsets
set autoscale fix
set size 1,1

##set key top left
set key bottom left

set key spacing 1.12 font "Helvetica, 14"
##set key box lt -1 lw 1 
set key box lt -1 lw 1 width 0 vertical maxrows 4


set grid back lc rgb '#808080' lt 0 lw 3

#-----------------------------------------------

# start plotting
set multiplot

## 1-3  2-3
## 1-2  2-2
## 1-1  2-1

#-------------
# subplot  1-1
#-------------
set lmargin at screen left(1)
set rmargin at screen right(1)
set tmargin at screen top(1)
set bmargin at screen bot(1)


set xlabel name_axe_x offset 30,-0.6,0 font ',22'

####set xtics name_x0, name_x1, name_x2 font ',18'


### set decimals in x-axes
set xtics ("0" 0, "5,000" 5000, "10,000" 10000, "15,000" 15000, "20,000" 20000, "25,000" 25000) font ',18'



set ylabel '' offset 0
##set ylabel name_axe_y offset 0,0,-10 font ',22' 
set ytics name_y0,name_y1,name_y2 font ',18'

##set label 'A variant' at 20000, 120 font ',20'

    load name_11 

#-------------
# subplot  1-2
#-------------
set lmargin at screen left(1)
set rmargin at screen right(1)
set tmargin at screen top(2)
set bmargin at screen bot(2)


##set ylabel '' offset 0
set ylabel name_axe_y offset -2,0,0 font ',22' 
set ytics name_y0,name_y1,name_y2 font ',18'



unset xtics 

set xtics format ''
unset xlabel

unset label  
##set label 'B variant' at 20000, 120 font ',20'

    load name_12 


#-------------
# subplot  1-3
#-------------
set lmargin at screen left(1)
set rmargin at screen right(1)
set tmargin at screen top(3)
set bmargin at screen bot(3)


set ylabel '' offset 0
set ytics name_y0,name_y1,name_y2 font ',18'

set xtics format ''
unset xlabel

##set title name_acgt offset 30,0,0 font 'Arial-Bold,22'
set title name_acgt offset 30,0,0 font ',22'

unset label 
##set label 'C variant' at 20000, 120 font ',20'

    load name_13 


###########################################
#-------------
# subplot  2-1
#-------------
set lmargin at screen left(2)
set rmargin at screen right(2)
set tmargin at screen top(1)
set bmargin at screen bot(1)


set format x '%g'
set xlabel '' font ',20'


### set decimals in x-axes
set xtics ("0" 0, "5,000" 5000, "10,000" 10000, "15,000" 15000, "20,000" 20000, "25,000" 25000) font ',18'


set ytics format ''
unset ylabel

set title ''

unset label 
##set label 'D variant' at 20000, 120 font ',20'

    load name_21 


#-------------
# subplot  2-2
#-------------
set lmargin at screen left(2)
set rmargin at screen right(2)
set tmargin at screen top(2)
set bmargin at screen bot(2)


unset xtics 

set xtics format ''
unset xlabel

set ytics format ''
unset ylabel

unset label 
##set label 'E variant' at 20000, 120 font ',20'

    load name_22 


#-------------
# subplot  2-3
#-------------
set lmargin at screen left(2)
set rmargin at screen right(2)
set tmargin at screen top(3)
set bmargin at screen bot(3)


set xtics format ''
unset xlabel

set ytics format ''
unset ylabel

unset label 
set label name_4_protein at name_3_protein, -120 font ',18'


	## https://41j.com/blog/2016/08/marking-internals-in-gnuplot-graph-with-shading/

### rgb"green" notitle
## '#00ffff'
## "#eeeeee"
##'#aa00aa'

####unset key
set xrange[name_x0:name_x2]

set style rect fc lt -1 fs transparent solid 0.15 noborder
set obj rect from name_1_protein, graph 0 to name_2_protein, graph 1 fc rgb "red"

##unset label 
    load name_23 


###########################################
unset multiplot
###########################################


