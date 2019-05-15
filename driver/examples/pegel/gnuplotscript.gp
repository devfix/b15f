set margin 10,10
unset key
set grid
set title ''
set xlabel 'U_{OUT} [V]'
set ylabel 'U_{IN} [V]'
set xrange [0:5]
set yrange [0:5]
set label at 5,5 ' [V] = 0' left
unset output 
set terminal qt
unset output
plot "/tmp/tempfile0" using ($1*0.004888):($2*0.004888) binary format="%int16%int16" endian=big title ' [V] = 0' w l
