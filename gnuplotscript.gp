set margin 10,10
unset key
set grid
set title ''
set xlabel 'Desc X [Unit X]'
set ylabel 'Desc Y [Unit Y]'
set xrange [0:5000]
set yrange [0:50]
set label at 4995,49 'Desc P [Unit P] = 1' left
unset output 
set terminal qt
unset output
plot "/tmp/tempfile32" using ($1*4.887586):($2*0.048876) binary format="%int16%int16" endian=big title 'Desc P [Unit P] = 1' w l
