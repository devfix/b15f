set margin 10,10
unset key
set grid
set title ''
set xlabel 'U_{GS} [V]'
set ylabel 'I_D [mA]'
set xrange [5:0]
set x2range [5:0]
set y2range [0:50]
set yrange [0:50]
set label at 2,33 'U_{DS} [V] = 300' right
set label at 2,30 'U_{DS} [V] = 325' right
set label at 2,33 'U_{DS} [V] = 350' right
set label at 2,35 'U_{DS} [V] = 375' right
set label at 2,21 'U_{DS} [V] = 400' right
set label at 2,21 'U_{DS} [V] = 425' right
set label at 2,22 'U_{DS} [V] = 450' right
set label at 2,22 'U_{DS} [V] = 475' right
set label at 2,22 'U_{DS} [V] = 500' right
set label at 2,5 'U_{DS} [V] = 525' right
set label at 2,11 'U_{DS} [V] = 550' right
set label at 2,11 'U_{DS} [V] = 575' right
set label at 2,11 'U_{DS} [V] = 600' right
set label at 2,11 'U_{DS} [V] = 625' right
set label at 2,4 'U_{DS} [V] = 650' right
set label at 2,4 'U_{DS} [V] = 650' right
set label at 2,4 'U_{DS} [V] = 700' right
set y2tics
unset ytics
set ytics format ''
unset output 
set terminal qt
unset output
plot "/tmp/tempfile1" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 300' w l,"/tmp/tempfile2" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 325' w l,"/tmp/tempfile3" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 350' w l,"/tmp/tempfile4" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 375' w l,"/tmp/tempfile5" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 400' w l,"/tmp/tempfile6" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 425' w l,"/tmp/tempfile7" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 450' w l,"/tmp/tempfile8" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 475' w l,"/tmp/tempfile9" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 500' w l,"/tmp/tempfile10" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 525' w l,"/tmp/tempfile11" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 550' w l,"/tmp/tempfile12" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 575' w l,"/tmp/tempfile13" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 600' w l,"/tmp/tempfile14" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 625' w l,"/tmp/tempfile15" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 650' w l,"/tmp/tempfile16" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 675' w l,"/tmp/tempfile17" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{DS} [V] = 700' w l
