set margin 10,10
unset key
set grid
set title ''
set xlabel 'Zeit [t]'
set ylabel 'Spannung [V]'
set xrange [0:1023]
set yrange [0:1023]
set label at 1022,1022 '1' left
set label at 1022,511 '2' left
unset output 
set terminal qt
unset output
plot "/tmp/tempfile0" using ($1*1.000000):($2*1.000000) binary format="%int16%int16" endian=big title ' [] = 1' w l,"/tmp/tempfile1" using ($1*1.000000):($2*1.000000) binary format="%int16%int16" endian=big title ' [] = 2' w l
