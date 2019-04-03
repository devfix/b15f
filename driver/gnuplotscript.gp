set margin 10,10
unset key
set grid
set title ''
set xlabel 'U_{DS} [V]'
set ylabel 'I_D [mA]'
set xrange [0:5]
set yrange [0:50]
set label at 4,3 'U_{GS} [V] = 460' left
set label at 4,7 'U_{GS} [V] = 480' left
set label at 3,13 'U_{GS} [V] = 500' left
set label at 2,22 'U_{GS} [V] = 520' left
set label at 1,33 'U_{GS} [V] = 540' left
set label at 0,38 'U_{GS} [V] = 560' left
set label at 0,38 'U_{GS} [V] = 580' left
set label at 0,38 'U_{GS} [V] = 600' left
unset output 
set terminal qt
unset output
plot "/tmp/tempfile0" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 440' w l,"/tmp/tempfile1" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 460' w l,"/tmp/tempfile2" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 480' w l,"/tmp/tempfile3" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 500' w l,"/tmp/tempfile4" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 520' w l,"/tmp/tempfile5" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 540' w l,"/tmp/tempfile6" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 560' w l,"/tmp/tempfile7" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 580' w l,"/tmp/tempfile8" using ($1*0.004888):($2*0.048876) binary format="%int16%int16" endian=big title 'U_{GS} [V] = 600' w l
